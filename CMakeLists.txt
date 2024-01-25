cmake_minimum_required(VERSION 3.10)
project(main)

# Spécifiez la version de C
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Définissez le répertoire des sources
set(SOURCE_DIR src)

# Ajoutez les fichiers sources de GMP à votre projet
set(GMP_SOURCE_DIR third-party/gmp)

# Vérifiez si la bibliothèque GMP est déjà installée
find_library(GMP_LIB gmp)

if(NOT GMP_LIB)
    # Si GMP n'est pas installé, essayez de l'installer avec apt
    message("[INFO] - Installing GMP...")
    execute_process(COMMAND sudo apt install -y libgmp-dev
                    RESULT_VARIABLE result
                    OUTPUT_VARIABLE output)

    # Vérifiez le résultat de l'installation
    if(result)
        message(FATAL_ERROR "[ERROR] - Impossible d'installer la bibliothèque GMP : ${output}")
    endif()
endif()

# Collectez les fichiers source de votre projet
file(GLOB_RECURSE SOURCES ${SOURCE_DIR}/*.c)

# Créez l'exécutable à partir des sources
add_executable(main ${SOURCES})

# Incluez les en-têtes de votre projet
target_include_directories(main PRIVATE ${SOURCE_DIR})

# Liez l'exécutable à la bibliothèque GMP
target_link_libraries(main gmp)
