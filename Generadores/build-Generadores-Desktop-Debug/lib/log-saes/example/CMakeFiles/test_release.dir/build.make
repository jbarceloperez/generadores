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

# Include any dependencies generated for this target.
include lib/log-saes/example/CMakeFiles/test_release.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include lib/log-saes/example/CMakeFiles/test_release.dir/compiler_depend.make

# Include the progress variables for this target.
include lib/log-saes/example/CMakeFiles/test_release.dir/progress.make

# Include the compile flags for this target's objects.
include lib/log-saes/example/CMakeFiles/test_release.dir/flags.make

lib/log-saes/example/CMakeFiles/test_release.dir/test_release_autogen/mocs_compilation.cpp.o: lib/log-saes/example/CMakeFiles/test_release.dir/flags.make
lib/log-saes/example/CMakeFiles/test_release.dir/test_release_autogen/mocs_compilation.cpp.o: lib/log-saes/example/test_release_autogen/mocs_compilation.cpp
lib/log-saes/example/CMakeFiles/test_release.dir/test_release_autogen/mocs_compilation.cpp.o: lib/log-saes/example/CMakeFiles/test_release.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/workspace/Generadores/build-Generadores-Desktop-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object lib/log-saes/example/CMakeFiles/test_release.dir/test_release_autogen/mocs_compilation.cpp.o"
	cd /workspace/Generadores/build-Generadores-Desktop-Debug/lib/log-saes/example && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT lib/log-saes/example/CMakeFiles/test_release.dir/test_release_autogen/mocs_compilation.cpp.o -MF CMakeFiles/test_release.dir/test_release_autogen/mocs_compilation.cpp.o.d -o CMakeFiles/test_release.dir/test_release_autogen/mocs_compilation.cpp.o -c /workspace/Generadores/build-Generadores-Desktop-Debug/lib/log-saes/example/test_release_autogen/mocs_compilation.cpp

lib/log-saes/example/CMakeFiles/test_release.dir/test_release_autogen/mocs_compilation.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test_release.dir/test_release_autogen/mocs_compilation.cpp.i"
	cd /workspace/Generadores/build-Generadores-Desktop-Debug/lib/log-saes/example && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /workspace/Generadores/build-Generadores-Desktop-Debug/lib/log-saes/example/test_release_autogen/mocs_compilation.cpp > CMakeFiles/test_release.dir/test_release_autogen/mocs_compilation.cpp.i

lib/log-saes/example/CMakeFiles/test_release.dir/test_release_autogen/mocs_compilation.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test_release.dir/test_release_autogen/mocs_compilation.cpp.s"
	cd /workspace/Generadores/build-Generadores-Desktop-Debug/lib/log-saes/example && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /workspace/Generadores/build-Generadores-Desktop-Debug/lib/log-saes/example/test_release_autogen/mocs_compilation.cpp -o CMakeFiles/test_release.dir/test_release_autogen/mocs_compilation.cpp.s

lib/log-saes/example/CMakeFiles/test_release.dir/test_log.cpp.o: lib/log-saes/example/CMakeFiles/test_release.dir/flags.make
lib/log-saes/example/CMakeFiles/test_release.dir/test_log.cpp.o: /workspace/Generadores/lib/log-saes/example/test_log.cpp
lib/log-saes/example/CMakeFiles/test_release.dir/test_log.cpp.o: lib/log-saes/example/CMakeFiles/test_release.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/workspace/Generadores/build-Generadores-Desktop-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object lib/log-saes/example/CMakeFiles/test_release.dir/test_log.cpp.o"
	cd /workspace/Generadores/build-Generadores-Desktop-Debug/lib/log-saes/example && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT lib/log-saes/example/CMakeFiles/test_release.dir/test_log.cpp.o -MF CMakeFiles/test_release.dir/test_log.cpp.o.d -o CMakeFiles/test_release.dir/test_log.cpp.o -c /workspace/Generadores/lib/log-saes/example/test_log.cpp

lib/log-saes/example/CMakeFiles/test_release.dir/test_log.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test_release.dir/test_log.cpp.i"
	cd /workspace/Generadores/build-Generadores-Desktop-Debug/lib/log-saes/example && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /workspace/Generadores/lib/log-saes/example/test_log.cpp > CMakeFiles/test_release.dir/test_log.cpp.i

lib/log-saes/example/CMakeFiles/test_release.dir/test_log.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test_release.dir/test_log.cpp.s"
	cd /workspace/Generadores/build-Generadores-Desktop-Debug/lib/log-saes/example && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /workspace/Generadores/lib/log-saes/example/test_log.cpp -o CMakeFiles/test_release.dir/test_log.cpp.s

# Object files for target test_release
test_release_OBJECTS = \
"CMakeFiles/test_release.dir/test_release_autogen/mocs_compilation.cpp.o" \
"CMakeFiles/test_release.dir/test_log.cpp.o"

# External object files for target test_release
test_release_EXTERNAL_OBJECTS =

lib/log-saes/example/test_release: lib/log-saes/example/CMakeFiles/test_release.dir/test_release_autogen/mocs_compilation.cpp.o
lib/log-saes/example/test_release: lib/log-saes/example/CMakeFiles/test_release.dir/test_log.cpp.o
lib/log-saes/example/test_release: lib/log-saes/example/CMakeFiles/test_release.dir/build.make
lib/log-saes/example/test_release: lib/log-saes/example/CMakeFiles/test_release.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/workspace/Generadores/build-Generadores-Desktop-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable test_release"
	cd /workspace/Generadores/build-Generadores-Desktop-Debug/lib/log-saes/example && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test_release.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
lib/log-saes/example/CMakeFiles/test_release.dir/build: lib/log-saes/example/test_release
.PHONY : lib/log-saes/example/CMakeFiles/test_release.dir/build

lib/log-saes/example/CMakeFiles/test_release.dir/clean:
	cd /workspace/Generadores/build-Generadores-Desktop-Debug/lib/log-saes/example && $(CMAKE_COMMAND) -P CMakeFiles/test_release.dir/cmake_clean.cmake
.PHONY : lib/log-saes/example/CMakeFiles/test_release.dir/clean

lib/log-saes/example/CMakeFiles/test_release.dir/depend:
	cd /workspace/Generadores/build-Generadores-Desktop-Debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /workspace/Generadores /workspace/Generadores/lib/log-saes/example /workspace/Generadores/build-Generadores-Desktop-Debug /workspace/Generadores/build-Generadores-Desktop-Debug/lib/log-saes/example /workspace/Generadores/build-Generadores-Desktop-Debug/lib/log-saes/example/CMakeFiles/test_release.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : lib/log-saes/example/CMakeFiles/test_release.dir/depend

