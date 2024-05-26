# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

# Default target executed when no arguments are given to make.
default_target: all
.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/iamako/Documents/CHPS0801/projet/Stencil-Kokkos-OpenMP

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/iamako/Documents/CHPS0801/projet/Stencil-Kokkos-OpenMP

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "No interactive CMake dialog available..."
	/usr/bin/cmake -E echo No\ interactive\ CMake\ dialog\ available.
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache
.PHONY : edit_cache/fast

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/usr/bin/cmake --regenerate-during-build -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache
.PHONY : rebuild_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /home/iamako/Documents/CHPS0801/projet/Stencil-Kokkos-OpenMP/CMakeFiles /home/iamako/Documents/CHPS0801/projet/Stencil-Kokkos-OpenMP//CMakeFiles/progress.marks
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /home/iamako/Documents/CHPS0801/projet/Stencil-Kokkos-OpenMP/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean
.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named stencil_base.exe

# Build rule for target.
stencil_base.exe: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 stencil_base.exe
.PHONY : stencil_base.exe

# fast build rule for target.
stencil_base.exe/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/stencil_base.exe.dir/build.make CMakeFiles/stencil_base.exe.dir/build
.PHONY : stencil_base.exe/fast

#=============================================================================
# Target rules for targets named stencil_kokkos_cpu.exe

# Build rule for target.
stencil_kokkos_cpu.exe: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 stencil_kokkos_cpu.exe
.PHONY : stencil_kokkos_cpu.exe

# fast build rule for target.
stencil_kokkos_cpu.exe/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/stencil_kokkos_cpu.exe.dir/build.make CMakeFiles/stencil_kokkos_cpu.exe.dir/build
.PHONY : stencil_kokkos_cpu.exe/fast

#=============================================================================
# Target rules for targets named stencil_kokkos_gpu.exe

# Build rule for target.
stencil_kokkos_gpu.exe: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 stencil_kokkos_gpu.exe
.PHONY : stencil_kokkos_gpu.exe

# fast build rule for target.
stencil_kokkos_gpu.exe/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/stencil_kokkos_gpu.exe.dir/build.make CMakeFiles/stencil_kokkos_gpu.exe.dir/build
.PHONY : stencil_kokkos_gpu.exe/fast

#=============================================================================
# Target rules for targets named stencil_omp.exe

# Build rule for target.
stencil_omp.exe: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 stencil_omp.exe
.PHONY : stencil_omp.exe

# fast build rule for target.
stencil_omp.exe/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/stencil_omp.exe.dir/build.make CMakeFiles/stencil_omp.exe.dir/build
.PHONY : stencil_omp.exe/fast

stencil_base.o: stencil_base.cpp.o
.PHONY : stencil_base.o

# target to build an object file
stencil_base.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/stencil_base.exe.dir/build.make CMakeFiles/stencil_base.exe.dir/stencil_base.cpp.o
.PHONY : stencil_base.cpp.o

stencil_base.i: stencil_base.cpp.i
.PHONY : stencil_base.i

# target to preprocess a source file
stencil_base.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/stencil_base.exe.dir/build.make CMakeFiles/stencil_base.exe.dir/stencil_base.cpp.i
.PHONY : stencil_base.cpp.i

stencil_base.s: stencil_base.cpp.s
.PHONY : stencil_base.s

# target to generate assembly for a file
stencil_base.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/stencil_base.exe.dir/build.make CMakeFiles/stencil_base.exe.dir/stencil_base.cpp.s
.PHONY : stencil_base.cpp.s

stencil_kokkos_cpu.o: stencil_kokkos_cpu.cpp.o
.PHONY : stencil_kokkos_cpu.o

# target to build an object file
stencil_kokkos_cpu.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/stencil_kokkos_cpu.exe.dir/build.make CMakeFiles/stencil_kokkos_cpu.exe.dir/stencil_kokkos_cpu.cpp.o
.PHONY : stencil_kokkos_cpu.cpp.o

stencil_kokkos_cpu.i: stencil_kokkos_cpu.cpp.i
.PHONY : stencil_kokkos_cpu.i

# target to preprocess a source file
stencil_kokkos_cpu.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/stencil_kokkos_cpu.exe.dir/build.make CMakeFiles/stencil_kokkos_cpu.exe.dir/stencil_kokkos_cpu.cpp.i
.PHONY : stencil_kokkos_cpu.cpp.i

stencil_kokkos_cpu.s: stencil_kokkos_cpu.cpp.s
.PHONY : stencil_kokkos_cpu.s

# target to generate assembly for a file
stencil_kokkos_cpu.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/stencil_kokkos_cpu.exe.dir/build.make CMakeFiles/stencil_kokkos_cpu.exe.dir/stencil_kokkos_cpu.cpp.s
.PHONY : stencil_kokkos_cpu.cpp.s

stencil_kokkos_gpu.o: stencil_kokkos_gpu.cpp.o
.PHONY : stencil_kokkos_gpu.o

# target to build an object file
stencil_kokkos_gpu.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/stencil_kokkos_gpu.exe.dir/build.make CMakeFiles/stencil_kokkos_gpu.exe.dir/stencil_kokkos_gpu.cpp.o
.PHONY : stencil_kokkos_gpu.cpp.o

stencil_kokkos_gpu.i: stencil_kokkos_gpu.cpp.i
.PHONY : stencil_kokkos_gpu.i

# target to preprocess a source file
stencil_kokkos_gpu.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/stencil_kokkos_gpu.exe.dir/build.make CMakeFiles/stencil_kokkos_gpu.exe.dir/stencil_kokkos_gpu.cpp.i
.PHONY : stencil_kokkos_gpu.cpp.i

stencil_kokkos_gpu.s: stencil_kokkos_gpu.cpp.s
.PHONY : stencil_kokkos_gpu.s

# target to generate assembly for a file
stencil_kokkos_gpu.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/stencil_kokkos_gpu.exe.dir/build.make CMakeFiles/stencil_kokkos_gpu.exe.dir/stencil_kokkos_gpu.cpp.s
.PHONY : stencil_kokkos_gpu.cpp.s

stencil_omp.o: stencil_omp.cpp.o
.PHONY : stencil_omp.o

# target to build an object file
stencil_omp.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/stencil_omp.exe.dir/build.make CMakeFiles/stencil_omp.exe.dir/stencil_omp.cpp.o
.PHONY : stencil_omp.cpp.o

stencil_omp.i: stencil_omp.cpp.i
.PHONY : stencil_omp.i

# target to preprocess a source file
stencil_omp.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/stencil_omp.exe.dir/build.make CMakeFiles/stencil_omp.exe.dir/stencil_omp.cpp.i
.PHONY : stencil_omp.cpp.i

stencil_omp.s: stencil_omp.cpp.s
.PHONY : stencil_omp.s

# target to generate assembly for a file
stencil_omp.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/stencil_omp.exe.dir/build.make CMakeFiles/stencil_omp.exe.dir/stencil_omp.cpp.s
.PHONY : stencil_omp.cpp.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... edit_cache"
	@echo "... rebuild_cache"
	@echo "... stencil_base.exe"
	@echo "... stencil_kokkos_cpu.exe"
	@echo "... stencil_kokkos_gpu.exe"
	@echo "... stencil_omp.exe"
	@echo "... stencil_base.o"
	@echo "... stencil_base.i"
	@echo "... stencil_base.s"
	@echo "... stencil_kokkos_cpu.o"
	@echo "... stencil_kokkos_cpu.i"
	@echo "... stencil_kokkos_cpu.s"
	@echo "... stencil_kokkos_gpu.o"
	@echo "... stencil_kokkos_gpu.i"
	@echo "... stencil_kokkos_gpu.s"
	@echo "... stencil_omp.o"
	@echo "... stencil_omp.i"
	@echo "... stencil_omp.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

