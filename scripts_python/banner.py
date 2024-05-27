import os
import time
import random
import colorama
import subprocess
from colorama import Fore


ran = random.choice([Fore.RED, Fore.GREEN, Fore.YELLOW, Fore.MAGENTA, Fore.BLUE]);
nar = random.choice(["ban1.txt", "ban2.txt", "ban3.txt"])

print(ran)
subprocess.run(["cat", f"./banner/{nar}"])
print(Fore.RESET);