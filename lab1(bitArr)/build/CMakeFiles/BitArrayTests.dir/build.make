# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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

#Suppress display of executed commands.
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
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/home/drakowkq/work/OOP_FIT/lab1(bitArr)"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/home/drakowkq/work/OOP_FIT/lab1(bitArr)/build"

# Include any dependencies generated for this target.
include CMakeFiles/BitArrayTests.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/BitArrayTests.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/BitArrayTests.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/BitArrayTests.dir/flags.make

CMakeFiles/BitArrayTests.dir/lab1_tests.cpp.o: CMakeFiles/BitArrayTests.dir/flags.make
CMakeFiles/BitArrayTests.dir/lab1_tests.cpp.o: ../lab1_tests.cpp
CMakeFiles/BitArrayTests.dir/lab1_tests.cpp.o: CMakeFiles/BitArrayTests.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/drakowkq/work/OOP_FIT/lab1(bitArr)/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/BitArrayTests.dir/lab1_tests.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/BitArrayTests.dir/lab1_tests.cpp.o -MF CMakeFiles/BitArrayTests.dir/lab1_tests.cpp.o.d -o CMakeFiles/BitArrayTests.dir/lab1_tests.cpp.o -c "/home/drakowkq/work/OOP_FIT/lab1(bitArr)/lab1_tests.cpp"

CMakeFiles/BitArrayTests.dir/lab1_tests.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/BitArrayTests.dir/lab1_tests.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/drakowkq/work/OOP_FIT/lab1(bitArr)/lab1_tests.cpp" > CMakeFiles/BitArrayTests.dir/lab1_tests.cpp.i

CMakeFiles/BitArrayTests.dir/lab1_tests.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/BitArrayTests.dir/lab1_tests.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/drakowkq/work/OOP_FIT/lab1(bitArr)/lab1_tests.cpp" -o CMakeFiles/BitArrayTests.dir/lab1_tests.cpp.s

CMakeFiles/BitArrayTests.dir/bitArray.cpp.o: CMakeFiles/BitArrayTests.dir/flags.make
CMakeFiles/BitArrayTests.dir/bitArray.cpp.o: ../bitArray.cpp
CMakeFiles/BitArrayTests.dir/bitArray.cpp.o: CMakeFiles/BitArrayTests.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/drakowkq/work/OOP_FIT/lab1(bitArr)/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/BitArrayTests.dir/bitArray.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/BitArrayTests.dir/bitArray.cpp.o -MF CMakeFiles/BitArrayTests.dir/bitArray.cpp.o.d -o CMakeFiles/BitArrayTests.dir/bitArray.cpp.o -c "/home/drakowkq/work/OOP_FIT/lab1(bitArr)/bitArray.cpp"

CMakeFiles/BitArrayTests.dir/bitArray.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/BitArrayTests.dir/bitArray.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/drakowkq/work/OOP_FIT/lab1(bitArr)/bitArray.cpp" > CMakeFiles/BitArrayTests.dir/bitArray.cpp.i

CMakeFiles/BitArrayTests.dir/bitArray.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/BitArrayTests.dir/bitArray.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/drakowkq/work/OOP_FIT/lab1(bitArr)/bitArray.cpp" -o CMakeFiles/BitArrayTests.dir/bitArray.cpp.s

# Object files for target BitArrayTests
BitArrayTests_OBJECTS = \
"CMakeFiles/BitArrayTests.dir/lab1_tests.cpp.o" \
"CMakeFiles/BitArrayTests.dir/bitArray.cpp.o"

# External object files for target BitArrayTests
BitArrayTests_EXTERNAL_OBJECTS =

BitArrayTests: CMakeFiles/BitArrayTests.dir/lab1_tests.cpp.o
BitArrayTests: CMakeFiles/BitArrayTests.dir/bitArray.cpp.o
BitArrayTests: CMakeFiles/BitArrayTests.dir/build.make
BitArrayTests: /usr/lib/x86_64-linux-gnu/libgtest.a
BitArrayTests: CMakeFiles/BitArrayTests.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/home/drakowkq/work/OOP_FIT/lab1(bitArr)/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable BitArrayTests"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/BitArrayTests.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/BitArrayTests.dir/build: BitArrayTests
.PHONY : CMakeFiles/BitArrayTests.dir/build

CMakeFiles/BitArrayTests.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/BitArrayTests.dir/cmake_clean.cmake
.PHONY : CMakeFiles/BitArrayTests.dir/clean

CMakeFiles/BitArrayTests.dir/depend:
	cd "/home/drakowkq/work/OOP_FIT/lab1(bitArr)/build" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/home/drakowkq/work/OOP_FIT/lab1(bitArr)" "/home/drakowkq/work/OOP_FIT/lab1(bitArr)" "/home/drakowkq/work/OOP_FIT/lab1(bitArr)/build" "/home/drakowkq/work/OOP_FIT/lab1(bitArr)/build" "/home/drakowkq/work/OOP_FIT/lab1(bitArr)/build/CMakeFiles/BitArrayTests.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/BitArrayTests.dir/depend

