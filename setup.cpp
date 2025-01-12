#include<iostream>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<cstdlib>
#include<netdb.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<chrono>
#include<cmath>
#include<iomanip>
#include<sstream>
#include "httplib.h"
#include <curl/curl.h>
#include "color.h"

using namespace std;
using namespace chrono;
int templa(const char* host, int number){
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock == -1){
        cout<<"Error creating socket"<<endl;
    }
    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(number);
    serverAddress.sin_addr.s_addr = inet_addr(host);

    int result = connect(sock, (sockaddr*)&serverAddress, sizeof(serverAddress));
    if(result==-1){
        close(sock);
        return 1;
    }
    return 0;
}

int basic_scan(const char* host, int number, const char* service){
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock == -1){
    	cout<<"Error creating socket"<<endl;
    }
    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(number);
    serverAddress.sin_addr.s_addr = inet_addr(host);

    int result = connect(sock, (sockaddr*)&serverAddress, sizeof(serverAddress));
    if(result==-1){
    	close(sock);
    	return 1;
    }
    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<" "<<GREEN<<service<<endl;
    return 0;
}
int detect_service(const char* hostname, const char* port){
	struct addrinfo hints, *res;
    int socket_connection;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC; 
    hints.ai_socktype = SOCK_STREAM;

    if (getaddrinfo(hostname, port, &hints, &res) != 0) {
        return 1;
    }
    if ((socket_connection = socket(res->ai_family, res->ai_socktype, res->ai_protocol)) == -1) {
        freeaddrinfo(res);
        return 1;
    }
    if (connect(socket_connection, res->ai_addr, res->ai_addrlen) == -1) {
        close(socket_connection);
        freeaddrinfo(res);
        return 1;
    }
    const char* request = "GET / HTTP/1.1\r\nHost: localhost\r\n\r\n";
    if (send(socket_connection, request, strlen(request), 0) == -1) {
        close(socket_connection);
        freeaddrinfo(res);
        return 1;
    }
    char buffer[1024];
    ssize_t bytes_received = recv(socket_connection, buffer, sizeof(buffer) - 1, 0);
    if (bytes_received == -1) {
        close(socket_connection);
        freeaddrinfo(res);
        return 1;
    }
    buffer[bytes_received] = '\0';
    int port_num = std::stoi(port);
    struct servent* service = getservbyport(htons(port_num), "tcp");
    if (service != nullptr) {
        int colo = stoi(port);
        basic_scan(hostname, colo, service->s_name);
        //std::cout << "Servicio: " << service->s_name << ", Puerto: " << port << std::endl;
    } else {
        int oloc = stoi(port);
        basic_scan(hostname, oloc, "unknown");
    }
    close(socket_connection);
    freeaddrinfo(res);

    return 0;
}

class Mess{
    private:
    	int numero;
    public:
    	void help_funtion(){
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
            "use : ./prtker <ADDRESS> --httpsGET | https get requests"
            "use : ./prtker <ADDRESS> --arp | get macaddress",
            "use : ./prtker <ADDRESS> --icmp | icmp request"
    	};
    		size_t main = sizeof(var)/sizeof(string);
    		for(int i=0; i<main;i++){
    			cout<<var[i]<<endl;
    		}
    	}
        void icmp_principal(){
            cout<<BLUE<<"Starting ICMP PortSeeker 1.8"<<endl;
        }
        void icmp_info(){
            cout<<"./prtker <IPV4> --icmp"<<endl;
        }
        void arp_info(){
            cout<<"./prtker <IPV4> --arp"<<endl;
        }
    	void version(){
    		cout<<BLUE<<"PortSeeker version 1.8"<<endl;
    	}
    	void principal(){
    		cout<<BLUE<<"Starting BasicScan PortSeeker 1.8"<<endl;
    	}
    	void httpGET_scan(){
    		cout<<BLUE<<"Starting HTTPGET PortSeeker 1.8"<<endl;
    	}
        void server_version(){
            cout<<BLUE<<"Starting SERVERVERSION PortSeeker 1.8"<<endl;
        }
        void server_arp(){
            cout<<BLUE<<"Starting GETMACADRESS PortSeeker 1.8"<<endl;
        }
    	void banner(){
    		system("python3 scripts_python/banner.py");
    	}
    	void http_get_status(string vaca){
    		stringstream log;
    		log<<"python3 "<<"scripts_python/post.py -d "<<vaca;
    		system(log.str().c_str());
    	}

};

size_t WriteCallback(void* contents, size_t size, size_t nmemb, string* response){
	size_t totalSize = size * nmemb;
    response->append((char*)contents, totalSize);
    return totalSize;
}

class Connections{
private:
	int var;
	int var2;
public:
    int icmp_peticion(const char* direccion_remota){
        stringstream V_ar;
        V_ar<<"python3 scripts_python/icmp.py "<<direccion_remota;
        system(V_ar.str().c_str());
        return 0;
    }
	int getmacaddress(const char* direccionremota){
		stringstream comando;
    	comando<<"echo \"\\e[0;31mmac address: \\e[1;33m$(/usr/sbin/arping -c 1 "<<direccionremota<<" | grep \"from\" | awk \'{print $4}\')\"";
    	int verdad = system(comando.str().c_str());
    	if(verdad!=0){
    		cout<<"Error obtaining MAC address"<<endl;
    	}
    	return 0;
	}
	void peticion_http_get(const char* sitioweb){
    		httplib::Client client(sitioweb);
    		auto response = client.Get("/");
    		if(response && response->status == 200){
    			cout<<"Response : "<<response->body<<endl;
    		}else{
    			cout<<"Error sending request"<<endl;
    		}
    	}
    void peticion_https_Get(const char* netinet){
    		CURL* curl;
    		CURLcode res;
    		string response;
    		curl_global_init(CURL_GLOBAL_DEFAULT);
    		curl = curl_easy_init();
    		if(curl){
    			curl_easy_setopt(curl, CURLOPT_URL, netinet);
    			curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    			curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
    			res = curl_easy_perform(curl);
    			if(res!=CURLE_OK){
    				cout<<"Error on petition: "<<curl_easy_strerror(res)<<endl;
    			}else{
    				cout<<"Response: \n"<<response<<endl;
    			}
    			curl_easy_cleanup(curl);

    		}
    		curl_global_cleanup();
    	}
};	

int char_intconverter(const char* str){
	int numero_a = 0;
	int indice = 0;
	bool negativo = false;
	if(str[indice]=='-'){
		negativo = true;
		indice++;
	}
	while (str[indice] != '\0'){
		numero_a = numero_a * 10 +(str[indice] - '0');
		indice++;
	}

	if(negativo){
		numero_a = -numero_a;
	}
	return numero_a;
}
int main(int argc, char* argv[]){
//int detect_service(const char* hostname, const char* port){
    //detect_service("192.168.8.136", "4000");
    if(argc==2){
        if(strcmp(argv[1], "--version") == 0 ){
            Mess colorama;
            Mess* pip = &colorama;
            pip->version();
            return 0;
        }
        if(strcmp(argv[1], "--help") == 0 || strcmp(argv[1], "-h") == 0){
            Mess locali;
            Mess* loca = & locali;
            loca -> help_funtion();
            return 0;
        }
        if(strcmp(argv[1], "--arp") == 0){
            Mess local;
            Mess* lol = &local;
            lol->arp_info();
            return 0;
        }
        if(strcmp(argv[1], "--icmp") == 0){
            Mess _UPDATED_;
            Mess* __LOADER__ = &_UPDATED_;
            __LOADER__->icmp_info();
        }
        auto peticionGET = steady_clock::now();
        Mess ban;
        Mess* banner = &ban;
        banner->banner();
        Mess glue;
        Mess* paper = &glue;
        paper->principal();
        Connections pp;
        Connections* pptx = &pp;
        pptx->getmacaddress(argv[1]);
        for(int i=0;i<=10000;i++){
            string str = to_string(i);
            const char* char_app = str.c_str();
            detect_service(argv[1], char_app);
        }
        auto peticionGETFinal = steady_clock::now();
        duration<double> duration = peticionGETFinal - peticionGET;
        double httpget = duration.count();
        double factore = pow(10, 2);
        double decimal_a = round(httpget * factore) / factore;
        cout<<GREEN<<"PortSeeker done: scan in "<<fixed<<setprecision(2)<<decimal_a;
        cout<<" seconds"<<RESET<<endl;
    }
    if(argc==3){
        int very = strcmp(argv[2], "-p");
        int nice = strcmp(argv[2], "-sV");
        int http = strcmp(argv[2], "--httpGET");
        int https = strcmp(argv[2], "--httpsGET");
        int arp = strcmp(argv[2], "--arp");
        int icmp = strcmp(argv[2], "--icmp");
        if(icmp==0){
            auto _CONTROL_ = steady_clock::now();
            Mess _BANNER_; Mess* _BAN_ = &_BANNER_;
            _BAN_->banner();
            Mess Ratman; Mess* rATMAN = & Ratman;
            rATMAN->icmp_principal();
            Connections upx;
            Connections* xpx = &upx;
            xpx->icmp_peticion(argv[1]);
            auto FINAL = steady_clock::now();
            duration<double> duration = FINAL - _CONTROL_;
            double argget = duration.count();
            double factor = pow(10, 2);
            double dimal = round(argget * factor) / factor;
            cout<<GREEN<<"PortSeeker done: scan in "<<fixed<<setprecision(2)<<dimal;
            cout<<" seconds"<<RESET<<endl;
        }
        if(arp==0){
            auto controlador = steady_clock::now();
            //ARP REQUESTS
            Mess banner;
            Mess* bann = &banner;
            bann->banner();
            Mess tar;
            Mess* rat = &tar;
            rat->server_arp();
            Connections _A_;
            Connections* _ARP = &_A_;
            _ARP->getmacaddress(argv[1]);
            auto final = steady_clock::now();
            duration<double> duration = final - controlador;
            double argget = duration.count();
            double factor = pow(10, 2);
            double dimal = round(argget * factor) / factor;
            cout<<GREEN<<"PortSeeker done: scan in "<<fixed<<setprecision(2)<<dimal;
            cout<<" seconds"<<RESET<<endl;
        }
        if(very==0){
            cout<<"Specify a port for -p"<<endl;
        }
        if(nice==0){
            auto peticionGET = steady_clock::now();
            Mess ban1;
            Mess* ban11 = &ban1;
            ban11->banner();
            Mess k1;
            Mess* k11 = &k1;
            k11->server_version();
            Connections _0;
            Connections* _0_ = &_0;
            _0_->getmacaddress(argv[1]);

            for(int x=0; x<=10000;x++){
                int point = templa(argv[1], x);
                if(point==0){
                     stringstream con;
                     con<<"bash ./bash_scripts/local.sh "<<argv[1]<<" "<<x;
                     system(con.str().c_str());
                }
            }
            auto peticionGETFinal = steady_clock::now();
            duration<double> duration = peticionGETFinal - peticionGET;
            double httpget = duration.count();
            double factore = pow(10, 2);
            double decimal_a = round(httpget * factore) / factore;
            cout<<GREEN<<"PortSeeker done: scan in "<<fixed<<setprecision(2)<<decimal_a;
            cout<<" seconds"<<RESET<<endl;
        }
        if(http==0){
            //void peticion_http_get(const char* sitioweb){
            auto peticionGET = steady_clock::now();
            Mess log;
            Mess* gol = &log;
            gol->banner();
            Mess co_;
            Mess* _co = &co_;
            _co->httpGET_scan();
            Connections psr;
            Connections* rsp = &psr;
            rsp->peticion_http_get(argv[1]);
            auto peticionGETFinal = steady_clock::now();
            duration<double> duration = peticionGETFinal - peticionGET;
            double httpget = duration.count();
            double factore = pow(10, 2);
            double decimal_a = round(httpget * factore) / factore;
            cout<<GREEN<<"PortSeeker done: scan in "<<fixed<<setprecision(2)<<decimal_a;
            cout<<" seconds"<<RESET<<endl;
        }
        if(https==0){
            //void peticion_https_Get(const char* netinet)
            auto peticionGET = steady_clock::now();
            Mess man;
            Mess* nam = &man;
            nam->banner();
            Connections vv;
            Connections* cc = &vv;
            cc->peticion_https_Get(argv[1]);
            auto peticionGETFinal = steady_clock::now();
            duration<double> duration = peticionGETFinal - peticionGET;
            double httpget = duration.count();
            double factore = pow(10, 2);
            double decimal_a = round(httpget * factore) / factore;
            cout<<GREEN<<"PortSeeker done: scan in "<<fixed<<setprecision(2)<<decimal_a;
            cout<<" seconds"<<RESET<<endl;
        }


    }
    if(argc==4){
        int hh = strcmp(argv[2], "-p");
        if(hh==0){
            auto peticionGET = steady_clock::now();
            Mess ll;Mess* kl=&ll;
            kl->banner();
            Mess maine;Mess* eniam=&maine;
            eniam->principal();
            //int detect_service(const char* hostname, const char* port)
            detect_service(argv[1], argv[3]);
            stringstream corr;
            corr<<"bash ./bash_scripts/local.sh "<<argv[1]<<" "<<argv[3];
            system(corr.str().c_str());
            auto peticionGETFinal = steady_clock::now();
            duration<double> duration = peticionGETFinal - peticionGET;
            double httpget = duration.count();
            double factore = pow(10, 2);
            double decimal_a = round(httpget * factore) / factore;
            cout<<GREEN<<"PortSeeker done: scan in "<<fixed<<setprecision(2)<<decimal_a;
            cout<<" seconds"<<RESET<<endl;

        }

    }
    return 0;
}