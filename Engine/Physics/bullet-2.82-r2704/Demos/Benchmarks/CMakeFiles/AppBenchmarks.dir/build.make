# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 2.8

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list

# Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "E:\Code\cmake\CMake 2.8\bin\cmake.exe"

# The command to remove a file.
RM = "E:\Code\cmake\CMake 2.8\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The program to use to edit the cache.
CMAKE_EDIT_COMMAND = "E:\Code\cmake\CMake 2.8\bin\cmake-gui.exe"

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\AJ\Desktop\bullet-2.82-r2704

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\AJ\Desktop\bullet-2.82-r2704

# Include any dependencies generated for this target.
include Demos/Benchmarks/CMakeFiles/AppBenchmarks.dir/depend.make

# Include the progress variables for this target.
include Demos/Benchmarks/CMakeFiles/AppBenchmarks.dir/progress.make

# Include the compile flags for this target's objects.
include Demos/Benchmarks/CMakeFiles/AppBenchmarks.dir/flags.make

Demos/Benchmarks/CMakeFiles/AppBenchmarks.dir/main.obj: Demos/Benchmarks/CMakeFiles/AppBenchmarks.dir/flags.make
Demos/Benchmarks/CMakeFiles/AppBenchmarks.dir/main.obj: Demos/Benchmarks/CMakeFiles/AppBenchmarks.dir/includes_CXX.rsp
Demos/Benchmarks/CMakeFiles/AppBenchmarks.dir/main.obj: Demos/Benchmarks/main.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report C:\Users\AJ\Desktop\bullet-2.82-r2704\CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object Demos/Benchmarks/CMakeFiles/AppBenchmarks.dir/main.obj"
	cd /d C:\Users\AJ\Desktop\bullet-2.82-r2704\Demos\Benchmarks && E:\Code\MinGW\bin\g++.exe   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles\AppBenchmarks.dir\main.obj -c C:\Users\AJ\Desktop\bullet-2.82-r2704\Demos\Benchmarks\main.cpp

Demos/Benchmarks/CMakeFiles/AppBenchmarks.dir/main.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/AppBenchmarks.dir/main.i"
	cd /d C:\Users\AJ\Desktop\bullet-2.82-r2704\Demos\Benchmarks && E:\Code\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_FLAGS) -E C:\Users\AJ\Desktop\bullet-2.82-r2704\Demos\Benchmarks\main.cpp > CMakeFiles\AppBenchmarks.dir\main.i

Demos/Benchmarks/CMakeFiles/AppBenchmarks.dir/main.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/AppBenchmarks.dir/main.s"
	cd /d C:\Users\AJ\Desktop\bullet-2.82-r2704\Demos\Benchmarks && E:\Code\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_FLAGS) -S C:\Users\AJ\Desktop\bullet-2.82-r2704\Demos\Benchmarks\main.cpp -o CMakeFiles\AppBenchmarks.dir\main.s

Demos/Benchmarks/CMakeFiles/AppBenchmarks.dir/main.obj.requires:
.PHONY : Demos/Benchmarks/CMakeFiles/AppBenchmarks.dir/main.obj.requires

Demos/Benchmarks/CMakeFiles/AppBenchmarks.dir/main.obj.provides: Demos/Benchmarks/CMakeFiles/AppBenchmarks.dir/main.obj.requires
	$(MAKE) -f Demos\Benchmarks\CMakeFiles\AppBenchmarks.dir\build.make Demos/Benchmarks/CMakeFiles/AppBenchmarks.dir/main.obj.provides.build
.PHONY : Demos/Benchmarks/CMakeFiles/AppBenchmarks.dir/main.obj.provides

Demos/Benchmarks/CMakeFiles/AppBenchmarks.dir/main.obj.provides.build: Demos/Benchmarks/CMakeFiles/AppBenchmarks.dir/main.obj

Demos/Benchmarks/CMakeFiles/AppBenchmarks.dir/BenchmarkDemo.obj: Demos/Benchmarks/CMakeFiles/AppBenchmarks.dir/flags.make
Demos/Benchmarks/CMakeFiles/AppBenchmarks.dir/BenchmarkDemo.obj: Demos/Benchmarks/CMakeFiles/AppBenchmarks.dir/includes_CXX.rsp
Demos/Benchmarks/CMakeFiles/AppBenchmarks.dir/BenchmarkDemo.obj: Demos/Benchmarks/BenchmarkDemo.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report C:\Users\AJ\Desktop\bullet-2.82-r2704\CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object Demos/Benchmarks/CMakeFiles/AppBenchmarks.dir/BenchmarkDemo.obj"
	cd /d C:\Users\AJ\Desktop\bullet-2.82-r2704\Demos\Benchmarks && E:\Code\MinGW\bin\g++.exe   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles\AppBenchmarks.dir\BenchmarkDemo.obj -c C:\Users\AJ\Desktop\bullet-2.82-r2704\Demos\Benchmarks\BenchmarkDemo.cpp

Demos/Benchmarks/CMakeFiles/AppBenchmarks.dir/BenchmarkDemo.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/AppBenchmarks.dir/BenchmarkDemo.i"
	cd /d C:\Users\AJ\Desktop\bullet-2.82-r2704\Demos\Benchmarks && E:\Code\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_FLAGS) -E C:\Users\AJ\Desktop\bullet-2.82-r2704\Demos\Benchmarks\BenchmarkDemo.cpp > CMakeFiles\AppBenchmarks.dir\BenchmarkDemo.i

Demos/Benchmarks/CMakeFiles/AppBenchmarks.dir/BenchmarkDemo.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/AppBenchmarks.dir/BenchmarkDemo.s"
	cd /d C:\Users\AJ\Desktop\bullet-2.82-r2704\Demos\Benchmarks && E:\Code\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_FLAGS) -S C:\Users\AJ\Desktop\bullet-2.82-r2704\Demos\Benchmarks\BenchmarkDemo.cpp -o CMakeFiles\AppBenchmarks.dir\BenchmarkDemo.s

Demos/Benchmarks/CMakeFiles/AppBenchmarks.dir/BenchmarkDemo.obj.requires:
.PHONY : Demos/Benchmarks/CMakeFiles/AppBenchmarks.dir/BenchmarkDemo.obj.requires

Demos/Benchmarks/CMakeFiles/AppBenchmarks.dir/BenchmarkDemo.obj.provides: Demos/Benchmarks/CMakeFiles/AppBenchmarks.dir/BenchmarkDemo.obj.requires
	$(MAKE) -f Demos\Benchmarks\CMakeFiles\AppBenchmarks.dir\build.make Demos/Benchmarks/CMakeFiles/AppBenchmarks.dir/BenchmarkDemo.obj.provides.build
.PHONY : Demos/Benchmarks/CMakeFiles/AppBenchmarks.dir/BenchmarkDemo.obj.provides

Demos/Benchmarks/CMakeFiles/AppBenchmarks.dir/BenchmarkDemo.obj.provides.build: Demos/Benchmarks/CMakeFiles/AppBenchmarks.dir/BenchmarkDemo.obj

Demos/Benchmarks/CMakeFiles/AppBenchmarks.dir/__/__/build/bullet.obj: Demos/Benchmarks/CMakeFiles/AppBenchmarks.dir/flags.make
Demos/Benchmarks/CMakeFiles/AppBenchmarks.dir/__/__/build/bullet.obj: build/bullet.rc
	$(CMAKE_COMMAND) -E cmake_progress_report C:\Users\AJ\Desktop\bullet-2.82-r2704\CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building RC object Demos/Benchmarks/CMakeFiles/AppBenchmarks.dir/__/__/build/bullet.obj"
	cd /d C:\Users\AJ\Desktop\bullet-2.82-r2704\Demos\Benchmarks && E:\Code\MinGW\bin\windres.exe  -O coff $(RC_FLAGS) $(RC_DEFINES) C:\Users\AJ\Desktop\bullet-2.82-r2704\build\bullet.rc CMakeFiles\AppBenchmarks.dir\__\__\build\bullet.obj

Demos/Benchmarks/CMakeFiles/AppBenchmarks.dir/__/__/build/bullet.obj.requires:
.PHONY : Demos/Benchmarks/CMakeFiles/AppBenchmarks.dir/__/__/build/bullet.obj.requires

Demos/Benchmarks/CMakeFiles/AppBenchmarks.dir/__/__/build/bullet.obj.provides: Demos/Benchmarks/CMakeFiles/AppBenchmarks.dir/__/__/build/bullet.obj.requires
	$(MAKE) -f Demos\Benchmarks\CMakeFiles\AppBenchmarks.dir\build.make Demos/Benchmarks/CMakeFiles/AppBenchmarks.dir/__/__/build/bullet.obj.provides.build
.PHONY : Demos/Benchmarks/CMakeFiles/AppBenchmarks.dir/__/__/build/bullet.obj.provides

Demos/Benchmarks/CMakeFiles/AppBenchmarks.dir/__/__/build/bullet.obj.provides.build: Demos/Benchmarks/CMakeFiles/AppBenchmarks.dir/__/__/build/bullet.obj

# Object files for target AppBenchmarks
AppBenchmarks_OBJECTS = \
"CMakeFiles/AppBenchmarks.dir/main.obj" \
"CMakeFiles/AppBenchmarks.dir/BenchmarkDemo.obj" \
"CMakeFiles/AppBenchmarks.dir/__/__/build/bullet.obj"

# External object files for target AppBenchmarks
AppBenchmarks_EXTERNAL_OBJECTS =

Demos/Benchmarks/AppBenchmarks.exe: Demos/Benchmarks/CMakeFiles/AppBenchmarks.dir/main.obj
Demos/Benchmarks/AppBenchmarks.exe: Demos/Benchmarks/CMakeFiles/AppBenchmarks.dir/BenchmarkDemo.obj
Demos/Benchmarks/AppBenchmarks.exe: Demos/Benchmarks/CMakeFiles/AppBenchmarks.dir/__/__/build/bullet.obj
Demos/Benchmarks/AppBenchmarks.exe: Demos/Benchmarks/CMakeFiles/AppBenchmarks.dir/build.make
Demos/Benchmarks/AppBenchmarks.exe: Demos/OpenGL/libOpenGLSupport_Debug.dll.a
Demos/Benchmarks/AppBenchmarks.exe: src/BulletDynamics/libBulletDynamics_Debug.dll.a
Demos/Benchmarks/AppBenchmarks.exe: src/BulletCollision/libBulletCollision_Debug.dll.a
Demos/Benchmarks/AppBenchmarks.exe: src/LinearMath/libLinearMath_Debug.dll.a
Demos/Benchmarks/AppBenchmarks.exe: Demos/Benchmarks/CMakeFiles/AppBenchmarks.dir/objects1.rsp
Demos/Benchmarks/AppBenchmarks.exe: Demos/Benchmarks/CMakeFiles/AppBenchmarks.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable AppBenchmarks.exe"
	cd /d C:\Users\AJ\Desktop\bullet-2.82-r2704\Demos\Benchmarks && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\AppBenchmarks.dir\link.txt --verbose=$(VERBOSE)
	cd /d C:\Users\AJ\Desktop\bullet-2.82-r2704\Demos\Benchmarks && "E:\Code\cmake\CMake 2.8\bin\cmake.exe" -E copy_if_different C:/Users/AJ/Desktop/bullet-2.82-r2704/GLUT32.DLL C:/Users/AJ/Desktop/bullet-2.82-r2704/Demos/Benchmarks

# Rule to build all files generated by this target.
Demos/Benchmarks/CMakeFiles/AppBenchmarks.dir/build: Demos/Benchmarks/AppBenchmarks.exe
.PHONY : Demos/Benchmarks/CMakeFiles/AppBenchmarks.dir/build

Demos/Benchmarks/CMakeFiles/AppBenchmarks.dir/requires: Demos/Benchmarks/CMakeFiles/AppBenchmarks.dir/main.obj.requires
Demos/Benchmarks/CMakeFiles/AppBenchmarks.dir/requires: Demos/Benchmarks/CMakeFiles/AppBenchmarks.dir/BenchmarkDemo.obj.requires
Demos/Benchmarks/CMakeFiles/AppBenchmarks.dir/requires: Demos/Benchmarks/CMakeFiles/AppBenchmarks.dir/__/__/build/bullet.obj.requires
.PHONY : Demos/Benchmarks/CMakeFiles/AppBenchmarks.dir/requires

Demos/Benchmarks/CMakeFiles/AppBenchmarks.dir/clean:
	cd /d C:\Users\AJ\Desktop\bullet-2.82-r2704\Demos\Benchmarks && $(CMAKE_COMMAND) -P CMakeFiles\AppBenchmarks.dir\cmake_clean.cmake
.PHONY : Demos/Benchmarks/CMakeFiles/AppBenchmarks.dir/clean

Demos/Benchmarks/CMakeFiles/AppBenchmarks.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\AJ\Desktop\bullet-2.82-r2704 C:\Users\AJ\Desktop\bullet-2.82-r2704\Demos\Benchmarks C:\Users\AJ\Desktop\bullet-2.82-r2704 C:\Users\AJ\Desktop\bullet-2.82-r2704\Demos\Benchmarks C:\Users\AJ\Desktop\bullet-2.82-r2704\Demos\Benchmarks\CMakeFiles\AppBenchmarks.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : Demos/Benchmarks/CMakeFiles/AppBenchmarks.dir/depend
