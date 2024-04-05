echo "[*] Instalando librerias"
sudo apt -y install libcurl4-openssl-dev
sudo apt -y install g++
echo "[+] Compilando fichero <compile.cpp>"
g++ compile.cpp -o prtker -std=c++11 -lcurl
sudo chmod +x prtker
