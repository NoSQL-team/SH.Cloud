# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.17

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


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
CMAKE_COMMAND = /snap/clion/129/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /snap/clion/129/bin/cmake/linux/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/lerakry/tp/program_c++/ServerQueue

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/lerakry/tp/program_c++/ServerQueue/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/ServerQueue.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/ServerQueue.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/ServerQueue.dir/flags.make

CMakeFiles/ServerQueue.dir/project/src/main.cpp.o: CMakeFiles/ServerQueue.dir/flags.make
CMakeFiles/ServerQueue.dir/project/src/main.cpp.o: ../project/src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lerakry/tp/program_c++/ServerQueue/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/ServerQueue.dir/project/src/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ServerQueue.dir/project/src/main.cpp.o -c /home/lerakry/tp/program_c++/ServerQueue/project/src/main.cpp

CMakeFiles/ServerQueue.dir/project/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ServerQueue.dir/project/src/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/lerakry/tp/program_c++/ServerQueue/project/src/main.cpp > CMakeFiles/ServerQueue.dir/project/src/main.cpp.i

CMakeFiles/ServerQueue.dir/project/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ServerQueue.dir/project/src/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/lerakry/tp/program_c++/ServerQueue/project/src/main.cpp -o CMakeFiles/ServerQueue.dir/project/src/main.cpp.s

# Object files for target ServerQueue
ServerQueue_OBJECTS = \
"CMakeFiles/ServerQueue.dir/project/src/main.cpp.o"

# External object files for target ServerQueue
ServerQueue_EXTERNAL_OBJECTS =

ServerQueue: CMakeFiles/ServerQueue.dir/project/src/main.cpp.o
ServerQueue: CMakeFiles/ServerQueue.dir/build.make
ServerQueue: CMakeFiles/ServerQueue.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/lerakry/tp/program_c++/ServerQueue/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ServerQueue"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ServerQueue.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/ServerQueue.dir/build: ServerQueue

.PHONY : CMakeFiles/ServerQueue.dir/build

CMakeFiles/ServerQueue.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/ServerQueue.dir/cmake_clean.cmake
.PHONY : CMakeFiles/ServerQueue.dir/clean

CMakeFiles/ServerQueue.dir/depend:
	cd /home/lerakry/tp/program_c++/ServerQueue/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/lerakry/tp/program_c++/ServerQueue /home/lerakry/tp/program_c++/ServerQueue /home/lerakry/tp/program_c++/ServerQueue/cmake-build-debug /home/lerakry/tp/program_c++/ServerQueue/cmake-build-debug /home/lerakry/tp/program_c++/ServerQueue/cmake-build-debug/CMakeFiles/ServerQueue.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/ServerQueue.dir/depend
