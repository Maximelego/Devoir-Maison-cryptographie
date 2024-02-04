cmake_minimum_required(VERSION 3.10)
project(main)

# Specify the C version
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Set the compilation flags (including -O3)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O3")

# Define the source directory
set(SOURCE_DIR src)

# Add GMP source files to your project
set(GMP_SOURCE_DIR third-party/gmp)

# Check if the GMP library is already installed
find_library(GMP_LIB gmp)

if(NOT GMP_LIB)
    # If GMP is not installed, try installing it with apt
    message("[INFO] - GMP was not found on the system.")
    message("[INFO] - Installing GMP using apt...")
    
    execute_process(COMMAND sudo apt install -y libgmp-dev
                    RESULT_VARIABLE result
                    OUTPUT_VARIABLE output)

    message("${output}")

    # Check the installation result
    if(result)
        message(FATAL_ERROR "[ERROR] - Error while installing GMP library : ${output}")
    endif()
endif()

# Collect the source files of your project
file(GLOB_RECURSE SOURCES ${SOURCE_DIR}/*.c)

# Create the executable from the sources
add_executable(main ${SOURCES})

# Include the headers of your project
target_include_directories(main PRIVATE ${SOURCE_DIR})

# Link the executable to the GMP library
target_link_libraries(main gmp)
