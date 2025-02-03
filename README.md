# PortSeeker version: 3.0
```
A port scanner that allows you to scan a wide range of ports, with different functions for different network protocols.
```
<center>
    <img src="logo.jpeg"><br>
    <img src="011.png">
    <img src="02.jpg">
</center>
* 
Port Scanner, opensource and programmed in C++ for linux distros.

# Free Open-Source vulnerability scanner

# For arch based distros
##You need to run this program with administrator permissions
```
sudo bash arch_start.sh
./prtker -h
```
# For debian based distros
```
sudo bash debian_start.sh
sudo ./prtker

```
# execute
```
sudo ./prtker -h
```
# MANUAL INSTALACION

# install dependencies for ArchLinux

```
sudo pacman -Syy
sudo pacman -S python
sudo pacman -S python-pip
sudo pacman -S nc
sudo pacman -S nmap
sudo pacman -S arping
sudo pacman -S gcc
sudo pacman -S curl
```

# install dependencies for debian
```
sudo apt -y install libcurl4-openssl-dev
sudo apt -y install g++
sudo apt -y install netcat
sudo apt -y install nc
sudo apt -y install arping
sudo apt -y install nmap
sudo apt -y install python3
sudo apt -y install python3-pip
```
# install python3 libraries

```
pip3 install scapy --break-system-packages
pip3 install colorama --break-system-packages
pip3 install asyncio --break-system-packages
pip3 install bleak --break-system-packages
```
# OR
```
pip3 install -r requirements.txt --break-system-packages
```
### COMPILE CODE
```
g++ -c main.cpp
g++ -c sockk.cpp
g++ -c bluetooth.cpp
g++ -c info.cpp
g++ main.o sockk.o bluetooth.o info.o -o prtker -lcurl
```
# Commands LAN

## How to do a basic scan?
To achieve this we need to run our executable, then specify the address we want to scan, in this case 192.168.1.1 will be used as an example.
```
./prtker 192.168.1.1
```

## How to do a port version scan?
To achieve this we must run the program and specify an address followed by the -sV argument that will perform a port version scan.
```
`./prtker 192.168.1.1 -sV
```
## How to scan a specific port?
To achieve this we must specify as argument ADDRESS> PARSE> PORT>
```
`./prtker 192.168.1.1 -p 8080
```
## What is -httpGET used for?
It works to make an http get request to an address provided by the user, the usage is as follows:
```
./prtker 192.168.1.1 --httpGET
```
## What is -httpsGET used for?
This, unlike the previous one, works to make a request via the https protocol to an http server provided by the user.
```
./prtker 192.168.1.1 --httpsGET
```
## How can I get the MAC address of a remote computer?
For those who like to obtain information about a target, it never hurts to know its MAC address. PortSeeker has a function that allows the user to use an ARP request to obtain the MAC address of a remote computer within the same network.
```
./prtker 192.168.1.1 --arp
```
## How do I make an icmp request?
PortSeeker also has a function to make requests under the ICMP protocol (ping) which in certain cases can be used to discover the operating system of a target, although it is not recommended because it is not very functional.
```
./prtker 192.168.1.1 --icmp
```
## How do I detect the operating system with PortSeeker?
To obtain the operating system of a remote computer using PortSeeker is quite simple, you just have to write the following:
```
./prtker 192.168.1.1 --osdetection
```

# Commands BLUETOOTH

PortSeeker also has functions to scan via Bluetooth, to start this process we must enable the Bluetooth service on our device.

```
systemctl start bluetooth.service
```
OR
```
service bluetooth start
```

### Now to list the bluetooth devices in our network is quite simple

```
./prtker --list-bluetooth
```

And how do we connect? It's very simple.
```
./prtker <FF:FF:FF:FF:FF> --bluetooth-connect
```

## info commands
```
./prtker --help
./prtker -h
./prtker --version
```
## Improvements:

```
>>> New documentation, improvements and optimization in the code
>>> New features for bluetooth
>>> New function for ICMP requests
>>> New function to obtain mac address
>>> Http and https requests are returned
>>> Now with new help menu with the "--help" option
>>> Optimized code
>>> new port version scanning function
>>> New colors on console ***
>>> New feature for quieter network scans
>>> Feature to obtain server status code
>>> Performance improvement
>>> Friendlier Banner and UI
```

## Authors

@DigitalNinja00
@jsposu
@Cr0w-ui