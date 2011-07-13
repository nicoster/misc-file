/* Copyright (C) 2009-2010 OpenPeak Inc.
 * All rights reserved.
 *
 * This file contains confidential information of
 * OpenPeak Inc. Unauthorized reproduction or
 * distribution of this file is subject to civil
 * and criminal penalties.
 *
 * http://www.openpeak.com
 * email: info@openpeak.com
 */

package org.mfn.dishes.sync.platform;

import android.content.ContentProviderOperation;
import android.content.ContentResolver;
import android.content.Context;
import android.content.OperationApplicationException;
import android.database.sqlite.SQLiteException;
import android.os.RemoteException;
import android.provider.ContactsContract;
import android.util.Log;


import java.util.ArrayList;

import org.mfn.dishes.sync.syncadapter.SyncAdapter;



/**
 * This class handles execution of batch mOperations on Contacts provider.
 */
public class BatchOperation {
    private static final String TAG = "BatchOperation";

    private final ContentResolver mResolver;

    // List for storing the batch mOperations
    ArrayList<ContentProviderOperation> mOperations;

    public BatchOperation(Context context, ContentResolver resolver) {
        mResolver = resolver;
        mOperations = new ArrayList<ContentProviderOperation>();
    }

    public int size() {
        return mOperations.size();
    }

    public void add(ContentProviderOperation cpo) {
        mOperations.add(cpo);
    }

    public int execute() {
    	int retu = 0;
        if (mOperations.size() == 0) {
            return retu;
        }
        // Apply the mOperations to the content provider
        try {
            mResolver.applyBatch(ContactsContract.AUTHORITY, mOperations);
            retu = 1;
        } catch (final OperationApplicationException e1) {
            Log.e(SyncAdapter.TAG, TAG + ": " + "storing contact data failed", e1);
            retu = -1;
        } catch (final RemoteException e2) {
            Log.e(SyncAdapter.TAG, TAG + ": " + "storing contact data failed", e2);
            retu = -1;
        } catch (SQLiteException se) {
            Log.e(SyncAdapter.TAG, TAG + ": " + "storing contact data failed", se);
            retu = -1;
        } catch (Exception e){
        	Log.e(SyncAdapter.TAG, TAG + ": " + "storing contact data failed", e);
            retu = -1;
        }
        mOperations.clear();
        return retu;
    }

}
