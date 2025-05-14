#ifndef SYS_LOGGER_H
#define SYS_LOGGER_H

#include <iostream>
#include <windows.h>
#include <stdio.h>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <ctime>
#include <string>

using namespace std;

#define DIV 1073741824

class Logger {
    
    public:
        
        struct cpu_sys_info{
            int oem_id;
            int num_processors;
            int page_size;
            int processor_type;
            int processor_mask;
        };

        struct mem_sys_info{
            int current_mem_load;
            int total_phys_mem;
            int avail_phys_mem;
            int total_virt_mem;
            int avail_virt_mem;
        };

        struct dsk_sys_info{
            int total_bytes;
            int avail_bytes;
            int total_free_bytes;
        };

        struct sys_info{
            Logger::cpu_sys_info cpu;
            Logger::mem_sys_info mem;
            Logger::dsk_sys_info dsk;
            char log_time[64];
        };

        Logger();
        string getTimeStamp();
        cpu_sys_info getCpuInfo();
        mem_sys_info getMemInfo();
        dsk_sys_info getDiskInfo();
        sys_info getAllSysInfo();

    private:
        
};

#endif