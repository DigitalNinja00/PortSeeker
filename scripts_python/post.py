import os
import time
import argparse
import requests

parse = argparse.ArgumentParser("options");
parse.add_argument("-d", "--direccion");
args = parse.parse_args();

def function_number_status():
	try:
		res = requests.get(args.direccion);
		print("Codigo de estado: ", res.status_code)
		print(res.url)
	except OSError:
		print("Error al obtener numero de estado")
function_number_status()