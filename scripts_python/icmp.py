import sys
from scapy.all import sr1, IP, ICMP

def icmp_ping(destination):
    packet = IP(dst=destination) / ICMP()
    response = sr1(packet, timeout=2)
    if response:
        print(f"Response received : {destination}:")
        response.show()
    else:
        print(f"response not received {destination}")
if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Uso: python icmp.py <address>")
        sys.exit(1)
    destination_ip = sys.argv[1]
    icmp_ping(destination_ip)
