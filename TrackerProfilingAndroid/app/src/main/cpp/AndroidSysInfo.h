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
09-12 18:50:23.450 29995-29995/com.ml.national E/shiyang jni: shiyang self time_cost_sum=3806.966309 avg=76.139328
74.635414
73.676041
75.465622
74.276558
73.127602
74.827080
73.005730
72.777084
73.007812
102.177078
77.005211
76.433853
76.552605
75.277611
75.325523
72.667183
72.723442
72.235413
72.986458
101.067184
74.537506
73.049477
72.985939
73.328651
73.361977
72.463547
71.771873
72.504684
69.970314
99.078651
77.478127
76.134377
76.641144
74.036980
72.344795
73.601044
71.481247
74.403130
71.322403
99.053131
73.332817
70.156769
71.472389
73.940620
71.359375
70.365105
72.259377
71.143753
75.018753
99.118752
09-12 18:50:23.450 29995-29995/com.ml.national E/shiyang: shiyang  mTracker.init over
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
#if 0
09-14 14:10:36.703 10560-10560/com.ml.national E/shiyang jni: shiyang self time_cost_sum=1296.683228 avg=25.933664
09-14 14:10:36.703 10560-10560/com.ml.national E/shiyang jni: shiyang self time_cost[0]=25.416355
09-14 14:10:36.703 10560-10560/com.ml.national E/shiyang jni: shiyang self time_cost[1]=26.220207
09-14 14:10:36.703 10560-10560/com.ml.national E/shiyang jni: shiyang self time_cost[2]=23.812500
09-14 14:10:36.703 10560-10560/com.ml.national E/shiyang jni: shiyang self time_cost[3]=24.265469
09-14 14:10:36.703 10560-10560/com.ml.national E/shiyang jni: shiyang self time_cost[4]=24.483856
09-14 14:10:36.703 10560-10560/com.ml.national E/shiyang jni: shiyang self time_cost[5]=24.787657
09-14 14:10:36.703 10560-10560/com.ml.national E/shiyang jni: shiyang self time_cost[6]=25.059999
09-14 14:10:36.703 10560-10560/com.ml.national E/shiyang jni: shiyang self time_cost[7]=24.946669
09-14 14:10:36.703 10560-10560/com.ml.national E/shiyang jni: shiyang self time_cost[8]=24.280832
09-14 14:10:36.703 10560-10560/com.ml.national E/shiyang jni: shiyang self time_cost[9]=38.499741
09-14 14:10:36.703 10560-10560/com.ml.national E/shiyang jni: shiyang self time_cost[10]=25.245625
09-14 14:10:36.703 10560-10560/com.ml.national E/shiyang jni: shiyang self time_cost[11]=23.904114
09-14 14:10:36.703 10560-10560/com.ml.national E/shiyang jni: shiyang self time_cost[12]=25.099739
09-14 14:10:36.703 10560-10560/com.ml.national E/shiyang jni: shiyang self time_cost[13]=24.739271
09-14 14:10:36.703 10560-10560/com.ml.national E/shiyang jni: shiyang self time_cost[14]=24.244532
09-14 14:10:36.703 10560-10560/com.ml.national E/shiyang jni: shiyang self time_cost[15]=23.043386
09-14 14:10:36.703 10560-10560/com.ml.national E/shiyang jni: shiyang self time_cost[16]=23.535259
09-14 14:10:36.703 10560-10560/com.ml.national E/shiyang jni: shiyang self time_cost[17]=23.339792
09-14 14:10:36.703 10560-10560/com.ml.national E/shiyang jni: shiyang self time_cost[18]=22.482395
09-14 14:10:36.703 10560-10560/com.ml.national E/shiyang jni: shiyang self time_cost[19]=37.597084
09-14 14:10:36.703 10560-10560/com.ml.national E/shiyang jni: shiyang self time_cost[20]=25.057917
09-14 14:10:36.703 10560-10560/com.ml.national E/shiyang jni: shiyang self time_cost[21]=24.998905
09-14 14:10:36.703 10560-10560/com.ml.national E/shiyang jni: shiyang self time_cost[22]=24.633177
09-14 14:10:36.703 10560-10560/com.ml.national E/shiyang jni: shiyang self time_cost[23]=24.000832
09-14 14:10:36.703 10560-10560/com.ml.national E/shiyang jni: shiyang self time_cost[24]=24.910416
09-14 14:10:36.703 10560-10560/com.ml.national E/shiyang jni: shiyang self time_cost[25]=25.154947
09-14 14:10:36.703 10560-10560/com.ml.national E/shiyang jni: shiyang self time_cost[26]=25.439116
09-14 14:10:36.703 10560-10560/com.ml.national E/shiyang jni: shiyang self time_cost[27]=24.863125
09-14 14:10:36.703 10560-10560/com.ml.national E/shiyang jni: shiyang self time_cost[28]=24.804792
09-14 14:10:36.703 10560-10560/com.ml.national E/shiyang jni: shiyang self time_cost[29]=48.358021
09-14 14:10:36.703 10560-10560/com.ml.national E/shiyang jni: shiyang self time_cost[30]=27.127344
09-14 14:10:36.703 10560-10560/com.ml.national E/shiyang jni: shiyang self time_cost[31]=22.756876
09-14 14:10:36.703 10560-10560/com.ml.national E/shiyang jni: shiyang self time_cost[32]=23.200781
09-14 14:10:36.703 10560-10560/com.ml.national E/shiyang jni: shiyang self time_cost[33]=23.249741
09-14 14:10:36.703 10560-10560/com.ml.national E/shiyang jni: shiyang self time_cost[34]=23.782553
09-14 14:10:36.703 10560-10560/com.ml.national E/shiyang jni: shiyang self time_cost[35]=25.230364
09-14 14:10:36.703 10560-10560/com.ml.national E/shiyang jni: shiyang self time_cost[36]=25.038439
09-14 14:10:36.703 10560-10560/com.ml.national E/shiyang jni: shiyang self time_cost[37]=25.107395
09-14 14:10:36.703 10560-10560/com.ml.national E/shiyang jni: shiyang self time_cost[38]=23.791409
09-14 14:10:36.703 10560-10560/com.ml.national E/shiyang jni: shiyang self time_cost[39]=34.068855
09-14 14:10:36.703 10560-10560/com.ml.national E/shiyang jni: shiyang self time_cost[40]=21.951563
09-14 14:10:36.703 10560-10560/com.ml.national E/shiyang jni: shiyang self time_cost[41]=24.409897
09-14 14:10:36.703 10560-10560/com.ml.national E/shiyang jni: shiyang self time_cost[42]=22.503227
09-14 14:10:36.703 10560-10560/com.ml.national E/shiyang jni: shiyang self time_cost[43]=22.675053
09-14 14:10:36.703 10560-10560/com.ml.national E/shiyang jni: shiyang self time_cost[44]=23.708958
09-14 14:10:36.703 10560-10560/com.ml.national E/shiyang jni: shiyang self time_cost[45]=24.102968
09-14 14:10:36.703 10560-10560/com.ml.national E/shiyang jni: shiyang self time_cost[46]=24.471146
09-14 14:10:36.703 10560-10560/com.ml.national E/shiyang jni: shiyang self time_cost[47]=25.122761
09-14 14:10:36.703 10560-10560/com.ml.national E/shiyang jni: shiyang self time_cost[48]=25.080990
09-14 14:10:36.703 10560-10560/com.ml.national E/shiyang jni: shiyang self time_cost[49]=42.076981
#endif