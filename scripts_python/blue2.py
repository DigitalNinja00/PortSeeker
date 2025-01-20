import asyncio
from bleak import BleakClient
import argparse
parse = argparse.ArgumentParser()
parse.add_argument("-a", "--address", help="MAC ADDRESS");
args = parse.parse_args();
async def connect_to_bluetooth_device(device_address):
    async with BleakClient(device_address) as client:
        if client.is_connected:
            print(f"Connected {device_address}")
        else:
            print(f"Error connecting {device_address}")
asyncio.run(connect_to_bluetooth_device(args.address))
