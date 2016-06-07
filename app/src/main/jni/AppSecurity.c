#include <jni.h>
#include <string.h>
#include <stdio.h>
#include <android/log.h>

#define TAG "com.hieunv.app.security.Security"

//#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG,TAG ,__VA_ARGS__)
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, TAG, __VA_ARGS__)
//#define LOGW(...) __android_log_print(ANDROID_LOG_WARN,TAG ,__VA_ARGS__)
//#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR,TAG ,__VA_ARGS__)
//#define LOGF(...) __android_log_print(ANDROID_LOG_FATAL,TAG ,__VA_ARGS__)

#define EMPTY_STRING ""
#define NOT_EXPECTED_DEVICE_ID "000000000000000"
#define NOT_EXPECTED_SERIAL_NO ""

#define PACKAGE_NAME "com.hieunv.app.security"




jstring getPackageName(JNIEnv *env, jobject context) {
    jclass contextClass = (*env)->GetObjectClass(env, context);
    jmethodID getPackageName = (*env)->GetMethodID(env, contextClass, "getPackageName", "()Ljava/lang/String;");
    jobject packageName = (*env)->CallObjectMethod(env, context, getPackageName);
    return (jstring) packageName;
}

jstring getSerialNo(JNIEnv *env) {
    jclass systemPropertiesClass = (*env)->FindClass(env, "android/os/SystemProperties");
    if (systemPropertiesClass == 0) {
        return (*env)->NewStringUTF(env, "");
    }

    jmethodID get = (*env)->GetStaticMethodID(env, systemPropertiesClass, "get", "(Ljava/lang/String;Ljava/lang/String;)Ljava/lang/String;");
    if (get == 0) {
        return (*env)->NewStringUTF(env, "");
    }

    jobject serialNo = (*env)->CallStaticObjectMethod(env, systemPropertiesClass, get, (*env)->NewStringUTF(env, "ro.serialno"), (*env)->NewStringUTF(env, ""));
    return (jstring) serialNo;
}


jstring getDeviceID(JNIEnv *env, jobject context) {
    jclass contextClass = (*env)->FindClass(env, "android/content/Context");

    if (contextClass == 0) {
        return (*env)->NewStringUTF(env, "");
    }

    jmethodID getSystemService = (*env)->GetMethodID(env, contextClass, "getSystemService", "(Ljava/lang/String;)Ljava/lang/Object;");

    if (getSystemService == 0) {
        return (*env)->NewStringUTF(env, "");
    }

    jfieldID TELEPHONY_SERVICE = (*env)->GetStaticFieldID(env, contextClass, "TELEPHONY_SERVICE", "Ljava/lang/String;");
    if (TELEPHONY_SERVICE == 0) {
        return (*env)->NewStringUTF(env, "");
    }

    jobject str = (*env)->GetStaticObjectField(env, contextClass, TELEPHONY_SERVICE);
    jobject telephonyManager = (*env)->CallObjectMethod(env, context, getSystemService, str);

    if (telephonyManager == 0) {
        return (*env)->NewStringUTF(env, "");
    }

    jclass telephonyManagerClass = (*env)->FindClass(env, "android/telephony/TelephonyManager");
    if (telephonyManagerClass == 0) {
        return (*env)->NewStringUTF(env, "");
    }

    jmethodID getDeviceId = (*env)->GetMethodID(env, telephonyManagerClass, "getDeviceId", "()Ljava/lang/String;");
    if (getDeviceId == 0) {
        return (*env)->NewStringUTF(env, "");
    }

    jobject deviceID = (*env)->CallObjectMethod(env, telephonyManager, getDeviceId);
    return (jstring) deviceID;
}

JNIEXPORT jstring JNICALL Java_com_hieunv_app_security_Security_getSalt(JNIEnv *env, jclass type, jobject context) {
    jstring deviceIDString = getDeviceID(env, context);
    const char *deviceID = (*env)->GetStringUTFChars(env, deviceIDString, 0);
    if (strcmp(deviceID, EMPTY_STRING) == 0 || strcmp(deviceID, NOT_EXPECTED_DEVICE_ID) == 0) {
        return (*env)->NewStringUTF(env, "Ue7ST9SQKrp25cEh");
    }
    (*env)->ReleaseStringUTFChars(env, deviceIDString, deviceID);

    jstring serialNoString = getSerialNo(env);
    const char *serialNo = (*env)->GetStringUTFChars(env, serialNoString, 0);
    if (strcmp(serialNo, EMPTY_STRING) == 0 || strcmp(serialNo, NOT_EXPECTED_SERIAL_NO) == 0) {
        return ((*env))->NewStringUTF(env, "GfP5GRePydNmM7kh");
    }
    (*env)->ReleaseStringUTFChars(env, serialNoString, serialNo);

    jstring packageNameString = getPackageName(env, context);
    const char *packageName = (*env)->GetStringUTFChars(env, packageNameString, 0);
    if (strcmp(packageName, PACKAGE_NAME) != 0) {
        return (*env)->NewStringUTF(env, "xKJnEYue6ZW44j4n");
    }

    (*env)->ReleaseStringUTFChars(env, packageNameString, packageName);
    return (*env)->NewStringUTF(env, "AXLqBm44PWH6mrwv");
}