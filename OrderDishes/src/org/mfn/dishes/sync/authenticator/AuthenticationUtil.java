package org.mfn.dishes.sync.authenticator;

import org.mfn.dishes.Constants;

import android.accounts.Account;
import android.accounts.AccountManager;
import android.content.ContentProviderClient;
import android.content.ContentResolver;
import android.content.ContentValues;
import android.content.Context;
import android.database.Cursor;
import android.net.Uri;
import android.os.Bundle;
import android.os.RemoteException;
import android.provider.ContactsContract;
import android.provider.ContactsContract.Settings;
import android.util.Log;

public class AuthenticationUtil {

	public static String TAG = "AuthenticationUtil";

	private static final int CONTACTS_VISIBILITY_NOT_FOUND = -1;
	private static final int CONTACTS_VISIBILITY_VISIBLE = 1;
	private static final int CONTACTS_VISIBILITY_HIDDEN = 0;

	public static ImAccount mAccount;

	public synchronized static void saveNewAccount(Context context) {

		if (mAccount == null) {
			Log.e(TAG, "saveNewAccount: mAccount is empty!");
			return;
		}

		AccountManager mAccountManager = AccountManager.get(context);

		Account[] mAccounts = mAccountManager.getAccountsByType(Constants.ACCOUNT_TYPE);
		if (mAccounts.length > 0) {
			Log.i(TAG, "saveNewAccount: account exist:" + mAccount.accountName);
			return;
		}
		final Account account = new Account(mAccount.accountName, Constants.ACCOUNT_TYPE);

		Bundle userData = new Bundle();
		userData.putString(Constants.PARAM_SERVER_ADDRESS, mAccount.serverAddress);
		userData.putString(Constants.PARAM_SERVER_PORT, mAccount.serverPort);
		mAccountManager.addAccountExplicitly(account, mAccount.password, userData);

		handleSyncContacts(account, context.getContentResolver(), mAccount);
	}

	public static ImAccount getAccountData(Context context) {
		AccountManager mAccountManager = AccountManager.get(context);

		Account[] mAccounts = mAccountManager.getAccountsByType(Constants.ACCOUNT_TYPE);
		if (mAccounts.length > 0) {
			ImAccount imAccount = new ImAccount();
			
			imAccount.accountName = mAccounts[0].name;
			imAccount.password = mAccountManager.getPassword(mAccounts[0]);
			imAccount.serverAddress = mAccountManager.getUserData(mAccounts[0], Constants.PARAM_SERVER_ADDRESS);
			
			return imAccount;
		}
		return null;
	}

	public static void setAccountData(ImAccount mAccount) {
		AuthenticationUtil.mAccount = mAccount;
	}

	public synchronized static void saveEditAccount(Context context, Account account) {
		if (mAccount == null) {
			Log.e(TAG, "saveEditAccount: mAccount is empty!");
			return;
		}

		AccountManager mAccountManager = AccountManager.get(context);

		mAccountManager.setPassword(account, mAccount.password);
		mAccountManager.setUserData(account, Constants.PARAM_SERVER_ADDRESS, mAccount.serverAddress);
		mAccountManager.setUserData(account, Constants.PARAM_SERVER_PORT, mAccount.serverPort);

		handleSyncContacts(account, context.getContentResolver(), mAccount);

	}

	private static void handleSyncContacts(final Account account, ContentResolver resolver, ImAccount mAccount) {
		Log.i(TAG, "handleSyncContacts:");
		ContentResolver.setSyncAutomatically(account, ContactsContract.AUTHORITY, mAccount.syncContacts);
		final Bundle bundle = new Bundle();
		if (mAccount.syncContacts) {
			ContentResolver.addPeriodicSync(account, ContactsContract.AUTHORITY, bundle,
					Constants.SYNC_CONTACTS_POLL_FREQUENCY);
		} else {
			resolver.cancelSync(account, ContactsContract.AUTHORITY);
			ContentResolver.removePeriodicSync(account, ContactsContract.AUTHORITY, bundle);
		}
		ContentResolver.setIsSyncable(account, ContactsContract.AUTHORITY, mAccount.syncContacts ? 1 : 0);
		final int contactsVisibility = getContactsVisibility(resolver, account.name, account.type);
		if ((contactsVisibility == CONTACTS_VISIBILITY_NOT_FOUND)
				|| ((contactsVisibility == CONTACTS_VISIBILITY_VISIBLE) && !mAccount.syncContacts)
				|| ((contactsVisibility == CONTACTS_VISIBILITY_HIDDEN) && mAccount.syncContacts)) {
			final ContentProviderClient client = resolver.acquireContentProviderClient(ContactsContract.AUTHORITY_URI);
			final ContentValues cv = new ContentValues();
			cv.put(Settings.ACCOUNT_NAME, account.name);
			cv.put(Settings.ACCOUNT_TYPE, account.type);
			cv.put(Settings.UNGROUPED_VISIBLE, mAccount.syncContacts);
			try {
				client.insert(
						Settings.CONTENT_URI.buildUpon()
								.appendQueryParameter(ContactsContract.CALLER_IS_SYNCADAPTER, "true").build(), cv);
			} catch (RemoteException re) {
				Log.i(TAG, "handleSyncContacts remote exception" + re, re);
			}
			client.release();
		}
	}

	private static int getContactsVisibility(final ContentResolver resolver, final String accountName,
			final String accountType) {
		final Uri settingsUri = Settings.CONTENT_URI.buildUpon()
				.appendQueryParameter(Settings.ACCOUNT_NAME, accountName)
				.appendQueryParameter(Settings.ACCOUNT_TYPE, accountType).build();
		final Cursor cursor = resolver.query(settingsUri, new String[]{Settings.UNGROUPED_VISIBLE}, null, null, null);
		int contactsVisibility = CONTACTS_VISIBILITY_NOT_FOUND;
		if (cursor != null && cursor.moveToFirst()) {
			contactsVisibility = cursor.getInt(0);
		}
		cursor.close();
		return contactsVisibility;
	}
}
