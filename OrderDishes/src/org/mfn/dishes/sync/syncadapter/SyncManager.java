package org.mfn.dishes.sync.syncadapter;

import java.util.Timer;
import java.util.TimerTask;

import org.mfn.dishes.DishesApp;
import org.mfn.dishes.util.DishesDataAdapter;
import org.mfn.dishes.vo.DishObj;
import org.mfn.dishes.vo.UserInfoObj;

import android.accounts.Account;
import android.accounts.AccountManager;
import android.content.ContentResolver;
import android.content.Context;
import android.os.Bundle;
import android.provider.ContactsContract;
import android.provider.SyncStateContract.Constants;
import android.util.Log;


public class SyncManager {

    public static final String TAG = "SyncManager";

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
    	
		UserInfoObj[] objs = new UserInfoObj[10];
		for (int i = 0; i < 10; i++) {
			objs[i] = new UserInfoObj();
			objs[i].id = Integer.toString(i);
			objs[i].name = "Frey " + "Wang" + i;
			objs[i].level = Integer.toString(i % 3);
		}
		adapter.syncUsersInfo(objs);
    	
		DishObj[] dobjs = new DishObj[10];
    	for (int i=0;i<10;i++){
    		dobjs[i] = new DishObj();
			dobjs[i].id = Integer.toString(i);
			dobjs[i].query_code = "QWE:"+i;
			dobjs[i].query_code2 = "QWEWE:"+i;
			dobjs[i].name = "红烧肉" + i;
			dobjs[i].size = Integer.toString(i);
			dobjs[i].unit = "QWEWE:"+i;
			dobjs[i].price = 3.1f*i;
			dobjs[i].type = Integer.toString(i);
			dobjs[i].variable_price = i%2 ==0;
//			dobjs[i].cook_style="COOK:"+i;
			dobjs[i].flag =i;
			dobjs[i].cost = 2.2f*i;
			dobjs[i].image=i+"diadiaodiaoudaio.bmp";
    	}
    	adapter.syncDishesInfo(dobjs);
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
            Log.w(TAG, "Account not exist...");
            return;
        }
        
        if (ContentResolver.getIsSyncable(account, ContactsContract.AUTHORITY) < 1) {
            Log.w(TAG, "Account not support sync...");
            return;
        }
        
        Log.d(TAG, "startTimerSync...");
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
            Log.w(TAG, "Account not exist...");
            return;
        }

        if (ContentResolver.isSyncActive(account, ContactsContract.AUTHORITY)
                || ContentResolver.getIsSyncable(account, ContactsContract.AUTHORITY) < 1) {
            Log.d(TAG, "Is in Sync process or not support sync, cancel this Sync Request.");
            return;
        }

        Log.d(TAG, "requestSync...");
        timer.cancel();
        timer = new Timer();
        timer.schedule(new TimerTask() {
            public void run() {
                startTimerSync();
            }
        }, 10000);
    }
  

}
