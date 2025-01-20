import asyncio
from bleak import BleakScanner
import colorama
from colorama import Fore
async def listar_dispositivos():
	dispositivos = await BleakScanner.discover();
	for dispositivo in dispositivos:
		print(f"{Fore.RED}MacAdress : {Fore.GREEN}{dispositivo.address}, {Fore.RED}Name: {Fore.GREEN}{dispositivo.name} {Fore.RESET}");
asyncio.run(listar_dispositivos());
