# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.25

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
CMAKE_SOURCE_DIR = /workspace/Generadores

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /workspace/Generadores/build-Generadores-Desktop-Debug

# Utility rule file for test_debug_autogen.

# Include any custom commands dependencies for this target.
include lib/log-saes/example/CMakeFiles/test_debug_autogen.dir/compiler_depend.make

# Include the progress variables for this target.
include lib/log-saes/example/CMakeFiles/test_debug_autogen.dir/progress.make

lib/log-saes/example/CMakeFiles/test_debug_autogen:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/workspace/Generadores/build-Generadores-Desktop-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Automatic MOC and UIC for target test_debug"
	cd /workspace/Generadores/build-Generadores-Desktop-Debug/lib/log-saes/example && /usr/bin/cmake -E cmake_autogen /workspace/Generadores/build-Generadores-Desktop-Debug/lib/log-saes/example/CMakeFiles/test_debug_autogen.dir/AutogenInfo.json Debug

test_debug_autogen: lib/log-saes/example/CMakeFiles/test_debug_autogen
test_debug_autogen: lib/log-saes/example/CMakeFiles/test_debug_autogen.dir/build.make
.PHONY : test_debug_autogen

# Rule to build all files generated by this target.
lib/log-saes/example/CMakeFiles/test_debug_autogen.dir/build: test_debug_autogen
.PHONY : lib/log-saes/example/CMakeFiles/test_debug_autogen.dir/build

lib/log-saes/example/CMakeFiles/test_debug_autogen.dir/clean:
	cd /workspace/Generadores/build-Generadores-Desktop-Debug/lib/log-saes/example && $(CMAKE_COMMAND) -P CMakeFiles/test_debug_autogen.dir/cmake_clean.cmake
.PHONY : lib/log-saes/example/CMakeFiles/test_debug_autogen.dir/clean

lib/log-saes/example/CMakeFiles/test_debug_autogen.dir/depend:
	cd /workspace/Generadores/build-Generadores-Desktop-Debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /workspace/Generadores /workspace/Generadores/lib/log-saes/example /workspace/Generadores/build-Generadores-Desktop-Debug /workspace/Generadores/build-Generadores-Desktop-Debug/lib/log-saes/example /workspace/Generadores/build-Generadores-Desktop-Debug/lib/log-saes/example/CMakeFiles/test_debug_autogen.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : lib/log-saes/example/CMakeFiles/test_debug_autogen.dir/depend

