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
include Demos/HelloWorld/CMakeFiles/AppHelloWorld.dir/depend.make

# Include the progress variables for this target.
include Demos/HelloWorld/CMakeFiles/AppHelloWorld.dir/progress.make

# Include the compile flags for this target's objects.
include Demos/HelloWorld/CMakeFiles/AppHelloWorld.dir/flags.make

Demos/HelloWorld/CMakeFiles/AppHelloWorld.dir/HelloWorld.obj: Demos/HelloWorld/CMakeFiles/AppHelloWorld.dir/flags.make
Demos/HelloWorld/CMakeFiles/AppHelloWorld.dir/HelloWorld.obj: Demos/HelloWorld/CMakeFiles/AppHelloWorld.dir/includes_CXX.rsp
Demos/HelloWorld/CMakeFiles/AppHelloWorld.dir/HelloWorld.obj: Demos/HelloWorld/HelloWorld.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report C:\Users\AJ\Desktop\bullet-2.82-r2704\CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object Demos/HelloWorld/CMakeFiles/AppHelloWorld.dir/HelloWorld.obj"
	cd /d C:\Users\AJ\Desktop\bullet-2.82-r2704\Demos\HelloWorld && E:\Code\MinGW\bin\g++.exe   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles\AppHelloWorld.dir\HelloWorld.obj -c C:\Users\AJ\Desktop\bullet-2.82-r2704\Demos\HelloWorld\HelloWorld.cpp

Demos/HelloWorld/CMakeFiles/AppHelloWorld.dir/HelloWorld.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/AppHelloWorld.dir/HelloWorld.i"
	cd /d C:\Users\AJ\Desktop\bullet-2.82-r2704\Demos\HelloWorld && E:\Code\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_FLAGS) -E C:\Users\AJ\Desktop\bullet-2.82-r2704\Demos\HelloWorld\HelloWorld.cpp > CMakeFiles\AppHelloWorld.dir\HelloWorld.i

Demos/HelloWorld/CMakeFiles/AppHelloWorld.dir/HelloWorld.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/AppHelloWorld.dir/HelloWorld.s"
	cd /d C:\Users\AJ\Desktop\bullet-2.82-r2704\Demos\HelloWorld && E:\Code\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_FLAGS) -S C:\Users\AJ\Desktop\bullet-2.82-r2704\Demos\HelloWorld\HelloWorld.cpp -o CMakeFiles\AppHelloWorld.dir\HelloWorld.s

Demos/HelloWorld/CMakeFiles/AppHelloWorld.dir/HelloWorld.obj.requires:
.PHONY : Demos/HelloWorld/CMakeFiles/AppHelloWorld.dir/HelloWorld.obj.requires

Demos/HelloWorld/CMakeFiles/AppHelloWorld.dir/HelloWorld.obj.provides: Demos/HelloWorld/CMakeFiles/AppHelloWorld.dir/HelloWorld.obj.requires
	$(MAKE) -f Demos\HelloWorld\CMakeFiles\AppHelloWorld.dir\build.make Demos/HelloWorld/CMakeFiles/AppHelloWorld.dir/HelloWorld.obj.provides.build
.PHONY : Demos/HelloWorld/CMakeFiles/AppHelloWorld.dir/HelloWorld.obj.provides

Demos/HelloWorld/CMakeFiles/AppHelloWorld.dir/HelloWorld.obj.provides.build: Demos/HelloWorld/CMakeFiles/AppHelloWorld.dir/HelloWorld.obj

Demos/HelloWorld/CMakeFiles/AppHelloWorld.dir/__/__/build/bullet.obj: Demos/HelloWorld/CMakeFiles/AppHelloWorld.dir/flags.make
Demos/HelloWorld/CMakeFiles/AppHelloWorld.dir/__/__/build/bullet.obj: build/bullet.rc
	$(CMAKE_COMMAND) -E cmake_progress_report C:\Users\AJ\Desktop\bullet-2.82-r2704\CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building RC object Demos/HelloWorld/CMakeFiles/AppHelloWorld.dir/__/__/build/bullet.obj"
	cd /d C:\Users\AJ\Desktop\bullet-2.82-r2704\Demos\HelloWorld && E:\Code\MinGW\bin\windres.exe  -O coff $(RC_FLAGS) $(RC_DEFINES) C:\Users\AJ\Desktop\bullet-2.82-r2704\build\bullet.rc CMakeFiles\AppHelloWorld.dir\__\__\build\bullet.obj

Demos/HelloWorld/CMakeFiles/AppHelloWorld.dir/__/__/build/bullet.obj.requires:
.PHONY : Demos/HelloWorld/CMakeFiles/AppHelloWorld.dir/__/__/build/bullet.obj.requires

Demos/HelloWorld/CMakeFiles/AppHelloWorld.dir/__/__/build/bullet.obj.provides: Demos/HelloWorld/CMakeFiles/AppHelloWorld.dir/__/__/build/bullet.obj.requires
	$(MAKE) -f Demos\HelloWorld\CMakeFiles\AppHelloWorld.dir\build.make Demos/HelloWorld/CMakeFiles/AppHelloWorld.dir/__/__/build/bullet.obj.provides.build
.PHONY : Demos/HelloWorld/CMakeFiles/AppHelloWorld.dir/__/__/build/bullet.obj.provides

Demos/HelloWorld/CMakeFiles/AppHelloWorld.dir/__/__/build/bullet.obj.provides.build: Demos/HelloWorld/CMakeFiles/AppHelloWorld.dir/__/__/build/bullet.obj

# Object files for target AppHelloWorld
AppHelloWorld_OBJECTS = \
"CMakeFiles/AppHelloWorld.dir/HelloWorld.obj" \
"CMakeFiles/AppHelloWorld.dir/__/__/build/bullet.obj"

# External object files for target AppHelloWorld
AppHelloWorld_EXTERNAL_OBJECTS =

Demos/HelloWorld/AppHelloWorld.exe: Demos/HelloWorld/CMakeFiles/AppHelloWorld.dir/HelloWorld.obj
Demos/HelloWorld/AppHelloWorld.exe: Demos/HelloWorld/CMakeFiles/AppHelloWorld.dir/__/__/build/bullet.obj
Demos/HelloWorld/AppHelloWorld.exe: Demos/HelloWorld/CMakeFiles/AppHelloWorld.dir/build.make
Demos/HelloWorld/AppHelloWorld.exe: src/BulletDynamics/libBulletDynamics_Debug.dll.a
Demos/HelloWorld/AppHelloWorld.exe: src/BulletCollision/libBulletCollision_Debug.dll.a
Demos/HelloWorld/AppHelloWorld.exe: src/LinearMath/libLinearMath_Debug.dll.a
Demos/HelloWorld/AppHelloWorld.exe: Demos/HelloWorld/CMakeFiles/AppHelloWorld.dir/objects1.rsp
Demos/HelloWorld/AppHelloWorld.exe: Demos/HelloWorld/CMakeFiles/AppHelloWorld.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable AppHelloWorld.exe"
	cd /d C:\Users\AJ\Desktop\bullet-2.82-r2704\Demos\HelloWorld && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\AppHelloWorld.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
Demos/HelloWorld/CMakeFiles/AppHelloWorld.dir/build: Demos/HelloWorld/AppHelloWorld.exe
.PHONY : Demos/HelloWorld/CMakeFiles/AppHelloWorld.dir/build

Demos/HelloWorld/CMakeFiles/AppHelloWorld.dir/requires: Demos/HelloWorld/CMakeFiles/AppHelloWorld.dir/HelloWorld.obj.requires
Demos/HelloWorld/CMakeFiles/AppHelloWorld.dir/requires: Demos/HelloWorld/CMakeFiles/AppHelloWorld.dir/__/__/build/bullet.obj.requires
.PHONY : Demos/HelloWorld/CMakeFiles/AppHelloWorld.dir/requires

Demos/HelloWorld/CMakeFiles/AppHelloWorld.dir/clean:
	cd /d C:\Users\AJ\Desktop\bullet-2.82-r2704\Demos\HelloWorld && $(CMAKE_COMMAND) -P CMakeFiles\AppHelloWorld.dir\cmake_clean.cmake
.PHONY : Demos/HelloWorld/CMakeFiles/AppHelloWorld.dir/clean

Demos/HelloWorld/CMakeFiles/AppHelloWorld.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\AJ\Desktop\bullet-2.82-r2704 C:\Users\AJ\Desktop\bullet-2.82-r2704\Demos\HelloWorld C:\Users\AJ\Desktop\bullet-2.82-r2704 C:\Users\AJ\Desktop\bullet-2.82-r2704\Demos\HelloWorld C:\Users\AJ\Desktop\bullet-2.82-r2704\Demos\HelloWorld\CMakeFiles\AppHelloWorld.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : Demos/HelloWorld/CMakeFiles/AppHelloWorld.dir/depend
