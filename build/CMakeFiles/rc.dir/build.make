# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.28

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
CMAKE_SOURCE_DIR = /mnt/c/Users/param/Param/Programming/C++/rime

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/c/Users/param/Param/Programming/C++/rime/build

# Include any dependencies generated for this target.
include CMakeFiles/rc.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/rc.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/rc.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/rc.dir/flags.make

parser.c: /mnt/c/Users/param/Param/Programming/C++/rime/src/rime/parser.y
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --blue --bold --progress-dir=/mnt/c/Users/param/Param/Programming/C++/rime/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "[BISON][parser] Building parser with bison 3.8.2"
	cd /mnt/c/Users/param/Param/Programming/C++/rime && /usr/bin/bison --defines=/mnt/c/Users/param/Param/Programming/C++/rime/build/parser.h -o /mnt/c/Users/param/Param/Programming/C++/rime/build/parser.c src/rime/parser.y

parser.h: parser.c
	@$(CMAKE_COMMAND) -E touch_nocreate parser.h

lexer.yy.c: /mnt/c/Users/param/Param/Programming/C++/rime/src/rime/lexer.l
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --blue --bold --progress-dir=/mnt/c/Users/param/Param/Programming/C++/rime/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "[FLEX][lexer] Building scanner with flex 2.6.4"
	cd /mnt/c/Users/param/Param/Programming/C++/rime && /usr/bin/flex -o/mnt/c/Users/param/Param/Programming/C++/rime/build/lexer.yy.c src/rime/lexer.l

CMakeFiles/rc.dir/parser.c.o: CMakeFiles/rc.dir/flags.make
CMakeFiles/rc.dir/parser.c.o: parser.c
CMakeFiles/rc.dir/parser.c.o: CMakeFiles/rc.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/mnt/c/Users/param/Param/Programming/C++/rime/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/rc.dir/parser.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/rc.dir/parser.c.o -MF CMakeFiles/rc.dir/parser.c.o.d -o CMakeFiles/rc.dir/parser.c.o -c /mnt/c/Users/param/Param/Programming/C++/rime/build/parser.c

CMakeFiles/rc.dir/parser.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/rc.dir/parser.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /mnt/c/Users/param/Param/Programming/C++/rime/build/parser.c > CMakeFiles/rc.dir/parser.c.i

CMakeFiles/rc.dir/parser.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/rc.dir/parser.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /mnt/c/Users/param/Param/Programming/C++/rime/build/parser.c -o CMakeFiles/rc.dir/parser.c.s

CMakeFiles/rc.dir/lexer.yy.c.o: CMakeFiles/rc.dir/flags.make
CMakeFiles/rc.dir/lexer.yy.c.o: lexer.yy.c
CMakeFiles/rc.dir/lexer.yy.c.o: parser.h
CMakeFiles/rc.dir/lexer.yy.c.o: CMakeFiles/rc.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/mnt/c/Users/param/Param/Programming/C++/rime/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/rc.dir/lexer.yy.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/rc.dir/lexer.yy.c.o -MF CMakeFiles/rc.dir/lexer.yy.c.o.d -o CMakeFiles/rc.dir/lexer.yy.c.o -c /mnt/c/Users/param/Param/Programming/C++/rime/build/lexer.yy.c

CMakeFiles/rc.dir/lexer.yy.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/rc.dir/lexer.yy.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /mnt/c/Users/param/Param/Programming/C++/rime/build/lexer.yy.c > CMakeFiles/rc.dir/lexer.yy.c.i

CMakeFiles/rc.dir/lexer.yy.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/rc.dir/lexer.yy.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /mnt/c/Users/param/Param/Programming/C++/rime/build/lexer.yy.c -o CMakeFiles/rc.dir/lexer.yy.c.s

CMakeFiles/rc.dir/src/rime/assembler.cpp.o: CMakeFiles/rc.dir/flags.make
CMakeFiles/rc.dir/src/rime/assembler.cpp.o: /mnt/c/Users/param/Param/Programming/C++/rime/src/rime/assembler.cpp
CMakeFiles/rc.dir/src/rime/assembler.cpp.o: CMakeFiles/rc.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/mnt/c/Users/param/Param/Programming/C++/rime/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/rc.dir/src/rime/assembler.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/rc.dir/src/rime/assembler.cpp.o -MF CMakeFiles/rc.dir/src/rime/assembler.cpp.o.d -o CMakeFiles/rc.dir/src/rime/assembler.cpp.o -c /mnt/c/Users/param/Param/Programming/C++/rime/src/rime/assembler.cpp

CMakeFiles/rc.dir/src/rime/assembler.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/rc.dir/src/rime/assembler.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/Users/param/Param/Programming/C++/rime/src/rime/assembler.cpp > CMakeFiles/rc.dir/src/rime/assembler.cpp.i

CMakeFiles/rc.dir/src/rime/assembler.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/rc.dir/src/rime/assembler.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/Users/param/Param/Programming/C++/rime/src/rime/assembler.cpp -o CMakeFiles/rc.dir/src/rime/assembler.cpp.s

CMakeFiles/rc.dir/src/rime/main.cpp.o: CMakeFiles/rc.dir/flags.make
CMakeFiles/rc.dir/src/rime/main.cpp.o: /mnt/c/Users/param/Param/Programming/C++/rime/src/rime/main.cpp
CMakeFiles/rc.dir/src/rime/main.cpp.o: CMakeFiles/rc.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/mnt/c/Users/param/Param/Programming/C++/rime/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/rc.dir/src/rime/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/rc.dir/src/rime/main.cpp.o -MF CMakeFiles/rc.dir/src/rime/main.cpp.o.d -o CMakeFiles/rc.dir/src/rime/main.cpp.o -c /mnt/c/Users/param/Param/Programming/C++/rime/src/rime/main.cpp

CMakeFiles/rc.dir/src/rime/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/rc.dir/src/rime/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/Users/param/Param/Programming/C++/rime/src/rime/main.cpp > CMakeFiles/rc.dir/src/rime/main.cpp.i

CMakeFiles/rc.dir/src/rime/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/rc.dir/src/rime/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/Users/param/Param/Programming/C++/rime/src/rime/main.cpp -o CMakeFiles/rc.dir/src/rime/main.cpp.s

# Object files for target rc
rc_OBJECTS = \
"CMakeFiles/rc.dir/parser.c.o" \
"CMakeFiles/rc.dir/lexer.yy.c.o" \
"CMakeFiles/rc.dir/src/rime/assembler.cpp.o" \
"CMakeFiles/rc.dir/src/rime/main.cpp.o"

# External object files for target rc
rc_EXTERNAL_OBJECTS =

/mnt/c/Users/param/Param/Programming/C++/rime/rc: CMakeFiles/rc.dir/parser.c.o
/mnt/c/Users/param/Param/Programming/C++/rime/rc: CMakeFiles/rc.dir/lexer.yy.c.o
/mnt/c/Users/param/Param/Programming/C++/rime/rc: CMakeFiles/rc.dir/src/rime/assembler.cpp.o
/mnt/c/Users/param/Param/Programming/C++/rime/rc: CMakeFiles/rc.dir/src/rime/main.cpp.o
/mnt/c/Users/param/Param/Programming/C++/rime/rc: CMakeFiles/rc.dir/build.make
/mnt/c/Users/param/Param/Programming/C++/rime/rc: CMakeFiles/rc.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/mnt/c/Users/param/Param/Programming/C++/rime/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Linking CXX executable /mnt/c/Users/param/Param/Programming/C++/rime/rc"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/rc.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/rc.dir/build: /mnt/c/Users/param/Param/Programming/C++/rime/rc
.PHONY : CMakeFiles/rc.dir/build

CMakeFiles/rc.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/rc.dir/cmake_clean.cmake
.PHONY : CMakeFiles/rc.dir/clean

CMakeFiles/rc.dir/depend: lexer.yy.c
CMakeFiles/rc.dir/depend: parser.c
CMakeFiles/rc.dir/depend: parser.h
	cd /mnt/c/Users/param/Param/Programming/C++/rime/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/c/Users/param/Param/Programming/C++/rime /mnt/c/Users/param/Param/Programming/C++/rime /mnt/c/Users/param/Param/Programming/C++/rime/build /mnt/c/Users/param/Param/Programming/C++/rime/build /mnt/c/Users/param/Param/Programming/C++/rime/build/CMakeFiles/rc.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/rc.dir/depend

