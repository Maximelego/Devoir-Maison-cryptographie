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

Création du makefile : 
```bash
mkdir build
cd build
cmake ..
```

Si libgmp-dev n'est pas disponible sur votre environnement, le programme cmake tentera de l'installer avec apt. Ceci est une action nécessitant un compte utilisateur *sudo*.
 
Build du projet :
```bash
make
```

Exécution du projet :
```bash
./main
```

Autres commandes : 
```bash
make clean  # Permet de nettoyer les fichiers compilés du projet.
make help   # Affiche une liste des commandes proposées par le makefile.
rm -r build # Permet de nettoyer le dossier build contenant les fichiers compilés par le makefile ainsi que ceux du cmake.
```

## Documentation des fonctions de base GMP proposée par ChatGPT.

Voici une brève présentation détaillée des principales fonctions de la bibliothèque GMP pour les entiers (mpz_t) :

### Initialisation et libération :

    `void mpz_init(mpz_t op)` : Initialise une variable GMP op pour stocker un entier.
    `void mpz_clear(mpz_t op)` : Libère la mémoire allouée pour la variable GMP op.

### Opérations arithmétiques :

    `void mpz_add(mpz_t rop, const mpz_t op1, const mpz_t op2)` : Ajoute les entiers op1 et op2 et stocke le résultat dans rop.
    `void mpz_sub(mpz_t rop, const mpz_t op1, const mpz_t op2)` : Soustrait op2 de op1 et stocke le résultat dans rop.
    `void mpz_mul(mpz_t rop, const mpz_t op1, const mpz_t op2)` : Multiplie les entiers op1 et op2 et stocke le résultat dans rop.
    `void mpz_div(mpz_t quot, const mpz_t num, const mpz_t denom)` : Divise num par denom et stocke le quotient dans quot.

Ces fonctions ont également des versions avec des opérations combinées, comme mpz_add_ui, mpz_sub_ui, mpz_mul_ui, mpz_div_ui, qui effectuent l'opération avec un entier constant.

### Comparaisons :

    int mpz_cmp(const mpz_t op1, const mpz_t op2) : Compare les entiers op1 et op2. Renvoie une valeur négative si op1 < op2, 0 si op1 = op2, et une valeur positive si op1 > op2.
    int mpz_cmp_ui(const mpz_t op1, unsigned long int op2) : Compare op1 avec l'entier constant op2.
    int mpz_cmpabs(const mpz_t op1, const mpz_t op2) : Compare les valeurs absolues de op1 et op2.

### Opérations bit à bit :

    void mpz_and(mpz_t rop, const mpz_t op1, const mpz_t op2) : Effectue un ET bit à bit entre op1 et op2 et stocke le résultat dans rop.
    void mpz_or(mpz_t rop, const mpz_t op1, const mpz_t op2) : Effectue un OU bit à bit entre op1 et op2 et stocke le résultat dans rop.
    void mpz_xor(mpz_t rop, const mpz_t op1, const mpz_t op2) : Effectue un OU exclusif bit à bit entre op1 et op2 et stocke le résultat dans rop.

Ces fonctions ont également des versions avec des opérations combinées, comme mpz_and_ui, mpz_ior_ui, mpz_xor_ui, qui effectuent l'opération avec un entier constant.

### Opérations sur les bits :

    void mpz_setbit(mpz_t rop, unsigned long int bit_index) : Positionne à 1 le bit d'index bit_index dans rop.
    void mpz_clrbit(mpz_t rop, unsigned long int bit_index) : Positionne à 0 le bit d'index bit_index dans rop.
    int mpz_tstbit(const mpz_t op, unsigned long int bit_index) : Renvoie 1 si le bit d'index bit_index dans op est positionné à 1, sinon 0.

Ces fonctions ne représentent qu'une petite partie des fonctionnalités offertes par la bibliothèque GMP pour les entiers. Pour plus d'informations, vous pouvez consulter la documentation officielle de GMP sur le site web de GNU : Documentation GMP - Fonctions pour les entiers.