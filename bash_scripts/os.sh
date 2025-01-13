sudo nmap -oG - $1 -O | grep -v '#' | grep OS | awk '{print $13 $14 $15}'
