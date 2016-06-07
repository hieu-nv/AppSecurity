package com.hieunv.app.security;

import android.content.Context;

/**
 * Created by HieuNV on 6/7/2016.
 */
public class Security {
    static {
        System.loadLibrary("AppSecurity");
    }
    public static native String getSalt(Context context);
}
