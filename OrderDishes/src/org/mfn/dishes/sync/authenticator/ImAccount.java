package org.mfn.dishes.sync.authenticator;

import org.mfn.dishes.Constants;

import android.accounts.Account;
import android.accounts.AccountManager;


public class ImAccount {

    public String accountName;
    public String password;
    public String serverAddress;
    public String serverPort = "5222";

    public boolean syncContacts = true;

    public ImAccount() {

    }

    public ImAccount(Account account, AccountManager mAccountManager) {
        accountName = account.name;
        password = mAccountManager.getPassword(account);
        serverAddress = mAccountManager.getUserData(account, Constants.PARAM_SERVER_ADDRESS);
        serverPort = mAccountManager.getUserData(account, Constants.PARAM_SERVER_PORT);
    }

    public String toString() {
        StringBuffer sb = new StringBuffer();
        sb.append("\taccountName=" + accountName);
        sb.append("\tserverAddress=" + serverAddress);
        sb.append("\tserverPort=" + serverPort);
        sb.append("\tsyncContacts=" + syncContacts);
        return sb.toString();
    }
}
