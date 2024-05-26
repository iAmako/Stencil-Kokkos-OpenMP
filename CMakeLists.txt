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
option(KOKKOS_ENABLE_OPENMP ON)


add_executable(stencil_kokkos_cpu.exe stencil_kokkos_cpu.cpp )
# Link Kokkos and OpenCV to the executable
target_link_libraries(stencil_kokkos_cpu.exe Kokkos::kokkos ${OpenCV_LIBS})

set(Kokkos_ENABLE_CUDA ON)
set(Kokkos_ENABLE_OPENMP OFF)
set(Kokkos_ENABLE_SERIAL OFF)

add_executable(stencil_kokkos_gpu.exe stencil_kokkos_gpu.cpp )
# Link Kokkos and OpenCV to the executable
target_link_libraries(stencil_kokkos_gpu.exe Kokkos::kokkos ${OpenCV_LIBS})
# Set CUDA as the target property
set_target_properties(stencil_kokkos_gpu.exe PROPERTIES CUDA_SEPARABLE_COMPILATION ON)

add_executable( stencil_omp.exe stencil_omp.cpp )
target_link_libraries( stencil_omp.exe ${OpenCV_LIBS} )