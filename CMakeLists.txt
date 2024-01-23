cmake_minimum_required(VERSION 3.10)
project(main)

# Spécifiez la version de C
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Définissez le répertoire des sources
set(SOURCE_DIR src)

# Recherchez la bibliothèque GMP
find_library(GMP_LIB gmp REQUIRED)

# Collectez les fichiers source
file(GLOB_RECURSE SOURCES ${SOURCE_DIR}/*.c)

# Créez l'exécutable à partir des sources
add_executable(main ${SOURCES})

# Liez l'exécutable à la bibliothèque GMP
target_link_libraries(main ${GMP_LIB})

# Incluez les en-têtes
target_include_directories(main PRIVATE ${SOURCE_DIR})