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
include Demos/ConcaveRaycastDemo/CMakeFiles/AppConcaveRayCastDemo.dir/depend.make

# Include the progress variables for this target.
include Demos/ConcaveRaycastDemo/CMakeFiles/AppConcaveRayCastDemo.dir/progress.make

# Include the compile flags for this target's objects.
include Demos/ConcaveRaycastDemo/CMakeFiles/AppConcaveRayCastDemo.dir/flags.make

Demos/ConcaveRaycastDemo/CMakeFiles/AppConcaveRayCastDemo.dir/ConcaveRaycastDemo.obj: Demos/ConcaveRaycastDemo/CMakeFiles/AppConcaveRayCastDemo.dir/flags.make
Demos/ConcaveRaycastDemo/CMakeFiles/AppConcaveRayCastDemo.dir/ConcaveRaycastDemo.obj: Demos/ConcaveRaycastDemo/CMakeFiles/AppConcaveRayCastDemo.dir/includes_CXX.rsp
Demos/ConcaveRaycastDemo/CMakeFiles/AppConcaveRayCastDemo.dir/ConcaveRaycastDemo.obj: Demos/ConcaveRaycastDemo/ConcaveRaycastDemo.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report C:\Users\AJ\Desktop\bullet-2.82-r2704\CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object Demos/ConcaveRaycastDemo/CMakeFiles/AppConcaveRayCastDemo.dir/ConcaveRaycastDemo.obj"
	cd /d C:\Users\AJ\Desktop\bullet-2.82-r2704\Demos\ConcaveRaycastDemo && E:\Code\MinGW\bin\g++.exe   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles\AppConcaveRayCastDemo.dir\ConcaveRaycastDemo.obj -c C:\Users\AJ\Desktop\bullet-2.82-r2704\Demos\ConcaveRaycastDemo\ConcaveRaycastDemo.cpp

Demos/ConcaveRaycastDemo/CMakeFiles/AppConcaveRayCastDemo.dir/ConcaveRaycastDemo.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/AppConcaveRayCastDemo.dir/ConcaveRaycastDemo.i"
	cd /d C:\Users\AJ\Desktop\bullet-2.82-r2704\Demos\ConcaveRaycastDemo && E:\Code\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_FLAGS) -E C:\Users\AJ\Desktop\bullet-2.82-r2704\Demos\ConcaveRaycastDemo\ConcaveRaycastDemo.cpp > CMakeFiles\AppConcaveRayCastDemo.dir\ConcaveRaycastDemo.i

Demos/ConcaveRaycastDemo/CMakeFiles/AppConcaveRayCastDemo.dir/ConcaveRaycastDemo.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/AppConcaveRayCastDemo.dir/ConcaveRaycastDemo.s"
	cd /d C:\Users\AJ\Desktop\bullet-2.82-r2704\Demos\ConcaveRaycastDemo && E:\Code\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_FLAGS) -S C:\Users\AJ\Desktop\bullet-2.82-r2704\Demos\ConcaveRaycastDemo\ConcaveRaycastDemo.cpp -o CMakeFiles\AppConcaveRayCastDemo.dir\ConcaveRaycastDemo.s

Demos/ConcaveRaycastDemo/CMakeFiles/AppConcaveRayCastDemo.dir/ConcaveRaycastDemo.obj.requires:
.PHONY : Demos/ConcaveRaycastDemo/CMakeFiles/AppConcaveRayCastDemo.dir/ConcaveRaycastDemo.obj.requires

Demos/ConcaveRaycastDemo/CMakeFiles/AppConcaveRayCastDemo.dir/ConcaveRaycastDemo.obj.provides: Demos/ConcaveRaycastDemo/CMakeFiles/AppConcaveRayCastDemo.dir/ConcaveRaycastDemo.obj.requires
	$(MAKE) -f Demos\ConcaveRaycastDemo\CMakeFiles\AppConcaveRayCastDemo.dir\build.make Demos/ConcaveRaycastDemo/CMakeFiles/AppConcaveRayCastDemo.dir/ConcaveRaycastDemo.obj.provides.build
.PHONY : Demos/ConcaveRaycastDemo/CMakeFiles/AppConcaveRayCastDemo.dir/ConcaveRaycastDemo.obj.provides

Demos/ConcaveRaycastDemo/CMakeFiles/AppConcaveRayCastDemo.dir/ConcaveRaycastDemo.obj.provides.build: Demos/ConcaveRaycastDemo/CMakeFiles/AppConcaveRayCastDemo.dir/ConcaveRaycastDemo.obj

Demos/ConcaveRaycastDemo/CMakeFiles/AppConcaveRayCastDemo.dir/main.obj: Demos/ConcaveRaycastDemo/CMakeFiles/AppConcaveRayCastDemo.dir/flags.make
Demos/ConcaveRaycastDemo/CMakeFiles/AppConcaveRayCastDemo.dir/main.obj: Demos/ConcaveRaycastDemo/CMakeFiles/AppConcaveRayCastDemo.dir/includes_CXX.rsp
Demos/ConcaveRaycastDemo/CMakeFiles/AppConcaveRayCastDemo.dir/main.obj: Demos/ConcaveRaycastDemo/main.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report C:\Users\AJ\Desktop\bullet-2.82-r2704\CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object Demos/ConcaveRaycastDemo/CMakeFiles/AppConcaveRayCastDemo.dir/main.obj"
	cd /d C:\Users\AJ\Desktop\bullet-2.82-r2704\Demos\ConcaveRaycastDemo && E:\Code\MinGW\bin\g++.exe   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles\AppConcaveRayCastDemo.dir\main.obj -c C:\Users\AJ\Desktop\bullet-2.82-r2704\Demos\ConcaveRaycastDemo\main.cpp

Demos/ConcaveRaycastDemo/CMakeFiles/AppConcaveRayCastDemo.dir/main.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/AppConcaveRayCastDemo.dir/main.i"
	cd /d C:\Users\AJ\Desktop\bullet-2.82-r2704\Demos\ConcaveRaycastDemo && E:\Code\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_FLAGS) -E C:\Users\AJ\Desktop\bullet-2.82-r2704\Demos\ConcaveRaycastDemo\main.cpp > CMakeFiles\AppConcaveRayCastDemo.dir\main.i

Demos/ConcaveRaycastDemo/CMakeFiles/AppConcaveRayCastDemo.dir/main.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/AppConcaveRayCastDemo.dir/main.s"
	cd /d C:\Users\AJ\Desktop\bullet-2.82-r2704\Demos\ConcaveRaycastDemo && E:\Code\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_FLAGS) -S C:\Users\AJ\Desktop\bullet-2.82-r2704\Demos\ConcaveRaycastDemo\main.cpp -o CMakeFiles\AppConcaveRayCastDemo.dir\main.s

Demos/ConcaveRaycastDemo/CMakeFiles/AppConcaveRayCastDemo.dir/main.obj.requires:
.PHONY : Demos/ConcaveRaycastDemo/CMakeFiles/AppConcaveRayCastDemo.dir/main.obj.requires

Demos/ConcaveRaycastDemo/CMakeFiles/AppConcaveRayCastDemo.dir/main.obj.provides: Demos/ConcaveRaycastDemo/CMakeFiles/AppConcaveRayCastDemo.dir/main.obj.requires
	$(MAKE) -f Demos\ConcaveRaycastDemo\CMakeFiles\AppConcaveRayCastDemo.dir\build.make Demos/ConcaveRaycastDemo/CMakeFiles/AppConcaveRayCastDemo.dir/main.obj.provides.build
.PHONY : Demos/ConcaveRaycastDemo/CMakeFiles/AppConcaveRayCastDemo.dir/main.obj.provides

Demos/ConcaveRaycastDemo/CMakeFiles/AppConcaveRayCastDemo.dir/main.obj.provides.build: Demos/ConcaveRaycastDemo/CMakeFiles/AppConcaveRayCastDemo.dir/main.obj

Demos/ConcaveRaycastDemo/CMakeFiles/AppConcaveRayCastDemo.dir/__/__/build/bullet.obj: Demos/ConcaveRaycastDemo/CMakeFiles/AppConcaveRayCastDemo.dir/flags.make
Demos/ConcaveRaycastDemo/CMakeFiles/AppConcaveRayCastDemo.dir/__/__/build/bullet.obj: build/bullet.rc
	$(CMAKE_COMMAND) -E cmake_progress_report C:\Users\AJ\Desktop\bullet-2.82-r2704\CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building RC object Demos/ConcaveRaycastDemo/CMakeFiles/AppConcaveRayCastDemo.dir/__/__/build/bullet.obj"
	cd /d C:\Users\AJ\Desktop\bullet-2.82-r2704\Demos\ConcaveRaycastDemo && E:\Code\MinGW\bin\windres.exe  -O coff $(RC_FLAGS) $(RC_DEFINES) C:\Users\AJ\Desktop\bullet-2.82-r2704\build\bullet.rc CMakeFiles\AppConcaveRayCastDemo.dir\__\__\build\bullet.obj

Demos/ConcaveRaycastDemo/CMakeFiles/AppConcaveRayCastDemo.dir/__/__/build/bullet.obj.requires:
.PHONY : Demos/ConcaveRaycastDemo/CMakeFiles/AppConcaveRayCastDemo.dir/__/__/build/bullet.obj.requires

Demos/ConcaveRaycastDemo/CMakeFiles/AppConcaveRayCastDemo.dir/__/__/build/bullet.obj.provides: Demos/ConcaveRaycastDemo/CMakeFiles/AppConcaveRayCastDemo.dir/__/__/build/bullet.obj.requires
	$(MAKE) -f Demos\ConcaveRaycastDemo\CMakeFiles\AppConcaveRayCastDemo.dir\build.make Demos/ConcaveRaycastDemo/CMakeFiles/AppConcaveRayCastDemo.dir/__/__/build/bullet.obj.provides.build
.PHONY : Demos/ConcaveRaycastDemo/CMakeFiles/AppConcaveRayCastDemo.dir/__/__/build/bullet.obj.provides

Demos/ConcaveRaycastDemo/CMakeFiles/AppConcaveRayCastDemo.dir/__/__/build/bullet.obj.provides.build: Demos/ConcaveRaycastDemo/CMakeFiles/AppConcaveRayCastDemo.dir/__/__/build/bullet.obj

# Object files for target AppConcaveRayCastDemo
AppConcaveRayCastDemo_OBJECTS = \
"CMakeFiles/AppConcaveRayCastDemo.dir/ConcaveRaycastDemo.obj" \
"CMakeFiles/AppConcaveRayCastDemo.dir/main.obj" \
"CMakeFiles/AppConcaveRayCastDemo.dir/__/__/build/bullet.obj"

# External object files for target AppConcaveRayCastDemo
AppConcaveRayCastDemo_EXTERNAL_OBJECTS =

Demos/ConcaveRaycastDemo/AppConcaveRayCastDemo.exe: Demos/ConcaveRaycastDemo/CMakeFiles/AppConcaveRayCastDemo.dir/ConcaveRaycastDemo.obj
Demos/ConcaveRaycastDemo/AppConcaveRayCastDemo.exe: Demos/ConcaveRaycastDemo/CMakeFiles/AppConcaveRayCastDemo.dir/main.obj
Demos/ConcaveRaycastDemo/AppConcaveRayCastDemo.exe: Demos/ConcaveRaycastDemo/CMakeFiles/AppConcaveRayCastDemo.dir/__/__/build/bullet.obj
Demos/ConcaveRaycastDemo/AppConcaveRayCastDemo.exe: Demos/ConcaveRaycastDemo/CMakeFiles/AppConcaveRayCastDemo.dir/build.make
Demos/ConcaveRaycastDemo/AppConcaveRayCastDemo.exe: Demos/OpenGL/libOpenGLSupport_Debug.dll.a
Demos/ConcaveRaycastDemo/AppConcaveRayCastDemo.exe: src/BulletDynamics/libBulletDynamics_Debug.dll.a
Demos/ConcaveRaycastDemo/AppConcaveRayCastDemo.exe: src/BulletCollision/libBulletCollision_Debug.dll.a
Demos/ConcaveRaycastDemo/AppConcaveRayCastDemo.exe: src/LinearMath/libLinearMath_Debug.dll.a
Demos/ConcaveRaycastDemo/AppConcaveRayCastDemo.exe: Demos/ConcaveRaycastDemo/CMakeFiles/AppConcaveRayCastDemo.dir/objects1.rsp
Demos/ConcaveRaycastDemo/AppConcaveRayCastDemo.exe: Demos/ConcaveRaycastDemo/CMakeFiles/AppConcaveRayCastDemo.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable AppConcaveRayCastDemo.exe"
	cd /d C:\Users\AJ\Desktop\bullet-2.82-r2704\Demos\ConcaveRaycastDemo && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\AppConcaveRayCastDemo.dir\link.txt --verbose=$(VERBOSE)
	cd /d C:\Users\AJ\Desktop\bullet-2.82-r2704\Demos\ConcaveRaycastDemo && "E:\Code\cmake\CMake 2.8\bin\cmake.exe" -E copy_if_different C:/Users/AJ/Desktop/bullet-2.82-r2704/GLUT32.DLL C:/Users/AJ/Desktop/bullet-2.82-r2704/Demos/ConcaveRaycastDemo

# Rule to build all files generated by this target.
Demos/ConcaveRaycastDemo/CMakeFiles/AppConcaveRayCastDemo.dir/build: Demos/ConcaveRaycastDemo/AppConcaveRayCastDemo.exe
.PHONY : Demos/ConcaveRaycastDemo/CMakeFiles/AppConcaveRayCastDemo.dir/build

Demos/ConcaveRaycastDemo/CMakeFiles/AppConcaveRayCastDemo.dir/requires: Demos/ConcaveRaycastDemo/CMakeFiles/AppConcaveRayCastDemo.dir/ConcaveRaycastDemo.obj.requires
Demos/ConcaveRaycastDemo/CMakeFiles/AppConcaveRayCastDemo.dir/requires: Demos/ConcaveRaycastDemo/CMakeFiles/AppConcaveRayCastDemo.dir/main.obj.requires
Demos/ConcaveRaycastDemo/CMakeFiles/AppConcaveRayCastDemo.dir/requires: Demos/ConcaveRaycastDemo/CMakeFiles/AppConcaveRayCastDemo.dir/__/__/build/bullet.obj.requires
.PHONY : Demos/ConcaveRaycastDemo/CMakeFiles/AppConcaveRayCastDemo.dir/requires

Demos/ConcaveRaycastDemo/CMakeFiles/AppConcaveRayCastDemo.dir/clean:
	cd /d C:\Users\AJ\Desktop\bullet-2.82-r2704\Demos\ConcaveRaycastDemo && $(CMAKE_COMMAND) -P CMakeFiles\AppConcaveRayCastDemo.dir\cmake_clean.cmake
.PHONY : Demos/ConcaveRaycastDemo/CMakeFiles/AppConcaveRayCastDemo.dir/clean

Demos/ConcaveRaycastDemo/CMakeFiles/AppConcaveRayCastDemo.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\AJ\Desktop\bullet-2.82-r2704 C:\Users\AJ\Desktop\bullet-2.82-r2704\Demos\ConcaveRaycastDemo C:\Users\AJ\Desktop\bullet-2.82-r2704 C:\Users\AJ\Desktop\bullet-2.82-r2704\Demos\ConcaveRaycastDemo C:\Users\AJ\Desktop\bullet-2.82-r2704\Demos\ConcaveRaycastDemo\CMakeFiles\AppConcaveRayCastDemo.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : Demos/ConcaveRaycastDemo/CMakeFiles/AppConcaveRayCastDemo.dir/depend
