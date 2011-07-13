
package org.mfn.dishes.sync.authenticator;


import org.mfn.dishes.sync.syncadapter.SyncAdapter;

import android.app.Service;
import android.content.Intent;
import android.os.IBinder;
import android.util.Log;


public class AuthenticationService extends Service {
    private static final String TAG = "AuthenticationService";

    private Authenticator mAuthenticator;

    @Override
    public void onCreate() {
        Log.v(SyncAdapter.TAG, "Authentication Service started.");
        mAuthenticator = new Authenticator(this);
    }

    @Override
    public void onDestroy() {
        Log.v(SyncAdapter.TAG, "Authentication Service stopped.");
    }

    @Override
    public IBinder onBind(Intent intent) {
        Log.v(SyncAdapter.TAG, "getBinder()...  returning the AccountAuthenticator binder for intent " + intent);
        return mAuthenticator.getIBinder();
    }
}
