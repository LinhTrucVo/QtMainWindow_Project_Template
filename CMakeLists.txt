cmake_minimum_required(VERSION 3.19)
project(QMainWindow_Project LANGUAGES C CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)
qt_standard_project_setup()

# Add the src subdirectory which contains the main CMakeLists.txt
add_subdirectory(src)