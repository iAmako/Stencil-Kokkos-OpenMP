cmake_minimum_required(VERSION 2.8)
project( Stencil )
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )
add_executable( stencil_base.exe stencil_base.cpp )
target_link_libraries( stencil_base.exe ${OpenCV_LIBS} )

add_executable( stencil_kokkos.exe stencil_kokkos.cpp )
target_link_libraries( stencil_kokkos.exe ${OpenCV_LIBS} )

add_executable( stencil_omp.exe stencil_omp.cpp )
target_link_libraries( stencil_omp.exe ${OpenCV_LIBS} )