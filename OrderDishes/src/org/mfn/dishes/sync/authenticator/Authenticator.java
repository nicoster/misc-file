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

package org.mfn.dishes.sync.authenticator;

import org.mfn.dishes.Constants;

import android.accounts.AbstractAccountAuthenticator;
import android.accounts.Account;
import android.accounts.AccountAuthenticatorResponse;
import android.accounts.AccountManager;
import android.content.Context;
import android.content.Intent;
import android.os.Bundle;
import android.util.Log;

/**
 * This class is an implementation of AbstractAccountAuthenticator for
 * authenticating accounts in the com.openpeak.cius.sync domain.
 */
class Authenticator extends AbstractAccountAuthenticator {

	private static final String TAG = "Authenticator";

	private final Context mContext;

	public Authenticator(Context context) {
		super(context);
		mContext = context;
	}

	/**
	 * {@inheritDoc}
	 */
	@Override
	public Bundle addAccount(AccountAuthenticatorResponse response,
			String accountType, String authTokenType,
			String[] requiredFeatures, Bundle options) {
		final Intent intent = new Intent(mContext, AuthenticatorActivity.class);
		intent.putExtra(AuthenticatorActivity.PARAM_AUTHTOKEN_TYPE,
				authTokenType);
		intent.putExtra(AccountManager.KEY_ACCOUNT_AUTHENTICATOR_RESPONSE,
				response);
		final Bundle bundle = new Bundle();
		bundle.putParcelable(AccountManager.KEY_INTENT, intent);
		return bundle;
	}

	/**
	 * {@inheritDoc}
	 */
	@Override
	public Bundle confirmCredentials(AccountAuthenticatorResponse response,
			Account account, Bundle options) {

		if (options != null && options.containsKey(AccountManager.KEY_PASSWORD)) {
			final String password = options
					.getString(AccountManager.KEY_PASSWORD);
			final String serverAddress = options
					.getString(Constants.PARAM_SERVER_ADDRESS);
			final String portNumber = options
					.getString(Constants.PARAM_SERVER_PORT);

			final Bundle result = new Bundle();
			return result;
		}
		// Launch AuthenticatorActivity to confirm credentials
		final Intent intent = new Intent(mContext, AuthenticatorActivity.class);
		intent.putExtra(AuthenticatorActivity.PARAM_USERNAME, account.name);

		final AccountManager am = AccountManager.get(mContext);
		intent.putExtra(Constants.PARAM_SERVER_ADDRESS,
				am.getUserData(account, Constants.PARAM_SERVER_ADDRESS));
		intent.putExtra(Constants.PARAM_SERVER_PORT,
				am.getUserData(account, Constants.PARAM_SERVER_PORT));

		intent.putExtra(AuthenticatorActivity.PARAM_CONFIRMCREDENTIALS, true);
		intent.putExtra(AccountManager.KEY_ACCOUNT_AUTHENTICATOR_RESPONSE,
				response);
		final Bundle bundle = new Bundle();
		bundle.putParcelable(AccountManager.KEY_INTENT, intent);
		return bundle;
	}

	/**
	 * {@inheritDoc}
	 */
	@Override
	public Bundle editProperties(AccountAuthenticatorResponse response,
			String accountType) {
		throw new UnsupportedOperationException();
	}

	/**
	 * {@inheritDoc}
	 */
	@Override
	public Bundle getAuthToken(AccountAuthenticatorResponse response,
			Account account, String authTokenType, Bundle loginOptions) {
		Log.i(TAG, "getAuthToken:");

		final Bundle result = new Bundle();
		return result;
	}

	/**
	 * {@inheritDoc}
	 */
	@Override
	public String getAuthTokenLabel(String authTokenType) {
		Log.i(TAG, "getAuthTokenLabel:");

		return null;
	}

	/**
	 * {@inheritDoc}
	 */
	@Override
	public Bundle hasFeatures(AccountAuthenticatorResponse response,
			Account account, String[] features) {
		final Bundle result = new Bundle();
		result.putBoolean(AccountManager.KEY_BOOLEAN_RESULT, false);
		return result;
	}

	/**
	 * {@inheritDoc}
	 */
	@Override
	public Bundle updateCredentials(AccountAuthenticatorResponse response,
			Account account, String authTokenType, Bundle loginOptions) {

		Log.i(TAG, "updateCredentials:");

		final Intent intent = new Intent(mContext, AuthenticatorActivity.class);
		intent.putExtra(AuthenticatorActivity.PARAM_USERNAME, account.name);

		final AccountManager am = AccountManager.get(mContext);
		intent.putExtra(Constants.PARAM_SERVER_ADDRESS,
				am.getUserData(account, Constants.PARAM_SERVER_ADDRESS));
		intent.putExtra(Constants.PARAM_SERVER_PORT,
				am.getUserData(account, Constants.PARAM_SERVER_PORT));
		intent.setAction("android.intent.action.VIEW");
		intent.putExtra("account", account);
		intent.putExtra(AuthenticatorActivity.PARAM_AUTHTOKEN_TYPE,
				authTokenType);
		intent.putExtra(AuthenticatorActivity.PARAM_CONFIRMCREDENTIALS, false);
		final Bundle bundle = new Bundle();
		bundle.putParcelable(AccountManager.KEY_INTENT, intent);
		return bundle;
	}

}
