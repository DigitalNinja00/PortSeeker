echo "[*] Instalando librerias"
sudo apt -y install libcurl4-openssl-dev
sudo apt -y install g++
sudo apt -y install netcat
sudo apt -y install nc
echo "[+] Compilando fichero <setup.cpp>"

g++ setup.cpp -o prtker -std=c++11 -lcurl
