set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

# Set the name and the supported language of the project
project(inventory LANGUAGES C CXX)
# Set the minimum version of cmake required to build this project
cmake_minimum_required(VERSION 3.8)


# Use the package PkgConfig to detect GTK+ headers/library files
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)

find_package(MySQL REQUIRED)

# Copy  Glade over
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/layout.glade
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

# Setup CMake to use GTK+, tell the compiler where to look for headers
# and to the linker where to look for libraries
include_directories(
		${GTK3_INCLUDE_DIRS}
		${MYSQL_INCLUDE_DIR})

link_directories(
		${GTK3_LIBRARY_DIRS}
		${MYSQL_LIBRARY_DIRS}
		)

# Add other flags to the compiler
add_definitions(${GTK3_CFLAGS_OTHER})

# Add an executable compiled from hello.c
add_executable(inventory main.c db.c)
# Link the target to the GTK+ libraries
target_link_libraries(inventory
        ${GTK3_LIBRARIES}
		${MYSQL_LIB})