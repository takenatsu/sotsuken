# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

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
CMAKE_SOURCE_DIR = /home/natsuki/sotsuken/src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/natsuki/sotsuken/build

# Include any dependencies generated for this target.
include roomba_500_series-master/CMakeFiles/go_dock.dir/depend.make

# Include the progress variables for this target.
include roomba_500_series-master/CMakeFiles/go_dock.dir/progress.make

# Include the compile flags for this target's objects.
include roomba_500_series-master/CMakeFiles/go_dock.dir/flags.make

roomba_500_series-master/CMakeFiles/go_dock.dir/src/GoDock/GoDock.o: roomba_500_series-master/CMakeFiles/go_dock.dir/flags.make
roomba_500_series-master/CMakeFiles/go_dock.dir/src/GoDock/GoDock.o: /home/natsuki/sotsuken/src/roomba_500_series-master/src/GoDock/GoDock.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/natsuki/sotsuken/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object roomba_500_series-master/CMakeFiles/go_dock.dir/src/GoDock/GoDock.o"
	cd /home/natsuki/sotsuken/build/roomba_500_series-master && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/go_dock.dir/src/GoDock/GoDock.o -c /home/natsuki/sotsuken/src/roomba_500_series-master/src/GoDock/GoDock.cpp

roomba_500_series-master/CMakeFiles/go_dock.dir/src/GoDock/GoDock.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/go_dock.dir/src/GoDock/GoDock.i"
	cd /home/natsuki/sotsuken/build/roomba_500_series-master && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/natsuki/sotsuken/src/roomba_500_series-master/src/GoDock/GoDock.cpp > CMakeFiles/go_dock.dir/src/GoDock/GoDock.i

roomba_500_series-master/CMakeFiles/go_dock.dir/src/GoDock/GoDock.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/go_dock.dir/src/GoDock/GoDock.s"
	cd /home/natsuki/sotsuken/build/roomba_500_series-master && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/natsuki/sotsuken/src/roomba_500_series-master/src/GoDock/GoDock.cpp -o CMakeFiles/go_dock.dir/src/GoDock/GoDock.s

roomba_500_series-master/CMakeFiles/go_dock.dir/src/GoDock/GoDock.o.requires:

.PHONY : roomba_500_series-master/CMakeFiles/go_dock.dir/src/GoDock/GoDock.o.requires

roomba_500_series-master/CMakeFiles/go_dock.dir/src/GoDock/GoDock.o.provides: roomba_500_series-master/CMakeFiles/go_dock.dir/src/GoDock/GoDock.o.requires
	$(MAKE) -f roomba_500_series-master/CMakeFiles/go_dock.dir/build.make roomba_500_series-master/CMakeFiles/go_dock.dir/src/GoDock/GoDock.o.provides.build
.PHONY : roomba_500_series-master/CMakeFiles/go_dock.dir/src/GoDock/GoDock.o.provides

roomba_500_series-master/CMakeFiles/go_dock.dir/src/GoDock/GoDock.o.provides.build: roomba_500_series-master/CMakeFiles/go_dock.dir/src/GoDock/GoDock.o


# Object files for target go_dock
go_dock_OBJECTS = \
"CMakeFiles/go_dock.dir/src/GoDock/GoDock.o"

# External object files for target go_dock
go_dock_EXTERNAL_OBJECTS =

/home/natsuki/sotsuken/devel/lib/libgo_dock.so: roomba_500_series-master/CMakeFiles/go_dock.dir/src/GoDock/GoDock.o
/home/natsuki/sotsuken/devel/lib/libgo_dock.so: roomba_500_series-master/CMakeFiles/go_dock.dir/build.make
/home/natsuki/sotsuken/devel/lib/libgo_dock.so: roomba_500_series-master/CMakeFiles/go_dock.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/natsuki/sotsuken/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX shared library /home/natsuki/sotsuken/devel/lib/libgo_dock.so"
	cd /home/natsuki/sotsuken/build/roomba_500_series-master && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/go_dock.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
roomba_500_series-master/CMakeFiles/go_dock.dir/build: /home/natsuki/sotsuken/devel/lib/libgo_dock.so

.PHONY : roomba_500_series-master/CMakeFiles/go_dock.dir/build

roomba_500_series-master/CMakeFiles/go_dock.dir/requires: roomba_500_series-master/CMakeFiles/go_dock.dir/src/GoDock/GoDock.o.requires

.PHONY : roomba_500_series-master/CMakeFiles/go_dock.dir/requires

roomba_500_series-master/CMakeFiles/go_dock.dir/clean:
	cd /home/natsuki/sotsuken/build/roomba_500_series-master && $(CMAKE_COMMAND) -P CMakeFiles/go_dock.dir/cmake_clean.cmake
.PHONY : roomba_500_series-master/CMakeFiles/go_dock.dir/clean

roomba_500_series-master/CMakeFiles/go_dock.dir/depend:
	cd /home/natsuki/sotsuken/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/natsuki/sotsuken/src /home/natsuki/sotsuken/src/roomba_500_series-master /home/natsuki/sotsuken/build /home/natsuki/sotsuken/build/roomba_500_series-master /home/natsuki/sotsuken/build/roomba_500_series-master/CMakeFiles/go_dock.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : roomba_500_series-master/CMakeFiles/go_dock.dir/depend
