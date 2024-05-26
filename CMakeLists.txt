cmake_minimum_required(VERSION 2.8)
project( Stencil )
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )
add_executable( stencil_base.exe stencil_base.cpp )
target_link_libraries( stencil_base.exe ${OpenCV_LIBS} )
# Specify the path where Kokkos is installed
set(Kokkos_DIR "~/local/kokkos/lib/cmake/Kokkos")  # Change this to your Kokkos install path
# Find Kokkos package
find_package(Kokkos REQUIRED)
option(Kokkos_ENABLE_CUDA_RELOCATABLE_DEVICE_CODE ON)
option(Kokkos_ENABLE_CUDA_LAMBDA ON)

add_executable(stencil_kokkos.exe stencil_kokkos.cpp )
# Link Kokkos and OpenCV to the executable
target_link_libraries(stencil_kokkos.exe Kokkos::kokkos ${OpenCV_LIBS})

add_executable( stencil_omp.exe stencil_omp.cpp )
target_link_libraries( stencil_omp.exe ${OpenCV_LIBS} )