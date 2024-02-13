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
./build/main <args>
```

Certains flags peuvent être utilisés à l'emplacement <args>, ils sont détaillés plus loin dans ce README.

Autres commandes (il faudra se placer dans le répertoire build pour pouvoir exécuter les commandes make) : 

```bash
make clean  # Permet de nettoyer les fichiers compilés du projet.
make help   # Affiche une liste des commandes proposées par le makefile.

rm -r build # Permet de nettoyer le dossier build contenant les fichiers compilés par le makefile ainsi que ceux du cmake.
```

## Arguments et Constantes

Ce programme a été développé dans l'optique de forunir diverses options pour le lancement du programme. Pour ce faire, plusieurs arguments ou paramètres peuvent y être modifiés / ajoutés.

### Arguments

Deux arguments peuvent être utilisés. Ils modifient complètement le comportement du programme :

- **-f**  : Fast mode. Ce flag permet d'exécuter des versions optimisées des tests, utilisant les fonctions implémentées par la librarie GMP. Les tests concernés sont les suivants : **Eval()** et **ExpMod()**. Il n'est pas intéressant d'utiliser ce flag pour vérifier les résultats des méthodes demandées dans le sujet, mais l'exécution du code est environ 20 fois plus rapide.

- **-t**  : Threaded Mode. Ce flag permet d'exécuter la majorité des tests en parallèle grâce à la librairie OpenMP. Le programme va alors utiliser autant de threads que possible en étant limité par la constante pré-processeur **ALLOCATED_CORES** détaillée ci-après.

Il est possible de combiner les deux flags pour obtenir le meilleur temps d'exécution possible. Ils peuvent être précisés dans n'importe quel ordre. Tout autre argument sera ignoré. Si ces flags sont situés après 2 arguments, ils seront ignorés.

### Constantes

Dans le fichier constants.h (situé au chemin **src/include/constants.h**), plusieurs constantes pré-processeurs ont été fournies.

#### Modes de Log

- *DEBUG_MODE*  : Cette constante est interprétée comme un booléen et permet d'afficher des informations sur le déroulement de l'exécution dans la sortie standard. Elle permet notamment d'afficher le temps d'exécution total tu programme.

- *LOG_TO_FILE* : Cette constante est interprétée comme un booléen et permet de stocker les résultats des différents tests dans des fichiers .txt situés à la raçine du projet. Ces fichiers sont nommés selon la syntaxe "output_<nom du test>.txt". **ATTENTION** : Ces fichiers sont des fichiers "temporaires", ils seront donc supprimés à l'exécution du script **clean.sh** ou lors d'une nouvelle exécution du programme, si la constante est toujours vraie.

#### Valeurs de Threading

- *ALLOCATED_CORES* : Cette valeur permet d'indiquer au programme le nombre de threads qu'elle peut créer lorsque le flag '-t' est précisé au lancement du script. Il est recommandé de donner à cette valeur, au maximum, le nombre total de coeurs disponibles sur votre processeur (logiques et physiques) - 2. Vous pouvez, bien évidemment, lui en attribuer plus ou moins, mais la stabilité de votre système ne sera pas garantie si cette valeur est trop grande. Si la valeur est négative ou nulle, la valeur 1 sera alors utilisée.

#### Constantes du programme

- *RANDOM_NUMBERS_SIZE* : Permet de définir la taille en bits des nombres générés aléatoirement dans les tests suivants : Decomp(), ExpMod() et test_ExpMods().

- *ITERATION_COUNT* : Permet de définir le nombre d'itérations des tests Decomp() et ExpMod().

- *MILLER_RABIN_ITERATIONS* : Permet de définir le nombre d'itérations que devra effectuer le test de Miller Rabin avant de s'arrêter, si le nombre est observé comme composé.

- *RANDOM_SEED* : Seed nécessaire à la génération des nombres aléatoires.