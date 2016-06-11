package com.hieunv.app.security;

import com.google.android.gms.auth.api.signin.GoogleSignInAccount;

/**
 * Created by HieuNV on 6/11/2016.
 */
public class AccountContext {

    private static final AccountContext instance = new AccountContext();

    private GoogleSignInAccount googleSignInAccount;

    private AccountContext() {

    }

    public static AccountContext getInstance() {
        return instance;
    }

    public boolean isGoogleAccount() {
        return googleSignInAccount != null;
    }

    public GoogleSignInAccount getGoogleSignInAccount() {
        return googleSignInAccount;
    }

    public void setGoogleSignInAccount(GoogleSignInAccount googleSignInAccount) {
        this.googleSignInAccount = googleSignInAccount;
    }
}
