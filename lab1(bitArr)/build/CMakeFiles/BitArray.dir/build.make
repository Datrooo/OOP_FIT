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
include CMakeFiles/BitArray.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/BitArray.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/BitArray.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/BitArray.dir/flags.make

CMakeFiles/BitArray.dir/bitArray.cpp.o: CMakeFiles/BitArray.dir/flags.make
CMakeFiles/BitArray.dir/bitArray.cpp.o: ../bitArray.cpp
CMakeFiles/BitArray.dir/bitArray.cpp.o: CMakeFiles/BitArray.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/drakowkq/work/OOP_FIT/lab1(bitArr)/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/BitArray.dir/bitArray.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/BitArray.dir/bitArray.cpp.o -MF CMakeFiles/BitArray.dir/bitArray.cpp.o.d -o CMakeFiles/BitArray.dir/bitArray.cpp.o -c "/home/drakowkq/work/OOP_FIT/lab1(bitArr)/bitArray.cpp"

CMakeFiles/BitArray.dir/bitArray.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/BitArray.dir/bitArray.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/drakowkq/work/OOP_FIT/lab1(bitArr)/bitArray.cpp" > CMakeFiles/BitArray.dir/bitArray.cpp.i

CMakeFiles/BitArray.dir/bitArray.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/BitArray.dir/bitArray.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/drakowkq/work/OOP_FIT/lab1(bitArr)/bitArray.cpp" -o CMakeFiles/BitArray.dir/bitArray.cpp.s

CMakeFiles/BitArray.dir/lab1.cpp.o: CMakeFiles/BitArray.dir/flags.make
CMakeFiles/BitArray.dir/lab1.cpp.o: ../lab1.cpp
CMakeFiles/BitArray.dir/lab1.cpp.o: CMakeFiles/BitArray.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/drakowkq/work/OOP_FIT/lab1(bitArr)/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/BitArray.dir/lab1.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/BitArray.dir/lab1.cpp.o -MF CMakeFiles/BitArray.dir/lab1.cpp.o.d -o CMakeFiles/BitArray.dir/lab1.cpp.o -c "/home/drakowkq/work/OOP_FIT/lab1(bitArr)/lab1.cpp"

CMakeFiles/BitArray.dir/lab1.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/BitArray.dir/lab1.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/drakowkq/work/OOP_FIT/lab1(bitArr)/lab1.cpp" > CMakeFiles/BitArray.dir/lab1.cpp.i

CMakeFiles/BitArray.dir/lab1.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/BitArray.dir/lab1.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/drakowkq/work/OOP_FIT/lab1(bitArr)/lab1.cpp" -o CMakeFiles/BitArray.dir/lab1.cpp.s

# Object files for target BitArray
BitArray_OBJECTS = \
"CMakeFiles/BitArray.dir/bitArray.cpp.o" \
"CMakeFiles/BitArray.dir/lab1.cpp.o"

# External object files for target BitArray
BitArray_EXTERNAL_OBJECTS =

BitArray: CMakeFiles/BitArray.dir/bitArray.cpp.o
BitArray: CMakeFiles/BitArray.dir/lab1.cpp.o
BitArray: CMakeFiles/BitArray.dir/build.make
BitArray: CMakeFiles/BitArray.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/home/drakowkq/work/OOP_FIT/lab1(bitArr)/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable BitArray"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/BitArray.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/BitArray.dir/build: BitArray
.PHONY : CMakeFiles/BitArray.dir/build

CMakeFiles/BitArray.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/BitArray.dir/cmake_clean.cmake
.PHONY : CMakeFiles/BitArray.dir/clean

CMakeFiles/BitArray.dir/depend:
	cd "/home/drakowkq/work/OOP_FIT/lab1(bitArr)/build" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/home/drakowkq/work/OOP_FIT/lab1(bitArr)" "/home/drakowkq/work/OOP_FIT/lab1(bitArr)" "/home/drakowkq/work/OOP_FIT/lab1(bitArr)/build" "/home/drakowkq/work/OOP_FIT/lab1(bitArr)/build" "/home/drakowkq/work/OOP_FIT/lab1(bitArr)/build/CMakeFiles/BitArray.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/BitArray.dir/depend

