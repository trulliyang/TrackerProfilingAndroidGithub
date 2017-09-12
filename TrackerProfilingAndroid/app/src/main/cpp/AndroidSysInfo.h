//
// Created by SHI.yang on 2017/8/29.
//

#ifndef TRACKERPROFILINGANDROID_ANDROIDSYSINFO_H
#define TRACKERPROFILINGANDROID_ANDROIDSYSINFO_H

#include <stdio.h>

#include <string.h>

#include <stdlib.h>

#include <fcntl.h>

#include <android/log.h>

#include <unistd.h>

#include <sys/time.h>

typedef unsigned long DWORD;



struct systemCPUdata

{

    unsigned long utime,stime,cutime,cstime;

    unsigned long vmem, rmem;

    char pname[255];

};



class AndroidMemInfo

{

public:

    AndroidMemInfo();

    ~AndroidMemInfo();

    void GetTotalPhys();

    void GetAvailPhys();

    DWORD ullTotalPhys;

    DWORD ullAvailPhys;



private:

    int m_memFile;



};
#if 0
09-12 14:36:51.912 17199-17199/com.ml.national E/shiyang jni: shiyang self time_cost_sum=3793.577637 avg=75.871552
09-12 14:36:51.912 17199-17199/com.ml.national E/shiyang jni: shiyang self time_cost[0]=74.846870
09-12 14:36:51.912 17199-17199/com.ml.national E/shiyang jni: shiyang self time_cost[1]=75.057808
09-12 14:36:51.912 17199-17199/com.ml.national E/shiyang jni: shiyang self time_cost[2]=75.788544
09-12 14:36:51.912 17199-17199/com.ml.national E/shiyang jni: shiyang self time_cost[3]=74.219795
09-12 14:36:51.912 17199-17199/com.ml.national E/shiyang jni: shiyang self time_cost[4]=74.557297
09-12 14:36:51.912 17199-17199/com.ml.national E/shiyang jni: shiyang self time_cost[5]=75.321869
09-12 14:36:51.912 17199-17199/com.ml.national E/shiyang jni: shiyang self time_cost[6]=73.293236
09-12 14:36:51.912 17199-17199/com.ml.national E/shiyang jni: shiyang self time_cost[7]=72.901558
09-12 14:36:51.912 17199-17199/com.ml.national E/shiyang jni: shiyang self time_cost[8]=74.043755
09-12 14:36:51.912 17199-17199/com.ml.national E/shiyang jni: shiyang self time_cost[9]=100.977600
09-12 14:36:51.912 17199-17199/com.ml.national E/shiyang jni: shiyang self time_cost[10]=73.959373
09-12 14:36:51.912 17199-17199/com.ml.national E/shiyang jni: shiyang self time_cost[11]=73.691147
09-12 14:36:51.912 17199-17199/com.ml.national E/shiyang jni: shiyang self time_cost[12]=74.191666
09-12 14:36:51.912 17199-17199/com.ml.national E/shiyang jni: shiyang self time_cost[13]=72.510933
09-12 14:36:51.912 17199-17199/com.ml.national E/shiyang jni: shiyang self time_cost[14]=73.451561
09-12 14:36:51.912 17199-17199/com.ml.national E/shiyang jni: shiyang self time_cost[15]=73.153648
09-12 14:36:51.912 17199-17199/com.ml.national E/shiyang jni: shiyang self time_cost[16]=72.718750
09-12 14:36:51.912 17199-17199/com.ml.national E/shiyang jni: shiyang self time_cost[17]=72.359375
09-12 14:36:51.912 17199-17199/com.ml.national E/shiyang jni: shiyang self time_cost[18]=73.103645
09-12 14:36:51.912 17199-17199/com.ml.national E/shiyang jni: shiyang self time_cost[19]=102.179688
09-12 14:36:51.912 17199-17199/com.ml.national E/shiyang jni: shiyang self time_cost[20]=74.678650
09-12 14:36:51.912 17199-17199/com.ml.national E/shiyang jni: shiyang self time_cost[21]=73.056770
09-12 14:36:51.912 17199-17199/com.ml.national E/shiyang jni: shiyang self time_cost[22]=73.671875
09-12 14:36:51.912 17199-17199/com.ml.national E/shiyang jni: shiyang self time_cost[23]=73.551559
09-12 14:36:51.912 17199-17199/com.ml.national E/shiyang jni: shiyang self time_cost[24]=73.432816
09-12 14:36:51.912 17199-17199/com.ml.national E/shiyang jni: shiyang self time_cost[25]=72.553650
09-12 14:36:51.912 17199-17199/com.ml.national E/shiyang jni: shiyang self time_cost[26]=71.668236
09-12 14:36:51.912 17199-17199/com.ml.national E/shiyang jni: shiyang self time_cost[27]=73.139061
09-12 14:36:51.912 17199-17199/com.ml.national E/shiyang jni: shiyang self time_cost[28]=70.344269
09-12 14:36:51.912 17199-17199/com.ml.national E/shiyang jni: shiyang self time_cost[29]=99.506248
09-12 14:36:51.912 17199-17199/com.ml.national E/shiyang jni: shiyang self time_cost[30]=74.336975
09-12 14:36:51.912 17199-17199/com.ml.national E/shiyang jni: shiyang self time_cost[31]=73.482819
09-12 14:36:51.912 17199-17199/com.ml.national E/shiyang jni: shiyang self time_cost[32]=73.448959
09-12 14:36:51.912 17199-17199/com.ml.national E/shiyang jni: shiyang self time_cost[33]=71.292191
09-12 14:36:51.912 17199-17199/com.ml.national E/shiyang jni: shiyang self time_cost[34]=72.277603
09-12 14:36:51.912 17199-17199/com.ml.national E/shiyang jni: shiyang self time_cost[35]=74.023438
09-12 14:36:51.912 17199-17199/com.ml.national E/shiyang jni: shiyang self time_cost[36]=71.735939
09-12 14:36:51.912 17199-17199/com.ml.national E/shiyang jni: shiyang self time_cost[37]=74.933853
09-12 14:36:51.912 17199-17199/com.ml.national E/shiyang jni: shiyang self time_cost[38]=71.123962
09-12 14:36:51.912 17199-17199/com.ml.national E/shiyang jni: shiyang self time_cost[39]=98.359375
09-12 14:36:51.912 17199-17199/com.ml.national E/shiyang jni: shiyang self time_cost[40]=73.345314
09-12 14:36:51.912 17199-17199/com.ml.national E/shiyang jni: shiyang self time_cost[41]=70.259895
09-12 14:36:51.912 17199-17199/com.ml.national E/shiyang jni: shiyang self time_cost[42]=71.629684
09-12 14:36:51.912 17199-17199/com.ml.national E/shiyang jni: shiyang self time_cost[43]=74.428650
09-12 14:36:51.912 17199-17199/com.ml.national E/shiyang jni: shiyang self time_cost[44]=72.166145
09-12 14:36:51.912 17199-17199/com.ml.national E/shiyang jni: shiyang self time_cost[45]=70.494789
09-12 14:36:51.912 17199-17199/com.ml.national E/shiyang jni: shiyang self time_cost[46]=72.529167
09-12 14:36:51.912 17199-17199/com.ml.national E/shiyang jni: shiyang self time_cost[47]=71.345314
09-12 14:36:51.912 17199-17199/com.ml.national E/shiyang jni: shiyang self time_cost[48]=75.371872
09-12 14:36:51.912 17199-17199/com.ml.national E/shiyang jni: shiyang self time_cost[49]=99.060417
#endif


class AndroidCpuUsage

{

public:

    AndroidCpuUsage();

    struct timeval m_lasttime, m_nowtime;

    struct systemCPUdata m_lastproc, m_nowproc;

    void getProcCPUStat(struct systemCPUdata *proc, int pid);

    DWORD GetUsedCpu();

};

#endif //TRACKERPROFILINGANDROID_ANDROIDSYSINFO_H
