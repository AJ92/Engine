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
include Demos/RagdollDemo/CMakeFiles/AppRagdollDemo.dir/depend.make

# Include the progress variables for this target.
include Demos/RagdollDemo/CMakeFiles/AppRagdollDemo.dir/progress.make

# Include the compile flags for this target's objects.
include Demos/RagdollDemo/CMakeFiles/AppRagdollDemo.dir/flags.make

Demos/RagdollDemo/CMakeFiles/AppRagdollDemo.dir/RagdollDemo.obj: Demos/RagdollDemo/CMakeFiles/AppRagdollDemo.dir/flags.make
Demos/RagdollDemo/CMakeFiles/AppRagdollDemo.dir/RagdollDemo.obj: Demos/RagdollDemo/CMakeFiles/AppRagdollDemo.dir/includes_CXX.rsp
Demos/RagdollDemo/CMakeFiles/AppRagdollDemo.dir/RagdollDemo.obj: Demos/RagdollDemo/RagdollDemo.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report C:\Users\AJ\Desktop\bullet-2.82-r2704\CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object Demos/RagdollDemo/CMakeFiles/AppRagdollDemo.dir/RagdollDemo.obj"
	cd /d C:\Users\AJ\Desktop\bullet-2.82-r2704\Demos\RagdollDemo && E:\Code\MinGW\bin\g++.exe   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles\AppRagdollDemo.dir\RagdollDemo.obj -c C:\Users\AJ\Desktop\bullet-2.82-r2704\Demos\RagdollDemo\RagdollDemo.cpp

Demos/RagdollDemo/CMakeFiles/AppRagdollDemo.dir/RagdollDemo.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/AppRagdollDemo.dir/RagdollDemo.i"
	cd /d C:\Users\AJ\Desktop\bullet-2.82-r2704\Demos\RagdollDemo && E:\Code\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_FLAGS) -E C:\Users\AJ\Desktop\bullet-2.82-r2704\Demos\RagdollDemo\RagdollDemo.cpp > CMakeFiles\AppRagdollDemo.dir\RagdollDemo.i

Demos/RagdollDemo/CMakeFiles/AppRagdollDemo.dir/RagdollDemo.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/AppRagdollDemo.dir/RagdollDemo.s"
	cd /d C:\Users\AJ\Desktop\bullet-2.82-r2704\Demos\RagdollDemo && E:\Code\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_FLAGS) -S C:\Users\AJ\Desktop\bullet-2.82-r2704\Demos\RagdollDemo\RagdollDemo.cpp -o CMakeFiles\AppRagdollDemo.dir\RagdollDemo.s

Demos/RagdollDemo/CMakeFiles/AppRagdollDemo.dir/RagdollDemo.obj.requires:
.PHONY : Demos/RagdollDemo/CMakeFiles/AppRagdollDemo.dir/RagdollDemo.obj.requires

Demos/RagdollDemo/CMakeFiles/AppRagdollDemo.dir/RagdollDemo.obj.provides: Demos/RagdollDemo/CMakeFiles/AppRagdollDemo.dir/RagdollDemo.obj.requires
	$(MAKE) -f Demos\RagdollDemo\CMakeFiles\AppRagdollDemo.dir\build.make Demos/RagdollDemo/CMakeFiles/AppRagdollDemo.dir/RagdollDemo.obj.provides.build
.PHONY : Demos/RagdollDemo/CMakeFiles/AppRagdollDemo.dir/RagdollDemo.obj.provides

Demos/RagdollDemo/CMakeFiles/AppRagdollDemo.dir/RagdollDemo.obj.provides.build: Demos/RagdollDemo/CMakeFiles/AppRagdollDemo.dir/RagdollDemo.obj

Demos/RagdollDemo/CMakeFiles/AppRagdollDemo.dir/main.obj: Demos/RagdollDemo/CMakeFiles/AppRagdollDemo.dir/flags.make
Demos/RagdollDemo/CMakeFiles/AppRagdollDemo.dir/main.obj: Demos/RagdollDemo/CMakeFiles/AppRagdollDemo.dir/includes_CXX.rsp
Demos/RagdollDemo/CMakeFiles/AppRagdollDemo.dir/main.obj: Demos/RagdollDemo/main.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report C:\Users\AJ\Desktop\bullet-2.82-r2704\CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object Demos/RagdollDemo/CMakeFiles/AppRagdollDemo.dir/main.obj"
	cd /d C:\Users\AJ\Desktop\bullet-2.82-r2704\Demos\RagdollDemo && E:\Code\MinGW\bin\g++.exe   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles\AppRagdollDemo.dir\main.obj -c C:\Users\AJ\Desktop\bullet-2.82-r2704\Demos\RagdollDemo\main.cpp

Demos/RagdollDemo/CMakeFiles/AppRagdollDemo.dir/main.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/AppRagdollDemo.dir/main.i"
	cd /d C:\Users\AJ\Desktop\bullet-2.82-r2704\Demos\RagdollDemo && E:\Code\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_FLAGS) -E C:\Users\AJ\Desktop\bullet-2.82-r2704\Demos\RagdollDemo\main.cpp > CMakeFiles\AppRagdollDemo.dir\main.i

Demos/RagdollDemo/CMakeFiles/AppRagdollDemo.dir/main.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/AppRagdollDemo.dir/main.s"
	cd /d C:\Users\AJ\Desktop\bullet-2.82-r2704\Demos\RagdollDemo && E:\Code\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_FLAGS) -S C:\Users\AJ\Desktop\bullet-2.82-r2704\Demos\RagdollDemo\main.cpp -o CMakeFiles\AppRagdollDemo.dir\main.s

Demos/RagdollDemo/CMakeFiles/AppRagdollDemo.dir/main.obj.requires:
.PHONY : Demos/RagdollDemo/CMakeFiles/AppRagdollDemo.dir/main.obj.requires

Demos/RagdollDemo/CMakeFiles/AppRagdollDemo.dir/main.obj.provides: Demos/RagdollDemo/CMakeFiles/AppRagdollDemo.dir/main.obj.requires
	$(MAKE) -f Demos\RagdollDemo\CMakeFiles\AppRagdollDemo.dir\build.make Demos/RagdollDemo/CMakeFiles/AppRagdollDemo.dir/main.obj.provides.build
.PHONY : Demos/RagdollDemo/CMakeFiles/AppRagdollDemo.dir/main.obj.provides

Demos/RagdollDemo/CMakeFiles/AppRagdollDemo.dir/main.obj.provides.build: Demos/RagdollDemo/CMakeFiles/AppRagdollDemo.dir/main.obj

# Object files for target AppRagdollDemo
AppRagdollDemo_OBJECTS = \
"CMakeFiles/AppRagdollDemo.dir/RagdollDemo.obj" \
"CMakeFiles/AppRagdollDemo.dir/main.obj"

# External object files for target AppRagdollDemo
AppRagdollDemo_EXTERNAL_OBJECTS =

Demos/RagdollDemo/AppRagdollDemo.exe: Demos/RagdollDemo/CMakeFiles/AppRagdollDemo.dir/RagdollDemo.obj
Demos/RagdollDemo/AppRagdollDemo.exe: Demos/RagdollDemo/CMakeFiles/AppRagdollDemo.dir/main.obj
Demos/RagdollDemo/AppRagdollDemo.exe: Demos/RagdollDemo/CMakeFiles/AppRagdollDemo.dir/build.make
Demos/RagdollDemo/AppRagdollDemo.exe: Demos/OpenGL/libOpenGLSupport_Debug.dll.a
Demos/RagdollDemo/AppRagdollDemo.exe: src/BulletDynamics/libBulletDynamics_Debug.dll.a
Demos/RagdollDemo/AppRagdollDemo.exe: src/BulletCollision/libBulletCollision_Debug.dll.a
Demos/RagdollDemo/AppRagdollDemo.exe: src/LinearMath/libLinearMath_Debug.dll.a
Demos/RagdollDemo/AppRagdollDemo.exe: Demos/RagdollDemo/CMakeFiles/AppRagdollDemo.dir/objects1.rsp
Demos/RagdollDemo/AppRagdollDemo.exe: Demos/RagdollDemo/CMakeFiles/AppRagdollDemo.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable AppRagdollDemo.exe"
	cd /d C:\Users\AJ\Desktop\bullet-2.82-r2704\Demos\RagdollDemo && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\AppRagdollDemo.dir\link.txt --verbose=$(VERBOSE)
	cd /d C:\Users\AJ\Desktop\bullet-2.82-r2704\Demos\RagdollDemo && "E:\Code\cmake\CMake 2.8\bin\cmake.exe" -E copy_if_different C:/Users/AJ/Desktop/bullet-2.82-r2704/GLUT32.DLL C:/Users/AJ/Desktop/bullet-2.82-r2704/Demos/RagdollDemo

# Rule to build all files generated by this target.
Demos/RagdollDemo/CMakeFiles/AppRagdollDemo.dir/build: Demos/RagdollDemo/AppRagdollDemo.exe
.PHONY : Demos/RagdollDemo/CMakeFiles/AppRagdollDemo.dir/build

Demos/RagdollDemo/CMakeFiles/AppRagdollDemo.dir/requires: Demos/RagdollDemo/CMakeFiles/AppRagdollDemo.dir/RagdollDemo.obj.requires
Demos/RagdollDemo/CMakeFiles/AppRagdollDemo.dir/requires: Demos/RagdollDemo/CMakeFiles/AppRagdollDemo.dir/main.obj.requires
.PHONY : Demos/RagdollDemo/CMakeFiles/AppRagdollDemo.dir/requires

Demos/RagdollDemo/CMakeFiles/AppRagdollDemo.dir/clean:
	cd /d C:\Users\AJ\Desktop\bullet-2.82-r2704\Demos\RagdollDemo && $(CMAKE_COMMAND) -P CMakeFiles\AppRagdollDemo.dir\cmake_clean.cmake
.PHONY : Demos/RagdollDemo/CMakeFiles/AppRagdollDemo.dir/clean

Demos/RagdollDemo/CMakeFiles/AppRagdollDemo.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\AJ\Desktop\bullet-2.82-r2704 C:\Users\AJ\Desktop\bullet-2.82-r2704\Demos\RagdollDemo C:\Users\AJ\Desktop\bullet-2.82-r2704 C:\Users\AJ\Desktop\bullet-2.82-r2704\Demos\RagdollDemo C:\Users\AJ\Desktop\bullet-2.82-r2704\Demos\RagdollDemo\CMakeFiles\AppRagdollDemo.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : Demos/RagdollDemo/CMakeFiles/AppRagdollDemo.dir/depend

