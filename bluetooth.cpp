#include<iostream>
#include<stdlib.h>
#include<cstring>
#include<sstream>
using namespace std;

int lister_bluetooth(){
	system("python3 scripts_python/blue.py");
	return 0;

}
int connected_bluetooth(string macaddress){
	stringstream Jojo;
    Jojo<<"python3 scripts_python/blue2.py -a "<<macaddress;
    system(Jojo.str().c_str());
    return 0;
}