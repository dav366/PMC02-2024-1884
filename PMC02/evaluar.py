import json
import subprocess
import sys
from pathlib import Path

if len(sys.argv) != 3:
    print("Uso: python evaluar.py <archivo.json> <ejecutable>")
    sys.exit(2)

archivo_casos = Path(sys.argv[1])
ejecutable = str(Path(sys.argv[2]).resolve())

try:
    casos = json.loads(archivo_casos.read_text(encoding="utf-8"))
except (OSError, json.JSONDecodeError) as error:
    print(f"No se pudo leer el archivo de pruebas: {error}")
    sys.exit(2)

correctos = 0

for caso in casos:
    etiqueta = caso["grupo"]
    try:
        resultado = subprocess.run(
            [ejecutable],
            input=caso["entrada"],
            text=True,
            capture_output=True,
            timeout=2
        )
        pasa = (
            resultado.returncode == 0
            and resultado.stdout.split() == caso["salida"].split()
        )
    except (subprocess.TimeoutExpired, OSError):
        pasa = False

    print(etiqueta, "OK" if pasa else "FALLO")
    if not pasa:
        print("  Salida esperada:", repr(caso["salida"]))
        if "resultado" in locals():
            print("  Salida obtenida:", repr(resultado.stdout))
            if resultado.stderr:
                print("  Error:", resultado.stderr.strip())

    correctos += int(pasa)

print(f"Casos correctos: {correctos} / {len(casos)}")
sys.exit(0 if correctos == len(casos) else 1)
