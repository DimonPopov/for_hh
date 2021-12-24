#include <stdio.h>

#include "ServerInfo.hpp"



int main()
{

    ServerInfo s;
    
    printf("Hostname: %s\n", s.getHostName().c_str());
    printf("Motherboard model: %s\n", s.getMotherboard().c_str());
    printf("CPU: %s\n", s.getCPU().c_str());
    printf("RAM:%5.1f Gb /%5.1f Gb\n", s.getFreeRam(), s.getTotalRam());
    printf("Trafic: [%7.2f Kb]/[%7.2f Kb]\n", s.getInTrafic(), s.getOutTrafic());
    printf("Release: %s\n", s.getReleace().c_str());


    return 0;
}