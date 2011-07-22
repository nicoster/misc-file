package org.mfn.dishes.sync.syncadapter;

import java.io.File;
import java.util.Date;
import java.util.HashMap;
import java.util.Timer;
import java.util.TimerTask;

import org.mfn.dishes.Constants;
import org.mfn.dishes.DishesApp;
import org.mfn.dishes.proto.main.MainClient;
import org.mfn.dishes.sync.authenticator.AuthenticationUtil;
import org.mfn.dishes.sync.authenticator.ImAccount;
import org.mfn.dishes.util.DishesDataAdapter;
import org.mfn.dishes.util.FunctionUtil;
import org.mfn.dishes.vo.DishInfoObj;
import org.mfn.dishes.vo.DishTypeObj;
import org.mfn.dishes.vo.FlavorInfoObj;
import org.mfn.dishes.vo.ImageInfoObj;
import org.mfn.dishes.vo.ServerImageInfoObj;
import org.mfn.dishes.vo.UserInfoObj;

import android.accounts.Account;
import android.accounts.AccountManager;
import android.content.ContentResolver;
import android.content.Context;
import android.os.Bundle;
import android.os.Environment;
import android.provider.ContactsContract;
import android.text.TextUtils;
import android.util.Log;


public class SyncManager {

    private Timer timer;
    
    private static SyncManager syncManager = null;

    private SyncManager() {
        timer = new Timer();
    }
    
    public static SyncManager getInstance(){
        if (syncManager == null){
            syncManager = new SyncManager();
        }
        return syncManager;
    }
    
    public synchronized void doFullSync(final Context context, final String accountName, boolean newThread) {
        
        if (newThread) {
            final Runnable runnable = new Runnable() {
                public void run() {
                	runFullSyncDatas(context, accountName);
                }
            };
            performOnBackgroundThread(runnable);
        } else {
        	runFullSyncDatas(context, accountName);
        }
    }


    @SuppressWarnings("unused")
	private static void sleepWhile() {
        try {
			Thread.sleep(1000 * 60);
        } catch (InterruptedException e) {
        }
    }
    
    private void runFullSyncDatas(Context context, String accountName) {
    	
    	DishesDataAdapter adapter = DishesDataAdapter.getInstance();
    	
		AccountManager mAccountManager = AccountManager.get(context);

		Account[] mAccounts = mAccountManager.getAccountsByType(Constants.ACCOUNT_TYPE);
		if (mAccounts.length == 0) {
			return;
		}

		
		MainClient cli = MainClient.getInstance();
		
		ImAccount imAccount = AuthenticationUtil.getAccountData(context);
		
		cli.init(imAccount.accountName, "pda", imAccount.serverAddress, Integer.parseInt(imAccount.serverPort), null);

		cli.login(imAccount.accountName, imAccount.password);
		
		UserInfoObj[] users = cli.getUserInfo();
		adapter.syncUsersInfo(users);
		
		DishInfoObj[] dishes = cli.getDishInfo();
		adapter.syncDishesInfo(dishes);

		DishTypeObj[] dishtypes = cli.getDishTypeInfo();
		adapter.syncDishTypeInfo(dishtypes);
		
		FlavorInfoObj[] flv = cli.getFlavorInfo();
		adapter.syncFlavorInfo(flv);
		
		ServerImageInfoObj svrImgs[] = cli.getImageInfo();
		
		HashMap<String, ImageInfoObj> dbImgMap = DishesDataAdapter.getInstance().listImageInfo();
		
		String imagePath = getDishesImageDir();
		Log.i(Constants.APP_TAG, "Begin download image to " + imagePath);
		for (int i = 0; i < svrImgs.length; i ++)
		{
			String name = svrImgs[i].name;
			String imgId = FunctionUtil.formatNum(name);
			ImageInfoObj dbImgObj = dbImgMap.get(imgId);
			Log.i(Constants.APP_TAG, "*" + svrImgs[i].name + "\t size=" + svrImgs[i].size + "\t modify_time="
					+ svrImgs[i].modified_time.toLocaleString());
			if (TextUtils.isEmpty(name) || name.equalsIgnoreCase(".") || name.equalsIgnoreCase(".."))
				continue;
			if (isImageUpdated(svrImgs[i], dbImgObj)) {
				cli.downloadImage(name, imagePath);
			}else{
				Log.w(Constants.APP_TAG, "No changed, don't download again...");
			}
		}		
    }
	
	private boolean isImageUpdated(ServerImageInfoObj sObj, ImageInfoObj obj) {
		if (obj == null) {
			return true;
		}

		Date dbModifyTime;
		if (sObj.name.toLowerCase().indexOf("t.bmp") > 0) {
			dbModifyTime = obj.small_modified_time;
		} else {
			dbModifyTime = obj.modified_time;
		}
		return sObj.modified_time.getTime() != dbModifyTime.getTime();
	}
    
	private String getDishesImageDir() {
		File imagePathDir = new File(Constants.DISHES_IMAGE_PATH);
		if (!imagePathDir.exists()) {
			imagePathDir.mkdirs();
		}
		return imagePathDir.getAbsolutePath();
	}
    
    public Thread performOnBackgroundThread(final Runnable runnable) {
        final Thread t = new Thread() {
            @Override
            public void run() {
                try {
                    runnable.run();
                } finally {

                }
            }
        };
        t.start();
        return t;
    }
    
    private void startTimerSync() {
        Account account = getAccount();
        if (account == null) {
            Log.w(Constants.APP_TAG, "Account not exist...");
            return;
        }
        
        if (ContentResolver.getIsSyncable(account, ContactsContract.AUTHORITY) < 1) {
            Log.w(Constants.APP_TAG, "Account not support sync...");
            return;
        }
        
        Log.d(Constants.APP_TAG, "startTimerSync...");
        Bundle bundle = new Bundle();
        ContentResolver.requestSync(account, ContactsContract.AUTHORITY, bundle);
    }

    private Account getAccount() {
        Context mContext = DishesApp.getInstance();
        AccountManager mAccountManager = AccountManager.get(mContext);

        Account[] mAccounts = mAccountManager.getAccountsByType(Constants.ACCOUNT_TYPE);
        if (mAccounts.length == 0) {
            return null;
        }

        return mAccounts[0];
    }
    
    public void requestSync() {
        final Account account = getAccount();
        if (account == null) {
            Log.w(Constants.APP_TAG, "Account not exist...");
            return;
        }

        if (ContentResolver.isSyncActive(account, ContactsContract.AUTHORITY)
                || ContentResolver.getIsSyncable(account, ContactsContract.AUTHORITY) < 1) {
            Log.d(Constants.APP_TAG, "Is in Sync process or not support sync, cancel this Sync Request.");
            return;
        }

        Log.d(Constants.APP_TAG, "requestSync...");
        timer.cancel();
        timer = new Timer();
        timer.schedule(new TimerTask() {
            public void run() {
                startTimerSync();
            }
        }, 10000);
    }
  

}
