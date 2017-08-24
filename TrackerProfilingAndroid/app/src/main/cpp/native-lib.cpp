#include <jni.h>
#include <string>
#include <android/log.h>
#include <amcomdef.h>
#include <arcsoft_spotlight.h>

std::string jstringTostring(JNIEnv *env, jstring jstr) {
    const char *c_str = NULL;
    c_str = env->GetStringUTFChars(jstr, NULL);
    std::string stemp(c_str);
    env->ReleaseStringUTFChars(jstr, c_str);
    return stemp;
}

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
Java_appmagics_trackerprofilingandroid_Tracker_initJNI(
        JNIEnv *env, jobject instance, jint type) {
    MRECT *_facerect = new MRECT();
    _facerect->bottom = 1;
    __android_log_print(ANDROID_LOG_ERROR, "shiyang jni", "shiyang jni init type = %d", type);
    __android_log_print(ANDROID_LOG_ERROR, "shiyang jni", "shiyang test bottom = %d", _facerect->bottom);
    delete(_facerect);
    _facerect = nullptr;

    MHandle mAsHandle = ASL_CreateEngine();
    if (!mAsHandle) {
        __android_log_print(ANDROID_LOG_ERROR, "shiyang jni2", "arcsoft create engine fail\n");
//        return false;
    }
}

extern "C"
JNIEXPORT void JNICALL
Java_appmagics_trackerprofilingandroid_Tracker_initJNI2(
        JNIEnv *env, jobject instance, jobject context, jstring respath_,
        jint imgw, jint imgh, jint formate, jint img_angle, jint type) {
    MRECT *_facerect = new MRECT();
    _facerect->bottom = 1;
    __android_log_print(ANDROID_LOG_ERROR, "shiyang jni", "shiyang jni init2 type = %d", type);
    __android_log_print(ANDROID_LOG_ERROR, "shiyang jni", "shiyang test bottom = %d", _facerect->bottom);
    delete(_facerect);
    _facerect = nullptr;

    MHandle mAsHandle = ASL_CreateEngine();
    if (!mAsHandle) {
        __android_log_print(ANDROID_LOG_ERROR, "shiyang jni2", "arcsoft create engine fail\n");
//        return false;
    }
    std::string resPath = jstringTostring(env, respath_);
    MLong result = ASL_Initialize(mAsHandle, resPath.c_str(), ASL_MAX_FACE_NUM,
                                  (MPVoid *) env, (void **) context);
    if (result != MOK) {
        __android_log_print(ANDROID_LOG_ERROR, "shiyang jni2", "arcsoft init fail\n");
//        return false;
    }
    //带不带美颜功能
    //ASL_SetProcessModel(mAsHandle, ASL_PROCESS_MODEL_NONE);
    ASL_SetProcessModel(mAsHandle, ASL_PROCESS_MODEL_FACEOUTLINE | ASL_PROCESS_MODEL_FACEBEAUTY);
    ASL_SetFaceSkinSoftenLevel(mAsHandle, 100);
    ASL_SetFaceBrightLevel(mAsHandle, 100);
    //
    int mAsPointNum = ASL_GetFaceOutlinePointCount();
    int *mAsPointArray = new int[ASL_MAX_FACE_NUM * mAsPointNum * 2];
    delete[] mAsPointArray;
    mAsPointArray = nullptr;
}