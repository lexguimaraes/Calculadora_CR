# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.30

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
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /mnt/c/Users/alexf/CLionProjects/testearqbin

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/c/Users/alexf/CLionProjects/testearqbin/cmake-build-release-wsl

# Include any dependencies generated for this target.
include CMakeFiles/testearqbin.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/testearqbin.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/testearqbin.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/testearqbin.dir/flags.make

CMakeFiles/testearqbin.dir/main.c.o: CMakeFiles/testearqbin.dir/flags.make
CMakeFiles/testearqbin.dir/main.c.o: /mnt/c/Users/alexf/CLionProjects/testearqbin/main.c
CMakeFiles/testearqbin.dir/main.c.o: CMakeFiles/testearqbin.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/mnt/c/Users/alexf/CLionProjects/testearqbin/cmake-build-release-wsl/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/testearqbin.dir/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/testearqbin.dir/main.c.o -MF CMakeFiles/testearqbin.dir/main.c.o.d -o CMakeFiles/testearqbin.dir/main.c.o -c /mnt/c/Users/alexf/CLionProjects/testearqbin/main.c

CMakeFiles/testearqbin.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/testearqbin.dir/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /mnt/c/Users/alexf/CLionProjects/testearqbin/main.c > CMakeFiles/testearqbin.dir/main.c.i

CMakeFiles/testearqbin.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/testearqbin.dir/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /mnt/c/Users/alexf/CLionProjects/testearqbin/main.c -o CMakeFiles/testearqbin.dir/main.c.s

# Object files for target testearqbin
testearqbin_OBJECTS = \
"CMakeFiles/testearqbin.dir/main.c.o"

# External object files for target testearqbin
testearqbin_EXTERNAL_OBJECTS =

testearqbin: CMakeFiles/testearqbin.dir/main.c.o
testearqbin: CMakeFiles/testearqbin.dir/build.make
testearqbin: CMakeFiles/testearqbin.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/mnt/c/Users/alexf/CLionProjects/testearqbin/cmake-build-release-wsl/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable testearqbin"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/testearqbin.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/testearqbin.dir/build: testearqbin
.PHONY : CMakeFiles/testearqbin.dir/build

CMakeFiles/testearqbin.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/testearqbin.dir/cmake_clean.cmake
.PHONY : CMakeFiles/testearqbin.dir/clean

CMakeFiles/testearqbin.dir/depend:
	cd /mnt/c/Users/alexf/CLionProjects/testearqbin/cmake-build-release-wsl && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/c/Users/alexf/CLionProjects/testearqbin /mnt/c/Users/alexf/CLionProjects/testearqbin /mnt/c/Users/alexf/CLionProjects/testearqbin/cmake-build-release-wsl /mnt/c/Users/alexf/CLionProjects/testearqbin/cmake-build-release-wsl /mnt/c/Users/alexf/CLionProjects/testearqbin/cmake-build-release-wsl/CMakeFiles/testearqbin.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/testearqbin.dir/depend

