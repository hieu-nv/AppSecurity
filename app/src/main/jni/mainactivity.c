#include <jni.h>


jstring Java_com_hieunv_app_security_MainActivity_getDeviceID(JNIEnv* env, jobject thiz ) {
    return (*env)->NewStringUTF(env, "HieuNV");
}