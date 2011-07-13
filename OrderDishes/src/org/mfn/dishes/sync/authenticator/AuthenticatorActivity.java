package org.mfn.dishes.sync.authenticator;

import java.util.regex.Pattern;

import org.mfn.dishes.Constants;
import org.mfn.dishes.R;

import android.accounts.Account;
import android.accounts.AccountAuthenticatorActivity;
import android.accounts.AccountManager;
import android.app.Activity;
import android.app.AlertDialog;
import android.app.Dialog;
import android.app.ProgressDialog;
import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.content.SharedPreferences;
import android.net.ConnectivityManager;
import android.net.NetworkInfo;
import android.os.Bundle;
import android.os.Handler;
import android.text.TextUtils;
import android.util.Log;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.Window;
import android.view.inputmethod.EditorInfo;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;

public class AuthenticatorActivity extends AccountAuthenticatorActivity {

	public static final String PARAM_CONFIRMCREDENTIALS = "confirmCredentials";

	public static final String PARAM_USERNAME = "username";

	public static final String PARAM_PASSWORD = "password";

	public static final String PARAM_AUTHTOKEN_TYPE = "authtokenType";

	private static final String TAG = "AuthenticatorActivity";

	private ConnectivityManager cManager;
	
	private AccountManager mAccountManager;

	ProgressDialog dialog;

	/** for posting authentication attempts back to UI thread */
	private final Handler mHandler = new Handler();

	private TextView mMessage;
	private EditText mPasswordEdit;
	private TextView mPasswordLabel;
	private EditText mUsernameEdit;
	private TextView mServerAddressLabel;
	private EditText mServerAddressEdit;
	private Button mBtnSave;
	private Button mBtnCancel;

	protected ArrayAdapter<CharSequence> mAdapter;

	private ImAccount mAccount = new ImAccount();

	private boolean isEditAccount;

	private SharedPreferences settings;

	private static boolean isInprogress;

	@Override
	public void onCreate(Bundle icicle) {
		super.onCreate(icicle);

		settings = getPreferences(Activity.MODE_PRIVATE);

		initViewElements();

	}

	public void onStart() {
		super.onStart();
	}

	private void initViewElements() {
		mAccountManager = AccountManager.get(this);
		
		cManager = (ConnectivityManager) getSystemService(Context.CONNECTIVITY_SERVICE);
		
		requestWindowFeature(Window.FEATURE_LEFT_ICON);
		setContentView(R.layout.login_activity);

		getWindow().setFeatureDrawableResource(Window.FEATURE_LEFT_ICON, android.R.drawable.ic_dialog_alert);

		mMessage = (TextView) findViewById(R.id.message);
		mUsernameEdit = (EditText) findViewById(R.id.username_edit);
		mPasswordEdit = (EditText) findViewById(R.id.password_edit);
		mPasswordLabel = (TextView) findViewById(R.id.password_label);
		mServerAddressLabel = (TextView) findViewById(R.id.server_address_label);
		mServerAddressEdit = (EditText) findViewById(R.id.server_address_edit);
		mMessage = (TextView) findViewById(R.id.message);
		mBtnSave = (Button) findViewById(R.id.save_button);

		// For Obfuscate
		mBtnSave.setOnClickListener(new OnClickListener() {
			public void onClick(View v) {
				handleSave(v);
			}
		});

		mBtnCancel = (Button) findViewById(R.id.cancel_button);
		mBtnCancel.setOnClickListener(new OnClickListener() {
			public void onClick(View v) {
				handleCancel(v);
			}
		});
	}

	public void createOrUpdateAccount() {
		final Intent intent = getIntent();
		Account[] mAccounts = mAccountManager.getAccountsByType(Constants.ACCOUNT_TYPE);

		// If in UCM Login Type has been changed, current account will be
		// unused.
		boolean unUsedAccount = false;
		if (mAccounts.length > 0) {
			Account account = mAccounts[0];
		}

		if ("android.intent.action.VIEW".equals(intent.getAction()) || unUsedAccount) {
			Account account = (Account) getIntent().getParcelableExtra("account");
			if (unUsedAccount) {
				account = mAccounts[0];
			}
			ImAccount existAccount = new ImAccount(account, mAccountManager);
			Log.i(TAG, "Click Exist Account, Prepare edit current Account:" + existAccount.toString());
			// Edit account setting

			if (account != null) {
				Log.i(TAG, "Account exists, Edit current Account:" + existAccount.toString());

				updateAccount(existAccount, account);

			}
		} else {
			// Add new account
			if (mAccounts.length > 0) {
				Log.e(TAG, "Number of accounts is " + mAccounts.length);
				showToast(R.string.multiple_accounts_toast);
				finish();
			} else {
				// this.displayView(propAdapter.getCiusLoginType());
			}
		}
	}

	private void updateAccount(ImAccount existAccount, Account account) {

	}

	void showToast(CharSequence msg) {
		Toast.makeText(this, msg, Toast.LENGTH_LONG).show();
	}

	public void showToast(int id) {
		Toast.makeText(this, id, Toast.LENGTH_LONG).show();
	}

	private void setReadOnly(EditText eText, boolean readOnly) {
		if (readOnly) {
			eText.setEnabled(false);
		} else {
			eText.setEnabled(true);
		}
	}

	public void displayView(int type) {
		Log.i(TAG, "=displayView, loginType=" + type);

		showWindowByLoginType(type);
	}

	private void showWindowByLoginType(int type) {

		mUsernameEdit.setImeOptions(EditorInfo.IME_ACTION_NEXT);
		mPasswordEdit.setImeOptions(EditorInfo.IME_ACTION_NEXT);
		mServerAddressEdit.setImeOptions(EditorInfo.IME_ACTION_DONE);

		mMessage.setText("");

	}

	@Override
	protected void onDestroy() {
		Log.d(TAG, "onDestroy()...");

		super.onDestroy();
	}

	protected void onStop() {
		super.onStop();
	}

	private ProgressDialog getProgressDialog(CharSequence msg) {
		ProgressDialog pDialog = new ProgressDialog(this);
		pDialog.setMessage(msg);
		pDialog.setIndeterminate(true);
		pDialog.setCancelable(false);
		pDialog.setOnCancelListener(new DialogInterface.OnCancelListener() {

			public void onCancel(DialogInterface dialog) {
				// TODO Auto-generated method stub

			}
		});
		return pDialog;
	}

	protected void onPrepareDialog(int id, Dialog dialog) {
		switch (id) {
			case 0 :
				dialog.setOnDismissListener(new DialogInterface.OnDismissListener() {
					public void onDismiss(DialogInterface dialog) {
						removeDialog(0);
					}
				});
		}
	}

	protected Dialog onCreateDialog(int id) {

		return null;
	}

	/**
	 * Handles onClick event on the Save button.
	 * 
	 * @param view
	 *            The Save button for which this method is invoked
	 */
	public void handleSave(View view) {
		NetworkInfo activeNetwork = cManager.getActiveNetworkInfo();

        if (activeNetwork != null && activeNetwork.isConnected()) {
        	 mAccount.accountName = mUsernameEdit.getText().toString();
             mAccount.password = mPasswordEdit.getText().toString();
             mAccount.serverAddress = mServerAddressEdit.getText().toString();
             AuthenticationUtil.setAccountData(mAccount);

             if (emptyFieldsCheck()) {
                 showRequiredFieldsDialog();
             } else {
            	 AuthenticationUtil.saveNewAccount(this);
            	 
            	 finish();
             }
        }else {
            if (!isFinishing())
                showNoNetworkAvailableDialog();
        }
	}

    private void showNoNetworkAvailableDialog() {
        new AlertDialog.Builder(this).setTitle(R.string.dialog_no_network_title).setCancelable(true).setMessage(
                R.string.dialog_no_network_message).setIcon(android.R.drawable.ic_dialog_alert).setPositiveButton(
                R.string.ok_button_label, null).show();
    }

    private void showRequiredFieldsDialog() {
        int titleId = R.string.missing_fields_title;
        int msgId = R.string.login_activity_loginfail_missing_fields;
        new AlertDialog.Builder(this).setTitle(titleId).setCancelable(true).setMessage(msgId)
                .setIcon(android.R.drawable.ic_dialog_alert).setPositiveButton(R.string.ok_button_label, null).show();
    }
    
	private boolean emptyFieldsCheck() {

		boolean isEmpty = true;

		isEmpty = TextUtils.isEmpty(mAccount.accountName) || TextUtils.isEmpty(mAccount.password)
				|| TextUtils.isEmpty(mAccount.serverAddress);

		return isEmpty;
	}

	public void handleCancel(View view) {
		this.finish();
	}

	/**
	 * 
	 * Called when response is received from the server for authentication
	 * request. See onAuthenticationResult(). Sets the
	 * AccountAuthenticatorResult which is sent back to the caller. Also sets
	 * the authToken in AccountManager for this account.
	 * 
	 * @param the
	 *            confirmCredentials result.
	 */

	protected void finishLogin() {
		Log.d(TAG, "finishLogin():" + mAccount.toString());
		final Account account = new Account(mAccount.accountName, Constants.ACCOUNT_TYPE);

		if (isEditAccount) {
			AuthenticationUtil.saveEditAccount(this, account);
		} else {

			AuthenticationUtil.saveNewAccount(this);

		}

		final Intent intent = new Intent();

		intent.putExtra(AccountManager.KEY_ACCOUNT_NAME, mAccount.accountName);
		intent.putExtra(AccountManager.KEY_ACCOUNT_TYPE, Constants.ACCOUNT_TYPE);
		intent.putExtra(Constants.PARAM_SERVER_ADDRESS, mAccount.serverAddress);
		intent.putExtra(Constants.PARAM_SERVER_PORT, mAccount.serverPort);

		finish();
	}

	/**
	 * Called when the authentication process completes (see attemptLogin()).
	 */
	public void onAuthenticationResult(boolean result, int resourceId) {
		Log.i(TAG, "onAuthenticationResult:" + result + " resourceId:" + resourceId);
		// Hide the progress dialog
		hideProgress(true);
		if (result) {
			finishLogin();
		} else {
			Log.e(TAG, "onAuthenticationResult: failed to authenticate");

			if (!isFinishing()) {
				// showInvalidPasswordDialog(resourceId);
			}
		}
	}

	/**
	 * Returns the message to be displayed at the top of the login dialog box.
	 */
	private CharSequence getMessage() {
		getString(R.string.app_name);
		if (TextUtils.isEmpty(mAccount.accountName)) {
			// If no username, then we ask the user to log in using an
			// appropriate service.
			final CharSequence msg = getText(R.string.login_activity_newaccount_text);
			return msg;
		}
		if (TextUtils.isEmpty(mAccount.password)) {
			// We have an account but no password
			return getText(R.string.login_activity_loginfail_text_pwmissing);
		}
		return null;
	}

	public static boolean validateUserName(ImAccount mAccount) {

		Pattern userNamePattern = Pattern
				.compile("^[a-z0-9!#$%&'*+/=?^_`{|}~-]+(?:\\.[a-z0-9!#$%&'*+/=?^_`{|}~-]+)*@(?:[a-z0-9](?:[a-z0-9-]*[a-z0-9])?\\.)+[a-z0-9](?:[a-z0-9-]*[a-z0-9])?$");

		if (!userNamePattern.matcher(mAccount.accountName).matches()) {
			return false;
		}

		return true;
	}

	/**
	 * Hides the progress UI for a lengthy operation.
	 */
	protected void hideProgress(boolean signon) {

	}

	/**
	 * Shows the progress UI for a lengthy operation.
	 */
	protected void showProgress(boolean signon) {

	}

}
