# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/lerakrya/nosql/noskool/ServerUsers

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/lerakrya/nosql/noskool/ServerUsers

# Include any dependencies generated for this target.
include CMakeFiles/test_db.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/test_db.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/test_db.dir/flags.make

CMakeFiles/test_db.dir/test_db.cpp.o: CMakeFiles/test_db.dir/flags.make
CMakeFiles/test_db.dir/test_db.cpp.o: test_db.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lerakrya/nosql/noskool/ServerUsers/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/test_db.dir/test_db.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/test_db.dir/test_db.cpp.o -c /home/lerakrya/nosql/noskool/ServerUsers/test_db.cpp

CMakeFiles/test_db.dir/test_db.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test_db.dir/test_db.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/lerakrya/nosql/noskool/ServerUsers/test_db.cpp > CMakeFiles/test_db.dir/test_db.cpp.i

CMakeFiles/test_db.dir/test_db.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test_db.dir/test_db.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/lerakrya/nosql/noskool/ServerUsers/test_db.cpp -o CMakeFiles/test_db.dir/test_db.cpp.s

# Object files for target test_db
test_db_OBJECTS = \
"CMakeFiles/test_db.dir/test_db.cpp.o"

# External object files for target test_db
test_db_EXTERNAL_OBJECTS =

test_db: CMakeFiles/test_db.dir/test_db.cpp.o
test_db: CMakeFiles/test_db.dir/build.make
test_db: libServerUsers.a
test_db: /usr/lib/x86_64-linux-gnu/libpqxx.so
test_db: /usr/lib/x86_64-linux-gnu/libpq.so
test_db: /usr/lib/x86_64-linux-gnu/libboost_system.so.1.71.0
test_db: /usr/lib/x86_64-linux-gnu/libboost_log.so.1.71.0
test_db: /usr/lib/x86_64-linux-gnu/libboost_thread.so.1.71.0
test_db: /usr/lib/x86_64-linux-gnu/libboost_regex.so.1.71.0
test_db: /usr/lib/x86_64-linux-gnu/libboost_atomic.so.1.71.0
test_db: /usr/lib/x86_64-linux-gnu/libboost_chrono.so.1.71.0
test_db: /usr/lib/x86_64-linux-gnu/libboost_date_time.so.1.71.0
test_db: /usr/lib/x86_64-linux-gnu/libboost_filesystem.so.1.71.0
test_db: CMakeFiles/test_db.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/lerakrya/nosql/noskool/ServerUsers/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable test_db"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test_db.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/test_db.dir/build: test_db

.PHONY : CMakeFiles/test_db.dir/build

CMakeFiles/test_db.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/test_db.dir/cmake_clean.cmake
.PHONY : CMakeFiles/test_db.dir/clean

CMakeFiles/test_db.dir/depend:
	cd /home/lerakrya/nosql/noskool/ServerUsers && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/lerakrya/nosql/noskool/ServerUsers /home/lerakrya/nosql/noskool/ServerUsers /home/lerakrya/nosql/noskool/ServerUsers /home/lerakrya/nosql/noskool/ServerUsers /home/lerakrya/nosql/noskool/ServerUsers/CMakeFiles/test_db.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/test_db.dir/depend

