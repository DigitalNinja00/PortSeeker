#include<iostream>
#include<sstream>
#include "color.h"

using namespace std;

void Connection_bluetooth(){
    cout<<BLUE<<"Starting BLUETOOTH CONNECT PortSeeker 3.0"<<endl;
}
void Connection_bluetooth_info(){
    cout<<"./prtker <MACADDRESS> --bluetooth-connect"<<endl;
}
void bluetooth_list(){
    cout<<BLUE<<"Starting BLUETOOTH LIST DEVICES PortSeeker 3.0"<<endl;
}
void bluettoh_info(){
    cout<<"./prtker --list-bluetooth"<<endl;
}
void crazy_principal(){
    cout<<BLUE<<"Starting CRAZYMODE PortSeeker 3.0"<<endl;
}
void crazy_info(){
    cout<<"./prtker <IPV4> --CRAZYMODE"<<endl;
}
void os_principal(){
    cout<<BLUE<<"Starting OSDETECTION PortSeeker 3.0"<<endl;
}
void os_info(){
    cout<<"./prtker <IPV4> --osdetection"<<endl;
}
void icmp_principal(){
    cout<<BLUE<<"Starting ICMP PortSeeker 3.0"<<endl;
}
void icmp_info(){
    cout<<"./prtker <IPV4> --icmp"<<endl;
}
void arp_info(){
    cout<<"./prtker <IPV4> --arp"<<endl;
}
void version(){
	cout<<BLUE<<"PortSeeker version 3.0"<<endl;
}
void principal(){
	cout<<BLUE<<"Starting BasicScan PortSeeker 3.0"<<endl;
}
void httpGET_scan(){
	cout<<BLUE<<"Starting HTTPGET PortSeeker 3.0"<<endl;
}
void server_version(){
    cout<<BLUE<<"Starting SERVERVERSION PortSeeker 3.0"<<endl;
}
void server_arp(){
    cout<<BLUE<<"Starting GETMACADRESS PortSeeker 3.0"<<endl;
}
void banner(){
	system("python3 scripts_python/banner.py");
}
void http_get_status(string vaca){
	stringstream log;
	log<<"python3 "<<"scripts_python/post.py -d "<<vaca;
	system(log.str().c_str());
}
void print_(double final){
	cout<<GREEN<<"PortSeeker done: scan in "<<final;;
	cout<<" seconds"<<RESET<<endl;
}
void print_bs(double dab){
	cout<<GREEN<<"PortSeeker done: 10000 ports scanned scan in "<<dab;
	cout<<" seconds"<<RESET<<endl;
}
void help_function(){
    /*
    int http = strcmp(argv[2], "--httpGET");
    int https = strcmp(argv[2], "--httpsGET");
    */
	string var[]={"\033[1;31m!!!!!USE ROOT!!!!!",
	"\033[0m==--Help list==",
    "use : ./prtker <ADDRESS> | Normal scanner",
    "use : ./prtker <ADDRESS> -p <PORT> | Specific port scan",
    "use : ./prtker <ADDRESS> -sV | Port version scan",
    "use : ./prtker <ADDRESS> --httpGET | http get request",
    "use : ./prtker <ADDRESS> --httpsGET | https get requests",
    "use : ./prtker <ADDRESS> --arp | get macaddress",
    "use : ./prtker <ADDRESS> --icmp | icmp request",
    "use : ./prtker <ADDRESS> --osdetection | OS Detection",
    "use : ./prtker --list-bluetooth | list bluetooth devices",
    "use : ./prtker <MACADDRESS> --bluetooth-connect | Connection Bluetooth"
    };
	size_t main = sizeof(var)/sizeof(string);
	for(int i=0; i<main;i++){
		cout<<var[i]<<endl;
	}
}