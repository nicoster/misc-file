/* Copyright (C) 2009-2010 OpenPeak Inc.
 * All rights reserved.
 *
 * This file contains confidential information of
 * OpenPeak Inc. Unauthorized reproduction or
 * distribution of this file is subject to civil
 * and criminal penalties.
 *
 */

package org.mfn.dishes.sync.syncadapter;

import android.accounts.Account;
import android.content.AbstractThreadedSyncAdapter;
import android.content.ContentProviderClient;
import android.content.Context;
import android.content.SyncResult;
import android.os.Bundle;
import android.util.Log;


/**
 * SyncAdapter implementation for syncing sample SyncAdapter contacts to the
 * platform ContactOperations provider.
 */
public class SyncAdapter extends AbstractThreadedSyncAdapter {

    private Context mContext;

    public SyncAdapter(Context context, boolean autoInitialize) {
        super(context, autoInitialize);
        mContext = context;
    }

    // DO NOT CHANGE
    public static final String TAG = "SyncAdapter";

    @Override
    public void onPerformSync(Account account, Bundle extras, String authority, ContentProviderClient provider,
            SyncResult syncResult) {
        Log.d(TAG, "onPerformSync:" + account.name);
        SyncManager.getInstance().doFullSync(mContext, account.name, false);
    }

}
