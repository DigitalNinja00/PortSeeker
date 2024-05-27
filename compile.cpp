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
//int funtions

const bool kk = false;


class Mess{
    private:
    	int numero;
    public:
    	void help_funtion(){
    		string var[]={"\033[1;31m!!!!!USE ROOT!!!!!",
    		"\033[0m==--Help list==",
    		"-sP | prtker -sP <ip> <port>",
    		"-Bs | prtker -Bs <ip>",
    		"-httpGET | prtker -httpGET <ip or direction>",
    		"-httpsGET | prtker -httpsGET <ip or direction>",
    		"==INFO==",
    		"-Bs",
    		"Do basic port scanner, send petitions TCP,",
    		"From port 1 to 10,000",
    		"-sP",
			"Specific port scanning, works to scan a specific port",
			"sends a single TCP/IP request",
			"-httpGET | works to make http get requests to",
			"http servers, does not work for https",
			"-httpsGET | works to make https get requests to",
			"https and http servers",
			"-httpPOST | works to make POST requests to servers",
			"-httpSTATUSCODE | works to obtain the status code via http",
			"-sS | works to perform a quieter scan"

    	};
    		size_t main = sizeof(var)/sizeof(string);
    		for(int i=0; i<main;i++){
    			cout<<var[i]<<endl;
    		}
    	}
    	void version(){
    		cout<<"PortSeeker version 1.5"<<endl;
    	}
    	void principal(){
    		cout<<BLUE<<"Starting BasicScan PortSeeker 1.5"<<endl;;
    	}
    	void httpGET_scan(){
    		cout<<BLUE<<"Starting HTTPGET PortSeeker 1.5"<<endl;
    	}
    	void code_status(){
    		cout<<BLUE<<"Starting HTTPSTATUSCODE PortSeeker 1.5"<<endl;
    	}
    	void banner(){
    		system("python3 scripts_python/banner.py");
    	}
    	void http_get_status(string vaca){
    		stringstream log;
    		log<<"python3 "<<"scripts_python/post.py -d "<<vaca;
    		system(log.str().c_str());
    	}
    	void silent_scanner(){
    		cout<<BLUE<<"Starting SilentScan PortSeeker 1.5"<<endl;
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
    			cout<<"Error obtaining ip"<<endl;
    			return 1;
    		}
    		char hostname[NI_MAXHOST];
    		if(getnameinfo(res->ai_addr, res->ai_addrlen, hostname, sizeof(hostname), NULL, 0, 0) != 0){
    			cout<<"Error obtaining hostname"<<endl;
    			return 1;
    		}
    		cout<<RED<<"Hostname: "<<YELLOW<<remoteipaddress<<GREEN<<" "<<hostname<<RESET<<endl;
    		return 0;
    	}
    	int getmacaddress(const char* direccionremota){
    		//geta¡macfuntion
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


    	int basic_scan(char host[], int number){
    		int sock = socket(AF_INET, SOCK_STREAM, 0); //se crea un socket
    		if(sock == -1){
    			cout<<"Error creating socket"<<endl;
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
    			cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  tcpmux"<<endl;
    		}
			if(number==5){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  rje"<<endl;
			}
			if(number==7){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  echo"<<endl;
			}
			if(number==9){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  discard"<<endl;
			}
			if(number==11){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  systat"<<endl;
			}
			if(number==13){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  daytime"<<endl;
			}
			if(number==17){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  qotd"<<endl;
			}
			if(number==18){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  msp"<<endl;
			}
			if(number==19){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  chargen"<<endl;
			}
			if(number==20){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  ftpS-data"<<endl;
			}
			if(number==21){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  ftp-control"<<endl;
			}
			if(number==22){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  ssh"<<endl;
			}
			if(number==23){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  telnet"<<endl;
			}
			if(number==25){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  smtp"<<endl;
			}
			if(number==37){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  time"<<endl;
			}
			if(number==39){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  rlp"<<endl;
			}
			if(number==42){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  nameserver"<<endl;
			}
			if(number==43){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  nickname"<<endl;
			}
			if(number==49){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  tacacs"<<endl;
			}
			if(number==50){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  re-mail-ck"<<endl;
			}
			if(number==53){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  domain"<<endl;
			}
			if(number==63){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  whois++"<<endl;
			}
			if(number==66){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  Oracle SQLNet"<<endl;
			}
			if(number==70){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  gopher"<<endl;
			}
			if(number==79){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  finjer"<<endl;
			}
			if(number==80){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  http"<<endl;
			}
			if(number==88){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  kerberos"<<endl;
			}
			if(number==95){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  supdup"<<endl;
			}
			if(number==101){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  hostname"<<endl;
			}
			if(number==107){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  rtelnet"<<endl;
			}
			if(number==109){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  pop2"<<endl;
			}
			if(number==110){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  pop3"<<endl;
			}
			if(number==111){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  sunrpc"<<endl;
			}
			if(number==113){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  auth"<<endl;
			}
			if(number==115){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  sftp"<<endl;
			}
			if(number==117){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  uupc-path"<<endl;
			}
			if(number==119){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  nntp"<<endl;
			}
			if(number==135){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  epmap"<<endl;
			}
			if(number==139){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  netbios-ns"<<endl;
			}
			if(number==143){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  imap"<<endl;
			}
			if(number==174){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  mailq"<<endl;
			}
			if(number==177){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  xdmcp"<<endl;
			}
			if(number==178){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  nextstep"<<endl;
			}
			if(number==179){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  bgp"<<endl;
			}
			if(number==194){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  irc"<<endl;
			}
			if(number==199){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  smux"<<endl;
			}
			if(number==201){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  at-rtmp"<<endl;
			}
			if(number==202){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  at-nbp"<<endl;
			}
			if(number==204){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  at-echo"<<endl;
			}
			if(number==206){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  at-zis"<<endl;
			}
			if(number==209){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  qmtp"<<endl;
			}
			if(number==210){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  z39.50"<<endl;
			}
			if(number==213){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  ipx"<<endl;
			}
			if(number==220){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  imap3"<<endl;
			}
			if(number==245){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  link"<<endl;
			}
			if(number==347){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  fatserv"<<endl;
			}
			if(number==363){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  rsvp_tunnel"<<endl;
			}
			if(number==369){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  rpc2portmap"<<endl;
			}
			if(number==370){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  codaauth2"<<endl;
			}
			if(number==372){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  ulistproc"<<endl;
			}
			if(number==389){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  Idap"<<endl;
			}
			if(number==427){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  svrloc"<<endl;
			}
			if(number==434){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  mobileip-agent"<<endl;
			}
			if(number==435){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  tcpmux"<<endl;
			}
			if(number==443){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  https"<<endl;
			}
			if(number==444){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  snpp"<<endl;
			}
			if(number==445){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  microsoft-ds"<<endl;
			}
			if(number==465){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  smtps"<<endl;
			}
			if(number==512){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  exec"<<endl;
			}
			if(number==513){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  rlogin"<<endl;
			}
			if(number==514){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  syslog"<<endl;
			}
			if(number==515){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  WindowsPrinter"<<endl;
			}
			if(number==587){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  smtp"<<endl;
			}
			if(number==591){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  fileMaker"<<endl;
			}
			if(number==631){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  cups"<<endl;
			}
			if(number==666){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  Doom"<<endl;
			}
			if(number==690){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  vatp"<<endl;
			}
			if(number==993){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  imap4SSL"<<endl;
			}
			if(number==995){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  pop3SSL"<<endl;
			}
			if(number>996){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  know"<<endl;
			}

    		close(sock);
    		return 0;
    		
    		//close(sock);

    	}
    	int silent_scan(char direccion[], int number){
    		int conector = socket(AF_INET, SOCK_STREAM, 0);
    		if(conector==-1){
    			cout<<"Error creating socket"<<endl;
    		}
    		sockaddr_in serverMain;
    		serverMain.sin_family = AF_INET;
    		serverMain.sin_port = htons(number);
    		serverMain.sin_addr.s_addr = inet_addr(direccion);
    		int resultado = connect(conector, (sockaddr*)&serverMain, sizeof(serverMain));
    		if(resultado==-1){
    			close(conector);
    			return 1;
    		}
    		if(number==1){
    			cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  tcpmux"<<endl;
    		}
			if(number==5){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  rje"<<endl;
			}
			if(number==7){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  echo"<<endl;
			}
			if(number==9){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  discard"<<endl;
			}
			if(number==11){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  systat"<<endl;
			}
			if(number==13){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  daytime"<<endl;
			}
			if(number==17){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  qotd"<<endl;
			}
			if(number==18){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  msp"<<endl;
			}
			if(number==19){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  chargen"<<endl;
			}
			if(number==20){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  ftpS-data"<<endl;
			}
			if(number==21){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  ftp-control"<<endl;
			}
			if(number==22){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  ssh"<<endl;
			}
			if(number==23){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  telnet"<<endl;
			}
			if(number==25){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  smtp"<<endl;
			}
			if(number==37){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  time"<<endl;
			}
			if(number==39){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  rlp"<<endl;
			}
			if(number==42){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  nameserver"<<endl;
			}
			if(number==43){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  nickname"<<endl;
			}
			if(number==49){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  tacacs"<<endl;
			}
			if(number==50){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  re-mail-ck"<<endl;
			}
			if(number==53){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  domain"<<endl;
			}
			if(number==63){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  whois++"<<endl;
			}
			if(number==66){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  Oracle SQLNet"<<endl;
			}
			if(number==70){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  gopher"<<endl;
			}
			if(number==79){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  finjer"<<endl;
			}
			if(number==80){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  http"<<endl;
			}
			if(number==88){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  kerberos"<<endl;
			}
			if(number==95){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  supdup"<<endl;
			}
			if(number==101){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  hostname"<<endl;
			}
			if(number==107){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  rtelnet"<<endl;
			}
			if(number==109){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  pop2"<<endl;
			}
			if(number==110){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  pop3"<<endl;
			}
			if(number==111){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  sunrpc"<<endl;
			}
			if(number==113){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  auth"<<endl;
			}
			if(number==115){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  sftp"<<endl;
			}
			if(number==117){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  uupc-path"<<endl;
			}
			if(number==119){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  nntp"<<endl;
			}
			if(number==135){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  epmap"<<endl;
			}
			if(number==139){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  netbios-ns"<<endl;
			}
			if(number==143){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  imap"<<endl;
			}
			if(number==174){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  mailq"<<endl;
			}
			if(number==177){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  xdmcp"<<endl;
			}
			if(number==178){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  nextstep"<<endl;
			}
			if(number==179){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  bgp"<<endl;
			}
			if(number==194){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  irc"<<endl;
			}
			if(number==199){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  smux"<<endl;
			}
			if(number==201){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  at-rtmp"<<endl;
			}
			if(number==202){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  at-nbp"<<endl;
			}
			if(number==204){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  at-echo"<<endl;
			}
			if(number==206){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  at-zis"<<endl;
			}
			if(number==209){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  qmtp"<<endl;
			}
			if(number==210){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  z39.50"<<endl;
			}
			if(number==213){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  ipx"<<endl;
			}
			if(number==220){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  imap3"<<endl;
			}
			if(number==245){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  link"<<endl;
			}
			if(number==347){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  fatserv"<<endl;
			}
			if(number==363){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  rsvp_tunnel"<<endl;
			}
			if(number==369){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  rpc2portmap"<<endl;
			}
			if(number==370){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  codaauth2"<<endl;
			}
			if(number==372){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  ulistproc"<<endl;
			}
			if(number==389){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  Idap"<<endl;
			}
			if(number==427){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  svrloc"<<endl;
			}
			if(number==434){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  mobileip-agent"<<endl;
			}
			if(number==435){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  tcpmux"<<endl;
			}
			if(number==443){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  https"<<endl;
			}
			if(number==444){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  snpp"<<endl;
			}
			if(number==445){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  microsoft-ds"<<endl;
			}
			if(number==465){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  smtps"<<endl;
			}
			if(number==512){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  exec"<<endl;
			}
			if(number==513){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  rlogin"<<endl;
			}
			if(number==514){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  syslog"<<endl;
			}
			if(number==515){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  WindowsPrinter"<<endl;
			}
			if(number==587){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  smtp"<<endl;
			}
			if(number==591){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  fileMaker"<<endl;
			}
			if(number==631){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  cups"<<endl;
			}
			if(number==666){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  Doom"<<endl;
			}
			if(number==690){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  vatp"<<endl;
			}
			if(number==993){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  imap4SSL"<<endl;
			}
			if(number==995){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  pop3SSL"<<endl;
			}
			if(number>996){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  know"<<endl;
			}
    		close(conector);
    		return 0;
    	}

    	int port_s_scan(char direc[], int number){
    		int enchufe =  socket(AF_INET, SOCK_STREAM, 0);
    		if(enchufe==-1){
    			cout<<"Error creating socket"<<endl;
    		}
    		sockaddr_in serverDick;
    		serverDick.sin_family = AF_INET;
    		serverDick.sin_port = htons(number);
    		serverDick.sin_addr.s_addr = inet_addr(direc);

    		int result = connect(enchufe, (sockaddr*)&serverDick, sizeof(serverDick));
    		if(result==-1){
	    		if(number==1){
	    			cout<<RED<<"!->TCP "<<YELLOW<<"\\ close! \\ "<<RED<<number<<GREEN<<"  tcpmux"<<endl;
	    		}
				if(number==5){
				    cout<<RED<<"!->TCP "<<YELLOW<<"\\ close! \\ "<<RED<<number<<GREEN<<"  rje"<<endl;
				}
				if(number==7){
				    cout<<RED<<"!->TCP "<<YELLOW<<"\\ close! \\ "<<RED<<number<<GREEN<<"  echo"<<endl;
				}
				if(number==9){
				    cout<<RED<<"!->TCP "<<YELLOW<<"\\ close! \\ "<<RED<<number<<GREEN<<"  discard"<<endl;
				}
				if(number==11){
				    cout<<RED<<"!->TCP "<<YELLOW<<"\\ close! \\ "<<RED<<number<<GREEN<<"  systat"<<endl;
				}
				if(number==13){
				    cout<<RED<<"!->TCP "<<YELLOW<<"\\ close! \\ "<<RED<<number<<GREEN<<"  daytime"<<endl;
				}
				if(number==17){
				    cout<<RED<<"!->TCP "<<YELLOW<<"\\ close! \\ "<<RED<<number<<GREEN<<"  qotd"<<endl;
				}
				if(number==18){
				    cout<<RED<<"!->TCP "<<YELLOW<<"\\ close! \\ "<<RED<<number<<GREEN<<"  msp"<<endl;
				}
				if(number==19){
				    cout<<RED<<"!->TCP "<<YELLOW<<"\\ close! \\ "<<RED<<number<<GREEN<<"  chargen"<<endl;
				}
				if(number==20){
				    cout<<RED<<"!->TCP "<<YELLOW<<"\\ close! \\ "<<RED<<number<<GREEN<<"  ftpS-data"<<endl;
				}
				if(number==21){
				    cout<<RED<<"!->TCP "<<YELLOW<<"\\ close! \\ "<<RED<<number<<GREEN<<"  ftp-control"<<endl;
				}
				if(number==22){
				    cout<<RED<<"!->TCP "<<YELLOW<<"\\ close! \\ "<<RED<<number<<GREEN<<"  ssh"<<endl;
				}
				if(number==23){
				    cout<<RED<<"!->TCP "<<YELLOW<<"\\ close! \\ "<<RED<<number<<GREEN<<"  telnet"<<endl;
				}
				if(number==25){
				    cout<<RED<<"!->TCP "<<YELLOW<<"\\ close! \\ "<<RED<<number<<GREEN<<"  smtp"<<endl;
				}
				if(number==37){
				    cout<<RED<<"!->TCP "<<YELLOW<<"\\ close! \\ "<<RED<<number<<GREEN<<"  time"<<endl;
				}
				if(number==39){
				    cout<<RED<<"!->TCP "<<YELLOW<<"\\ close! \\ "<<RED<<number<<GREEN<<"  rlp"<<endl;
				}
				if(number==42){
				    cout<<RED<<"!->TCP "<<YELLOW<<"\\ close! \\ "<<RED<<number<<GREEN<<"  nameserver"<<endl;
				}
				if(number==43){
				    cout<<RED<<"!->TCP "<<YELLOW<<"\\ close! \\ "<<RED<<number<<GREEN<<"  nickname"<<endl;
				}
				if(number==49){
				    cout<<RED<<"!->TCP "<<YELLOW<<"\\ close! \\ "<<RED<<number<<GREEN<<"  tacacs"<<endl;
				}
				if(number==50){
				    cout<<RED<<"!->TCP "<<YELLOW<<"\\ close! \\ "<<RED<<number<<GREEN<<"  re-mail-ck"<<endl;
				}
				if(number==53){
				    cout<<RED<<"!->TCP "<<YELLOW<<"\\ close! \\ "<<RED<<number<<GREEN<<"  domain"<<endl;
				}
				if(number==63){
				    cout<<RED<<"!->TCP "<<YELLOW<<"\\ close! \\ "<<RED<<number<<GREEN<<"  whois++"<<endl;
				}
				if(number==66){
				    cout<<RED<<"!->TCP "<<YELLOW<<"\\ close! \\ "<<RED<<number<<GREEN<<"  Oracle SQLNet"<<endl;
				}
				if(number==70){
				    cout<<RED<<"!->TCP "<<YELLOW<<"\\ close! \\ "<<RED<<number<<GREEN<<"  gopher"<<endl;
				}
				if(number==79){
				    cout<<RED<<"!->TCP "<<YELLOW<<"\\ close! \\ "<<RED<<number<<GREEN<<"  finjer"<<endl;
				}
				if(number==80){
				    cout<<RED<<"!->TCP "<<YELLOW<<"\\ close! \\ "<<RED<<number<<GREEN<<"  http"<<endl;
				}
				if(number==88){
				    cout<<RED<<"!->TCP "<<YELLOW<<"\\ close! \\ "<<RED<<number<<GREEN<<"  kerberos"<<endl;
				}
				if(number==95){
				    cout<<RED<<"!->TCP "<<YELLOW<<"\\ close! \\ "<<RED<<number<<GREEN<<"  supdup"<<endl;
				}
				if(number==101){
				    cout<<RED<<"!->TCP "<<YELLOW<<"\\ close! \\ "<<RED<<number<<GREEN<<"  hostname"<<endl;
				}
				if(number==107){
				    cout<<RED<<"!->TCP "<<YELLOW<<"\\ close! \\ "<<RED<<number<<GREEN<<"  rtelnet"<<endl;
				}
				if(number==109){
				    cout<<RED<<"!->TCP "<<YELLOW<<"\\ close! \\ "<<RED<<number<<GREEN<<"  pop2"<<endl;
				}
				if(number==110){
				    cout<<RED<<"!->TCP "<<YELLOW<<"\\ close! \\ "<<RED<<number<<GREEN<<"  pop3"<<endl;
				}
				if(number==111){
				    cout<<RED<<"!->TCP "<<YELLOW<<"\\ close! \\ "<<RED<<number<<GREEN<<"  sunrpc"<<endl;
				}
				if(number==113){
				    cout<<RED<<"!->TCP "<<YELLOW<<"\\ close! \\ "<<RED<<number<<GREEN<<"  auth"<<endl;
				}
				if(number==115){
				    cout<<RED<<"!->TCP "<<YELLOW<<"\\ close! \\ "<<RED<<number<<GREEN<<"  sftp"<<endl;
				}
				if(number==117){
				    cout<<RED<<"!->TCP "<<YELLOW<<"\\ close! \\ "<<RED<<number<<GREEN<<"  uupc-path"<<endl;
				}
				if(number==119){
				    cout<<RED<<"!->TCP "<<YELLOW<<"\\ close! \\ "<<RED<<number<<GREEN<<"  nntp"<<endl;
				}
				if(number==135){
				    cout<<RED<<"!->TCP "<<YELLOW<<"\\ close! \\ "<<RED<<number<<GREEN<<"  epmap"<<endl;
				}
				if(number==139){
				    cout<<RED<<"!->TCP "<<YELLOW<<"\\ close! \\ "<<RED<<number<<GREEN<<"  netbios-ns"<<endl;
				}
				if(number==143){
				    cout<<RED<<"!->TCP "<<YELLOW<<"\\ close! \\ "<<RED<<number<<GREEN<<"  imap"<<endl;
				}
				if(number==174){
				    cout<<RED<<"!->TCP "<<YELLOW<<"\\ close! \\ "<<RED<<number<<GREEN<<"  mailq"<<endl;
				}
				if(number==177){
				    cout<<RED<<"!->TCP "<<YELLOW<<"\\ close! \\ "<<RED<<number<<GREEN<<"  xdmcp"<<endl;
				}
				if(number==178){
				    cout<<RED<<"!->TCP "<<YELLOW<<"\\ close! \\ "<<RED<<number<<GREEN<<"  nextstep"<<endl;
				}
				if(number==179){
				    cout<<RED<<"!->TCP "<<YELLOW<<"\\ close! \\ "<<RED<<number<<GREEN<<"  bgp"<<endl;
				}
				if(number==194){
				    cout<<RED<<"!->TCP "<<YELLOW<<"\\ close! \\ "<<RED<<number<<GREEN<<"  irc"<<endl;
				}
				if(number==199){
				    cout<<RED<<"!->TCP "<<YELLOW<<"\\ close! \\ "<<RED<<number<<GREEN<<"  smux"<<endl;
				}
				if(number==201){
				    cout<<RED<<"!->TCP "<<YELLOW<<"\\ close! \\ "<<RED<<number<<GREEN<<"  at-rtmp"<<endl;
				}
				if(number==202){
				    cout<<RED<<"!->TCP "<<YELLOW<<"\\ close! \\ "<<RED<<number<<GREEN<<"  at-nbp"<<endl;
				}
				if(number==204){
				    cout<<RED<<"!->TCP "<<YELLOW<<"\\ close! \\ "<<RED<<number<<GREEN<<"  at-echo"<<endl;
				}
				if(number==206){
				    cout<<RED<<"!->TCP "<<YELLOW<<"\\ close! \\ "<<RED<<number<<GREEN<<"  at-zis"<<endl;
				}
				if(number==209){
				    cout<<RED<<"!->TCP "<<YELLOW<<"\\ close! \\ "<<RED<<number<<GREEN<<"  qmtp"<<endl;
				}
				if(number==210){
				    cout<<RED<<"!->TCP "<<YELLOW<<"\\ close! \\ "<<RED<<number<<GREEN<<"  z39.50"<<endl;
				}
				if(number==213){
				    cout<<RED<<"!->TCP "<<YELLOW<<"\\ close! \\ "<<RED<<number<<GREEN<<"  ipx"<<endl;
				}
				if(number==220){
				    cout<<RED<<"!->TCP "<<YELLOW<<"\\ close! \\ "<<RED<<number<<GREEN<<"  imap3"<<endl;
				}
				if(number==245){
				    cout<<RED<<"!->TCP "<<YELLOW<<"\\ close! \\ "<<RED<<number<<GREEN<<"  link"<<endl;
				}
				if(number==347){
				    cout<<RED<<"!->TCP "<<YELLOW<<"\\ close! \\ "<<RED<<number<<GREEN<<"  fatserv"<<endl;
				}
				if(number==363){
				    cout<<RED<<"!->TCP "<<YELLOW<<"\\ close! \\ "<<RED<<number<<GREEN<<"  rsvp_tunnel"<<endl;
				}
				if(number==369){
				    cout<<RED<<"!->TCP "<<YELLOW<<"\\ close! \\ "<<RED<<number<<GREEN<<"  rpc2portmap"<<endl;
				}
				if(number==370){
				    cout<<RED<<"!->TCP "<<YELLOW<<"\\ close! \\ "<<RED<<number<<GREEN<<"  codaauth2"<<endl;
				}
				if(number==372){
				    cout<<RED<<"!->TCP "<<YELLOW<<"\\ close! \\ "<<RED<<number<<GREEN<<"  ulistproc"<<endl;
				}
				if(number==389){
				    cout<<RED<<"!->TCP "<<YELLOW<<"\\ close! \\ "<<RED<<number<<GREEN<<"  Idap"<<endl;
				}
				if(number==427){
				    cout<<RED<<"!->TCP "<<YELLOW<<"\\ close! \\ "<<RED<<number<<GREEN<<"  svrloc"<<endl;
				}
				if(number==434){
				    cout<<RED<<"!->TCP "<<YELLOW<<"\\ close! \\ "<<RED<<number<<GREEN<<"  mobileip-agent"<<endl;
				}
				if(number==435){
				    cout<<RED<<"!->TCP "<<YELLOW<<"\\ close! \\ "<<RED<<number<<GREEN<<"  tcpmux"<<endl;
				}
				if(number==443){
				    cout<<RED<<"!->TCP "<<YELLOW<<"\\ close! \\ "<<RED<<number<<GREEN<<"  https"<<endl;
				}
				if(number==444){
				    cout<<RED<<"!->TCP "<<YELLOW<<"\\ close! \\ "<<RED<<number<<GREEN<<"  snpp"<<endl;
				}
				if(number==445){
				    cout<<RED<<"!->TCP "<<YELLOW<<"\\ close! \\ "<<RED<<number<<GREEN<<"  microsoft-ds"<<endl;
				}
				if(number==465){
				    cout<<RED<<"!->TCP "<<YELLOW<<"\\ close! \\ "<<RED<<number<<GREEN<<"  smtps"<<endl;
				}
				if(number==512){
				    cout<<RED<<"!->TCP "<<YELLOW<<"\\ close! \\ "<<RED<<number<<GREEN<<"  exec"<<endl;
				}
				if(number==513){
				    cout<<RED<<"!->TCP "<<YELLOW<<"\\ close! \\ "<<RED<<number<<GREEN<<"  rlogin"<<endl;
				}
				if(number==514){
				    cout<<RED<<"!->TCP "<<YELLOW<<"\\ close! \\ "<<RED<<number<<GREEN<<"  syslog"<<endl;
				}
				if(number==515){
				    cout<<RED<<"!->TCP "<<YELLOW<<"\\ close! \\ "<<RED<<number<<GREEN<<"  WindowsPrinter"<<endl;
				}
				if(number==587){
				    cout<<RED<<"!->TCP "<<YELLOW<<"\\ close! \\ "<<RED<<number<<GREEN<<"  smtp"<<endl;
				}
				if(number==591){
				    cout<<RED<<"!->TCP "<<YELLOW<<"\\ close! \\ "<<RED<<number<<GREEN<<"  fileMaker"<<endl;
				}
				if(number==631){
				    cout<<RED<<"!->TCP "<<YELLOW<<"\\ close! \\ "<<RED<<number<<GREEN<<"  cups"<<endl;
				}
				if(number==666){
				    cout<<RED<<"!->TCP "<<YELLOW<<"\\ close! \\ "<<RED<<number<<GREEN<<"  Doom"<<endl;
				}
				if(number==690){
				    cout<<RED<<"!->TCP "<<YELLOW<<"\\ close! \\ "<<RED<<number<<GREEN<<"  vatp"<<endl;
				}
				if(number==993){
				    cout<<RED<<"!->TCP "<<YELLOW<<"\\ close! \\ "<<RED<<number<<GREEN<<"  imap4SSL"<<endl;
				}
				if(number==995){
				    cout<<RED<<"!->TCP "<<YELLOW<<"\\ close! \\ "<<RED<<number<<GREEN<<"  pop3SSL"<<endl;
				}
				if(number>996){
				    cout<<RED<<"!->TCP "<<YELLOW<<"\\ close! \\ "<<RED<<number<<GREEN<<"  know"<<endl;
				}

    			close(enchufe);
    			return 1;
    		}
    		if(number==1){
    			cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  tcpmux"<<endl;
    		}
			if(number==5){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  rje"<<endl;
			}
			if(number==7){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  echo"<<endl;
			}
			if(number==9){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  discard"<<endl;
			}
			if(number==11){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  systat"<<endl;
			}
			if(number==13){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  daytime"<<endl;
			}
			if(number==17){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  qotd"<<endl;
			}
			if(number==18){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  msp"<<endl;
			}
			if(number==19){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  chargen"<<endl;
			}
			if(number==20){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  ftpS-data"<<endl;
			}
			if(number==21){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  ftp-control"<<endl;
			}
			if(number==22){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  ssh"<<endl;
			}
			if(number==23){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  telnet"<<endl;
			}
			if(number==25){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  smtp"<<endl;
			}
			if(number==37){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  time"<<endl;
			}
			if(number==39){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  rlp"<<endl;
			}
			if(number==42){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  nameserver"<<endl;
			}
			if(number==43){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  nickname"<<endl;
			}
			if(number==49){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  tacacs"<<endl;
			}
			if(number==50){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  re-mail-ck"<<endl;
			}
			if(number==53){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  domain"<<endl;
			}
			if(number==63){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  whois++"<<endl;
			}
			if(number==66){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  Oracle SQLNet"<<endl;
			}
			if(number==70){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  gopher"<<endl;
			}
			if(number==79){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  finjer"<<endl;
			}
			if(number==80){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  http"<<endl;
			}
			if(number==88){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  kerberos"<<endl;
			}
			if(number==95){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  supdup"<<endl;
			}
			if(number==101){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  hostname"<<endl;
			}
			if(number==107){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  rtelnet"<<endl;
			}
			if(number==109){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  pop2"<<endl;
			}
			if(number==110){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  pop3"<<endl;
			}
			if(number==111){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  sunrpc"<<endl;
			}
			if(number==113){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  auth"<<endl;
			}
			if(number==115){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  sftp"<<endl;
			}
			if(number==117){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  uupc-path"<<endl;
			}
			if(number==119){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  nntp"<<endl;
			}
			if(number==135){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  epmap"<<endl;
			}
			if(number==139){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  netbios-ns"<<endl;
			}
			if(number==143){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  imap"<<endl;
			}
			if(number==174){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  mailq"<<endl;
			}
			if(number==177){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  xdmcp"<<endl;
			}
			if(number==178){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  nextstep"<<endl;
			}
			if(number==179){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  bgp"<<endl;
			}
			if(number==194){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  irc"<<endl;
			}
			if(number==199){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  smux"<<endl;
			}
			if(number==201){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  at-rtmp"<<endl;
			}
			if(number==202){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  at-nbp"<<endl;
			}
			if(number==204){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  at-echo"<<endl;
			}
			if(number==206){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  at-zis"<<endl;
			}
			if(number==209){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  qmtp"<<endl;
			}
			if(number==210){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  z39.50"<<endl;
			}
			if(number==213){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  ipx"<<endl;
			}
			if(number==220){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  imap3"<<endl;
			}
			if(number==245){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  link"<<endl;
			}
			if(number==347){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  fatserv"<<endl;
			}
			if(number==363){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  rsvp_tunnel"<<endl;
			}
			if(number==369){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  rpc2portmap"<<endl;
			}
			if(number==370){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  codaauth2"<<endl;
			}
			if(number==372){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  ulistproc"<<endl;
			}
			if(number==389){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  Idap"<<endl;
			}
			if(number==427){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  svrloc"<<endl;
			}
			if(number==434){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  mobileip-agent"<<endl;
			}
			if(number==435){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  tcpmux"<<endl;
			}
			if(number==443){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  https"<<endl;
			}
			if(number==444){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  snpp"<<endl;
			}
			if(number==445){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  microsoft-ds"<<endl;
			}
			if(number==465){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  smtps"<<endl;
			}
			if(number==512){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  exec"<<endl;
			}
			if(number==513){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  rlogin"<<endl;
			}
			if(number==514){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  syslog"<<endl;
			}
			if(number==515){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  WindowsPrinter"<<endl;
			}
			if(number==587){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  smtp"<<endl;
			}
			if(number==591){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  fileMaker"<<endl;
			}
			if(number==631){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  cups"<<endl;
			}
			if(number==666){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  Doom"<<endl;
			}
			if(number==690){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  vatp"<<endl;
			}
			if(number==993){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  imap4SSL"<<endl;
			}
			if(number==995){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  pop3SSL"<<endl;
			}
			if(number>996){
			    cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<number<<GREEN<<"  know"<<endl;
			}
    		close(enchufe);
    		return 0;
    		
    	}
};

class Alert{
    public:
    	void alert_bc(){
    		cout<<"Specify an address for use: -Bs <ip>"<<endl;
		}	
		void alert_sp(){
    		cout<<"Specify an address and port for -sP\nusage: -sP <ip> <port>"<<endl;
		}
		void alert_sp_b(){
    		cout<<"Specify an address and port for -sP\nusage: -sP <ip> <port>"<<endl;
		}
		void alert_http_get(){
    		cout<<"Specify an address for -httpGET\nusage: -httpGET <ip or address>"<<endl;
		}
		void alert_https_get(){
    		cout<<"Specify an address for -httpsGET\nusage: -httpsGET <url>"<<endl;
		}
		void alert_hp(){
    		cout<<"Specify a URL for -httpPOST\nusage: -httpPOST <url>"<<endl;
		}
		void alert_code(){
    		cout<<"Specify a URL for -httpSTATUSCODE\nusage: -httpSTATUSCODE <url>"<<endl;
		}
		void alert_ss(){
    		cout<<"Specify an address for -sS\nusage: -sS <address>"<<endl;
		}

};

int main(int argc, char *argv[]){
	//auto inicio = steady_clock::now();
	
	if(argc==1){
		printf("Specify an argument\n use --help for more information\n");
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
								}else{
									int result_ff = strcmp(argv[1], "-httpPOST");
									if(result_ff==0){
										//TEXTO
										Alert maniatico;
										Alert* monico = &maniatico;
										monico->alert_hp();
									}else{
										int result_gg = strcmp(argv[1], "-httpSTATUSCODE");
										if(result_gg==0){
											Alert ben;
											Alert* ven = &ben;
											ven->alert_code();
										}else{
											int result_hh = strcmp(argv[1], "-sS");
											if(result_hh==0){
												Alert ss;
												Alert* rr = &ss;
												rr->alert_ss();
												}
											}
										}
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
					//=================================================
					Mess ban;
					Mess* main = &ban;
					main->banner();

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
					cout<<GREEN<<"PortSeeker done: 10,000 ports scanned in "<<fixed<<setprecision(2)<<decimal;
					cout<<" seconds"<<RESET<<endl;

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
							Mess calculo;
							Mess* modulo = &calculo;
							modulo->banner();
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
							cout<<GREEN<<"PortSeeker done: HTTP_GET in "<<fixed<<setprecision(2)<<decimal_a;
							cout<<" seconds"<<RESET<<endl;
						}else{
							int verificador_c = strcmp(argv[1], "-httpsGET");
							if(verificador_c==0){
								auto peticion = steady_clock::now();
								Mess kk;
								Mess* kkk = &kk;
								kkk->httpGET_scan();
								Mess canada;
								Mess* cana = &canada;
								cana->banner();
								Enchufe elMal;
								Enchufe* local = &elMal;
								local->peticion_https_Get(argv[2]);
								auto peticion_final = steady_clock::now();
								duration<double> duration = peticion_final - peticion;
								double httpsget = duration.count();
								double fatores = pow(10, 2);
								double decimal_b = round(httpsget * fatores) / fatores;
								cout<<GREEN<<"PortSeeker done: HTTPS_GET in "<<fixed<<setprecision(2)<<decimal_b;
								cout<<" seconds"<<RESET<<endl;
							}else{
								int var = strcmp(argv[1], "-httpPOST");
								if(var==0){
									//AGREGAR FUNCION HTTP POST
									cout<<"Correct command"<<endl;
								}else{
									int log_b = strcmp(argv[1], "-httpSTATUSCODE");
									if(log_b==0){
										auto repeticion = steady_clock::now();
										Mess pedro_fuma_piedra;
										Mess* log = &pedro_fuma_piedra;
										Mess megamente;
										Mess* puntero = &megamente;
										puntero->banner();
										log->code_status();
										Mess kk;
										Mess* poli = &kk;
										poli->http_get_status(argv[2]);
										auto peticion_lac = steady_clock::now();
										duration<double> duration = peticion_lac-repeticion;
										double httpsget = duration.count();
										double factores = pow(10, 2);
										double decimal = round(httpsget * factores) / factores;
										cout<<GREEN<<"PortSeeker done : HTTPSTATUSCODE in "<<fixed<<setprecision(2)<<decimal;
										cout<<" seconds"<<RESET<<endl;
									}else{
										int controlador = strcmp(argv[1], "-sS");
										if(controlador==0){
											Mess localizador;
											Mess* flecha = &localizador;
											flecha->banner();
											Mess local;
											Mess* cara = &local;
											cara->silent_scanner();
											auto completo = steady_clock::now();
											Enchufe manager;
											Enchufe* colador = &manager;
											for(int log=0; log<10001;log++){
												colador->silent_scan(argv[2], log);
												system("sleep 1.5");
											}
											auto finales = steady_clock::now();
											duration<double> duration = finales-completo;
											double httpsget = duration.count();
											double caracol = pow(10, 2);
											double valor = round(httpsget * caracol) / caracol;
											cout<<GREEN<<"PortSeeker done: SilentScan in "<<fixed<<setprecision(2)<<caracol;
											cout<<" seconds"<<RESET<<endl;
										}
									}
								}
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
						Mess texto;
						Mess* manager = &texto;
						manager->banner();
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
						cout<<"PortSeeker done: 1 ports scanned in "<<fixed<<setprecision(2)<<decimal_ss;
						cout<<" seconds"<<endl;
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
