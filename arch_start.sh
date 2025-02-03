sudo pacman -Syy
sudo pacman -S python
sudo pacman -S python-pip
sudo pacman -S nc
sudo pacman -S nmap
sudo pacman -S arping
sudo pacman -S gcc
sudo pacman -S curl

pip3 install scapy --break-system-packages
pip3 install colorama --break-system-packages
pip3 install asyncio --break-system-packages
pip3 install bleak --break-system-packages

g++ -c main.cpp
g++ -c sockk.cpp
g++ -c bluetooth.cpp
g++ -c info.cpp
g++ main.o sockk.o bluetooth.o info.o -o prtker -lcurl
