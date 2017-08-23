#include <jni.h>
#include <string>
#include <android/log.h>
#include <amcomdef.h>
#include <arcsoft_spotlight.h>
extern "C"
JNIEXPORT jstring JNICALL
Java_appmagics_trackerprofilingandroid_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}

extern "C"
JNIEXPORT void JNICALL
Java_appmagics_trackerprofilingandroid_Tracker_initJNI(JNIEnv *env, jobject instance, jint type) {
    MRECT *_facerect = new MRECT();
    _facerect->bottom = 1;
    __android_log_print(ANDROID_LOG_ERROR, "shiyang jni2", "shiyang jni init type = %d", type);
    __android_log_print(ANDROID_LOG_ERROR, "shiyang jni2", "shiyang test bottom = %d", _facerect->bottom);
    delete(_facerect);
    _facerect = nullptr;

    MHandle mAsHandle = ASL_CreateEngine();
}