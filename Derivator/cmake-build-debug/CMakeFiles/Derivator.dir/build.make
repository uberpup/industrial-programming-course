# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.15

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


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

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /home/vladimir/.local/share/JetBrains/Toolbox/apps/CLion/ch-1/193.5233.144/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/vladimir/.local/share/JetBrains/Toolbox/apps/CLion/ch-1/193.5233.144/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/home/vladimir/CLionProjects/Industrial Programming Course/industrial-programming-course/Derivator"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/home/vladimir/CLionProjects/Industrial Programming Course/industrial-programming-course/Derivator/cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/Derivator.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Derivator.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Derivator.dir/flags.make

CMakeFiles/Derivator.dir/main.cpp.o: CMakeFiles/Derivator.dir/flags.make
CMakeFiles/Derivator.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/vladimir/CLionProjects/Industrial Programming Course/industrial-programming-course/Derivator/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Derivator.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Derivator.dir/main.cpp.o -c "/home/vladimir/CLionProjects/Industrial Programming Course/industrial-programming-course/Derivator/main.cpp"

CMakeFiles/Derivator.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Derivator.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/vladimir/CLionProjects/Industrial Programming Course/industrial-programming-course/Derivator/main.cpp" > CMakeFiles/Derivator.dir/main.cpp.i

CMakeFiles/Derivator.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Derivator.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/vladimir/CLionProjects/Industrial Programming Course/industrial-programming-course/Derivator/main.cpp" -o CMakeFiles/Derivator.dir/main.cpp.s

CMakeFiles/Derivator.dir/sources/tree_dot_converter.cpp.o: CMakeFiles/Derivator.dir/flags.make
CMakeFiles/Derivator.dir/sources/tree_dot_converter.cpp.o: ../sources/tree_dot_converter.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/vladimir/CLionProjects/Industrial Programming Course/industrial-programming-course/Derivator/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/Derivator.dir/sources/tree_dot_converter.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Derivator.dir/sources/tree_dot_converter.cpp.o -c "/home/vladimir/CLionProjects/Industrial Programming Course/industrial-programming-course/Derivator/sources/tree_dot_converter.cpp"

CMakeFiles/Derivator.dir/sources/tree_dot_converter.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Derivator.dir/sources/tree_dot_converter.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/vladimir/CLionProjects/Industrial Programming Course/industrial-programming-course/Derivator/sources/tree_dot_converter.cpp" > CMakeFiles/Derivator.dir/sources/tree_dot_converter.cpp.i

CMakeFiles/Derivator.dir/sources/tree_dot_converter.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Derivator.dir/sources/tree_dot_converter.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/vladimir/CLionProjects/Industrial Programming Course/industrial-programming-course/Derivator/sources/tree_dot_converter.cpp" -o CMakeFiles/Derivator.dir/sources/tree_dot_converter.cpp.s

CMakeFiles/Derivator.dir/sources/derivator.cpp.o: CMakeFiles/Derivator.dir/flags.make
CMakeFiles/Derivator.dir/sources/derivator.cpp.o: ../sources/derivator.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/vladimir/CLionProjects/Industrial Programming Course/industrial-programming-course/Derivator/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/Derivator.dir/sources/derivator.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Derivator.dir/sources/derivator.cpp.o -c "/home/vladimir/CLionProjects/Industrial Programming Course/industrial-programming-course/Derivator/sources/derivator.cpp"

CMakeFiles/Derivator.dir/sources/derivator.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Derivator.dir/sources/derivator.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/vladimir/CLionProjects/Industrial Programming Course/industrial-programming-course/Derivator/sources/derivator.cpp" > CMakeFiles/Derivator.dir/sources/derivator.cpp.i

CMakeFiles/Derivator.dir/sources/derivator.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Derivator.dir/sources/derivator.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/vladimir/CLionProjects/Industrial Programming Course/industrial-programming-course/Derivator/sources/derivator.cpp" -o CMakeFiles/Derivator.dir/sources/derivator.cpp.s

CMakeFiles/Derivator.dir/sources/tree.cpp.o: CMakeFiles/Derivator.dir/flags.make
CMakeFiles/Derivator.dir/sources/tree.cpp.o: ../sources/tree.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/vladimir/CLionProjects/Industrial Programming Course/industrial-programming-course/Derivator/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/Derivator.dir/sources/tree.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Derivator.dir/sources/tree.cpp.o -c "/home/vladimir/CLionProjects/Industrial Programming Course/industrial-programming-course/Derivator/sources/tree.cpp"

CMakeFiles/Derivator.dir/sources/tree.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Derivator.dir/sources/tree.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/vladimir/CLionProjects/Industrial Programming Course/industrial-programming-course/Derivator/sources/tree.cpp" > CMakeFiles/Derivator.dir/sources/tree.cpp.i

CMakeFiles/Derivator.dir/sources/tree.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Derivator.dir/sources/tree.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/vladimir/CLionProjects/Industrial Programming Course/industrial-programming-course/Derivator/sources/tree.cpp" -o CMakeFiles/Derivator.dir/sources/tree.cpp.s

# Object files for target Derivator
Derivator_OBJECTS = \
"CMakeFiles/Derivator.dir/main.cpp.o" \
"CMakeFiles/Derivator.dir/sources/tree_dot_converter.cpp.o" \
"CMakeFiles/Derivator.dir/sources/derivator.cpp.o" \
"CMakeFiles/Derivator.dir/sources/tree.cpp.o"

# External object files for target Derivator
Derivator_EXTERNAL_OBJECTS =

Derivator: CMakeFiles/Derivator.dir/main.cpp.o
Derivator: CMakeFiles/Derivator.dir/sources/tree_dot_converter.cpp.o
Derivator: CMakeFiles/Derivator.dir/sources/derivator.cpp.o
Derivator: CMakeFiles/Derivator.dir/sources/tree.cpp.o
Derivator: CMakeFiles/Derivator.dir/build.make
Derivator: CMakeFiles/Derivator.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/home/vladimir/CLionProjects/Industrial Programming Course/industrial-programming-course/Derivator/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX executable Derivator"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Derivator.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Derivator.dir/build: Derivator

.PHONY : CMakeFiles/Derivator.dir/build

CMakeFiles/Derivator.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Derivator.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Derivator.dir/clean

CMakeFiles/Derivator.dir/depend:
	cd "/home/vladimir/CLionProjects/Industrial Programming Course/industrial-programming-course/Derivator/cmake-build-debug" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/home/vladimir/CLionProjects/Industrial Programming Course/industrial-programming-course/Derivator" "/home/vladimir/CLionProjects/Industrial Programming Course/industrial-programming-course/Derivator" "/home/vladimir/CLionProjects/Industrial Programming Course/industrial-programming-course/Derivator/cmake-build-debug" "/home/vladimir/CLionProjects/Industrial Programming Course/industrial-programming-course/Derivator/cmake-build-debug" "/home/vladimir/CLionProjects/Industrial Programming Course/industrial-programming-course/Derivator/cmake-build-debug/CMakeFiles/Derivator.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/Derivator.dir/depend

