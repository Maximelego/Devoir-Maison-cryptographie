# Devoir Maison cryptographie

## Guide d'installation du programme.

### Pré-requis :

Ce programme C nécessite les outils suivants : 

- CMake (VERSION 3.10)
- Makefile
- gcc
- libgmp-dev (peut être installé avec l'exécution du CMakeLists.txt s'il n'est pas détecté)

### Installation et exécution :

Placez vous dans le dossier du programme avec votre terminal de commandes.

Création du repertoire build: 

```bash
chmod +x ./build.sh
./build.sh
```

Si libgmp-dev n'est pas disponible sur votre environnement, le programme cmake tentera de l'installer avec apt. Ceci est une action nécessitant un compte utilisateur *sudo*.

Exécution du projet :

```bash
./build/main
```

Autres commandes (il faudra se placer dans le répertoire build pour pouvoir exécuter les commandes make) : 

```bash
make clean  # Permet de nettoyer les fichiers compilés du projet.
make help   # Affiche une liste des commandes proposées par le makefile.

rm -r build # Permet de nettoyer le dossier build contenant les fichiers compilés par le makefile ainsi que ceux du cmake.
```