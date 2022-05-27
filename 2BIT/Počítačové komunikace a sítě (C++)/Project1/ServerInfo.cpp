/**
 * Project: Vytvoření serveru komunikujícího prostřednictvím protokolu HTTP
 *
 * File:     ServerInfo.cpp
 * Subject:  IPK 2022
 *
 * @author:  Vladislav Mikheda  xmikhe00
 */

#include "ServerInfo.h"
#include <unistd.h>
#include <fstream>
using namespace std;

/** sets the positions for the split line that will be needed to get the CPU load */
 void ServerInfo::position_setting(){
     ifstream in(file_proc_stat);
     string cpu_info;
     getline(in,cpu_info);
     pos_first_sub = cpu_info.find(' ') + 1;
     pos_second_sub = cpu_info.find(' ', pos_first_sub + 1);
     pos_third_sub = cpu_info.find(' ', pos_second_sub + 1);
     pos_fourth_sub = cpu_info.find(' ', pos_third_sub + 1);
     pos_fifth_sub = cpu_info.find(' ', pos_fourth_sub + 1);
     pos_sixth_sub = cpu_info.find(' ', pos_fifth_sub + 1);
     pos_seventh_sub = cpu_info.find(' ', pos_sixth_sub + 1);
     pos_eighth_sub = cpu_info.find(' ', pos_seventh_sub + 1);
     pos_ninth_sub = cpu_info.find(' ', pos_eighth_sub + 1);

     len_user = pos_second_sub - (pos_first_sub + 1);
     len_nice = pos_third_sub - (pos_second_sub + 1);
     len_system = pos_fourth_sub - (pos_third_sub + 1);
     len_idle = pos_fifth_sub - (pos_fourth_sub + 1);
     len_iowait = pos_sixth_sub - (pos_fifth_sub + 1);
     len_irq = pos_seventh_sub - (pos_sixth_sub + 1);
     len_softirq = pos_eighth_sub - (pos_seventh_sub + 1);
     len_steal  = pos_ninth_sub - (pos_eighth_sub + 1);
 }

/** sets the load on the cpu, first request */
void ServerInfo::set_load(){
     ifstream in(file_proc_stat);
     string cpu_info;
     getline(in,cpu_info);
     user = cpu_info.substr(pos_first_sub+1, len_user);
     nice = cpu_info.substr(pos_second_sub+1, len_nice);
     system = cpu_info.substr(pos_third_sub+1, len_system);
     idle = cpu_info.substr(pos_fourth_sub+1, len_idle);
     iowait = cpu_info.substr(pos_fifth_sub+1, len_iowait);
     irq = cpu_info.substr(pos_sixth_sub+1, len_irq);
     softirq = cpu_info.substr(pos_seventh_sub+1, len_softirq);
     steal = cpu_info.substr(pos_eighth_sub+1, len_steal);
}

/** sets the load on the cpu, second request */
 void ServerInfo::set_prev_load(){
     ifstream in(file_proc_stat);
     string cpu_info;
     getline(in,cpu_info);
     prevuser = cpu_info.substr(pos_first_sub + 1, len_user);
     prevnice = cpu_info.substr(pos_second_sub + 1, len_nice);
     prevsystem = cpu_info.substr(pos_third_sub + 1, len_system);
     previdle = cpu_info.substr(pos_fourth_sub + 1, len_idle);
     previowait = cpu_info.substr(pos_fifth_sub + 1, len_iowait);
     previrq = cpu_info.substr(pos_sixth_sub + 1, len_irq);
     prevsoftirq = cpu_info.substr(pos_seventh_sub + 1, len_softirq);
     prevsteal = cpu_info.substr(pos_eighth_sub + 1, len_steal);
}


ServerInfo::ServerInfo(){
     file_proc_stat = "/proc/stat";
}

/** finds and returns the CPU name */
string ServerInfo::get_cpu_name(){

    string cpu_info;
    ifstream in("/proc/cpuinfo");

    while (getline(in,cpu_info)){
        if(string::npos != cpu_info.find("model name")){
            break;
        }
    }
    int spase = 2;
    int pos_start = (int)cpu_info.find(':') + spase;
    int len_cpu_name =(int) (cpu_info.find('\n') - (cpu_info.find(':') + 1));

    return cpu_info.substr(pos_start,len_cpu_name);
 }

 //return host name
 string ServerInfo::get_host_name(){
     const int max_len_hostname = 255;
     char hostname[max_len_hostname];
     gethostname(hostname,max_len_hostname);
     return (string) hostname;
 }

/**
 * find cpu load in /proc/stat by algorithm
 * return cpu load
 */
 string ServerInfo::get_cpu_load(){

     position_setting();
     set_load();
     sleep(1);
     set_prev_load();

     long long prevIdle =  stoll(previdle)  + stoll(previowait);
     long long Idle =  stoll(idle)  + stoll(iowait);

     long long prevNonIdle =  stoll(prevuser)  + stoll(prevnice) + stoll(prevsystem) + stoll(prevnice) + stoll(previrq) + stoll(prevsoftirq) + stoll(prevsteal);
     long long NonIdle =  stoll(user)  + stoll(nice) + stoll(system) + stoll(prevnice)+ stoll(irq) + stoll(softirq) + stoll(steal);

     long long prevTotal = prevIdle + prevNonIdle;
     long long Total = Idle + NonIdle;

     long long totald = Total - prevTotal;
     long long idled = Idle - prevIdle;

    return to_string(((totald - idled)*100 / totald)).append("%");
}


