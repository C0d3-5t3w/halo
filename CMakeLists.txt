cmake_minimum_required(VERSION 3.10)
project(halo C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

# Add compiler warnings
if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
	add_compile_options(-Wall -Wextra -Wpedantic)
elseif(MSVC)
	add_compile_options(/W4)
endif()

# Source files
file(GLOB_RECURSE SOURCES "src/*.c")
file(GLOB_RECURSE HEADERS "include/*.h")

# Include directories
include_directories(include)

# Executable
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# Add subdirectories if needed
# add_subdirectory(lib)

# Link libraries
# target_link_libraries(${PROJECT_NAME} PRIVATE your_library)
