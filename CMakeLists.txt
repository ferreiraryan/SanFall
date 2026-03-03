cmake_minimum_required(VERSION 3.10)

# Nome do seu projeto
project(SandFall)

# Define o padrão do C++ (o 17 é excelente para começar)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Onde o CMake vai procurar os arquivos de código
# Por enquanto, vamos colocar tudo no src/main.cpp
add_executable(SandFall src/main.cpp)

# Se você já tiver a SDL2 instalada no Linux:
find_package(raylib REQUIRED)
target_link_libraries(SandFall raylib)
# find_package(SDL2 REQUIRED)
# include_directories(${SDL2_INCLUDE_DIRS})
# target_link_libraries(SandFall ${SDL2_LIBRARIES})
