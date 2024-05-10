cmake_minimum_required(VERSION 2.8)
project( Stencil )
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )
add_executable( stencil_kokkos.exe stencil_kokkos.cpp )
target_link_libraries( stencil_kokkos.exe ${OpenCV_LIBS} )