# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.24

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
CMAKE_COMMAND = "C:/Program Files/CMake/bin/cmake.exe"

# The command to remove a file.
RM = "C:/Program Files/CMake/bin/cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:/Users/mahus/Desktop/Warg/WARG_1B/ZeroPilot-Comp-2023

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:/Users/mahus/Desktop/Warg/WARG_1B/ZeroPilot-Comp-2023/build

# Utility rule file for UPLOAD.

# Include any custom commands dependencies for this target.
include CMakeFiles/UPLOAD.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/UPLOAD.dir/progress.make

CMakeFiles/UPLOAD:
	arm-none-eabi-gdb -iex "target remote tcp:127.0.0.1:3333" -iex "monitor program C:/Users/mahus/Desktop/Warg/WARG_1B/ZeroPilot-Comp-2023/build/ZeroPilot.elf" -iex "monitor reset init" -iex disconnect -iex quit

UPLOAD: CMakeFiles/UPLOAD
UPLOAD: CMakeFiles/UPLOAD.dir/build.make
.PHONY : UPLOAD

# Rule to build all files generated by this target.
CMakeFiles/UPLOAD.dir/build: UPLOAD
.PHONY : CMakeFiles/UPLOAD.dir/build

CMakeFiles/UPLOAD.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/UPLOAD.dir/cmake_clean.cmake
.PHONY : CMakeFiles/UPLOAD.dir/clean

CMakeFiles/UPLOAD.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" C:/Users/mahus/Desktop/Warg/WARG_1B/ZeroPilot-Comp-2023 C:/Users/mahus/Desktop/Warg/WARG_1B/ZeroPilot-Comp-2023 C:/Users/mahus/Desktop/Warg/WARG_1B/ZeroPilot-Comp-2023/build C:/Users/mahus/Desktop/Warg/WARG_1B/ZeroPilot-Comp-2023/build C:/Users/mahus/Desktop/Warg/WARG_1B/ZeroPilot-Comp-2023/build/CMakeFiles/UPLOAD.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/UPLOAD.dir/depend

