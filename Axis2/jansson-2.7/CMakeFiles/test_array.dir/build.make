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

# Include any dependencies generated for this target.
include CMakeFiles/test_array.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/test_array.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/test_array.dir/flags.make

CMakeFiles/test_array.dir/test/suites/api/test_array.c.o: CMakeFiles/test_array.dir/flags.make
CMakeFiles/test_array.dir/test/suites/api/test_array.c.o: test/suites/api/test_array.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/veret/Projects/NSConsole/nc-ui-prototype/Axis2/jansson-2.7/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object CMakeFiles/test_array.dir/test/suites/api/test_array.c.o"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/test_array.dir/test/suites/api/test_array.c.o   -c /home/veret/Projects/NSConsole/nc-ui-prototype/Axis2/jansson-2.7/test/suites/api/test_array.c

CMakeFiles/test_array.dir/test/suites/api/test_array.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/test_array.dir/test/suites/api/test_array.c.i"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -E /home/veret/Projects/NSConsole/nc-ui-prototype/Axis2/jansson-2.7/test/suites/api/test_array.c > CMakeFiles/test_array.dir/test/suites/api/test_array.c.i

CMakeFiles/test_array.dir/test/suites/api/test_array.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/test_array.dir/test/suites/api/test_array.c.s"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -S /home/veret/Projects/NSConsole/nc-ui-prototype/Axis2/jansson-2.7/test/suites/api/test_array.c -o CMakeFiles/test_array.dir/test/suites/api/test_array.c.s

CMakeFiles/test_array.dir/test/suites/api/test_array.c.o.requires:
.PHONY : CMakeFiles/test_array.dir/test/suites/api/test_array.c.o.requires

CMakeFiles/test_array.dir/test/suites/api/test_array.c.o.provides: CMakeFiles/test_array.dir/test/suites/api/test_array.c.o.requires
	$(MAKE) -f CMakeFiles/test_array.dir/build.make CMakeFiles/test_array.dir/test/suites/api/test_array.c.o.provides.build
.PHONY : CMakeFiles/test_array.dir/test/suites/api/test_array.c.o.provides

CMakeFiles/test_array.dir/test/suites/api/test_array.c.o.provides.build: CMakeFiles/test_array.dir/test/suites/api/test_array.c.o

# Object files for target test_array
test_array_OBJECTS = \
"CMakeFiles/test_array.dir/test/suites/api/test_array.c.o"

# External object files for target test_array
test_array_EXTERNAL_OBJECTS =

bin/test_array: CMakeFiles/test_array.dir/test/suites/api/test_array.c.o
bin/test_array: CMakeFiles/test_array.dir/build.make
bin/test_array: lib/libjansson.a
bin/test_array: CMakeFiles/test_array.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking C executable bin/test_array"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test_array.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/test_array.dir/build: bin/test_array
.PHONY : CMakeFiles/test_array.dir/build

CMakeFiles/test_array.dir/requires: CMakeFiles/test_array.dir/test/suites/api/test_array.c.o.requires
.PHONY : CMakeFiles/test_array.dir/requires

CMakeFiles/test_array.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/test_array.dir/cmake_clean.cmake
.PHONY : CMakeFiles/test_array.dir/clean

CMakeFiles/test_array.dir/depend:
	cd /home/veret/Projects/NSConsole/nc-ui-prototype/Axis2/jansson-2.7 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/veret/Projects/NSConsole/nc-ui-prototype/Axis2/jansson-2.7 /home/veret/Projects/NSConsole/nc-ui-prototype/Axis2/jansson-2.7 /home/veret/Projects/NSConsole/nc-ui-prototype/Axis2/jansson-2.7 /home/veret/Projects/NSConsole/nc-ui-prototype/Axis2/jansson-2.7 /home/veret/Projects/NSConsole/nc-ui-prototype/Axis2/jansson-2.7/CMakeFiles/test_array.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/test_array.dir/depend

