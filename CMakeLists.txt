<<<<<<< HEAD
# Set the name and the supported language of the project
project(inventory C)
# Set the minimum version of cmake required to build this project
cmake_minimum_required(VERSION 3.2)

# Use the package PkgConfig to detect GTK+ headers/library files
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)

# Copy  Glade over
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/layout.glade
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

pkg_check_modules(mysql REQUIRED mariadbclient)

# Setup CMake to use GTK+, tell the compiler where to look for headers
# and to the linker where to look for libraries
include_directories(${GTK3_INCLUDE_DIRS})
link_directories(${GTK3_LIBRARY_DIRS})

# Add other flags to the compiler
add_definitions(${GTK3_CFLAGS_OTHER})

# Add an executable compiled from hello.c
add_executable(inventory main.c)
# Link the target to the GTK+ libraries
target_link_libraries(inventory
        ${GTK3_LIBRARIES}
	PkgConfig::mysql)
=======
# Set the name and the supported language of the project
project(inventory C)
# Set the minimum version of cmake required to build this project
cmake_minimum_required(VERSION 3.2)

# Use the package PkgConfig to detect GTK+ headers/library files
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)

# Copy  Glade over
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/layout.glade
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

# find_package(MySQL REQUIRED)
find_package(PkgConfig)
pkg_check_modules(MySQL REQUIRED mysqlclient>=5.7)
#pkg_check_modules(mariadb REQUIRED IMPORTED_TARGET "mariadbclient")

# Setup CMake to use GTK+, tell the compiler where to look for headers
# and to the linker where to look for libraries
include_directories(
    ${GTK3_INCLUDE_DIRS}
    ${MySQL_INCLUDE_DIRS}
    )
link_directories(${GTK3_LIBRARY_DIRS})

# Add other flags to the compiler
add_definitions(${GTK3_CFLAGS_OTHER})

# Add an executable compiled from hello.c
add_executable(inventory main.c)

# Link the target to the GTK+ libraries
target_link_libraries(inventory
        ${GTK3_LIBRARIES}
        ${MySQL_LIBRARIES}
    )
>>>>>>> e9e705145fc4655f94b16ffc8cc4ed3267b40f6f
