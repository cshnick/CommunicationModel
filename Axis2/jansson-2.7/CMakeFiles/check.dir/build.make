# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

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
CMAKE_SOURCE_DIR = /home/veret/Projects/NSConsole/nc-ui-prototype/Axis2/jansson-2.7

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/veret/Projects/NSConsole/nc-ui-prototype/Axis2/jansson-2.7

# Utility rule file for check.

# Include the progress variables for this target.
include CMakeFiles/check.dir/progress.make

CMakeFiles/check: bin/json_process
CMakeFiles/check: bin/test_array
CMakeFiles/check: bin/test_copy
CMakeFiles/check: bin/test_dump
CMakeFiles/check: bin/test_dump_callback
CMakeFiles/check: bin/test_equal
CMakeFiles/check: bin/test_load
CMakeFiles/check: bin/test_loadb
CMakeFiles/check: bin/test_number
CMakeFiles/check: bin/test_object
CMakeFiles/check: bin/test_pack
CMakeFiles/check: bin/test_simple
CMakeFiles/check: bin/test_unpack
CMakeFiles/check: bin/test_memory_funcs
	/usr/bin/ctest

check: CMakeFiles/check
check: CMakeFiles/check.dir/build.make
.PHONY : check

# Rule to build all files generated by this target.
CMakeFiles/check.dir/build: check
.PHONY : CMakeFiles/check.dir/build

CMakeFiles/check.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/check.dir/cmake_clean.cmake
.PHONY : CMakeFiles/check.dir/clean

CMakeFiles/check.dir/depend:
	cd /home/veret/Projects/NSConsole/nc-ui-prototype/Axis2/jansson-2.7 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/veret/Projects/NSConsole/nc-ui-prototype/Axis2/jansson-2.7 /home/veret/Projects/NSConsole/nc-ui-prototype/Axis2/jansson-2.7 /home/veret/Projects/NSConsole/nc-ui-prototype/Axis2/jansson-2.7 /home/veret/Projects/NSConsole/nc-ui-prototype/Axis2/jansson-2.7 /home/veret/Projects/NSConsole/nc-ui-prototype/Axis2/jansson-2.7/CMakeFiles/check.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/check.dir/depend

