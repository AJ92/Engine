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
include Demos/Raytracer/CMakeFiles/AppRaytracer.dir/depend.make

# Include the progress variables for this target.
include Demos/Raytracer/CMakeFiles/AppRaytracer.dir/progress.make

# Include the compile flags for this target's objects.
include Demos/Raytracer/CMakeFiles/AppRaytracer.dir/flags.make

Demos/Raytracer/CMakeFiles/AppRaytracer.dir/Raytracer.obj: Demos/Raytracer/CMakeFiles/AppRaytracer.dir/flags.make
Demos/Raytracer/CMakeFiles/AppRaytracer.dir/Raytracer.obj: Demos/Raytracer/CMakeFiles/AppRaytracer.dir/includes_CXX.rsp
Demos/Raytracer/CMakeFiles/AppRaytracer.dir/Raytracer.obj: Demos/Raytracer/Raytracer.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report C:\Users\AJ\Desktop\bullet-2.82-r2704\CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object Demos/Raytracer/CMakeFiles/AppRaytracer.dir/Raytracer.obj"
	cd /d C:\Users\AJ\Desktop\bullet-2.82-r2704\Demos\Raytracer && E:\Code\MinGW\bin\g++.exe   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles\AppRaytracer.dir\Raytracer.obj -c C:\Users\AJ\Desktop\bullet-2.82-r2704\Demos\Raytracer\Raytracer.cpp

Demos/Raytracer/CMakeFiles/AppRaytracer.dir/Raytracer.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/AppRaytracer.dir/Raytracer.i"
	cd /d C:\Users\AJ\Desktop\bullet-2.82-r2704\Demos\Raytracer && E:\Code\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_FLAGS) -E C:\Users\AJ\Desktop\bullet-2.82-r2704\Demos\Raytracer\Raytracer.cpp > CMakeFiles\AppRaytracer.dir\Raytracer.i

Demos/Raytracer/CMakeFiles/AppRaytracer.dir/Raytracer.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/AppRaytracer.dir/Raytracer.s"
	cd /d C:\Users\AJ\Desktop\bullet-2.82-r2704\Demos\Raytracer && E:\Code\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_FLAGS) -S C:\Users\AJ\Desktop\bullet-2.82-r2704\Demos\Raytracer\Raytracer.cpp -o CMakeFiles\AppRaytracer.dir\Raytracer.s

Demos/Raytracer/CMakeFiles/AppRaytracer.dir/Raytracer.obj.requires:
.PHONY : Demos/Raytracer/CMakeFiles/AppRaytracer.dir/Raytracer.obj.requires

Demos/Raytracer/CMakeFiles/AppRaytracer.dir/Raytracer.obj.provides: Demos/Raytracer/CMakeFiles/AppRaytracer.dir/Raytracer.obj.requires
	$(MAKE) -f Demos\Raytracer\CMakeFiles\AppRaytracer.dir\build.make Demos/Raytracer/CMakeFiles/AppRaytracer.dir/Raytracer.obj.provides.build
.PHONY : Demos/Raytracer/CMakeFiles/AppRaytracer.dir/Raytracer.obj.provides

Demos/Raytracer/CMakeFiles/AppRaytracer.dir/Raytracer.obj.provides.build: Demos/Raytracer/CMakeFiles/AppRaytracer.dir/Raytracer.obj

Demos/Raytracer/CMakeFiles/AppRaytracer.dir/main.obj: Demos/Raytracer/CMakeFiles/AppRaytracer.dir/flags.make
Demos/Raytracer/CMakeFiles/AppRaytracer.dir/main.obj: Demos/Raytracer/CMakeFiles/AppRaytracer.dir/includes_CXX.rsp
Demos/Raytracer/CMakeFiles/AppRaytracer.dir/main.obj: Demos/Raytracer/main.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report C:\Users\AJ\Desktop\bullet-2.82-r2704\CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object Demos/Raytracer/CMakeFiles/AppRaytracer.dir/main.obj"
	cd /d C:\Users\AJ\Desktop\bullet-2.82-r2704\Demos\Raytracer && E:\Code\MinGW\bin\g++.exe   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles\AppRaytracer.dir\main.obj -c C:\Users\AJ\Desktop\bullet-2.82-r2704\Demos\Raytracer\main.cpp

Demos/Raytracer/CMakeFiles/AppRaytracer.dir/main.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/AppRaytracer.dir/main.i"
	cd /d C:\Users\AJ\Desktop\bullet-2.82-r2704\Demos\Raytracer && E:\Code\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_FLAGS) -E C:\Users\AJ\Desktop\bullet-2.82-r2704\Demos\Raytracer\main.cpp > CMakeFiles\AppRaytracer.dir\main.i

Demos/Raytracer/CMakeFiles/AppRaytracer.dir/main.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/AppRaytracer.dir/main.s"
	cd /d C:\Users\AJ\Desktop\bullet-2.82-r2704\Demos\Raytracer && E:\Code\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_FLAGS) -S C:\Users\AJ\Desktop\bullet-2.82-r2704\Demos\Raytracer\main.cpp -o CMakeFiles\AppRaytracer.dir\main.s

Demos/Raytracer/CMakeFiles/AppRaytracer.dir/main.obj.requires:
.PHONY : Demos/Raytracer/CMakeFiles/AppRaytracer.dir/main.obj.requires

Demos/Raytracer/CMakeFiles/AppRaytracer.dir/main.obj.provides: Demos/Raytracer/CMakeFiles/AppRaytracer.dir/main.obj.requires
	$(MAKE) -f Demos\Raytracer\CMakeFiles\AppRaytracer.dir\build.make Demos/Raytracer/CMakeFiles/AppRaytracer.dir/main.obj.provides.build
.PHONY : Demos/Raytracer/CMakeFiles/AppRaytracer.dir/main.obj.provides

Demos/Raytracer/CMakeFiles/AppRaytracer.dir/main.obj.provides.build: Demos/Raytracer/CMakeFiles/AppRaytracer.dir/main.obj

# Object files for target AppRaytracer
AppRaytracer_OBJECTS = \
"CMakeFiles/AppRaytracer.dir/Raytracer.obj" \
"CMakeFiles/AppRaytracer.dir/main.obj"

# External object files for target AppRaytracer
AppRaytracer_EXTERNAL_OBJECTS =

Demos/Raytracer/AppRaytracer.exe: Demos/Raytracer/CMakeFiles/AppRaytracer.dir/Raytracer.obj
Demos/Raytracer/AppRaytracer.exe: Demos/Raytracer/CMakeFiles/AppRaytracer.dir/main.obj
Demos/Raytracer/AppRaytracer.exe: Demos/Raytracer/CMakeFiles/AppRaytracer.dir/build.make
Demos/Raytracer/AppRaytracer.exe: Demos/OpenGL/libOpenGLSupport_Debug.dll.a
Demos/Raytracer/AppRaytracer.exe: src/BulletDynamics/libBulletDynamics_Debug.dll.a
Demos/Raytracer/AppRaytracer.exe: src/BulletCollision/libBulletCollision_Debug.dll.a
Demos/Raytracer/AppRaytracer.exe: src/LinearMath/libLinearMath_Debug.dll.a
Demos/Raytracer/AppRaytracer.exe: Demos/Raytracer/CMakeFiles/AppRaytracer.dir/objects1.rsp
Demos/Raytracer/AppRaytracer.exe: Demos/Raytracer/CMakeFiles/AppRaytracer.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable AppRaytracer.exe"
	cd /d C:\Users\AJ\Desktop\bullet-2.82-r2704\Demos\Raytracer && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\AppRaytracer.dir\link.txt --verbose=$(VERBOSE)
	cd /d C:\Users\AJ\Desktop\bullet-2.82-r2704\Demos\Raytracer && "E:\Code\cmake\CMake 2.8\bin\cmake.exe" -E copy_if_different C:/Users/AJ/Desktop/bullet-2.82-r2704/GLUT32.DLL C:/Users/AJ/Desktop/bullet-2.82-r2704/Demos/Raytracer

# Rule to build all files generated by this target.
Demos/Raytracer/CMakeFiles/AppRaytracer.dir/build: Demos/Raytracer/AppRaytracer.exe
.PHONY : Demos/Raytracer/CMakeFiles/AppRaytracer.dir/build

Demos/Raytracer/CMakeFiles/AppRaytracer.dir/requires: Demos/Raytracer/CMakeFiles/AppRaytracer.dir/Raytracer.obj.requires
Demos/Raytracer/CMakeFiles/AppRaytracer.dir/requires: Demos/Raytracer/CMakeFiles/AppRaytracer.dir/main.obj.requires
.PHONY : Demos/Raytracer/CMakeFiles/AppRaytracer.dir/requires

Demos/Raytracer/CMakeFiles/AppRaytracer.dir/clean:
	cd /d C:\Users\AJ\Desktop\bullet-2.82-r2704\Demos\Raytracer && $(CMAKE_COMMAND) -P CMakeFiles\AppRaytracer.dir\cmake_clean.cmake
.PHONY : Demos/Raytracer/CMakeFiles/AppRaytracer.dir/clean

Demos/Raytracer/CMakeFiles/AppRaytracer.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\AJ\Desktop\bullet-2.82-r2704 C:\Users\AJ\Desktop\bullet-2.82-r2704\Demos\Raytracer C:\Users\AJ\Desktop\bullet-2.82-r2704 C:\Users\AJ\Desktop\bullet-2.82-r2704\Demos\Raytracer C:\Users\AJ\Desktop\bullet-2.82-r2704\Demos\Raytracer\CMakeFiles\AppRaytracer.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : Demos/Raytracer/CMakeFiles/AppRaytracer.dir/depend

