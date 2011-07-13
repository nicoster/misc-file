package org.mfn.dishes.sync.syncadapter;

import java.util.Timer;
import java.util.TimerTask;

import org.mfn.dishes.DishesApp;

import android.accounts.Account;
import android.accounts.AccountManager;
import android.content.ContentResolver;
import android.content.Context;
import android.os.Bundle;
import android.os.RemoteException;
import android.os.SystemClock;
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
                    runFullSyncBuddies(context, accountName);
                }
            };
            performOnBackgroundThread(runnable);
        } else {
            runFullSyncBuddies(context, accountName);
        }
    }


    private static void sleepWhile() {
        try {
            Thread.currentThread().sleep(1000 * 60);
        } catch (InterruptedException e) {
        }
    }
    
    private void runFullSyncBuddies(Context context, String accountName) {

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
