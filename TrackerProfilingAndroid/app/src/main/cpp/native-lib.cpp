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
        JNIEnv *env, jobject instance, jobject context, jint type,
        jint imgw, jint imgh, jint formate, jstring respath_, jint img_angle) {
    MRECT *_facerect = new MRECT();
    _facerect->bottom = 1;
    __android_log_print(ANDROID_LOG_ERROR, "shiyang jni", "shiyang jni init2 type = %d", type);
    __android_log_print(ANDROID_LOG_ERROR, "shiyang jni", "shiyang test bottom = %d", _facerect->bottom);
    delete(_facerect);
    _facerect = nullptr;

    MHandle mAsHandle = ASL_CreateEngine();
    if (!mAsHandle) {
        __android_log_print(ANDROID_LOG_ERROR, "shiyang jni2", "shiyang arcsoft create engine fail\n");
//        return false;
    } else {
        __android_log_print(ANDROID_LOG_ERROR, "shiyang jni2", "shiyang arcsoft create engine sucess\n");
    }
    std::string resPath = jstringTostring(env, respath_);

//    FILE* p = fopen("/storage/emulated/0/track_data.dat", "r");
//    if (p) {
//        __android_log_print(ANDROID_LOG_ERROR, "shiyang jni2", "shiyang open data success\n");
//        fclose(p);
//    } else {
//        __android_log_print(ANDROID_LOG_ERROR, "shiyang jni2", "shiyang open data failed\n");
//    }

    FILE* pYUV = fopen("/storage/emulated/0/ws23.yuv", "r");
    int len = 1280*720*3/2;
    unsigned char *buf = new unsigned char[len];
    if (pYUV) {
        __android_log_print(ANDROID_LOG_ERROR, "shiyang jni2", "shiyang open yuv success\n");
        fread(buf, 1, len, pYUV);
    } else {
        __android_log_print(ANDROID_LOG_ERROR, "shiyang jni2", "shiyang open yuv failed\n");
    }

//    __android_log_print(ANDROID_LOG_ERROR, "shiyang jni2", "shiyang path = %s\n", resPath.c_str());
    MLong result = ASL_Initialize(mAsHandle, "/storage/emulated/0/track_data.dat", ASL_MAX_FACE_NUM,
                                  (MPVoid *) env, (void **) &context);
    if (result != MOK) {
        __android_log_print(ANDROID_LOG_ERROR, "shiyang jni2", "shiyang arcsoft init fail, result = %ld\n", result);
//        return false;
    } else {
        __android_log_print(ANDROID_LOG_ERROR, "shiyang jni2", "shiyang arcsoft init suceess\n");
    }

    ASL_SetProcessModel(mAsHandle, ASL_PROCESS_MODEL_FACEOUTLINE | ASL_PROCESS_MODEL_FACEBEAUTY);
    ASL_SetFaceSkinSoftenLevel(mAsHandle, 100);
    ASL_SetFaceBrightLevel(mAsHandle, 100);
    //
    int mAsPointNum = ASL_GetFaceOutlinePointCount();
    int *mAsPointArray = new int[ASL_MAX_FACE_NUM * mAsPointNum * 2];

    ASVLOFFSCREEN OffScreenIn;
    OffScreenIn.u32PixelArrayFormat = ASVL_PAF_NV21;
    OffScreenIn.i32Width = imgw;
    OffScreenIn.i32Height = imgh;

    OffScreenIn.pi32Pitch[0] = OffScreenIn.i32Width;
    OffScreenIn.pi32Pitch[1] = OffScreenIn.i32Width;
    OffScreenIn.ppu8Plane[0] = buf;
    OffScreenIn.ppu8Plane[1] = buf + sizeof(unsigned char)*1280*720;
    MInt32 nFaceCountInOut = ASL_MAX_FACE_NUM;
    MRECT rcFaceRectOut[ASL_MAX_FACE_NUM];
    MFloat faceOrientOut[ASL_MAX_FACE_NUM * 3];
    MPOINT *pFaceOutlinePointOut = (MPOINT *) mAsPointArray;
    __android_log_print(ANDROID_LOG_ERROR, "shiyang jni2", "shiyang ready to arcsoft process\n");
    MRESULT hr = ASL_Process(mAsHandle,
                             &OffScreenIn,
                             &OffScreenIn,
                             &nFaceCountInOut,
                             pFaceOutlinePointOut,
                             rcFaceRectOut,
                             faceOrientOut
    );
    if (hr != MOK) {
        __android_log_print(ANDROID_LOG_ERROR, "shiyang jni2", "shiyang arcsoft process fail\n");
    } else {
        __android_log_print(ANDROID_LOG_ERROR, "shiyang jni2", "shiyang arcsoft process sucess\n");
        __android_log_print(ANDROID_LOG_ERROR, "shiyang jni2", "shiyang face count=%d\n", nFaceCountInOut);
    }
    fclose(pYUV);
}