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
include Demos/FractureDemo/CMakeFiles/AppFractureDemo.dir/depend.make

# Include the progress variables for this target.
include Demos/FractureDemo/CMakeFiles/AppFractureDemo.dir/progress.make

# Include the compile flags for this target's objects.
include Demos/FractureDemo/CMakeFiles/AppFractureDemo.dir/flags.make

Demos/FractureDemo/CMakeFiles/AppFractureDemo.dir/main.obj: Demos/FractureDemo/CMakeFiles/AppFractureDemo.dir/flags.make
Demos/FractureDemo/CMakeFiles/AppFractureDemo.dir/main.obj: Demos/FractureDemo/CMakeFiles/AppFractureDemo.dir/includes_CXX.rsp
Demos/FractureDemo/CMakeFiles/AppFractureDemo.dir/main.obj: Demos/FractureDemo/main.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report C:\Users\AJ\Desktop\bullet-2.82-r2704\CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object Demos/FractureDemo/CMakeFiles/AppFractureDemo.dir/main.obj"
	cd /d C:\Users\AJ\Desktop\bullet-2.82-r2704\Demos\FractureDemo && E:\Code\MinGW\bin\g++.exe   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles\AppFractureDemo.dir\main.obj -c C:\Users\AJ\Desktop\bullet-2.82-r2704\Demos\FractureDemo\main.cpp

Demos/FractureDemo/CMakeFiles/AppFractureDemo.dir/main.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/AppFractureDemo.dir/main.i"
	cd /d C:\Users\AJ\Desktop\bullet-2.82-r2704\Demos\FractureDemo && E:\Code\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_FLAGS) -E C:\Users\AJ\Desktop\bullet-2.82-r2704\Demos\FractureDemo\main.cpp > CMakeFiles\AppFractureDemo.dir\main.i

Demos/FractureDemo/CMakeFiles/AppFractureDemo.dir/main.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/AppFractureDemo.dir/main.s"
	cd /d C:\Users\AJ\Desktop\bullet-2.82-r2704\Demos\FractureDemo && E:\Code\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_FLAGS) -S C:\Users\AJ\Desktop\bullet-2.82-r2704\Demos\FractureDemo\main.cpp -o CMakeFiles\AppFractureDemo.dir\main.s

Demos/FractureDemo/CMakeFiles/AppFractureDemo.dir/main.obj.requires:
.PHONY : Demos/FractureDemo/CMakeFiles/AppFractureDemo.dir/main.obj.requires

Demos/FractureDemo/CMakeFiles/AppFractureDemo.dir/main.obj.provides: Demos/FractureDemo/CMakeFiles/AppFractureDemo.dir/main.obj.requires
	$(MAKE) -f Demos\FractureDemo\CMakeFiles\AppFractureDemo.dir\build.make Demos/FractureDemo/CMakeFiles/AppFractureDemo.dir/main.obj.provides.build
.PHONY : Demos/FractureDemo/CMakeFiles/AppFractureDemo.dir/main.obj.provides

Demos/FractureDemo/CMakeFiles/AppFractureDemo.dir/main.obj.provides.build: Demos/FractureDemo/CMakeFiles/AppFractureDemo.dir/main.obj

Demos/FractureDemo/CMakeFiles/AppFractureDemo.dir/FractureDemo.obj: Demos/FractureDemo/CMakeFiles/AppFractureDemo.dir/flags.make
Demos/FractureDemo/CMakeFiles/AppFractureDemo.dir/FractureDemo.obj: Demos/FractureDemo/CMakeFiles/AppFractureDemo.dir/includes_CXX.rsp
Demos/FractureDemo/CMakeFiles/AppFractureDemo.dir/FractureDemo.obj: Demos/FractureDemo/FractureDemo.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report C:\Users\AJ\Desktop\bullet-2.82-r2704\CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object Demos/FractureDemo/CMakeFiles/AppFractureDemo.dir/FractureDemo.obj"
	cd /d C:\Users\AJ\Desktop\bullet-2.82-r2704\Demos\FractureDemo && E:\Code\MinGW\bin\g++.exe   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles\AppFractureDemo.dir\FractureDemo.obj -c C:\Users\AJ\Desktop\bullet-2.82-r2704\Demos\FractureDemo\FractureDemo.cpp

Demos/FractureDemo/CMakeFiles/AppFractureDemo.dir/FractureDemo.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/AppFractureDemo.dir/FractureDemo.i"
	cd /d C:\Users\AJ\Desktop\bullet-2.82-r2704\Demos\FractureDemo && E:\Code\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_FLAGS) -E C:\Users\AJ\Desktop\bullet-2.82-r2704\Demos\FractureDemo\FractureDemo.cpp > CMakeFiles\AppFractureDemo.dir\FractureDemo.i

Demos/FractureDemo/CMakeFiles/AppFractureDemo.dir/FractureDemo.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/AppFractureDemo.dir/FractureDemo.s"
	cd /d C:\Users\AJ\Desktop\bullet-2.82-r2704\Demos\FractureDemo && E:\Code\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_FLAGS) -S C:\Users\AJ\Desktop\bullet-2.82-r2704\Demos\FractureDemo\FractureDemo.cpp -o CMakeFiles\AppFractureDemo.dir\FractureDemo.s

Demos/FractureDemo/CMakeFiles/AppFractureDemo.dir/FractureDemo.obj.requires:
.PHONY : Demos/FractureDemo/CMakeFiles/AppFractureDemo.dir/FractureDemo.obj.requires

Demos/FractureDemo/CMakeFiles/AppFractureDemo.dir/FractureDemo.obj.provides: Demos/FractureDemo/CMakeFiles/AppFractureDemo.dir/FractureDemo.obj.requires
	$(MAKE) -f Demos\FractureDemo\CMakeFiles\AppFractureDemo.dir\build.make Demos/FractureDemo/CMakeFiles/AppFractureDemo.dir/FractureDemo.obj.provides.build
.PHONY : Demos/FractureDemo/CMakeFiles/AppFractureDemo.dir/FractureDemo.obj.provides

Demos/FractureDemo/CMakeFiles/AppFractureDemo.dir/FractureDemo.obj.provides.build: Demos/FractureDemo/CMakeFiles/AppFractureDemo.dir/FractureDemo.obj

Demos/FractureDemo/CMakeFiles/AppFractureDemo.dir/btFractureBody.obj: Demos/FractureDemo/CMakeFiles/AppFractureDemo.dir/flags.make
Demos/FractureDemo/CMakeFiles/AppFractureDemo.dir/btFractureBody.obj: Demos/FractureDemo/CMakeFiles/AppFractureDemo.dir/includes_CXX.rsp
Demos/FractureDemo/CMakeFiles/AppFractureDemo.dir/btFractureBody.obj: Demos/FractureDemo/btFractureBody.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report C:\Users\AJ\Desktop\bullet-2.82-r2704\CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object Demos/FractureDemo/CMakeFiles/AppFractureDemo.dir/btFractureBody.obj"
	cd /d C:\Users\AJ\Desktop\bullet-2.82-r2704\Demos\FractureDemo && E:\Code\MinGW\bin\g++.exe   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles\AppFractureDemo.dir\btFractureBody.obj -c C:\Users\AJ\Desktop\bullet-2.82-r2704\Demos\FractureDemo\btFractureBody.cpp

Demos/FractureDemo/CMakeFiles/AppFractureDemo.dir/btFractureBody.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/AppFractureDemo.dir/btFractureBody.i"
	cd /d C:\Users\AJ\Desktop\bullet-2.82-r2704\Demos\FractureDemo && E:\Code\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_FLAGS) -E C:\Users\AJ\Desktop\bullet-2.82-r2704\Demos\FractureDemo\btFractureBody.cpp > CMakeFiles\AppFractureDemo.dir\btFractureBody.i

Demos/FractureDemo/CMakeFiles/AppFractureDemo.dir/btFractureBody.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/AppFractureDemo.dir/btFractureBody.s"
	cd /d C:\Users\AJ\Desktop\bullet-2.82-r2704\Demos\FractureDemo && E:\Code\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_FLAGS) -S C:\Users\AJ\Desktop\bullet-2.82-r2704\Demos\FractureDemo\btFractureBody.cpp -o CMakeFiles\AppFractureDemo.dir\btFractureBody.s

Demos/FractureDemo/CMakeFiles/AppFractureDemo.dir/btFractureBody.obj.requires:
.PHONY : Demos/FractureDemo/CMakeFiles/AppFractureDemo.dir/btFractureBody.obj.requires

Demos/FractureDemo/CMakeFiles/AppFractureDemo.dir/btFractureBody.obj.provides: Demos/FractureDemo/CMakeFiles/AppFractureDemo.dir/btFractureBody.obj.requires
	$(MAKE) -f Demos\FractureDemo\CMakeFiles\AppFractureDemo.dir\build.make Demos/FractureDemo/CMakeFiles/AppFractureDemo.dir/btFractureBody.obj.provides.build
.PHONY : Demos/FractureDemo/CMakeFiles/AppFractureDemo.dir/btFractureBody.obj.provides

Demos/FractureDemo/CMakeFiles/AppFractureDemo.dir/btFractureBody.obj.provides.build: Demos/FractureDemo/CMakeFiles/AppFractureDemo.dir/btFractureBody.obj

Demos/FractureDemo/CMakeFiles/AppFractureDemo.dir/btFractureDynamicsWorld.obj: Demos/FractureDemo/CMakeFiles/AppFractureDemo.dir/flags.make
Demos/FractureDemo/CMakeFiles/AppFractureDemo.dir/btFractureDynamicsWorld.obj: Demos/FractureDemo/CMakeFiles/AppFractureDemo.dir/includes_CXX.rsp
Demos/FractureDemo/CMakeFiles/AppFractureDemo.dir/btFractureDynamicsWorld.obj: Demos/FractureDemo/btFractureDynamicsWorld.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report C:\Users\AJ\Desktop\bullet-2.82-r2704\CMakeFiles $(CMAKE_PROGRESS_4)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object Demos/FractureDemo/CMakeFiles/AppFractureDemo.dir/btFractureDynamicsWorld.obj"
	cd /d C:\Users\AJ\Desktop\bullet-2.82-r2704\Demos\FractureDemo && E:\Code\MinGW\bin\g++.exe   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles\AppFractureDemo.dir\btFractureDynamicsWorld.obj -c C:\Users\AJ\Desktop\bullet-2.82-r2704\Demos\FractureDemo\btFractureDynamicsWorld.cpp

Demos/FractureDemo/CMakeFiles/AppFractureDemo.dir/btFractureDynamicsWorld.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/AppFractureDemo.dir/btFractureDynamicsWorld.i"
	cd /d C:\Users\AJ\Desktop\bullet-2.82-r2704\Demos\FractureDemo && E:\Code\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_FLAGS) -E C:\Users\AJ\Desktop\bullet-2.82-r2704\Demos\FractureDemo\btFractureDynamicsWorld.cpp > CMakeFiles\AppFractureDemo.dir\btFractureDynamicsWorld.i

Demos/FractureDemo/CMakeFiles/AppFractureDemo.dir/btFractureDynamicsWorld.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/AppFractureDemo.dir/btFractureDynamicsWorld.s"
	cd /d C:\Users\AJ\Desktop\bullet-2.82-r2704\Demos\FractureDemo && E:\Code\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_FLAGS) -S C:\Users\AJ\Desktop\bullet-2.82-r2704\Demos\FractureDemo\btFractureDynamicsWorld.cpp -o CMakeFiles\AppFractureDemo.dir\btFractureDynamicsWorld.s

Demos/FractureDemo/CMakeFiles/AppFractureDemo.dir/btFractureDynamicsWorld.obj.requires:
.PHONY : Demos/FractureDemo/CMakeFiles/AppFractureDemo.dir/btFractureDynamicsWorld.obj.requires

Demos/FractureDemo/CMakeFiles/AppFractureDemo.dir/btFractureDynamicsWorld.obj.provides: Demos/FractureDemo/CMakeFiles/AppFractureDemo.dir/btFractureDynamicsWorld.obj.requires
	$(MAKE) -f Demos\FractureDemo\CMakeFiles\AppFractureDemo.dir\build.make Demos/FractureDemo/CMakeFiles/AppFractureDemo.dir/btFractureDynamicsWorld.obj.provides.build
.PHONY : Demos/FractureDemo/CMakeFiles/AppFractureDemo.dir/btFractureDynamicsWorld.obj.provides

Demos/FractureDemo/CMakeFiles/AppFractureDemo.dir/btFractureDynamicsWorld.obj.provides.build: Demos/FractureDemo/CMakeFiles/AppFractureDemo.dir/btFractureDynamicsWorld.obj

Demos/FractureDemo/CMakeFiles/AppFractureDemo.dir/__/__/build/bullet.obj: Demos/FractureDemo/CMakeFiles/AppFractureDemo.dir/flags.make
Demos/FractureDemo/CMakeFiles/AppFractureDemo.dir/__/__/build/bullet.obj: build/bullet.rc
	$(CMAKE_COMMAND) -E cmake_progress_report C:\Users\AJ\Desktop\bullet-2.82-r2704\CMakeFiles $(CMAKE_PROGRESS_5)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building RC object Demos/FractureDemo/CMakeFiles/AppFractureDemo.dir/__/__/build/bullet.obj"
	cd /d C:\Users\AJ\Desktop\bullet-2.82-r2704\Demos\FractureDemo && E:\Code\MinGW\bin\windres.exe  -O coff $(RC_FLAGS) $(RC_DEFINES) C:\Users\AJ\Desktop\bullet-2.82-r2704\build\bullet.rc CMakeFiles\AppFractureDemo.dir\__\__\build\bullet.obj

Demos/FractureDemo/CMakeFiles/AppFractureDemo.dir/__/__/build/bullet.obj.requires:
.PHONY : Demos/FractureDemo/CMakeFiles/AppFractureDemo.dir/__/__/build/bullet.obj.requires

Demos/FractureDemo/CMakeFiles/AppFractureDemo.dir/__/__/build/bullet.obj.provides: Demos/FractureDemo/CMakeFiles/AppFractureDemo.dir/__/__/build/bullet.obj.requires
	$(MAKE) -f Demos\FractureDemo\CMakeFiles\AppFractureDemo.dir\build.make Demos/FractureDemo/CMakeFiles/AppFractureDemo.dir/__/__/build/bullet.obj.provides.build
.PHONY : Demos/FractureDemo/CMakeFiles/AppFractureDemo.dir/__/__/build/bullet.obj.provides

Demos/FractureDemo/CMakeFiles/AppFractureDemo.dir/__/__/build/bullet.obj.provides.build: Demos/FractureDemo/CMakeFiles/AppFractureDemo.dir/__/__/build/bullet.obj

# Object files for target AppFractureDemo
AppFractureDemo_OBJECTS = \
"CMakeFiles/AppFractureDemo.dir/main.obj" \
"CMakeFiles/AppFractureDemo.dir/FractureDemo.obj" \
"CMakeFiles/AppFractureDemo.dir/btFractureBody.obj" \
"CMakeFiles/AppFractureDemo.dir/btFractureDynamicsWorld.obj" \
"CMakeFiles/AppFractureDemo.dir/__/__/build/bullet.obj"

# External object files for target AppFractureDemo
AppFractureDemo_EXTERNAL_OBJECTS =

Demos/FractureDemo/AppFractureDemo.exe: Demos/FractureDemo/CMakeFiles/AppFractureDemo.dir/main.obj
Demos/FractureDemo/AppFractureDemo.exe: Demos/FractureDemo/CMakeFiles/AppFractureDemo.dir/FractureDemo.obj
Demos/FractureDemo/AppFractureDemo.exe: Demos/FractureDemo/CMakeFiles/AppFractureDemo.dir/btFractureBody.obj
Demos/FractureDemo/AppFractureDemo.exe: Demos/FractureDemo/CMakeFiles/AppFractureDemo.dir/btFractureDynamicsWorld.obj
Demos/FractureDemo/AppFractureDemo.exe: Demos/FractureDemo/CMakeFiles/AppFractureDemo.dir/__/__/build/bullet.obj
Demos/FractureDemo/AppFractureDemo.exe: Demos/FractureDemo/CMakeFiles/AppFractureDemo.dir/build.make
Demos/FractureDemo/AppFractureDemo.exe: Demos/OpenGL/libOpenGLSupport_Debug.dll.a
Demos/FractureDemo/AppFractureDemo.exe: src/BulletDynamics/libBulletDynamics_Debug.dll.a
Demos/FractureDemo/AppFractureDemo.exe: src/BulletCollision/libBulletCollision_Debug.dll.a
Demos/FractureDemo/AppFractureDemo.exe: src/LinearMath/libLinearMath_Debug.dll.a
Demos/FractureDemo/AppFractureDemo.exe: Demos/FractureDemo/CMakeFiles/AppFractureDemo.dir/objects1.rsp
Demos/FractureDemo/AppFractureDemo.exe: Demos/FractureDemo/CMakeFiles/AppFractureDemo.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable AppFractureDemo.exe"
	cd /d C:\Users\AJ\Desktop\bullet-2.82-r2704\Demos\FractureDemo && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\AppFractureDemo.dir\link.txt --verbose=$(VERBOSE)
	cd /d C:\Users\AJ\Desktop\bullet-2.82-r2704\Demos\FractureDemo && "E:\Code\cmake\CMake 2.8\bin\cmake.exe" -E copy_if_different C:/Users/AJ/Desktop/bullet-2.82-r2704/GLUT32.DLL C:/Users/AJ/Desktop/bullet-2.82-r2704/Demos/FractureDemo
	cd /d C:\Users\AJ\Desktop\bullet-2.82-r2704\Demos\FractureDemo && "E:\Code\cmake\CMake 2.8\bin\cmake.exe" -E copy_if_different C:/Users/AJ/Desktop/bullet-2.82-r2704/GLUT32.DLL C:/Users/AJ/Desktop/bullet-2.82-r2704/Demos/FractureDemo/Debug

# Rule to build all files generated by this target.
Demos/FractureDemo/CMakeFiles/AppFractureDemo.dir/build: Demos/FractureDemo/AppFractureDemo.exe
.PHONY : Demos/FractureDemo/CMakeFiles/AppFractureDemo.dir/build

Demos/FractureDemo/CMakeFiles/AppFractureDemo.dir/requires: Demos/FractureDemo/CMakeFiles/AppFractureDemo.dir/main.obj.requires
Demos/FractureDemo/CMakeFiles/AppFractureDemo.dir/requires: Demos/FractureDemo/CMakeFiles/AppFractureDemo.dir/FractureDemo.obj.requires
Demos/FractureDemo/CMakeFiles/AppFractureDemo.dir/requires: Demos/FractureDemo/CMakeFiles/AppFractureDemo.dir/btFractureBody.obj.requires
Demos/FractureDemo/CMakeFiles/AppFractureDemo.dir/requires: Demos/FractureDemo/CMakeFiles/AppFractureDemo.dir/btFractureDynamicsWorld.obj.requires
Demos/FractureDemo/CMakeFiles/AppFractureDemo.dir/requires: Demos/FractureDemo/CMakeFiles/AppFractureDemo.dir/__/__/build/bullet.obj.requires
.PHONY : Demos/FractureDemo/CMakeFiles/AppFractureDemo.dir/requires

Demos/FractureDemo/CMakeFiles/AppFractureDemo.dir/clean:
	cd /d C:\Users\AJ\Desktop\bullet-2.82-r2704\Demos\FractureDemo && $(CMAKE_COMMAND) -P CMakeFiles\AppFractureDemo.dir\cmake_clean.cmake
.PHONY : Demos/FractureDemo/CMakeFiles/AppFractureDemo.dir/clean

Demos/FractureDemo/CMakeFiles/AppFractureDemo.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\AJ\Desktop\bullet-2.82-r2704 C:\Users\AJ\Desktop\bullet-2.82-r2704\Demos\FractureDemo C:\Users\AJ\Desktop\bullet-2.82-r2704 C:\Users\AJ\Desktop\bullet-2.82-r2704\Demos\FractureDemo C:\Users\AJ\Desktop\bullet-2.82-r2704\Demos\FractureDemo\CMakeFiles\AppFractureDemo.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : Demos/FractureDemo/CMakeFiles/AppFractureDemo.dir/depend

