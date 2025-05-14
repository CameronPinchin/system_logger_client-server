#include "sys_logger.h"

using namespace std;

Logger::Logger(){}

string Logger::getTimeStamp(){
    auto t = time(nullptr);
    auto tm = *localtime(&t);
    ostringstream oss;
    oss << put_time(&tm, "%d-%m-%Y %H-%M-%S");
    string s = oss.str();

    return s;
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

    mem.current_mem_load = memInfo.dwMemoryLoad;
    mem.total_phys_mem = memInfo.ullTotalPhys / DIV;
    mem.avail_phys_mem = memInfo.ullAvailPhys / DIV;
    mem.total_virt_mem = memInfo.ullTotalVirtual / DIV;
    mem.avail_virt_mem = memInfo.ullAvailVirtual / DIV;
   
    return mem;
}

Logger::dsk_sys_info Logger::getDiskInfo(){
    Logger::dsk_sys_info disk;
    ULARGE_INTEGER avail_bytes, total_bytes, free_bytes;
    if(!GetDiskFreeSpaceEx(NULL, &avail_bytes, &total_bytes, &free_bytes)){
        cout << "Error getting disk space information: %d\n", GetLastError(); 
    }
    disk.avail_bytes = static_cast<UINT64>(avail_bytes.QuadPart) / DIV;
    disk.total_bytes = static_cast<UINT64>(total_bytes.QuadPart) / DIV;
    disk.total_free_bytes = static_cast<UINT64>(free_bytes.QuadPart) / DIV;

    return disk;
}

Logger::sys_info Logger::getAllSysInfo(){
    Logger::sys_info system_info;
    system_info.cpu = getCpuInfo();
    system_info.mem = getMemInfo();
    system_info.dsk = getDiskInfo();
    strncpy(system_info.log_time, getTimeStamp().c_str(), sizeof(system_info.log_time));

    return system_info;
}

