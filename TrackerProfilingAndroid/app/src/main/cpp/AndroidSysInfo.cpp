//
// Created by SHI.yang on 2017/8/29.
//


#include "AndroidSysInfo.h"

#define  LOGW(x...)  __android_log_print(ANDROID_LOG_ERROR,"ANDROIDSYSINFO",x)



AndroidMemInfo::AndroidMemInfo()

{

    m_memFile = -1;

    ullTotalPhys = 0;

    ullAvailPhys = 0;

}



AndroidMemInfo::~AndroidMemInfo()

{

}



void AndroidMemInfo::GetAvailPhys()

{

    m_memFile = open("/proc/meminfo", O_RDONLY);



    if (m_memFile < 0)

    {

        LOGW("shiyang Unable to open /proc/meminfo");

    }



    char buffer[256];

    const int len = read(m_memFile, buffer, sizeof(buffer)-1);

    close(m_memFile);



    if (len < 0)

    {

        LOGW("shiyang Unable to read /proc/meminfo");

    }

    buffer[len] = 0;



    int numFound = 0;



    static const char* const sums[] = { "MemFree:", "Cached:", NULL };

    static const int sumsLen[] = { (int)strlen("MemFree:"), (int)strlen("Cached:"), NULL };



    char* p = buffer;

    while (*p && numFound < 2)

    {

        int i = 0;

        while (sums[i])

        {

            if (strncmp(p, sums[i], sumsLen[i]) == 0)

            {

                p += sumsLen[i];

                while (*p == ' ') p++;

                char* num = p;

                while (*p >= '0' && *p <= '9') p++;

                if (*p != 0)

                {

                    *p = 0;

                    p++;

                    if (*p == 0) p--;

                }

                ullAvailPhys += atoll(num) * 1024;

                numFound++;

                break;

            }

            i++;

        }

        p++;

    }

}



void AndroidMemInfo::GetTotalPhys()

{

    m_memFile = open("/proc/meminfo", O_RDONLY);



    if (m_memFile < 0)

    {

        LOGW("shiyang Unable to open /proc/meminfo");

    }



    char buffer[256];

    const int len = read(m_memFile, buffer, sizeof(buffer)-1);

    close(m_memFile);



    if (len < 0)

    {

        LOGW("shiyang Unable to read /proc/meminfo");

    }



    buffer[len] = 0;



    static const char* const sums[] = { "MemTotal:", NULL };

    static const int sumsLen[] = { (int)strlen("MemTotal:"), NULL };



    char* p = buffer;

    while (*p )

    {

        int i = 0;

        while (sums[i])

        {

            if (strncmp(p, sums[i], sumsLen[i]) == 0)

            {

                p += sumsLen[i];

                while (*p == ' ') p++;

                char* num = p;

                while (*p >= '0' && *p <= '9') p++;

                if (*p != 0)

                {

                    *p = 0;

                    p++;

                    if (*p == 0) p--;

                }

                ullTotalPhys += atoll(num) * 1024;

                break;

            }

            i++;

        }

        p++;

    }

}



AndroidCpuUsage::AndroidCpuUsage()

{

    timerclear(&m_lasttime);

    timerclear(&m_nowtime);



    m_lastproc.utime = 0;

    m_lastproc.stime = 0;

    m_lastproc.cutime = 0;

    m_lastproc.cstime = 0;



    m_nowproc.utime = 0;

    m_nowproc.stime = 0;

    m_nowproc.cutime = 0;

    m_nowproc.cstime = 0;

}



void AndroidCpuUsage::getProcCPUStat(struct systemCPUdata *proc, int pid)

{

    FILE *file;

    unsigned long itemp;

    char ctemp;

    char line[255];



    sprintf(line, "/proc/%d/stat", pid);

    file = fopen(line, "r");

    if (file == NULL)

    {

        LOGW("AndroidCpuUsage Error: process not found!\n");

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



DWORD AndroidCpuUsage::GetUsedCpu()

{



    gettimeofday(&m_nowtime, NULL);



    getProcCPUStat(&m_nowproc,getpid());

    DWORD percent = 0;



    // for the first time ,it's always return 0;

    if ( m_lasttime.tv_sec == 0 && m_lasttime.tv_usec == 0)

    {

        percent = 0;

    }

    else

    {

        DWORD usedtime = m_nowproc.utime + m_nowproc.stime - m_lastproc.utime - m_lastproc.stime;

        percent = usedtime/(m_nowtime.tv_sec - m_lasttime.tv_sec);

    }

    m_lastproc.utime = m_nowproc.utime;

    m_lastproc.stime = m_nowproc.stime;

    m_lastproc.cutime = m_nowproc.cutime;

    m_lastproc.cstime = m_nowproc.cstime;



    m_lasttime.tv_sec = m_nowtime.tv_sec;

    m_lasttime.tv_usec = m_nowtime.tv_usec;



    char tchBuf[128] = "\0";

    memset(tchBuf, 0, sizeof(tchBuf));

    snprintf(tchBuf, sizeof(tchBuf), "AndroidCpuUsage GetUsedCpu:%d",percent);



    LOGW("shiyang  %s", tchBuf);

    return percent;

}