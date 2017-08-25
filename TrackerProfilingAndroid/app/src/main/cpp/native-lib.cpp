#include <jni.h>
#include <string>
#include <android/log.h>
#include <amcomdef.h>
#include <arcsoft_spotlight.h>
#include <MG_Facepp.h>
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
Java_appmagics_trackerprofilingandroid_Tracker_initJNI0(
        JNIEnv *env, jobject instance, jobject context, jint type,
        jint imgw, jint imgh, jint formate, jstring respath_, jint img_angle) {
    __android_log_print(ANDROID_LOG_ERROR, "shiyang jni0", "shiyang jni init2 type = %d", type);

    MHandle mAsHandle = ASL_CreateEngine();
    if (!mAsHandle) {
        __android_log_print(ANDROID_LOG_ERROR, "shiyang jni0", "shiyang arcsoft create engine fail\n");
//        return false;
    } else {
        __android_log_print(ANDROID_LOG_ERROR, "shiyang jni0", "shiyang arcsoft create engine sucess\n");
    }
    std::string resPath = jstringTostring(env, respath_);

    FILE* pYUV = fopen("/storage/emulated/0/ws23.yuv", "r");
    int len = 1280*720*3/2;
    unsigned char *buf = new unsigned char[len];
    if (pYUV) {
        __android_log_print(ANDROID_LOG_ERROR, "shiyang jni0", "shiyang open yuv success\n");
        fread(buf, 1, len, pYUV);
    } else {
        __android_log_print(ANDROID_LOG_ERROR, "shiyang jni0", "shiyang open yuv failed\n");
    }

//    __android_log_print(ANDROID_LOG_ERROR, "shiyang jni2", "shiyang path = %s\n", resPath.c_str());
    MLong result = ASL_Initialize(mAsHandle, "/storage/emulated/0/track_data.dat", ASL_MAX_FACE_NUM,
                                  (MPVoid *) env, (void **) &context);
    if (result != MOK) {
        __android_log_print(ANDROID_LOG_ERROR, "shiyang jni0", "shiyang arcsoft init fail, result = %ld\n", result);
//        return false;
    } else {
        __android_log_print(ANDROID_LOG_ERROR, "shiyang jni0", "shiyang arcsoft init suceess\n");
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
    __android_log_print(ANDROID_LOG_ERROR, "shiyang jni0", "shiyang ready to arcsoft process\n");
    MRESULT hr = ASL_Process(mAsHandle,
                             &OffScreenIn,
                             &OffScreenIn,
                             &nFaceCountInOut,
                             pFaceOutlinePointOut,
                             rcFaceRectOut,
                             faceOrientOut
    );
    if (hr != MOK) {
        __android_log_print(ANDROID_LOG_ERROR, "shiyang jni0", "shiyang arcsoft process fail\n");
    } else {
        __android_log_print(ANDROID_LOG_ERROR, "shiyang jni0", "shiyang arcsoft process sucess\n");
        __android_log_print(ANDROID_LOG_ERROR, "shiyang jni0", "shiyang arcsoft face count = %d\n", nFaceCountInOut);
    }
    fclose(pYUV);
    delete[] mAsPointArray;
    mAsPointArray = nullptr;
}

extern "C"
JNIEXPORT void JNICALL
Java_appmagics_trackerprofilingandroid_Tracker_initJNI1(
        JNIEnv *env, jobject instance, jobject context, jint type,
        jint imgw, jint imgh, jint formate, jstring respath_, jint img_angle) {
    __android_log_print(
            ANDROID_LOG_ERROR,
            "shiyang jni1",
            "shiyang jni init2 type = %d", type
    );

    MG_FPP_APIHANDLE apihandle;
    MG_FPP_IMAGEHANDLE imgHandle;
//    std::string path = "/storage/emulated/0/megviifacepp_0_4_7_model";
    FILE *fp = fopen("/storage/emulated/0/megviifacepp_0_4_7_model", "r");
    if (fp) {
        fseek(fp, 0, SEEK_END);
        int t_file_len = ftell(fp); //文件长度
        rewind(fp);
//        void * data = new size_t[t_file_len];
        void * data = new unsigned char[t_file_len];
        fread(data, 1, (size_t)t_file_len, fp);

        int createCode = mg_facepp.CreateApiHandle((JNIEnv*) env, (jobject) context,
                                                   (const MG_BYTE *) data, t_file_len, &apihandle);
        if (apihandle && createCode == MG_RETCODE_OK) {
            __android_log_print(
                    ANDROID_LOG_ERROR,
                    "shiyang jni1",
                    "shiyang jni Face++ 初始化成功"
            );

            MG_FPP_APICONFIG config;
            config.detection_mode = MG_FPP_DETECTIONMODE_TRACKING;
            config.rotation = (MG_UINT32)img_angle;

            int configResult = mg_facepp.SetDetectConfig(apihandle, &config);
            if (configResult == MG_RETCODE_OK) {
                __android_log_print(
                        ANDROID_LOG_ERROR,
                        "shiyang jni1",
                        "shiyang jni Face++ 设置配置成功"
                );
            }

            int imgHandleCode = mg_facepp.CreateImageHandle(imgw, imgh, &imgHandle);
            if (imgHandleCode == MG_RETCODE_OK) {
                __android_log_print(
                        ANDROID_LOG_ERROR,
                        "shiyang jni1",
                        "shiyang jni Face++ 生成img Handle 成功"
                );
            } else {
                __android_log_print(
                        ANDROID_LOG_ERROR,
                        "shiyang jni1",
                        "shiyang jni Face++ 生成img Handle 失败, createCode = %d", imgHandleCode
                );
            }
        } else {
            __android_log_print(
                    ANDROID_LOG_ERROR,
                    "shiyang jni1",
                    "shiyang jni Face++ 初始化失败,createCode = %d", createCode
            );
        }

        delete[] data;
        fclose(fp);
    } else {
        __android_log_print(
                ANDROID_LOG_ERROR,
                "shiyang jni1",
                "shiyang jni open face++ data file failed"
        );
    }

    if (apihandle) {
        if (!imgHandle) {
            mg_facepp.CreateImageHandle(imgw, imgh, &imgHandle);
        }

        FILE* pYUV = fopen("/storage/emulated/0/ws23.yuv", "r");
        int len = 1280*720*3/2*50;
        unsigned char *buf = new unsigned char[len];
        if (pYUV) {
            __android_log_print(ANDROID_LOG_ERROR, "shiyang jni1", "shiyang open yuv success\n");
            fread(buf, 1, len, pYUV);
        } else {
            __android_log_print(ANDROID_LOG_ERROR, "shiyang jni1", "shiyang open yuv failed\n");
        }

        for (int i=0; i<50; i++) {
            mg_facepp.SetImageData(imgHandle, (const MG_BYTE *) buf + i*1280*720*3/2, MG_IMAGEMODE_NV21);

            int m_face_count;
            mg_facepp.Detect(apihandle, imgHandle, &m_face_count);
            __android_log_print(
                    ANDROID_LOG_ERROR,
                    "shiyang jni1",
                    "shiyang face count = %d\n", m_face_count
            );
        }
    }


}

extern "C"
JNIEXPORT void JNICALL
Java_appmagics_trackerprofilingandroid_Tracker_initJNI2(
        JNIEnv *env, jobject instance, jobject context, jint type,
        jint imgw, jint imgh, jint formate, jstring respath_, jint img_angle) {}

extern "C"
JNIEXPORT void JNICALL
Java_appmagics_trackerprofilingandroid_Tracker_initJNI3(
        JNIEnv *env, jobject instance, jobject context, jint type,
        jint imgw, jint imgh, jint formate, jstring respath_, jint img_angle) {}

extern "C"
JNIEXPORT void JNICALL
Java_appmagics_trackerprofilingandroid_Tracker_initJNI4(
        JNIEnv *env, jobject instance, jobject context, jint type,
        jint imgw, jint imgh, jint formate, jstring respath_, jint img_angle) {}

extern "C"
JNIEXPORT void JNICALL
Java_appmagics_trackerprofilingandroid_Tracker_initJNI5(
        JNIEnv *env, jobject instance, jobject context, jint type,
        jint imgw, jint imgh, jint formate, jstring respath_, jint img_angle) {}

extern "C"
JNIEXPORT void JNICALL
Java_appmagics_trackerprofilingandroid_Tracker_initJNI6(
        JNIEnv *env, jobject instance, jobject context, jint type,
        jint imgw, jint imgh, jint formate, jstring respath_, jint img_angle) {}