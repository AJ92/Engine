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
include Extras/GIMPACTUtils/CMakeFiles/GIMPACTUtils.dir/depend.make

# Include the progress variables for this target.
include Extras/GIMPACTUtils/CMakeFiles/GIMPACTUtils.dir/progress.make

# Include the compile flags for this target's objects.
include Extras/GIMPACTUtils/CMakeFiles/GIMPACTUtils.dir/flags.make

Extras/GIMPACTUtils/CMakeFiles/GIMPACTUtils.dir/btGImpactConvexDecompositionShape.obj: Extras/GIMPACTUtils/CMakeFiles/GIMPACTUtils.dir/flags.make
Extras/GIMPACTUtils/CMakeFiles/GIMPACTUtils.dir/btGImpactConvexDecompositionShape.obj: Extras/GIMPACTUtils/CMakeFiles/GIMPACTUtils.dir/includes_CXX.rsp
Extras/GIMPACTUtils/CMakeFiles/GIMPACTUtils.dir/btGImpactConvexDecompositionShape.obj: Extras/GIMPACTUtils/btGImpactConvexDecompositionShape.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report C:\Users\AJ\Desktop\bullet-2.82-r2704\CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object Extras/GIMPACTUtils/CMakeFiles/GIMPACTUtils.dir/btGImpactConvexDecompositionShape.obj"
	cd /d C:\Users\AJ\Desktop\bullet-2.82-r2704\Extras\GIMPACTUtils && E:\Code\MinGW\bin\g++.exe   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles\GIMPACTUtils.dir\btGImpactConvexDecompositionShape.obj -c C:\Users\AJ\Desktop\bullet-2.82-r2704\Extras\GIMPACTUtils\btGImpactConvexDecompositionShape.cpp

Extras/GIMPACTUtils/CMakeFiles/GIMPACTUtils.dir/btGImpactConvexDecompositionShape.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/GIMPACTUtils.dir/btGImpactConvexDecompositionShape.i"
	cd /d C:\Users\AJ\Desktop\bullet-2.82-r2704\Extras\GIMPACTUtils && E:\Code\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_FLAGS) -E C:\Users\AJ\Desktop\bullet-2.82-r2704\Extras\GIMPACTUtils\btGImpactConvexDecompositionShape.cpp > CMakeFiles\GIMPACTUtils.dir\btGImpactConvexDecompositionShape.i

Extras/GIMPACTUtils/CMakeFiles/GIMPACTUtils.dir/btGImpactConvexDecompositionShape.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/GIMPACTUtils.dir/btGImpactConvexDecompositionShape.s"
	cd /d C:\Users\AJ\Desktop\bullet-2.82-r2704\Extras\GIMPACTUtils && E:\Code\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_FLAGS) -S C:\Users\AJ\Desktop\bullet-2.82-r2704\Extras\GIMPACTUtils\btGImpactConvexDecompositionShape.cpp -o CMakeFiles\GIMPACTUtils.dir\btGImpactConvexDecompositionShape.s

Extras/GIMPACTUtils/CMakeFiles/GIMPACTUtils.dir/btGImpactConvexDecompositionShape.obj.requires:
.PHONY : Extras/GIMPACTUtils/CMakeFiles/GIMPACTUtils.dir/btGImpactConvexDecompositionShape.obj.requires

Extras/GIMPACTUtils/CMakeFiles/GIMPACTUtils.dir/btGImpactConvexDecompositionShape.obj.provides: Extras/GIMPACTUtils/CMakeFiles/GIMPACTUtils.dir/btGImpactConvexDecompositionShape.obj.requires
	$(MAKE) -f Extras\GIMPACTUtils\CMakeFiles\GIMPACTUtils.dir\build.make Extras/GIMPACTUtils/CMakeFiles/GIMPACTUtils.dir/btGImpactConvexDecompositionShape.obj.provides.build
.PHONY : Extras/GIMPACTUtils/CMakeFiles/GIMPACTUtils.dir/btGImpactConvexDecompositionShape.obj.provides

Extras/GIMPACTUtils/CMakeFiles/GIMPACTUtils.dir/btGImpactConvexDecompositionShape.obj.provides.build: Extras/GIMPACTUtils/CMakeFiles/GIMPACTUtils.dir/btGImpactConvexDecompositionShape.obj

# Object files for target GIMPACTUtils
GIMPACTUtils_OBJECTS = \
"CMakeFiles/GIMPACTUtils.dir/btGImpactConvexDecompositionShape.obj"

# External object files for target GIMPACTUtils
GIMPACTUtils_EXTERNAL_OBJECTS =

Extras/GIMPACTUtils/libGIMPACTUtils_Debug.dll: Extras/GIMPACTUtils/CMakeFiles/GIMPACTUtils.dir/btGImpactConvexDecompositionShape.obj
Extras/GIMPACTUtils/libGIMPACTUtils_Debug.dll: Extras/GIMPACTUtils/CMakeFiles/GIMPACTUtils.dir/build.make
Extras/GIMPACTUtils/libGIMPACTUtils_Debug.dll: Extras/ConvexDecomposition/libConvexDecomposition_Debug.dll.a
Extras/GIMPACTUtils/libGIMPACTUtils_Debug.dll: src/BulletCollision/libBulletCollision_Debug.dll.a
Extras/GIMPACTUtils/libGIMPACTUtils_Debug.dll: src/LinearMath/libLinearMath_Debug.dll.a
Extras/GIMPACTUtils/libGIMPACTUtils_Debug.dll: Extras/GIMPACTUtils/CMakeFiles/GIMPACTUtils.dir/objects1.rsp
Extras/GIMPACTUtils/libGIMPACTUtils_Debug.dll: Extras/GIMPACTUtils/CMakeFiles/GIMPACTUtils.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX shared library libGIMPACTUtils_Debug.dll"
	cd /d C:\Users\AJ\Desktop\bullet-2.82-r2704\Extras\GIMPACTUtils && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\GIMPACTUtils.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
Extras/GIMPACTUtils/CMakeFiles/GIMPACTUtils.dir/build: Extras/GIMPACTUtils/libGIMPACTUtils_Debug.dll
.PHONY : Extras/GIMPACTUtils/CMakeFiles/GIMPACTUtils.dir/build

Extras/GIMPACTUtils/CMakeFiles/GIMPACTUtils.dir/requires: Extras/GIMPACTUtils/CMakeFiles/GIMPACTUtils.dir/btGImpactConvexDecompositionShape.obj.requires
.PHONY : Extras/GIMPACTUtils/CMakeFiles/GIMPACTUtils.dir/requires

Extras/GIMPACTUtils/CMakeFiles/GIMPACTUtils.dir/clean:
	cd /d C:\Users\AJ\Desktop\bullet-2.82-r2704\Extras\GIMPACTUtils && $(CMAKE_COMMAND) -P CMakeFiles\GIMPACTUtils.dir\cmake_clean.cmake
.PHONY : Extras/GIMPACTUtils/CMakeFiles/GIMPACTUtils.dir/clean

Extras/GIMPACTUtils/CMakeFiles/GIMPACTUtils.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\AJ\Desktop\bullet-2.82-r2704 C:\Users\AJ\Desktop\bullet-2.82-r2704\Extras\GIMPACTUtils C:\Users\AJ\Desktop\bullet-2.82-r2704 C:\Users\AJ\Desktop\bullet-2.82-r2704\Extras\GIMPACTUtils C:\Users\AJ\Desktop\bullet-2.82-r2704\Extras\GIMPACTUtils\CMakeFiles\GIMPACTUtils.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : Extras/GIMPACTUtils/CMakeFiles/GIMPACTUtils.dir/depend

