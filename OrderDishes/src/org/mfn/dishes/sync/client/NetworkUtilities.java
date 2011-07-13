package org.mfn.dishes.sync.client;

import android.content.Context;
import android.os.Handler;
import android.os.RemoteException;
import android.util.Log;

public class NetworkUtilities {
	private static final String TAG = "NetworkUtilities";

	public static Context mContext;
	public static Handler mHandler;

	/**
	 * Executes the network requests on a separate thread.
	 * 
	 * @param runnable
	 *            The runnable instance containing network mOperations to be
	 *            executed.
	 */
	public static Thread performOnBackgroundThread(final Runnable runnable) {
		final Thread t = new Thread() {
			@Override
			public void run() {
				try {
					runnable.run();
				} finally {

				}
			}
		};
		try {
			t.sleep(500);
		} catch (InterruptedException e) {
			e.printStackTrace();
			Log.e(TAG, "performOnBackgroundThread() failed, msg:  " + e.toString());
		}
		t.start();
		return t;
	}

	/**
	 * Connects to the Voiper server, authenticates the provided username and
	 * password.
	 * 
	 * @param username
	 *            The user's username
	 * @param password
	 *            The user's password
	 * @param handler
	 *            The hander instance from the calling UI thread.
	 * @param context
	 *            The context of the calling Activity.
	 * @return boolean The boolean result indicating whether the user was
	 *         successfully authenticated.
	 */
	public static void authenticate(String username, String password, String serverAddress, String portNumber) {

	}

	/**
	 * Attempts to authenticate the user credentials on the server.
	 * 
	 * @param username
	 *            The user's username
	 * @param password
	 *            The user's password to be authenticated
	 * @param mLoginType
	 *            CLOUD, SSO .etc
	 * @param handler
	 *            The main UI thread's handler instance.
	 * @param context
	 *            The caller Activity's context
	 * @return Thread The thread on which the network mOperations are executed.
	 */
	public static Thread attemptAuth(final String mUsername, final String mPassword, final String mServerAddress,
			final String mServerPort, final Handler handler, final Context context) {

		mContext = context;
		mHandler = handler;

		final Runnable runnable = new Runnable() {
			public void run() {
				// authenticate(mUsername, mPassword, mServerAddress,
				// mServerPort, mLoginType);
			}
		};
		// run on background thread.
		return NetworkUtilities.performOnBackgroundThread(runnable);
	}

}
