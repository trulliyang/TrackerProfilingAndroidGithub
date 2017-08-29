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
