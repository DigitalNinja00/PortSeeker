echo "[*] Instalando librerias"
sudo apt -y install libcurl4-openssl-dev
sudo apt -y install g++
sudo apt -y install netcat
sudo apt -y install nc
sudo apt -y install arping
sudo apt -y install nmap
sudo apt -y install python3
sudo apt -y install python3-pip

pip3 install scapy --break-system-packages
echo "[+] Compilando fichero <setup.cpp>"

g++ setup.cpp -o prtker -std=c++11 -lcurl
