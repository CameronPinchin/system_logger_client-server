#include "sys_logger.h"

using namespace std;

Logger::Logger(){
    cout << "Logger created." << endl;
}

Logger::cpu_sys_info Logger::getCpuInfo(){
    Logger::cpu_sys_info cpu;
    SYSTEM_INFO sysInfo;
    GetSystemInfo(&sysInfo);

    cpu.oem_id = sysInfo.dwOemId;
    cpu.num_processors = sysInfo.dwNumberOfProcessors;
    cpu.page_size = sysInfo.dwPageSize;
    cpu.processor_type = sysInfo.dwProcessorType;
    cpu.processor_mask = sysInfo.dwActiveProcessorMask;

    return cpu;
}

Logger::mem_sys_info Logger::getMemInfo(){
    Logger::mem_sys_info mem;
    MEMORYSTATUSEX memInfo;
    memInfo.dwLength = sizeof(memInfo);
    GlobalMemoryStatusEx(&memInfo);

    mem.total_phys_mem = memInfo.ullTotalPhys / DIV;
    mem.avail_phys_mem = memInfo.ullAvailPhys / DIV;
    mem.total_virt_mem = memInfo.ullTotalVirtual / DIV;
    mem.avail_virt_mem = memInfo.ullAvailVirtual / DIV;

    return mem;
}

Logger::dsk_sys_info Logger::getDiskInfo(){
    Logger::dsk_sys_info disk;
    if(!GetDiskFreeSpaceEx(NULL, &disk.avail_bytes, &disk.total_bytes, &disk.total_free_bytes)){
        cout << "Error getting disk space information: %d\n", GetLastError(); 
    }
    return disk;
}

Logger::sys_info Logger::getAllSysInfo(){
    Logger::sys_info system_info;
    system_info.cpu = getCpuInfo();
    system_info.mem = getMemInfo();
    system_info.dsk = getDiskInfo();
    return system_info;
}

