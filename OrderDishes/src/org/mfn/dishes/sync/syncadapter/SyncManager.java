package org.mfn.dishes.sync.syncadapter;

import java.io.File;
import java.util.ArrayList;
import java.util.Date;
import java.util.HashMap;
import java.util.Timer;
import java.util.TimerTask;

import org.mfn.dishes.Constants;
import org.mfn.dishes.DishesApp;
import org.mfn.dishes.proto.main.MainClient;
import org.mfn.dishes.sync.authenticator.AuthenticationUtil;
import org.mfn.dishes.sync.authenticator.ImAccount;
import org.mfn.dishes.util.FunctionUtil;
import org.mfn.dishes.vo.DishCategoryInfo;
import org.mfn.dishes.vo.DishInfo;
import org.mfn.dishes.vo.FlavorInfo;
import org.mfn.dishes.vo.ImageInfo;
import org.mfn.dishes.vo.ServerImageInfo;
import org.mfn.dishes.vo.UserInfo;

import android.accounts.Account;
import android.accounts.AccountManager;
import android.content.ContentResolver;
import android.content.Context;
import android.os.Bundle;
import android.provider.ContactsContract;
import android.text.TextUtils;
import android.util.Log;


public class SyncManager {
    private Timer timer;
    
    private static SyncManager syncManager = null;
    private SyncDBOperator syncDBOperator = null;
    
    private SyncManager() {
        timer = new Timer();
        syncDBOperator = SyncDBOperator.getInstance();
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
		AccountManager mAccountManager = AccountManager.get(context);

		Account[] mAccounts = mAccountManager.getAccountsByType(Constants.ACCOUNT_TYPE);
		if (mAccounts.length == 0) {
			return;
		}

		
		MainClient mainClient = MainClient.getInstance();
		
		ImAccount imAccount = AuthenticationUtil.getAccountData(context);
		
		mainClient.init(imAccount.accountName, "pda", imAccount.serverAddress, Integer.parseInt(imAccount.serverPort), null);

		mainClient.login(imAccount.accountName, imAccount.password);
		
		UserInfo[] userInfos = mainClient.getUserInfos();
		syncDBOperator.saveUserInfo(userInfos);
		
		FlavorInfo[] flavorInfos = mainClient.getFlavorInfos();
		syncDBOperator.saveFlavorInfo(flavorInfos);
		
		DishCategoryInfo[] dishCategoryInfos = mainClient.getDishCategoryInfos();
		syncDBOperator.saveDishCategoryInfo(dishCategoryInfos);

		DishInfo[] dishInfos = mainClient.getDishInfos();
		syncDBOperator.saveDishInfo(dishInfos);		
		
		syncImagesDatas(mainClient);
    }
	
    /**
     * sync image datas
     * @param cli
     */
	private void syncImagesDatas(MainClient cli) {
		ServerImageInfo[] svrImgs = cli.getImageInfo();
		if (svrImgs == null || svrImgs.length == 0) {
			Log.e(Constants.APP_TAG, "syncImagesDatas error, data is null");
			return;
		}

		HashMap<String, ImageInfo> dbImgMap = syncDBOperator.getImageInfos();

		String imagePath = getDishesImageDir();
		Log.i(Constants.APP_TAG, "Begin download image to " + imagePath);
		
		ArrayList<ServerImageInfo> validlist = new ArrayList<ServerImageInfo>();
		boolean imgChangeFlag = false;
		
		for (int i = 0; i < svrImgs.length; i++) {

			String name = svrImgs[i].getName();
			if (TextUtils.isEmpty(name) || name.equalsIgnoreCase(".") || name.equalsIgnoreCase("..") || !FunctionUtil.isImageFile(name)){
				continue;
			}				

			validlist.add(svrImgs[i]);
//			String imgId = FunctionUtil.formatDishId(name);
//
//			ImageInfo dbImg = dbImgMap.get(imgId);
//
//			String fullImgPath = imagePath + name;
//			if (isImageUpdated(svrImgs[i], dbImg) || !imageExist(fullImgPath)) {
//				Log.w(Constants.APP_TAG, "Download..." + fullImgPath);
//				cli.downloadImage(name, imagePath);
//				imgChangeFlag = true;
//			} else {
//				Log.w(Constants.APP_TAG, "No changed, don't download again...");
//			}
		}
		imgChangeFlag = true;
		if (imgChangeFlag) {
			syncDBOperator.saveImageInfo((ServerImageInfo[]) validlist.toArray(new ServerImageInfo[0]));
		}
	}
    
	/**
	 * check whether image exist
	 * @param fullImgPath
	 * @return
	 */
	private boolean imageExist(String fullImgPath) {
		File file = new File(fullImgPath);
		boolean exist = file.exists();
		if (!exist) {
			Log.w(Constants.APP_TAG, fullImgPath + " is not exist............");
		}

		return exist;
	}
    
	/**
	 * check whether image has updated
	 * @param serverImageInfo
	 * @param imageInfo
	 * @return
	 */
	private boolean isImageUpdated(ServerImageInfo serverImageInfo, ImageInfo imageInfo) {
		if (imageInfo == null || serverImageInfo == null || serverImageInfo.getModified_time() == null) {
			return true;
		}

		Date dbModifyTime;
		String dbImgName;
		if(FunctionUtil.isVideo(serverImageInfo.getName())){
			dbModifyTime = imageInfo.getVideoModifiedTime();
			dbImgName = imageInfo.getVideoName();
		}else if (FunctionUtil.isSmallImage(serverImageInfo.getName())) {
			dbModifyTime = imageInfo.getSmallImageModifyTime();
			dbImgName = imageInfo.getSmallImageName();
		} else {
			dbModifyTime = imageInfo.getImageModifyTime();
			dbImgName = imageInfo.getImageName();
		}
		
		if (dbModifyTime == null) {
			return true;
		}

		Log.i(Constants.APP_TAG, "Server:name" + serverImageInfo.getName() + "\t modify_time=" + serverImageInfo.getModified_time().getTime());
		Log.i(Constants.APP_TAG, "Local::id=" + imageInfo.getId() + " name" + dbImgName +"\t modify_time=" + dbModifyTime.getTime());
		
		return serverImageInfo.getModified_time().getTime() != dbModifyTime.getTime();
	}
    
	/**
	 * get image dir
	 * @return
	 */
	private String getDishesImageDir() {
		File imagePathDir = new File(Constants.DISHES_IMAGE_PATH);
		if (!imagePathDir.exists()) {
			imagePathDir.mkdirs();
		}
		return Constants.DISHES_IMAGE_PATH;
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
