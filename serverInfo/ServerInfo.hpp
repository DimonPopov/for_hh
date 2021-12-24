#pragma once


#include <fstream>
#include <sstream>
#include <vector>
#include <iterator>

#include <sys/sysinfo.h>
#include <sys/utsname.h>
#include <limits.h>
#include <unistd.h>

namespace dataSize{
    constexpr double Kb = 1024;
    constexpr double Mb = Kb * 1024;
    constexpr double Gb = Mb * 1024;
}




class ServerInfo 
{
private:
    std::string hostName;
    std::string release;
    std::string CPU;
    std::string motherboard;
    double totalRam;
    double freeRam;
    double inTrafic;
    double outTrafic;
public:
    ServerInfo();
    std::string getHostName() const;
    std::string getCPU() const;
    std::string getReleace() const;
    std::string getMotherboard() const;
    double getTotalRam() const;
    double getFreeRam() const;
    double getInTrafic() const;
    double getOutTrafic() const;
};


ServerInfo::ServerInfo() : inTrafic(0), outTrafic(0)
{
    // hostname
    char name[HOST_NAME_MAX + 1];
    gethostname(name, HOST_NAME_MAX + 1);
    hostName = name;

    // RAM
    struct sysinfo si;
    if(sysinfo(&si) != -1)
    {
        totalRam = si.totalram / dataSize::Gb;
        freeRam = si.freeram / dataSize::Gb;
    }

    // release version
    struct utsname di;
    if(uname(&di) != -1)
    {
        release = di.version;
    }

    // CPU
    std::ifstream f;
    f.open("/proc/cpuinfo");
    if(f.is_open()){
        while(getline(f, CPU))
        {
            if(CPU.find("model name") != std::string::npos)
            {
                CPU.erase(0, CPU.find(":") + 2);
                break;
            }
        }
    }
    f.close();

    // motherboard
    std::string boardVendor;
    std::string boardName;
    f.open("/sys/devices/virtual/dmi/id/board_vendor");
    if(f.is_open()){
        getline(f, boardVendor);
    }
    f.close();
    f.open("/sys/devices/virtual/dmi/id/board_name");
    if(f.is_open()){
        getline(f, boardName);
    }
    f.close();

    motherboard = boardVendor + ' ' + boardName;

    // traffic
    f.open("/proc/net/dev");
    std::string str;

    if(f.is_open()){
        while(getline(f, str))
        {            
            if(str.find(":") != std::string::npos)
            {
                str.erase(0, str.find(":") + 1);

                std::stringstream strStream(str);
                std::vector<u_int32_t> vec;
                vec.reserve(16);

                std::copy(std::istream_iterator<u_int32_t>(strStream), {}, back_inserter(vec));

                inTrafic += vec[0];
                outTrafic += vec[8];
            }
            
        }
        inTrafic  /= dataSize::Kb;
        outTrafic /= dataSize::Kb;
    }
    f.close();
}



std::string ServerInfo::getHostName() const {
    return hostName;
}

std::string ServerInfo::getCPU() const {
    return CPU;
}

std::string ServerInfo::getMotherboard() const {
    return motherboard;
}

std::string ServerInfo::getReleace() const {
    return release;
}

double ServerInfo::getFreeRam() const {
    return freeRam;
}

double ServerInfo::getTotalRam() const {
    return totalRam;
}

double ServerInfo::getInTrafic() const {
    return inTrafic;
}

double ServerInfo::getOutTrafic() const {
    return outTrafic;
}