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
CMAKE_SOURCE_DIR = /mnt/c/Users/sunwenli/Documents/GitHub/ChatTogether/server

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/c/Users/sunwenli/Documents/GitHub/ChatTogether/server/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/server.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/server.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/server.dir/flags.make

CMakeFiles/server.dir/main.c.o: CMakeFiles/server.dir/flags.make
CMakeFiles/server.dir/main.c.o: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/sunwenli/Documents/GitHub/ChatTogether/server/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/server.dir/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/server.dir/main.c.o   -c /mnt/c/Users/sunwenli/Documents/GitHub/ChatTogether/server/main.c

CMakeFiles/server.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/server.dir/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /mnt/c/Users/sunwenli/Documents/GitHub/ChatTogether/server/main.c > CMakeFiles/server.dir/main.c.i

CMakeFiles/server.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/server.dir/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /mnt/c/Users/sunwenli/Documents/GitHub/ChatTogether/server/main.c -o CMakeFiles/server.dir/main.c.s

CMakeFiles/server.dir/user.c.o: CMakeFiles/server.dir/flags.make
CMakeFiles/server.dir/user.c.o: ../user.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/sunwenli/Documents/GitHub/ChatTogether/server/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/server.dir/user.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/server.dir/user.c.o   -c /mnt/c/Users/sunwenli/Documents/GitHub/ChatTogether/server/user.c

CMakeFiles/server.dir/user.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/server.dir/user.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /mnt/c/Users/sunwenli/Documents/GitHub/ChatTogether/server/user.c > CMakeFiles/server.dir/user.c.i

CMakeFiles/server.dir/user.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/server.dir/user.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /mnt/c/Users/sunwenli/Documents/GitHub/ChatTogether/server/user.c -o CMakeFiles/server.dir/user.c.s

CMakeFiles/server.dir/client.c.o: CMakeFiles/server.dir/flags.make
CMakeFiles/server.dir/client.c.o: ../client.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/sunwenli/Documents/GitHub/ChatTogether/server/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/server.dir/client.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/server.dir/client.c.o   -c /mnt/c/Users/sunwenli/Documents/GitHub/ChatTogether/server/client.c

CMakeFiles/server.dir/client.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/server.dir/client.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /mnt/c/Users/sunwenli/Documents/GitHub/ChatTogether/server/client.c > CMakeFiles/server.dir/client.c.i

CMakeFiles/server.dir/client.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/server.dir/client.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /mnt/c/Users/sunwenli/Documents/GitHub/ChatTogether/server/client.c -o CMakeFiles/server.dir/client.c.s

# Object files for target server
server_OBJECTS = \
"CMakeFiles/server.dir/main.c.o" \
"CMakeFiles/server.dir/user.c.o" \
"CMakeFiles/server.dir/client.c.o"

# External object files for target server
server_EXTERNAL_OBJECTS =

server: CMakeFiles/server.dir/main.c.o
server: CMakeFiles/server.dir/user.c.o
server: CMakeFiles/server.dir/client.c.o
server: CMakeFiles/server.dir/build.make
server: CMakeFiles/server.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/mnt/c/Users/sunwenli/Documents/GitHub/ChatTogether/server/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking C executable server"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/server.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/server.dir/build: server

.PHONY : CMakeFiles/server.dir/build

CMakeFiles/server.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/server.dir/cmake_clean.cmake
.PHONY : CMakeFiles/server.dir/clean

CMakeFiles/server.dir/depend:
	cd /mnt/c/Users/sunwenli/Documents/GitHub/ChatTogether/server/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/c/Users/sunwenli/Documents/GitHub/ChatTogether/server /mnt/c/Users/sunwenli/Documents/GitHub/ChatTogether/server /mnt/c/Users/sunwenli/Documents/GitHub/ChatTogether/server/cmake-build-debug /mnt/c/Users/sunwenli/Documents/GitHub/ChatTogether/server/cmake-build-debug /mnt/c/Users/sunwenli/Documents/GitHub/ChatTogether/server/cmake-build-debug/CMakeFiles/server.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/server.dir/depend

