#include<iostream>
#include<chrono>
#include<cstring>
#include<string.h>
#include<stdio.h>
#include<sstream>

using namespace std;

/*
int main(){
	auto inicio = chrono::high_resolution_clock::now();
	Connect_Socket("192.168.43.1", 8080);
	auto fin = chrono::high_resolution_clock::now();
	chrono::duration<double> duracion = fin - inicio;
	cout<<duracion.count()<<endl;
}
*/
//FUNCIONES LOCALES 

//FUNCIONES DE INFORMACION
void Connection_bluetooth();
void Connection_bluetooth_info();
void bluetooth_list();
void bluettoh_info();
void crazy_principal();
void crazy_info();
void os_principal();
void os_info();
void icmp_principal();
void icmp_info();
void arp_info();
void version();
void principal();
void httpGET_scan();
void server_version();
void server_arp();
void banner();
void http_get_status(string vaca);
void print_(double final);
void print_bs(double dab);
void help_function();
//FUNCIONES DE RESULTADO

//FUNCIONES BLUETOOTH
int lister_bluetooth();
int connected_bluetooth(string macaddress);

//FUNCIONES SOCKETS
int Connect_Socket(const char * hostname, int puerto);
int os_function(const char* direccion);
int server_version_const(const char* dir, const char* port);
int getmacaddress(const char* direccionremota);
int icmp_peticion(const char* direccion_remota);
void peticion_https_Get(const char* netinet);
void peticion_http_get(const char* sitioweb);
int main(int argc, char* argv[]){
	banner();
	if(argc==2){
		if(strcmp(argv[1], "--bluetooth-connect")==0){
			bluettoh_info();
			return 0;
		}
		if(strcmp(argv[1], "--list-bluetooth")==0){
			bluetooth_list();
			auto var = chrono::high_resolution_clock::now();
			lister_bluetooth();
			auto var2 = chrono::high_resolution_clock::now();
			chrono::duration<double> duracion = var2 - var;
			print_(duracion.count());
			return 0;
		}
		if(strcmp(argv[1], "--CRAZYMODE")==0){
			crazy_info();
			return 0;
		}
		if(strcmp(argv[1], "--osdetection") == 0){
			os_info();
			return 0;
		}
		if(strcmp(argv[1], "--version")==0){
			version();
			return 0;
		}
		if(strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0){
			help_function();
			return 0;
		}
		if(strcmp(argv[1], "--arp") == 0){
			arp_info();
			return 0;
		}
		if(strcmp(argv[1], "--icmp")==0){
			icmp_info();
			return 0;
		}
		principal();
		auto control = chrono::high_resolution_clock::now();
		for(int x=0; x<10001;x++){
			Connect_Socket(argv[1], x);
		}
		auto final = chrono::high_resolution_clock::now();
		chrono::duration<double> dur = final - control;
		print_bs(dur.count());
	}
	if(argc==3){
		if(strcmp(argv[2], "--bluetooth-connect")==0){
			auto loader = chrono::high_resolution_clock::now();
			Connection_bluetooth();
			connected_bluetooth(argv[1]);
			auto reader = chrono::high_resolution_clock::now();
			chrono::duration<double> esperar = reader - loader;
			print_(esperar.count());
			return 0;
		}
		if(strcmp(argv[2], "--osdetection")==0){
			auto con = chrono::high_resolution_clock::now();
			os_principal();
			os_function(argv[1]);
			auto noc = chrono::high_resolution_clock::now();
			chrono::duration<double> wait = noc-con;
			print_(wait.count());
			return 0;
		}
		if(strcmp(argv[2], "-sV")==0){
			auto oo = chrono::high_resolution_clock::now();
			server_version();
			for(int i=0; i<=10001;i++){
				stringstream bb;
				bb<<i;
				server_version_const(argv[1], bb.str().c_str());
			}
			auto uu = chrono::high_resolution_clock::now();
			chrono::duration<double> controler = uu - oo;
			print_(controler.count());
		}
		if(strcmp(argv[2], "--arp")==0){
			auto ar = chrono::high_resolution_clock::now();
			server_arp();
			getmacaddress(argv[1]);
			auto rp = chrono::high_resolution_clock::now();
			chrono::duration<double> manager = rp - ar;
			print_(manager.count());
		}
		if(strcmp(argv[2], "--icmp")==0){
			auto ic = chrono::high_resolution_clock::now();
			icmp_principal();
			icmp_peticion(argv[1]);
			auto mp = chrono::high_resolution_clock::now();
			chrono::duration<double> feh = mp - ic;
			print_(feh.count());
		}
		if(strcmp(argv[2], "--httpGET")==0){
			auto indi = chrono::high_resolution_clock::now();
			httpGET_scan();
			peticion_http_get(argv[1]);
			auto idni = chrono::high_resolution_clock::now();
			chrono::duration<double> camisa = idni-indi;
			print_(camisa.count());
		}
		if(strcmp(argv[2], "--httpsGET") == 0){
			auto jj = chrono::high_resolution_clock::now();
			httpGET_scan();
			peticion_https_Get(argv[1]);
			auto kk = chrono::high_resolution_clock::now();
			chrono::duration<double> durar = kk - jj;
			print_(durar.count());
		}
	}
	if(argc==4){
		if(strcmp(argv[3], "-p")){
			auto jjj = chrono::high_resolution_clock::now();
			principal();
			Connect_Socket(argv[1], atoi(argv[3]));
			auto xdd = chrono::high_resolution_clock::now();
			chrono::duration<double> dir = xdd-jjj;
			print_(dir.count());
		}
	}
	return 0;
}