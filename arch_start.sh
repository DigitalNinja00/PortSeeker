sudo pacman -Syy
sudo pacman -S python
sudo pacman -S python-pip
sudo pacman -S nc
sudo pacman -S nmap
sudo pacman -S arping
sudo pacman -S gcc
sudo pacman -S curl

pip3 install scapy --break-system-packages

g++ setup.cpp -o prtker -std=c++11 -lcurl
