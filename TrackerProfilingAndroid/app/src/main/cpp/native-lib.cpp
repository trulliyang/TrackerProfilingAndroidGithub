#include <jni.h>
#include <string>
#include <android/log.h>
#include <amcomdef.h>
#include <arcsoft_spotlight.h>
#include <MG_Facepp.h>
#include <FaceTracker.h>
#include "AndroidSysInfo.h"
#include "time.h"
extern int clock_gettime(int, struct timespec *);
struct timespec now;


#define  LOGE(x...)  __android_log_print(ANDROID_LOG_ERROR,"shiyang jni",x)

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
    LOGE("shiyang jni init type = %d", type);
    LOGE("shiyang test bottom = %d", _facerect->bottom);
    delete(_facerect);
    _facerect = nullptr;

    MHandle mAsHandle = ASL_CreateEngine();
    if (!mAsHandle) {
        LOGE("arcsoft create engine fail\n");
    }
}

extern "C"
JNIEXPORT void JNICALL
Java_appmagics_trackerprofilingandroid_Tracker_initJNI0(
        JNIEnv *env, jobject instance, jobject context, jint type,
        jint imgw, jint imgh, jint formate, jstring respath_, jint img_angle) {
//    LOGE("shiyang jni init2 type = %d", type);
//    AndroidMemInfo *mem0 = new AndroidMemInfo();
//    mem0->GetTotalPhys();
//    mem0->GetAvailPhys();
//    LOGE("shiyang ram 0 avil=%lu, tot=%lu", mem0->ullAvailPhys, mem0->ullTotalPhys);
//
//    AndroidMemInfo *mem1 = new AndroidMemInfo();
//    mem1->GetTotalPhys();
//    mem1->GetAvailPhys();
//    LOGE("shiyang ram 1 avil=%lu, tot=%lu", mem1->ullAvailPhys, mem1->ullTotalPhys);

//    mem->GetTotalPhys();
//    mem->GetAvailPhys();
//    LOGE("shiyang ram 2 avil=%lu, tot=%lu", mem->ullAvailPhys, mem->ullTotalPhys);

    MHandle mAsHandle = ASL_CreateEngine();
    if (!mAsHandle) {
        LOGE("shiyang arcsoft create engine fail\n");
    } else {
        LOGE("shiyang arcsoft create engine sucess\n");
    }
    std::string resPath = jstringTostring(env, respath_);

    FILE *pYUV = fopen("/storage/emulated/0/ws23.yuv", "r");
    int lenPerFrame = 1280 * 720 * 3 / 2;
    int Frame = 50;
    int len = lenPerFrame * Frame;
    unsigned char *buf = new unsigned char[len];
    if (pYUV) {
        LOGE("shiyang open yuv success\n");
        fread(buf, 1, len, pYUV);
        fclose(pYUV);
    } else {
        LOGE("shiyang open yuv failed\n");
    }

//    AndroidMemInfo *mem100 = new AndroidMemInfo();
//    mem100->GetTotalPhys();
//    mem100->GetAvailPhys();
//    LOGE("shiyang ram 100 avil=%lu, tot=%lu", mem100->ullAvailPhys, mem100->ullTotalPhys);

    MLong result = ASL_Initialize(mAsHandle, "/storage/emulated/0/track_data.dat", ASL_MAX_FACE_NUM,
                                  (MPVoid *) env, (void **) &context);
    if (result != MOK) {
        LOGE("shiyang arcsoft init fail, result = 0X%lx\n", result);
//        return;
    } else {
//        LOGE("shiyang arcsoft init suceess\n");
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






    float time_cost[Frame];
    float sum = 0.0;
//    AndroidCpuUsage *cpu = new AndroidCpuUsage();
    for (int i=0; i<Frame; i++) {
        OffScreenIn.pi32Pitch[0] = OffScreenIn.i32Width;
        OffScreenIn.pi32Pitch[1] = OffScreenIn.i32Width;
        OffScreenIn.ppu8Plane[0] = buf + i*lenPerFrame;
        OffScreenIn.ppu8Plane[1] = buf + i*lenPerFrame + sizeof(unsigned char) * 1280 * 720;
        MInt32 nFaceCountInOut = ASL_MAX_FACE_NUM;
        MRECT rcFaceRectOut[ASL_MAX_FACE_NUM];
        MFloat faceOrientOut[ASL_MAX_FACE_NUM * 3];
        MPOINT *pFaceOutlinePointOut = (MPOINT *) mAsPointArray;
//        LOGE("shiyang ready to arcsoft process\n");



        // begin
        clock_gettime(CLOCK_MONOTONIC, &now);
        long long int time_begin = now.tv_sec * 1000000000LL + now.tv_nsec;
        MRESULT hr = ASL_Process(mAsHandle,
                                 &OffScreenIn,
                                 &OffScreenIn,
                                 &nFaceCountInOut,
                                 pFaceOutlinePointOut,
                                 rcFaceRectOut,
                                 faceOrientOut
        );
        clock_gettime(CLOCK_MONOTONIC, &now);
        long long int time_end = now.tv_sec * 1000000000LL + now.tv_nsec;
//        if (nFaceCountInOut<=0) {
//            LOGE("shiyang ready to arcsoft no face\n");
//            i--;
//            continue;
//        }


        time_cost[i] = (time_end - time_begin)/1000000.0f;
        sum += time_cost[i];
        // end





//        cpu->GetUsedCpu();
//        cpu->getProcCPUStat();
        if (hr != MOK) {
            LOGE("shiyang arcsoft process fail err code = 0X%x\n", hr);
        } else {
//            LOGE("shiyang arcsoft process sucess\n");
//            LOGE("shiyang arcsoft frame %d face count = %d\n", i, nFaceCountInOut);
        }
    }

    LOGE("shiyang AS time_cost_sum=%f", sum);
    for (int i=0; i<Frame; i++) {
        LOGE("shiyang AS time_cost[%d]=%f", i, time_cost[i]);
    }

    delete[] buf;
    buf = nullptr;
    delete[] mAsPointArray;
    mAsPointArray = nullptr;
}

extern "C"
JNIEXPORT void JNICALL
Java_appmagics_trackerprofilingandroid_Tracker_initJNI1(
        JNIEnv *env, jobject instance, jobject context, jint type,
        jint imgw, jint imgh, jint formate, jstring respath_, jint img_angle) {
    LOGE("shiyang jni init2 type = %d", type);

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
            LOGE("shiyang jni Face++ 初始化成功");

            MG_FPP_APICONFIG config;
            config.detection_mode = MG_FPP_DETECTIONMODE_TRACKING;
            config.rotation = (MG_UINT32)img_angle;

            int configResult = mg_facepp.SetDetectConfig(apihandle, &config);
            if (configResult == MG_RETCODE_OK) {
                LOGE("shiyang jni Face++ 设置配置成功");
            }

            int imgHandleCode = mg_facepp.CreateImageHandle(imgw, imgh, &imgHandle);
            if (imgHandleCode == MG_RETCODE_OK) {
                LOGE("shiyang jni Face++ 生成img Handle 成功");
            } else {
                LOGE("shiyang jni Face++ 生成img Handle 失败, createCode = %d", imgHandleCode);
            }
        } else {
            LOGE("shiyang jni Face++ 初始化失败,createCode = %d", createCode);
        }

        delete[] data;
        fclose(fp);
    } else {
        LOGE("shiyang jni open face++ data file failed");
    }

    if (apihandle) {
        if (!imgHandle) {
            mg_facepp.CreateImageHandle(imgw, imgh, &imgHandle);
        }

        FILE* pYUV = fopen("/storage/emulated/0/ws23.yuv", "r");
        int lenPerFrame = 1280*720*3/2;
        int Frame = 50;
        int len = lenPerFrame*Frame;
        unsigned char *buf = new unsigned char[len];
        if (pYUV) {
            LOGE("shiyang open yuv success\n");
            fread(buf, 1, len, pYUV);
            fclose(pYUV);
        } else {
            LOGE("shiyang open yuv failed\n");
        }


        float time_cost[Frame];
        float sum = 0.0;
        // first 10 frame never detects face;

        for (int i=0; i<30; i++) {
            mg_facepp.SetImageData(imgHandle, (const MG_BYTE *) buf, MG_IMAGEMODE_NV21);
            int m_face_count;
            mg_facepp.Detect(apihandle, imgHandle, &m_face_count);
        }

        for (int i=0; i<Frame; i++) {
            // begin
            clock_gettime(CLOCK_MONOTONIC, &now);
            long long int time_begin = now.tv_sec * 1000000000LL + now.tv_nsec;

            mg_facepp.SetImageData(imgHandle, (const MG_BYTE *) buf + i*lenPerFrame, MG_IMAGEMODE_NV21);
            int m_face_count;
            mg_facepp.Detect(apihandle, imgHandle, &m_face_count);

            clock_gettime(CLOCK_MONOTONIC, &now);
            long long int time_end = now.tv_sec * 1000000000LL + now.tv_nsec;
            time_cost[i] = (time_end - time_begin)/1000000.0f;
            sum += time_cost[i];
            // end
            if (m_face_count<1) {
                LOGE("shiyang frame %d face count = %d\n", i, m_face_count);
            }
//            LOGE("shiyang frame %d face count = %d\n", i, m_face_count);;
        }
        delete[] buf;
        LOGE("shiyang FPP time_cost_sum=%f", sum);
        for (int i=0; i<Frame; i++) {
            LOGE("shiyang FPP time_cost[%d]=%f", i, time_cost[i]);
        }
    }
    if (imgHandle) {
        mg_facepp.ReleaseImageHandle(imgHandle);
    }
    if (apihandle) {
        mg_facepp.ReleaseApiHandle(apihandle);
    }

}

extern "C"
JNIEXPORT void JNICALL
Java_appmagics_trackerprofilingandroid_Tracker_initJNI2(
        JNIEnv *env, jobject instance, jobject context, jint type,
        jint imgw, jint imgh, jint formate, jstring respath_, jint img_angle) {
    LOGE("shiyang jni init2 type = %d", type);
    // lisence

    // init

    // detect

}

extern "C"
JNIEXPORT void JNICALL
Java_appmagics_trackerprofilingandroid_Tracker_initJNI3(
        JNIEnv *env, jobject instance, jobject context, jint type,
        jint imgw, jint imgh, jint formate, jstring respath_, jint img_angle) {
    LOGE("shiyang jni init2 type = %d", type);

//    std::string path = std::string("/storage/emulated/0/model");
    FaceTracker *m_FaceTracker = nullptr;
    m_FaceTracker = new FaceTracker("/storage/emulated/0/model", "/main_clnf_multi_pie.txt"); 
//    m_FaceTracker = new FaceTracker("/storage/emulated/0/model3", "/main_clnf_multi_pie_fast.txt");
    if (m_FaceTracker) {
        LOGE("shiyang jni init2 new self tracker ok");
    } else {
        LOGE("shiyang jni init2 new self tracker shiit");
    }

    FILE* pYUV = fopen("/storage/emulated/0/ws23.yuv", "r");
    int lenPerFrame = 1280*720*3/2;
    int Frame = 50;
    int len = lenPerFrame*Frame;
    unsigned char *buf = new unsigned char[len];
    if (pYUV) {
        LOGE("shiyang open yuv success\n");
        fread(buf, 1, len, pYUV);
        fclose(pYUV);
    } else {
        LOGE("shiyang open yuv failed\n");
    }

    int colorType = 1;
    int face_rotate = 3;

    for (int i=0; i<10; i++) {
        std::vector<FacialInfo> result_list =
                m_FaceTracker->FacialLandmarkDetectInVideo((char *)(buf+i*lenPerFrame), imgw, imgh,
                                                           colorType * imgw * sizeof(char), colorType,
                                                           faceOritation(face_rotate));
//        int m_face_count = result_list.size();
//        LOGE("shiyang detectSELF face count = %d", m_face_count);
    }

    float time_cost[Frame];
    float sum = 0.0;
//    int num_ignore = 0;
//    bool needIgnore = false;
    for (int i=0; i<Frame; i++) {

        // begin
        clock_gettime(CLOCK_MONOTONIC, &now);
        long long int time_begin = now.tv_sec * 1000000000LL + now.tv_nsec;
        std::vector<FacialInfo> result_list =
                m_FaceTracker->FacialLandmarkDetectInVideo((char *)(buf+i*lenPerFrame), imgw, imgh,
                colorType * imgw * sizeof(char), colorType, faceOritation(face_rotate));
        clock_gettime(CLOCK_MONOTONIC, &now);
        long long int time_end = now.tv_sec * 1000000000LL + now.tv_nsec;
        time_cost[i] = (time_end - time_begin)/1000000.0f;
//        if (i%10 == 9) {
//            time_cost[i] = 0.0f;
//        }
        sum += time_cost[i];

        int m_face_count = result_list.size();
        LOGE("shiyang detectSELF face count = %d", m_face_count);
    }

    LOGE("shiyang self time_cost_sum=%f avg=%f", sum, sum/Frame);

    for (int i=0; i<Frame; i++) {
        LOGE("shiyang self time_cost[%d]=%f", i, time_cost[i]);
    }

}



extern "C"
JNIEXPORT void JNICALL
Java_appmagics_trackerprofilingandroid_Tracker_initJNI4(
        JNIEnv *env, jobject instance, jobject context, jint type,
        jint imgw, jint imgh, jint formate, jstring respath_, jint img_angle) {

}

extern "C"
JNIEXPORT void JNICALL
Java_appmagics_trackerprofilingandroid_Tracker_initJNI5(
        JNIEnv *env, jobject instance, jobject context, jint type,
        jint imgw, jint imgh, jint formate, jstring respath_, jint img_angle) {

}

extern "C"
JNIEXPORT void JNICALL
Java_appmagics_trackerprofilingandroid_Tracker_initJNI6(
        JNIEnv *env, jobject instance, jobject context, jint type,
        jint imgw, jint imgh, jint formate, jstring respath_, jint img_angle) {

}






void getProcCPUStat(struct systemCPUdata *proc, int pid)

{

    FILE *file;

    unsigned long itemp;

    char ctemp;

    char line[255];



    sprintf(line, "/proc/%d/stat", pid);

    file = fopen(line, "r");

    if (file == NULL)

    {
        LOGE("AndroidCpuUsage Error: process not found!\n");

        return;

    }

    fgets(line, 255, file);

    fclose(file);

    sscanf(line, "%d %s %c %d %d %d %d %d %lu %lu %lu %lu %lu %lu %lu "

                   "%ld %ld %ld %ld %ld %ld %lu %lu %ld",

           (int*)&itemp, proc->pname, &ctemp, (int*)&itemp, (int*)&itemp, (int*)&itemp, (int*)&itemp, (int*)&itemp,

           &itemp, &itemp, &itemp, &itemp, &itemp, &proc->utime, &proc->stime,

           &proc->cutime, &proc->cstime, &itemp, &itemp, &itemp, &itemp, &itemp, &proc->vmem, &proc->rmem

    );



}

#if 0 //self model3 fast.txt
09-18 21:19:56.672 8875-8875/com.ml.national E/shiyang jni: shiyang self time_cost_sum=1729.778809 avg=34.595577
09-18 21:19:56.672 8875-8875/com.ml.national E/shiyang jni: shiyang self time_cost[0]=33.365574
09-18 21:19:56.672 8875-8875/com.ml.national E/shiyang jni: shiyang self time_cost[1]=33.213333
09-18 21:19:56.672 8875-8875/com.ml.national E/shiyang jni: shiyang self time_cost[2]=33.805103
09-18 21:19:56.672 8875-8875/com.ml.national E/shiyang jni: shiyang self time_cost[3]=33.444427
09-18 21:19:56.672 8875-8875/com.ml.national E/shiyang jni: shiyang self time_cost[4]=34.197033
09-18 21:19:56.672 8875-8875/com.ml.national E/shiyang jni: shiyang self time_cost[5]=33.599895
09-18 21:19:56.672 8875-8875/com.ml.national E/shiyang jni: shiyang self time_cost[6]=33.448437
09-18 21:19:56.672 8875-8875/com.ml.national E/shiyang jni: shiyang self time_cost[7]=32.480518
09-18 21:19:56.672 8875-8875/com.ml.national E/shiyang jni: shiyang self time_cost[8]=31.952345
09-18 21:19:56.672 8875-8875/com.ml.national E/shiyang jni: shiyang self time_cost[9]=50.707657
09-18 21:19:56.672 8875-8875/com.ml.national E/shiyang jni: shiyang self time_cost[10]=32.075779
09-18 21:19:56.672 8875-8875/com.ml.national E/shiyang jni: shiyang self time_cost[11]=32.274063
09-18 21:19:56.672 8875-8875/com.ml.national E/shiyang jni: shiyang self time_cost[12]=31.644428
09-18 21:19:56.672 8875-8875/com.ml.national E/shiyang jni: shiyang self time_cost[13]=33.313072
09-18 21:19:56.672 8875-8875/com.ml.national E/shiyang jni: shiyang self time_cost[14]=32.655312
09-18 21:19:56.672 8875-8875/com.ml.national E/shiyang jni: shiyang self time_cost[15]=32.491302
09-18 21:19:56.672 8875-8875/com.ml.national E/shiyang jni: shiyang self time_cost[16]=32.773281
09-18 21:19:56.673 8875-8875/com.ml.national E/shiyang jni: shiyang self time_cost[17]=33.834740
09-18 21:19:56.673 8875-8875/com.ml.national E/shiyang jni: shiyang self time_cost[18]=31.415991
09-18 21:19:56.673 8875-8875/com.ml.national E/shiyang jni: shiyang self time_cost[19]=56.875362
09-18 21:19:56.673 8875-8875/com.ml.national E/shiyang jni: shiyang self time_cost[20]=32.938751
09-18 21:19:56.673 8875-8875/com.ml.national E/shiyang jni: shiyang self time_cost[21]=31.939531
09-18 21:19:56.673 8875-8875/com.ml.national E/shiyang jni: shiyang self time_cost[22]=32.175468
09-18 21:19:56.673 8875-8875/com.ml.national E/shiyang jni: shiyang self time_cost[23]=31.356876
09-18 21:19:56.673 8875-8875/com.ml.national E/shiyang jni: shiyang self time_cost[24]=32.424427
09-18 21:19:56.673 8875-8875/com.ml.national E/shiyang jni: shiyang self time_cost[25]=31.302032
09-18 21:19:56.673 8875-8875/com.ml.national E/shiyang jni: shiyang self time_cost[26]=31.286457
09-18 21:19:56.673 8875-8875/com.ml.national E/shiyang jni: shiyang self time_cost[27]=30.239479
09-18 21:19:56.673 8875-8875/com.ml.national E/shiyang jni: shiyang self time_cost[28]=32.209740
09-18 21:19:56.673 8875-8875/com.ml.national E/shiyang jni: shiyang self time_cost[29]=57.111927
09-18 21:19:56.673 8875-8875/com.ml.national E/shiyang jni: shiyang self time_cost[30]=29.328176
09-18 21:19:56.673 8875-8875/com.ml.national E/shiyang jni: shiyang self time_cost[31]=31.109896
09-18 21:19:56.673 8875-8875/com.ml.national E/shiyang jni: shiyang self time_cost[32]=32.863384
09-18 21:19:56.673 8875-8875/com.ml.national E/shiyang jni: shiyang self time_cost[33]=35.769115
09-18 21:19:56.673 8875-8875/com.ml.national E/shiyang jni: shiyang self time_cost[34]=33.425781
09-18 21:19:56.673 8875-8875/com.ml.national E/shiyang jni: shiyang self time_cost[35]=30.778437
09-18 21:19:56.673 8875-8875/com.ml.national E/shiyang jni: shiyang self time_cost[36]=30.937187
09-18 21:19:56.673 8875-8875/com.ml.national E/shiyang jni: shiyang self time_cost[37]=32.490417
09-18 21:19:56.673 8875-8875/com.ml.national E/shiyang jni: shiyang self time_cost[38]=34.002708
09-18 21:19:56.673 8875-8875/com.ml.national E/shiyang jni: shiyang self time_cost[39]=52.394688
09-18 21:19:56.673 8875-8875/com.ml.national E/shiyang jni: shiyang self time_cost[40]=32.127865
09-18 21:19:56.673 8875-8875/com.ml.national E/shiyang jni: shiyang self time_cost[41]=30.940260
09-18 21:19:56.673 8875-8875/com.ml.national E/shiyang jni: shiyang self time_cost[42]=31.369013
09-18 21:19:56.673 8875-8875/com.ml.national E/shiyang jni: shiyang self time_cost[43]=33.227760
09-18 21:19:56.673 8875-8875/com.ml.national E/shiyang jni: shiyang self time_cost[44]=32.947033
09-18 21:19:56.673 8875-8875/com.ml.national E/shiyang jni: shiyang self time_cost[45]=33.145000
09-18 21:19:56.673 8875-8875/com.ml.national E/shiyang jni: shiyang self time_cost[46]=32.105053
09-18 21:19:56.673 8875-8875/com.ml.national E/shiyang jni: shiyang self time_cost[47]=32.369324
09-18 21:19:56.673 8875-8875/com.ml.national E/shiyang jni: shiyang self time_cost[48]=32.876144
09-18 21:19:56.673 8875-8875/com.ml.national E/shiyang jni: shiyang self time_cost[49]=53.019375
#endif