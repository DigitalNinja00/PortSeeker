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
using namespace std;
using namespace chrono;
//int funtions

const bool kk = false;


class Mess{
    private:
    	int numero;
    public:
    	void help_funtion(){
    		string var[]={"\033[1;31m!!!!!USE ROOT!!!!!",
    		"\033[0m==USO DE COMANDOS==",
    		"-sP | prtker -sP <ip> <port>",
    		"-Bs | prtker -Bs <ip>",
    		"-httpGET | prtker -httpGET <ip or direction>",
    		"-httpsGET | prtker -httpsGET <ip or direction>",
    		"==INFO DE COMANDOS==",
    		"-Bs",
    		"Hace un escaneo basico de puertos, manda peticiones TCP,",
    		"desde el puerto 1 hasta el 10,000",
    		"-sP",
    		"Escaneo de puerto especifico, funciona para escanear un puerto",
    		"especifico, manda una sola solicitud TCP/IP",
    		"-httpGET | funciona para hacer peticiones http get a",
    		"servidores http no funciona para https",
    		"-httpsGET | funciona para hacer peticiones https get a",
    		"servidores https y http"
    	};
    		size_t main = sizeof(var)/sizeof(string);
    		for(int i=0; i<main;i++){
    			cout<<var[i]<<endl;
    		}
    	}
    	void version(){
    		cout<<"PortSeeker version 1.3"<<endl;
    	}
    	void principal(){
    		cout<<"Starting BasicScan PortSeeker 1.3"<<endl;;
    	}
    	void httpGET_scan(){
    		cout<<"Starting HTTPGET PortSeeker 1.3"<<endl;
    	}

};

//verificadores

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
size_t WriteCallback(void* contents, size_t size, size_t nmemb, string* response){
	size_t totalSize = size * nmemb;
    response->append((char*)contents, totalSize);
    return totalSize;
}

class Enchufe{
    public:
    	int gethostbyaddr(const char* remoteipaddress){
    		struct addrinfo hints, *res;
    		memset(&hints, 0, sizeof(hints));
    		hints.ai_family = AF_UNSPEC;
    		hints.ai_socktype = SOCK_STREAM;

    		if(getaddrinfo(remoteipaddress, NULL, &hints, &res) != 0){
    			cout<<"Error al obtener la direccion"<<endl;
    			return 1;
    		}
    		char hostname[NI_MAXHOST];
    		if(getnameinfo(res->ai_addr, res->ai_addrlen, hostname, sizeof(hostname), NULL, 0, 0) != 0){
    			cout<<"Error al obtener hostname"<<endl;
    			return 1;
    		}
    		cout<<"Hostname: "<<remoteipaddress<<" "<<hostname<<endl;
    		return 0;
    	}
    	int getmacaddress(const char* direccionremota){
    		//geta¡macfuntion
    		stringstream comando;
    		comando<<"echo \"direccion mac: $(/usr/sbin/arping -c 1 "<<direccionremota<<" | grep \"from\" | awk \'{print $4}\')\"";
    		int verdad = system(comando.str().c_str());
    		if(verdad!=0){
    			cout<<"Error al obtener direccion mac"<<endl;
    		}
    		return 0;
    	}
    	void peticion_http_get(const char* sitioweb){
    		httplib::Client client(sitioweb);
    		auto response = client.Get("/");
    		if(response && response->status == 200){
    			cout<<"Respuesta : "<<response->body<<endl;
    		}else{
    			cout<<"Error al enviar solicitud"<<endl;
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
    				cout<<"Error en peticion: "<<curl_easy_strerror(res)<<endl;
    			}else{
    				cout<<"Respuesta: \n"<<response<<endl;
    			}
    			curl_easy_cleanup(curl);

    		}
    		curl_global_cleanup();
    	}


    	int basic_scan(char host[], int number){
    		int sock = socket(AF_INET, SOCK_STREAM, 0); //se crea un socket
    		if(sock == -1){
    			cout<<"Error al crear socket"<<endl;
    		}
    		//configuracion de la direccion del servidor
    		sockaddr_in serverAddress;
    		serverAddress.sin_family = AF_INET;
    		serverAddress.sin_port = htons(number);
    		serverAddress.sin_addr.s_addr = inet_addr(host);

    		//se establece la conexion
    		int result = connect(sock, (sockaddr*)&serverAddress, sizeof(serverAddress));
    		if(result==-1){
    			close(sock);
    			return 1;
    		}

    		//conexion establecida
    		//cout<<"!->TCP|open!|"<<number<<endl;//host number
    		//function_read_name_tcp(number);
    		//cout<<"!->TCP \\ open!  "<<number<<"  domain"<<endl;
    		
    		if(number==1){
    			cout<<"!->TCP \\ open!  "<<number<<"  tcpmux"<<endl;
    		}
    		if(number==5){
    			cout<<"!->TCP \\ open!  "<<number<<"  rje"<<endl;
    		}
    		if(number==7){
    			cout<<"!->TCP \\ open!  "<<number<<"  echo"<<endl;
    		}
    		if(number==9){
    			cout<<"!->TCP \\ open!  "<<number<<"  discard"<<endl;
    		}
    		if(number==11){
    			cout<<"!->TCP \\ open!  "<<number<<"  systat"<<endl;
    		}
    		if(number==13){
    			cout<<"!->TCP \\ open!  "<<number<<"  daytime"<<endl;
    		}
    		if(number==17){
    			cout<<"!->TCP \\ open!  "<<number<<"  qotd"<<endl;
    		}
    		if(number==18){
    			cout<<"!->TCP \\ open!  "<<number<<"  msp"<<endl;
    		}
    		if(number==19){
    			cout<<"!->TCP \\ open!  "<<number<<"  chargen"<<endl;
    		}
    		if(number==20){
    			cout<<"!->TCP \\ open!  "<<number<<"  ftpS-data"<<endl;
    		}
    		if(number==21){
    			cout<<"!->TCP \\ open!  "<<number<<"  ftp-control"<<endl;
    		}
    		if(number==22){
    			cout<<"!->TCP \\ open!  "<<number<<"  ssh"<<endl;
    		}
    		if(number==23){
    			cout<<"!->TCP \\ open!  "<<number<<"  telnet"<<endl;
    		}
    		if(number==25){
    			cout<<"!->TCP \\ open!  "<<number<<"  smtp"<<endl;
    		}
    		if(number==37){
    			cout<<"!->TCP \\ open!  "<<number<<"  time"<<endl;
    		}
    		if(number==39){
    			cout<<"!->TCP \\ open!  "<<number<<"  rlp"<<endl;
    		}
    		if(number==42){
    			cout<<"!->TCP \\ open!  "<<number<<"  nameserver"<<endl;
    		}
    		if(number==43){
    			cout<<"!->TCP \\ open!  "<<number<<"  nickname"<<endl;
    		}
    		if(number==49){
    			cout<<"!->TCP \\ open!  "<<number<<"  tacacs"<<endl;
    		}
    		if(number==50){
    			cout<<"!->TCP \\ open!  "<<number<<"  re-mail-ck"<<endl;
    		}
    		if(number==53){
    			cout<<"!->TCP \\ open!  "<<number<<"  domain"<<endl;
    		}
    		if(number==63){
    			cout<<"!->TCP \\ open!  "<<number<<"  whois++"<<endl;
    		}
    		if(number==66){
    			cout<<"!->TCP \\ open!  "<<number<<"  Oracle SQLNet"<<endl;
    		}
    		if(number==70){
    			cout<<"!->TCP \\ open!  "<<number<<"  gopher"<<endl;
    		}
    		if(number==79){
    			cout<<"!->TCP \\ open!  "<<number<<"  finjer"<<endl;
    		}
    		if(number==80){
    			cout<<"!->TCP \\ open!  "<<number<<"  http"<<endl;
    		}
    		if(number==88){
    			cout<<"!->TCP \\ open!  "<<number<<"  kerberos"<<endl;
    		}
    		if(number==95){
    			cout<<"!->TCP \\ open!  "<<number<<"  supdup"<<endl;
    		}
    		if(number==101){
    			cout<<"!->TCP \\ open!  "<<number<<"  hostname"<<endl;
    		}
    		if(number==107){
    			cout<<"!->TCP \\ open!  "<<number<<"  rtelnet"<<endl;
    		}
    		if(number==109){
    			cout<<"!->TCP \\ open!  "<<number<<"  pop2"<<endl;
    		}
    		if(number==110){
    			cout<<"!->TCP \\ open!  "<<number<<"  pop3"<<endl;
    		}
    		if(number==111){
    			cout<<"!->TCP \\ open!  "<<number<<"  sunrpc"<<endl;
    		}
    		if(number==113){
    			cout<<"!->TCP \\ open!  "<<number<<"  auth"<<endl;
    		}
    		if(number==115){
    			cout<<"!->TCP \\ open!  "<<number<<"  sftp"<<endl;
    		}
    		if(number==117){
    			cout<<"!->TCP \\ open!  "<<number<<"  uupc-path"<<endl;
    		}
    		if(number==119){
    			cout<<"!->TCP \\ open!  "<<number<<"  nntp"<<endl;
    		}
    		if(number==135){
    			cout<<"!->TCP \\ open!  "<<number<<"  epmap"<<endl;
    		}
    		if(number==139){
    			cout<<"!->TCP \\ open!  "<<number<<"  netbios-ns"<<endl;
    		}
    		if(number==143){
    			cout<<"!->TCP \\ open!  "<<number<<"  imap"<<endl;
    		}
    		if(number==174){
    			cout<<"!->TCP \\ open!  "<<number<<"  mailq"<<endl;
    		}
    		if(number==177){
    			cout<<"!->TCP \\ open!  "<<number<<"  xdmcp"<<endl;
    		}
    		if(number==178){
    			cout<<"!->TCP \\ open!  "<<number<<"  nextstep"<<endl;
    		}
    		if(number==179){
    			cout<<"!->TCP \\ open!  "<<number<<"  bgp"<<endl;
    		}
    		if(number==194){
    			cout<<"!->TCP \\ open!  "<<number<<"  irc"<<endl;
    		}
    		if(number==199){
    			cout<<"!->TCP \\ open!  "<<number<<"  smux"<<endl;
    		}
    		if(number==201){
    			cout<<"!->TCP \\ open!  "<<number<<"  at-rtmp"<<endl;
    		}
    		if(number==202){
    			cout<<"!->TCP \\ open!  "<<number<<"  at-nbp"<<endl;
    		}
    		if(number==204){
    			cout<<"!->TCP \\ open!  "<<number<<"  at-echo"<<endl;
    		}
    		if(number==206){
    			cout<<"!->TCP \\ open!  "<<number<<"  at-zis"<<endl;
    		}
    		if(number==209){
    			cout<<"!->TCP \\ open!  "<<number<<"  qmtp"<<endl;
    		}
    		if(number==210){
    			cout<<"!->TCP \\ open!  "<<number<<"  z39.50"<<endl;
    		}
    		if(number==213){
    			cout<<"!->TCP \\ open!  "<<number<<"  ipx"<<endl;
    		}
    		if(number==220){
    			cout<<"!->TCP \\ open!  "<<number<<"  imap3"<<endl;
    		}
    		if(number==245){
    			cout<<"!->TCP \\ open!  "<<number<<"  link"<<endl;
    		}
    		if(number==347){
    			cout<<"!->TCP \\ open!  "<<number<<"  fatserv"<<endl;
    		}
    		if(number==363){
    			cout<<"!->TCP \\ open!  "<<number<<"  rsvp_tunnel"<<endl;
    		}
    		if(number==369){
    			cout<<"!->TCP \\ open!  "<<number<<"  rpc2portmap"<<endl;
    		}
    		if(number==370){
    			cout<<"!->TCP \\ open!  "<<number<<"  codaauth2"<<endl;
    		}
    		if(number==372){
    			cout<<"!->TCP \\ open!  "<<number<<"  ulistproc"<<endl;
    		}
    		if(number==389){
    			cout<<"!->TCP \\ open!  "<<number<<"  Idap"<<endl;
    		}
    		if(number==427){
    			cout<<"!->TCP \\ open!  "<<number<<"  svrloc"<<endl;
    		}
    		if(number==434){
    			cout<<"!->TCP \\ open!  "<<number<<"  mobileip-agent"<<endl;    			
    		}
    		if(number==435){
    			cout<<"!->TCP \\ open!  "<<number<<"  tcpmux"<<endl;	
    		}
    		if(number==443){
    			cout<<"!->TCP \\ open!  "<<number<<"  https"<<endl;
    		}
    		if(number==444){
    		    cout<<"!->TCP \\ open!  "<<number<<"  snpp"<<endl;	
    		}
    		if(number==445){
    			cout<<"!->TCP \\ open!  "<<number<<"  microsoft-ds"<<endl;
    		}
    		if(number==465){
    			cout<<"!->TCP \\ open!  "<<number<<"  smtps"<<endl;
    		}
    		if(number==512){
    			cout<<"!->TCP \\ open!  "<<number<<"  exec"<<endl;
    		}
    		if(number==513){
    			cout<<"!->TCP \\ open!  "<<number<<"  rlogin"<<endl;
    		}
    		if(number==514){
    			cout<<"!->TCP \\ open!  "<<number<<"  syslog"<<endl;
    		}
    		if(number==515){
    			cout<<"!->TCP \\ open!  "<<number<<"  WindowsPrinter"<<endl;
    		}
    		if(number==587){
    			cout<<"!->TCP \\ open!  "<<number<<"  smtp"<<endl;
    		}
    		if(number==591){
    			cout<<"!->TCP \\ open!  "<<number<<"  fileMaker"<<endl;
    		}
    		if(number==631){
    			cout<<"!->TCP \\ open!  "<<number<<"  cups"<<endl;
    		}
    		if(number==666){
    			cout<<"!->TCP \\ open!  "<<number<<"  Doom"<<endl;
    		}
    		if(number==690){
    			cout<<"!->TCP \\ open!  "<<number<<"  vatp"<<endl;
    		}
    		if(number==993){
    			cout<<"!->TCP \\ open!  "<<number<<"  imap4SSL"<<endl;
    		}
    		if(number==995){
    			cout<<"!->TCP \\ open!  "<<number<<"  pop3SSL"<<endl;
    		}
    		if(number>996){
    			cout<<"!->TCP \\ open!  "<<number<<"  know"<<endl;
    		}
    		close(sock);
    		return 0;
    		
    		//close(sock);

    	}

    	int port_s_scan(char direc[], int number){
    		int enchufe =  socket(AF_INET, SOCK_STREAM, 0);
    		if(enchufe==-1){
    			cout<<"Error al crear socket"<<endl;
    		}
    		sockaddr_in serverDick;
    		serverDick.sin_family = AF_INET;
    		serverDick.sin_port = htons(number);
    		serverDick.sin_addr.s_addr = inet_addr(direc);

    		int result = connect(enchufe, (sockaddr*)&serverDick, sizeof(serverDick));
    		if(result==-1){
	    		if(number==1){
	    			cout<<"!->TCP \\ close!  "<<number<<"  tcpmux"<<endl;
	    		}
	    		if(number==5){
	    			cout<<"!->TCP \\ close!  "<<number<<"  rje"<<endl;
	    		}
	    		if(number==7){
	    			cout<<"!->TCP \\ close!  "<<number<<"  echo"<<endl;
	    		}
	    		if(number==9){
	    			cout<<"!->TCP \\ close!  "<<number<<"  discard"<<endl;
	    		}
	    		if(number==11){
	    			cout<<"!->TCP \\ close!  "<<number<<"  systat"<<endl;
	    		}
	    		if(number==13){
	    			cout<<"!->TCP \\ close!  "<<number<<"  daytime"<<endl;
	    		}
	    		if(number==17){
	    			cout<<"!->TCP \\ close!  "<<number<<"  qotd"<<endl;
	    		}
	    		if(number==18){
	    			cout<<"!->TCP \\ close!  "<<number<<"  msp"<<endl;
	    		}
	    		if(number==19){
	    			cout<<"!->TCP \\ close!  "<<number<<"  chargen"<<endl;
	    		}
	    		if(number==20){
	    			cout<<"!->TCP \\ close!  "<<number<<"  ftpS-data"<<endl;
	    		}
	    		if(number==21){
	    			cout<<"!->TCP \\ close!  "<<number<<"  ftp-control"<<endl;
	    		}
	    		if(number==22){
	    			cout<<"!->TCP \\ close!  "<<number<<"  ssh"<<endl;
	    		}
	    		if(number==23){
	    			cout<<"!->TCP \\ close!  "<<number<<"  telnet"<<endl;
	    		}
	    		if(number==25){
	    			cout<<"!->TCP \\ close!  "<<number<<"  smtp"<<endl;
	    		}
	    		if(number==37){
	    			cout<<"!->TCP \\ close!  "<<number<<"  time"<<endl;
	    		}
	    		if(number==39){
	    			cout<<"!->TCP \\ close!  "<<number<<"  rlp"<<endl;
	    		}
	    		if(number==42){
	    			cout<<"!->TCP \\ close!  "<<number<<"  nameserver"<<endl;
	    		}
	    		if(number==43){
	    			cout<<"!->TCP \\ close!  "<<number<<"  nickname"<<endl;
	    		}
	    		if(number==49){
	    			cout<<"!->TCP \\ close!  "<<number<<"  tacacs"<<endl;
	    		}
	    		if(number==50){
	    			cout<<"!->TCP \\ close!  "<<number<<"  re-mail-ck"<<endl;
	    		}
	    		if(number==53){
	    			cout<<"!->TCP \\ close!  "<<number<<"  domain"<<endl;
	    		}
	    		if(number==63){
	    			cout<<"!->TCP \\ close!  "<<number<<"  whois++"<<endl;
	    		}
	    		if(number==66){
	    			cout<<"!->TCP \\ close!  "<<number<<"  Oracle SQLNet"<<endl;
	    		}
	    		if(number==70){
	    			cout<<"!->TCP \\ close!  "<<number<<"  gopher"<<endl;
	    		}
	    		if(number==79){
	    			cout<<"!->TCP \\ close!  "<<number<<"  finjer"<<endl;
	    		}
	    		if(number==80){
	    			cout<<"!->TCP \\ close!  "<<number<<"  http"<<endl;
	    		}
	    		if(number==88){
	    			cout<<"!->TCP \\ close!  "<<number<<"  kerberos"<<endl;
	    		}
	    		if(number==95){
	    			cout<<"!->TCP \\ close!  "<<number<<"  supdup"<<endl;
	    		}
	    		if(number==101){
	    			cout<<"!->TCP \\ close!  "<<number<<"  hostname"<<endl;
	    		}
	    		if(number==107){
	    			cout<<"!->TCP \\ close!  "<<number<<"  rtelnet"<<endl;
	    		}
	    		if(number==109){
	    			cout<<"!->TCP \\ close!  "<<number<<"  pop2"<<endl;
	    		}
	    		if(number==110){
	    			cout<<"!->TCP \\ close!  "<<number<<"  pop3"<<endl;
	    		}
	    		if(number==111){
	    			cout<<"!->TCP \\ close!  "<<number<<"  sunrpc"<<endl;
	    		}
	    		if(number==113){
	    			cout<<"!->TCP \\ close!  "<<number<<"  auth"<<endl;
	    		}
	    		if(number==115){
	    			cout<<"!->TCP \\ close!  "<<number<<"  sftp"<<endl;
	    		}
	    		if(number==117){
	    			cout<<"!->TCP \\ close!  "<<number<<"  uupc-path"<<endl;
	    		}
	    		if(number==119){
	    			cout<<"!->TCP \\ close!  "<<number<<"  nntp"<<endl;
	    		}
	    		if(number==135){
	    			cout<<"!->TCP \\ close!  "<<number<<"  epmap"<<endl;
	    		}
	    		if(number==139){
	    			cout<<"!->TCP \\ close!  "<<number<<"  netbios-ns"<<endl;
	    		}
	    		if(number==143){
	    			cout<<"!->TCP \\ close!  "<<number<<"  imap"<<endl;
	    		}
	    		if(number==174){
	    			cout<<"!->TCP \\ close!  "<<number<<"  mailq"<<endl;
	    		}
	    		if(number==177){
	    			cout<<"!->TCP \\ close!  "<<number<<"  xdmcp"<<endl;
	    		}
	    		if(number==178){
	    			cout<<"!->TCP \\ close!  "<<number<<"  nextstep"<<endl;
	    		}
	    		if(number==179){
	    			cout<<"!->TCP \\ close!  "<<number<<"  bgp"<<endl;
	    		}
	    		if(number==194){
	    			cout<<"!->TCP \\ close!  "<<number<<"  irc"<<endl;
	    		}
	    		if(number==199){
	    			cout<<"!->TCP \\ close!  "<<number<<"  smux"<<endl;
	    		}
	    		if(number==201){
	    			cout<<"!->TCP \\ close!  "<<number<<"  at-rtmp"<<endl;
	    		}
	    		if(number==202){
	    			cout<<"!->TCP \\ close!  "<<number<<"  at-nbp"<<endl;
	    		}
	    		if(number==204){
	    			cout<<"!->TCP \\ close!  "<<number<<"  at-echo"<<endl;
	    		}
	    		if(number==206){
	    			cout<<"!->TCP \\ close!  "<<number<<"  at-zis"<<endl;
	    		}
	    		if(number==209){
	    			cout<<"!->TCP \\ close!  "<<number<<"  qmtp"<<endl;
	    		}
	    		if(number==210){
	    			cout<<"!->TCP \\ close!  "<<number<<"  z39.50"<<endl;
	    		}
	    		if(number==213){
	    			cout<<"!->TCP \\ close!  "<<number<<"  ipx"<<endl;
	    		}
	    		if(number==220){
	    			cout<<"!->TCP \\ close!  "<<number<<"  imap3"<<endl;
	    		}
	    		if(number==245){
	    			cout<<"!->TCP \\ close!  "<<number<<"  link"<<endl;
	    		}
	    		if(number==347){
	    			cout<<"!->TCP \\ close!  "<<number<<"  fatserv"<<endl;
	    		}
	    		if(number==363){
	    			cout<<"!->TCP \\ close!  "<<number<<"  rsvp_tunnel"<<endl;
	    		}
	    		if(number==369){
	    			cout<<"!->TCP \\ close!  "<<number<<"  rpc2portmap"<<endl;
	    		}
	    		if(number==370){
	    			cout<<"!->TCP \\ close!  "<<number<<"  codaauth2"<<endl;
	    		}
	    		if(number==372){
	    			cout<<"!->TCP \\ close!  "<<number<<"  ulistproc"<<endl;
	    		}
	    		if(number==389){
	    			cout<<"!->TCP \\ close!  "<<number<<"  Idap"<<endl;
	    		}
	    		if(number==427){
	    			cout<<"!->TCP \\ close!  "<<number<<"  svrloc"<<endl;
	    		}
	    		if(number==434){
	    			cout<<"!->TCP \\ close!  "<<number<<"  mobileip-agent"<<endl;    			
	    		}
	    		if(number==435){
	    			cout<<"!->TCP \\ close!  "<<number<<"  tcpmux"<<endl;	
	    		}
	    		if(number==443){
	    			cout<<"!->TCP \\ close!  "<<number<<"  https"<<endl;
	    		}
	    		if(number==444){
	    		    cout<<"!->TCP \\ close!  "<<number<<"  snpp"<<endl;	
	    		}
	    		if(number==445){
	    			cout<<"!->TCP \\ close!  "<<number<<"  microsoft-ds"<<endl;
	    		}
	    		if(number==465){
	    			cout<<"!->TCP \\ close!  "<<number<<"  smtps"<<endl;
	    		}
	    		if(number==512){
	    			cout<<"!->TCP \\ close!  "<<number<<"  exec"<<endl;
	    		}
	    		if(number==513){
	    			cout<<"!->TCP \\ close!  "<<number<<"  rlogin"<<endl;
	    		}
	    		if(number==514){
	    			cout<<"!->TCP \\ close!  "<<number<<"  syslog"<<endl;
	    		}
	    		if(number==515){
	    			cout<<"!->TCP \\ close!  "<<number<<"  WindowsPrinter"<<endl;
	    		}
	    		if(number==587){
	    			cout<<"!->TCP \\ close!  "<<number<<"  smtp"<<endl;
	    		}
	    		if(number==591){
	    			cout<<"!->TCP \\ close!  "<<number<<"  fileMaker"<<endl;
	    		}
	    		if(number==631){
	    			cout<<"!->TCP \\ close!  "<<number<<"  cups"<<endl;
	    		}
	    		if(number==666){
	    			cout<<"!->TCP \\ close!  "<<number<<"  Doom"<<endl;
	    		}
	    		if(number==690){
	    			cout<<"!->TCP \\ close!  "<<number<<"  vatp"<<endl;
	    		}
	    		if(number==993){
	    			cout<<"!->TCP \\ close!  "<<number<<"  imap4SSL"<<endl;
	    		}
	    		if(number==995){
	    			cout<<"!->TCP \\ close!  "<<number<<"  pop3SSL"<<endl;
	    		}
	    		if(number>996){
	    			cout<<"!->TCP \\ close!  "<<number<<"  know"<<endl;
	    		}
    			close(enchufe);
    			return 1;
    		}
    		if(number==1){
    			cout<<"!->TCP \\ open!  "<<number<<"  tcpmux"<<endl;
    		}
    		if(number==5){
    			cout<<"!->TCP \\ open!  "<<number<<"  rje"<<endl;
    		}
    		if(number==7){
    			cout<<"!->TCP \\ open!  "<<number<<"  echo"<<endl;
    		}
    		if(number==9){
    			cout<<"!->TCP \\ open!  "<<number<<"  discard"<<endl;
    		}
    		if(number==11){
    			cout<<"!->TCP \\ open!  "<<number<<"  systat"<<endl;
    		}
    		if(number==13){
    			cout<<"!->TCP \\ open!  "<<number<<"  daytime"<<endl;
    		}
    		if(number==17){
    			cout<<"!->TCP \\ open!  "<<number<<"  qotd"<<endl;
    		}
    		if(number==18){
    			cout<<"!->TCP \\ open!  "<<number<<"  msp"<<endl;
    		}
    		if(number==19){
    			cout<<"!->TCP \\ open!  "<<number<<"  chargen"<<endl;
    		}
    		if(number==20){
    			cout<<"!->TCP \\ open!  "<<number<<"  ftpS-data"<<endl;
    		}
    		if(number==21){
    			cout<<"!->TCP \\ open!  "<<number<<"  ftp-control"<<endl;
    		}
    		if(number==22){
    			cout<<"!->TCP \\ open!  "<<number<<"  ssh"<<endl;
    		}
    		if(number==23){
    			cout<<"!->TCP \\ open!  "<<number<<"  telnet"<<endl;
    		}
    		if(number==25){
    			cout<<"!->TCP \\ open!  "<<number<<"  smtp"<<endl;
    		}
    		if(number==37){
    			cout<<"!->TCP \\ open!  "<<number<<"  time"<<endl;
    		}
    		if(number==39){
    			cout<<"!->TCP \\ open!  "<<number<<"  rlp"<<endl;
    		}
    		if(number==42){
    			cout<<"!->TCP \\ open!  "<<number<<"  nameserver"<<endl;
    		}
    		if(number==43){
    			cout<<"!->TCP \\ open!  "<<number<<"  nickname"<<endl;
    		}
    		if(number==49){
    			cout<<"!->TCP \\ open!  "<<number<<"  tacacs"<<endl;
    		}
    		if(number==50){
    			cout<<"!->TCP \\ open!  "<<number<<"  re-mail-ck"<<endl;
    		}
    		if(number==53){
    			cout<<"!->TCP \\ open!  "<<number<<"  domain"<<endl;
    		}
    		if(number==63){
    			cout<<"!->TCP \\ open!  "<<number<<"  whois++"<<endl;
    		}
    		if(number==66){
    			cout<<"!->TCP \\ open!  "<<number<<"  Oracle SQLNet"<<endl;
    		}
    		if(number==70){
    			cout<<"!->TCP \\ open!  "<<number<<"  gopher"<<endl;
    		}
    		if(number==79){
    			cout<<"!->TCP \\ open!  "<<number<<"  finjer"<<endl;
    		}
    		if(number==80){
    			cout<<"!->TCP \\ open!  "<<number<<"  http"<<endl;
    		}
    		if(number==88){
    			cout<<"!->TCP \\ open!  "<<number<<"  kerberos"<<endl;
    		}
    		if(number==95){
    			cout<<"!->TCP \\ open!  "<<number<<"  supdup"<<endl;
    		}
    		if(number==101){
    			cout<<"!->TCP \\ open!  "<<number<<"  hostname"<<endl;
    		}
    		if(number==107){
    			cout<<"!->TCP \\ open!  "<<number<<"  rtelnet"<<endl;
    		}
    		if(number==109){
    			cout<<"!->TCP \\ open!  "<<number<<"  pop2"<<endl;
    		}
    		if(number==110){
    			cout<<"!->TCP \\ open!  "<<number<<"  pop3"<<endl;
    		}
    		if(number==111){
    			cout<<"!->TCP \\ open!  "<<number<<"  sunrpc"<<endl;
    		}
    		if(number==113){
    			cout<<"!->TCP \\ open!  "<<number<<"  auth"<<endl;
    		}
    		if(number==115){
    			cout<<"!->TCP \\ open!  "<<number<<"  sftp"<<endl;
    		}
    		if(number==117){
    			cout<<"!->TCP \\ open!  "<<number<<"  uupc-path"<<endl;
    		}
    		if(number==119){
    			cout<<"!->TCP \\ open!  "<<number<<"  nntp"<<endl;
    		}
    		if(number==135){
    			cout<<"!->TCP \\ open!  "<<number<<"  epmap"<<endl;
    		}
    		if(number==139){
    			cout<<"!->TCP \\ open!  "<<number<<"  netbios-ns"<<endl;
    		}
    		if(number==143){
    			cout<<"!->TCP \\ open!  "<<number<<"  imap"<<endl;
    		}
    		if(number==174){
    			cout<<"!->TCP \\ open!  "<<number<<"  mailq"<<endl;
    		}
    		if(number==177){
    			cout<<"!->TCP \\ open!  "<<number<<"  xdmcp"<<endl;
    		}
    		if(number==178){
    			cout<<"!->TCP \\ open!  "<<number<<"  nextstep"<<endl;
    		}
    		if(number==179){
    			cout<<"!->TCP \\ open!  "<<number<<"  bgp"<<endl;
    		}
    		if(number==194){
    			cout<<"!->TCP \\ open!  "<<number<<"  irc"<<endl;
    		}
    		if(number==199){
    			cout<<"!->TCP \\ open!  "<<number<<"  smux"<<endl;
    		}
    		if(number==201){
    			cout<<"!->TCP \\ open!  "<<number<<"  at-rtmp"<<endl;
    		}
    		if(number==202){
    			cout<<"!->TCP \\ open!  "<<number<<"  at-nbp"<<endl;
    		}
    		if(number==204){
    			cout<<"!->TCP \\ open!  "<<number<<"  at-echo"<<endl;
    		}
    		if(number==206){
    			cout<<"!->TCP \\ open!  "<<number<<"  at-zis"<<endl;
    		}
    		if(number==209){
    			cout<<"!->TCP \\ open!  "<<number<<"  qmtp"<<endl;
    		}
    		if(number==210){
    			cout<<"!->TCP \\ open!  "<<number<<"  z39.50"<<endl;
    		}
    		if(number==213){
    			cout<<"!->TCP \\ open!  "<<number<<"  ipx"<<endl;
    		}
    		if(number==220){
    			cout<<"!->TCP \\ open!  "<<number<<"  imap3"<<endl;
    		}
    		if(number==245){
    			cout<<"!->TCP \\ open!  "<<number<<"  link"<<endl;
    		}
    		if(number==347){
    			cout<<"!->TCP \\ open!  "<<number<<"  fatserv"<<endl;
    		}
    		if(number==363){
    			cout<<"!->TCP \\ open!  "<<number<<"  rsvp_tunnel"<<endl;
    		}
    		if(number==369){
    			cout<<"!->TCP \\ open!  "<<number<<"  rpc2portmap"<<endl;
    		}
    		if(number==370){
    			cout<<"!->TCP \\ open!  "<<number<<"  codaauth2"<<endl;
    		}
    		if(number==372){
    			cout<<"!->TCP \\ open!  "<<number<<"  ulistproc"<<endl;
    		}
    		if(number==389){
    			cout<<"!->TCP \\ open!  "<<number<<"  Idap"<<endl;
    		}
    		if(number==427){
    			cout<<"!->TCP \\ open!  "<<number<<"  svrloc"<<endl;
    		}
    		if(number==434){
    			cout<<"!->TCP \\ open!  "<<number<<"  mobileip-agent"<<endl;    			
    		}
    		if(number==435){
    			cout<<"!->TCP \\ open!  "<<number<<"  tcpmux"<<endl;	
    		}
    		if(number==443){
    			cout<<"!->TCP \\ open!  "<<number<<"  https"<<endl;
    		}
    		if(number==444){
    		    cout<<"!->TCP \\ open!  "<<number<<"  snpp"<<endl;	
    		}
    		if(number==445){
    			cout<<"!->TCP \\ open!  "<<number<<"  microsoft-ds"<<endl;
    		}
    		if(number==465){
    			cout<<"!->TCP \\ open!  "<<number<<"  smtps"<<endl;
    		}
    		if(number==512){
    			cout<<"!->TCP \\ open!  "<<number<<"  exec"<<endl;
    		}
    		if(number==513){
    			cout<<"!->TCP \\ open!  "<<number<<"  rlogin"<<endl;
    		}
    		if(number==514){
    			cout<<"!->TCP \\ open!  "<<number<<"  syslog"<<endl;
    		}
    		if(number==515){
    			cout<<"!->TCP \\ open!  "<<number<<"  WindowsPrinter"<<endl;
    		}
    		if(number==587){
    			cout<<"!->TCP \\ open!  "<<number<<"  smtp"<<endl;
    		}
    		if(number==591){
    			cout<<"!->TCP \\ open!  "<<number<<"  fileMaker"<<endl;
    		}
    		if(number==631){
    			cout<<"!->TCP \\ open!  "<<number<<"  cups"<<endl;
    		}
    		if(number==666){
    			cout<<"!->TCP \\ open!  "<<number<<"  Doom"<<endl;
    		}
    		if(number==690){
    			cout<<"!->TCP \\ open!  "<<number<<"  vatp"<<endl;
    		}
    		if(number==993){
    			cout<<"!->TCP \\ open!  "<<number<<"  imap4SSL"<<endl;
    		}
    		if(number==995){
    			cout<<"!->TCP \\ open!  "<<number<<"  pop3SSL"<<endl;
    		}
    		if(number>995){
    			cout<<"!->TCP \\ open!  "<<number<<"  know"<<endl;
    		}
    		close(enchufe);
    		return 0;
    		
    	}
};

class Alert{
    public:
    	void alert_bc(){
    		cout<<"Especifique una direccion para uso: -Bs <ip>"<<endl;
    	}
    	void alert_sp(){
    		cout<<"Especifique una direccion y puerto para -sP\nuso: -sP <ip> <port>"<<endl;
    	}
    	void alert_sp_b(){
    		cout<<"Especifique una direccion y puerto para -sP\nuso: -sP <ip> <port>"<<endl;
    	}
    	void alert_http_get(){
    		cout<<"Especifique una direccion para -httpGET\nuso: -httpGET <ip or direction>"<<endl;
    	}
    	void alert_https_get(){
    		cout<<"Especifique una direccion para -httpsGET\nuso: -httpsGET <ip or direction>"<<endl;
    	}
};

int main(int argc, char *argv[]){
	//auto inicio = steady_clock::now();
	
	if(argc==1){
		printf("Debe especificar un argumento\n use --help para mas informacion\n");
	}else{
		if(argc==2){
			int result;
			result = strcmp(argv[1], "--help");
			if(result==0){
				Mess objeto;
				Mess* puntero = &objeto;
				puntero->help_funtion();

			}else{
				int result_a = strcmp(argv[1], "--version");
				if(result_a==0){
					Mess egg;
					Mess* tniop = &egg;
					tniop->version();
				}else{
					int result_b = strcmp(argv[1], "-Bs");
					if(result_b==0){
						Alert a;
						Alert* b = &a;
						b->alert_bc();
					}else{
						int result_c = strcmp(argv[1], "-sP");
						if(result_c==0){
							Alert manager_a;
							Alert* point_manager_a = &manager_a;
							point_manager_a->alert_sp();
						}else{
							int resutl_d = strcmp(argv[1], "-httpGET");
							if(resutl_d==0){
								Alert paparazi;
								Alert* cam = &paparazi;
								cam->alert_http_get();
							}else{
								int result_e = strcmp(argv[1], "-httpsGET");
								if(result_e==0){
									Alert xuxa;
									Alert* qxopa = &xuxa;
									qxopa->alert_https_get();
								}
							}
						}
					}
				}
			}
		}else{
			if(argc==3){
				int ghostemane = strcmp(argv[1], "-Bs");
				if(ghostemane==0){
					auto escaneo_simple_inicio = steady_clock::now();
					Mess ruso;
					Mess* sovietico = &ruso;
					sovietico->principal();

					Enchufe annie;
					Enchufe* loco = &annie;
					loco->gethostbyaddr(argv[2]);

					Enchufe getMac;
					Enchufe* macc = &getMac;
					macc->getmacaddress(argv[2]);

					for(int x=0;x<10001;x++){
						Enchufe kim;
						Enchufe* dracula = &kim;
						dracula->basic_scan(argv[2], x);
					}
					auto escaneo_simple_final = steady_clock::now();
					duration<double> duration = escaneo_simple_final - escaneo_simple_inicio;
					double simplescan = duration.count();
					double factor = pow(10, 2);
					double decimal = round(simplescan * factor) / factor;
					cout<<"PortSeeker done: 10,000 puertos escaneados en "<<fixed<<setprecision(2)<<decimal;
					cout<<" segundos"<<endl;

				}else{
					int verficador_a = strcmp(argv[1], "-sP");
					if(verficador_a==0){
						Alert huevos;
						Alert* martillo;
						martillo->alert_sp_b();
					}else{
						int verificador_b = strcmp(argv[1], "-httpGET");
						if(verificador_b==0){
							//000000000000000000000000000000000000000000000000
							auto peticionGET = steady_clock::now();
							Mess payaso;
							Mess* assin = &payaso;
							assin->httpGET_scan();

							//Enchufe::peticion_http_get('https://google.com');
							Enchufe mentira;
							Enchufe* putas_mentiras = &mentira;
							putas_mentiras->peticion_http_get(argv[2]);
							auto peticionGETFinal = steady_clock::now();
							duration<double> duration = peticionGETFinal - peticionGET;
							double httpget = duration.count();
							double factore = pow(10, 2);
							double decimal_a = round(httpget * factore) / factore;
							cout<<"PortSeeker done: HTTP_GET en "<<fixed<<setprecision(2)<<decimal_a;
							cout<<" segundos"<<endl;
						}else{
							int verificador_c = strcmp(argv[1], "-httpsGET");
							if(verificador_c==0){
								auto peticion = steady_clock::now();
								Mess kk;
								Mess* kkk = &kk;
								kkk->httpGET_scan();

								Enchufe elMal;
								Enchufe* local = &elMal;
								local->peticion_https_Get(argv[2]);
								auto peticion_final = steady_clock::now();
								duration<double> duration = peticion_final - peticion;
								double httpsget = duration.count();
								double fatores = pow(10, 2);
								double decimal_b = round(httpsget * fatores) / fatores;
								cout<<"PortSeeker done: HTTPS_GET en "<<fixed<<setprecision(2)<<decimal_b;
								cout<<" segundos"<<endl;
							}
						}
					}
				}
			}else{
				if(argc==4){
					int kimdracula = strcmp(argv[1], "-sP");
					if(kimdracula==0){
						Mess nazi;
						auto inicio_s_scan = steady_clock::now();
						Mess* guerra = &nazi;
						guerra->principal();
						Enchufe cam;
						Enchufe* corriente = &cam;
						Enchufe atun;
						Enchufe* cebolla = &atun;
						char* par = const_cast<char*>(argv[2]);
						cebolla->gethostbyaddr(argv[2]);
						Enchufe solo;
						Enchufe* solito = &solo;
						solito->getmacaddress(argv[2]);
						int numeroso = char_intconverter(argv[3]);
						solito->port_s_scan(argv[2], numeroso);
						auto final_s_scan = steady_clock::now();
						duration<double> duration = final_s_scan - inicio_s_scan;
						double s_scan_s = duration.count();
						double factor_s = pow(10, 2);
						double decimal_ss = round(s_scan_s * factor_s) / factor_s;
						cout<<"PortSeeker done: 1 puerto escaneado en "<<fixed<<setprecision(2)<<decimal_ss;
						cout<<" segundos"<<endl;
					}
				}				
			}
		}
	}
	/*
	auto final = steady_clock::now();
	duration<double> duration = final - inicio;
	double duracionensegundos = duration.count();
	cout<<"PortSeeker done: tiempo de escaneo "<<duracionensegundos<<" segundos"<<endl;
	*/
	return 0;
}