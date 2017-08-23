#include <jni.h>
#include <string>
#include <android/log.h>

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
    __android_log_print(ANDROID_LOG_ERROR, "shiyang jni", "shiyang jni init type = %d", type);
}