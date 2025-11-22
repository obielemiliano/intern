cmake_minimum_required(VERSION 3.16)
project(cpp_scoring)
set(CMAKE_CXX_STANDARD 17)


# FetchContent to include crow single header or assume crow_all.h provided
find_package(Threads REQUIRED)

# Agregar esta línea para incluir el directorio include
include_directories(${CMAKE_SOURCE_DIR}/include)


add_executable(cpp_scoring src/main.cpp)


# If using nlohmann_json installed via package manager
find_package(nlohmann_json QUIET)
if (nlohmann_json_FOUND)
target_link_libraries(cpp_scoring PRIVATE nlohmann_json::nlohmann_json)
endif()


# Link threads
target_link_libraries(cpp_scoring PRIVATE Threads::Threads)


# Include directories if needed
# target_include_directories(cpp_scoring PRIVATE ${CROW_INCLUDE_DIRS})