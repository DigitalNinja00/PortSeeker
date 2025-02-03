#include<iostream>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<netinet/in.h>
#include<cstring>
#include<string.h>
#include<stdlib.h>
#include "color.h"
#include "httplib.h"
#include<map>
#include<sstream>
#include<curl/curl.h>

using namespace std;

void peticion_http_get(const char* sitioweb){
	httplib::Client client(sitioweb);
	auto response = client.Get("/");
	if(response && response->status == 200){
		cout<<"Response : "<<response->body<<endl;
	}else{
		cout<<"Error sending request"<<endl;
	}
}

static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}
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
int server_version_const(const char* dir, const char* port){
	stringstream colibri;
	colibri<<"bash ./bash_scripts/local.sh "<<dir<<" "<<port;
	system(colibri.str().c_str());
	return 0;
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
int os_function(const char* direccion){
	stringstream vara;
	vara<<"bash ./bash_scripts/os.sh "<<direccion;
	system(vara.str().c_str());
	return 0;
}
int Connect_Socket(const char * hostname, int puerto){
	map<int, string> porter;
	porter[7] = "Echo";
	porter[19] = "CHARGEN";
	porter[20] = "FTP Data";
	porter[21] = "FTP Control";
	porter[22] = "SSH";
	porter[23] = "Telnet";
	porter[25] = "SMTP";
	porter[37] = "Time";
	porter[42] = "Host Name Server";
	porter[43] = "WHOIS";
	porter[49] = "TACACS";
	porter[53] = "DNS";
	porter[67] = "DHCP Server";
	porter[68] = "DHCP Client";
	porter[69] = "TFTP";
	porter[70] = "Gopher";
	porter[79] = "Finger";
	porter[80] = "HTTP";
	porter[88] = "Kerberos";
	porter[102] = "MS Exchange";
	porter[110] = "POP3";
	porter[113] = "Ident";
	porter[119] = "NNTP";
	porter[123] = "NTP";
	porter[137] = "NetBIOS Name Service";
	porter[138] = "NetBIOS Datagram Service";
	porter[139] = "NetBIOS Session Service";
	porter[143] = "IMAP";
	porter[161] = "SNMP";
	porter[162] = "SNMP Trap";
	porter[179] = "BGP";
	porter[194] = "IRC";
	porter[201] = "AppleTalk Routing";
	porter[264] = "BGMP";
	porter[318] = "TSP";
	porter[389] = "LDAP";
	porter[443] = "HTTPS";
	porter[445] = "Microsoft-DS";
	porter[464] = "Kerberos Change/Set Password";
	porter[465] = "SMTP over SSL";
	porter[500] = "ISAKMP";
	porter[512] = "Rexec";
	porter[513] = "Rlogin";
	porter[514] = "Rsh";
	porter[515] = "LPD";
	porter[520] = "RIP";
	porter[521] = "RIPng";
	porter[530] = "RPC";
	porter[543] = "Kerberos Login";
	porter[544] = "Kerberos Shell";
	porter[546] = "DHCPv6 Client";
	porter[547] = "DHCPv6 Server";
	porter[554] = "RTSP";
	porter[563] = "NNTP over SSL";
	porter[587] = "SMTP (Submission)";
	porter[631] = "IPP";
	porter[636] = "LDAP over SSL";
	porter[993] = "IMAP over SSL";
	porter[995] = "POP3 over SSL";
	porter[1025] = "NFS or IIS";
	porter[1026] = "LSA or Direct";
	porter[1027] = "IIS";
	porter[1029] = "MS DCOM";
	porter[1080] = "Socks";
	porter[1194] = "OpenVPN";
	porter[1433] = "Microsoft SQL Server";
	porter[1434] = "Microsoft SQL Monitor";
	porter[1701] = "L2TP";
	porter[1723] = "PPTP";
	porter[1812] = "RADIUS Authentication";
	porter[1813] = "RADIUS Accounting";
	porter[1863] = "MSN Messenger";
	porter[1985] = "HSRP";
	porter[2000] = "Cisco SCCP";
	porter[2049] = "NFS";
	porter[2082] = "CPanel";
	porter[2083] = "CPanel over SSL";
	porter[2100] = "Oracle XDB";
	porter[2222] = "DirectAdmin";
	porter[2600] = "ZebOS RIP";
	porter[2601] = "ZebOS RIPng";
	porter[3128] = "HTTP Proxy";
	porter[3268] = "MS Global Catalog";
	porter[3269] = "MS Global Catalog over SSL";
	porter[3306] = "MySQL";
	porter[3389] = "RDP (Remote Desktop Protocol)";
	porter[3690] = "Subversion";
	porter[3724] = "World of Warcraft";
	porter[3784] = "Ventrilo";
	porter[3785] = "Ventrilo";
	porter[4333] = "mSQL";
	porter[4664] = "Google Desktop";
	porter[4672] = "eMule";
	porter[4899] = "Radmin";
	porter[5000] = "UPnP";
	porter[5001] = "Slingbox";
	porter[5190] = "AOL";
	porter[5222] = "XMPP Client";
	porter[5223] = "XMPP Client over SSL";
	porter[5432] = "PostgreSQL";
	porter[5500] = "VNC";
	porter[5631] = "PC Anywhere";
	porter[5632] = "PC Anywhere";
	porter[5800] = "VNC over HTTP";
	porter[5900] = "VNC";
	porter[6000] = "X11";
	porter[6001] = "X11";
	porter[6667] = "IRC";
	porter[6697] = "IRC over SSL";
	porter[6881] = "BitTorrent";
	porter[6999] = "BitTorrent";
	porter[8080] = "HTTP (Alternate)";
	int sock = socket(AF_INET, SOCK_STREAM, 0);
	if(sock<0){

	}
	struct sockaddr_in servidor;
	servidor.sin_family = AF_INET;
	servidor.sin_port = htons(puerto);
	servidor.sin_addr.s_addr = inet_addr(hostname);
	if(connect(sock, (struct sockaddr*)&servidor, sizeof(servidor)) < 0){
		close(sock);
		return -1;
	}else{

		if(puerto==puerto){
			cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<puerto<<" "<<GREEN<<porter[puerto]<<endl;
			close(sock);
			return -1;
		}else{
			cout<<RED<<">> TCP "<<YELLOW<<"\\ open \\ "<<RED<<puerto<<" "<<GREEN<<porter[puerto]<<endl;
			close(sock);
			return 1;
		}
	}
	return 0;

}
/*
int main(){
	auto inicio = chrono::high_resolution_clock::now();
	Connect_Socket("192.168.43.1", 8080);
	auto fin = chrono::high_resolution_clock::now();
	chrono::duration<double> duracion = fin - inicio;
	cout<<duracion.count()<<endl;
}
*/