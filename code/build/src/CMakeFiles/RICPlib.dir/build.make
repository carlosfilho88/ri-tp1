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
CMAKE_SOURCE_DIR = /home/cf/workspace/ri/code

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/cf/workspace/ri/code/build

# Include any dependencies generated for this target.
include src/CMakeFiles/RICPlib.dir/depend.make

# Include the progress variables for this target.
include src/CMakeFiles/RICPlib.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/RICPlib.dir/flags.make

src/CMakeFiles/RICPlib.dir/CollectionReader.o: src/CMakeFiles/RICPlib.dir/flags.make
src/CMakeFiles/RICPlib.dir/CollectionReader.o: ../src/CollectionReader.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/cf/workspace/ri/code/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/CMakeFiles/RICPlib.dir/CollectionReader.o"
	cd /home/cf/workspace/ri/code/build/src && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/RICPlib.dir/CollectionReader.o -c /home/cf/workspace/ri/code/src/CollectionReader.cpp

src/CMakeFiles/RICPlib.dir/CollectionReader.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/RICPlib.dir/CollectionReader.i"
	cd /home/cf/workspace/ri/code/build/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/cf/workspace/ri/code/src/CollectionReader.cpp > CMakeFiles/RICPlib.dir/CollectionReader.i

src/CMakeFiles/RICPlib.dir/CollectionReader.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/RICPlib.dir/CollectionReader.s"
	cd /home/cf/workspace/ri/code/build/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/cf/workspace/ri/code/src/CollectionReader.cpp -o CMakeFiles/RICPlib.dir/CollectionReader.s

src/CMakeFiles/RICPlib.dir/CollectionReader.o.requires:
.PHONY : src/CMakeFiles/RICPlib.dir/CollectionReader.o.requires

src/CMakeFiles/RICPlib.dir/CollectionReader.o.provides: src/CMakeFiles/RICPlib.dir/CollectionReader.o.requires
	$(MAKE) -f src/CMakeFiles/RICPlib.dir/build.make src/CMakeFiles/RICPlib.dir/CollectionReader.o.provides.build
.PHONY : src/CMakeFiles/RICPlib.dir/CollectionReader.o.provides

src/CMakeFiles/RICPlib.dir/CollectionReader.o.provides.build: src/CMakeFiles/RICPlib.dir/CollectionReader.o

src/CMakeFiles/RICPlib.dir/CollectionWriter.o: src/CMakeFiles/RICPlib.dir/flags.make
src/CMakeFiles/RICPlib.dir/CollectionWriter.o: ../src/CollectionWriter.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/cf/workspace/ri/code/build/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/CMakeFiles/RICPlib.dir/CollectionWriter.o"
	cd /home/cf/workspace/ri/code/build/src && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/RICPlib.dir/CollectionWriter.o -c /home/cf/workspace/ri/code/src/CollectionWriter.cpp

src/CMakeFiles/RICPlib.dir/CollectionWriter.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/RICPlib.dir/CollectionWriter.i"
	cd /home/cf/workspace/ri/code/build/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/cf/workspace/ri/code/src/CollectionWriter.cpp > CMakeFiles/RICPlib.dir/CollectionWriter.i

src/CMakeFiles/RICPlib.dir/CollectionWriter.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/RICPlib.dir/CollectionWriter.s"
	cd /home/cf/workspace/ri/code/build/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/cf/workspace/ri/code/src/CollectionWriter.cpp -o CMakeFiles/RICPlib.dir/CollectionWriter.s

src/CMakeFiles/RICPlib.dir/CollectionWriter.o.requires:
.PHONY : src/CMakeFiles/RICPlib.dir/CollectionWriter.o.requires

src/CMakeFiles/RICPlib.dir/CollectionWriter.o.provides: src/CMakeFiles/RICPlib.dir/CollectionWriter.o.requires
	$(MAKE) -f src/CMakeFiles/RICPlib.dir/build.make src/CMakeFiles/RICPlib.dir/CollectionWriter.o.provides.build
.PHONY : src/CMakeFiles/RICPlib.dir/CollectionWriter.o.provides

src/CMakeFiles/RICPlib.dir/CollectionWriter.o.provides.build: src/CMakeFiles/RICPlib.dir/CollectionWriter.o

src/CMakeFiles/RICPlib.dir/Document.o: src/CMakeFiles/RICPlib.dir/flags.make
src/CMakeFiles/RICPlib.dir/Document.o: ../src/Document.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/cf/workspace/ri/code/build/CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/CMakeFiles/RICPlib.dir/Document.o"
	cd /home/cf/workspace/ri/code/build/src && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/RICPlib.dir/Document.o -c /home/cf/workspace/ri/code/src/Document.cpp

src/CMakeFiles/RICPlib.dir/Document.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/RICPlib.dir/Document.i"
	cd /home/cf/workspace/ri/code/build/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/cf/workspace/ri/code/src/Document.cpp > CMakeFiles/RICPlib.dir/Document.i

src/CMakeFiles/RICPlib.dir/Document.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/RICPlib.dir/Document.s"
	cd /home/cf/workspace/ri/code/build/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/cf/workspace/ri/code/src/Document.cpp -o CMakeFiles/RICPlib.dir/Document.s

src/CMakeFiles/RICPlib.dir/Document.o.requires:
.PHONY : src/CMakeFiles/RICPlib.dir/Document.o.requires

src/CMakeFiles/RICPlib.dir/Document.o.provides: src/CMakeFiles/RICPlib.dir/Document.o.requires
	$(MAKE) -f src/CMakeFiles/RICPlib.dir/build.make src/CMakeFiles/RICPlib.dir/Document.o.provides.build
.PHONY : src/CMakeFiles/RICPlib.dir/Document.o.provides

src/CMakeFiles/RICPlib.dir/Document.o.provides.build: src/CMakeFiles/RICPlib.dir/Document.o

# Object files for target RICPlib
RICPlib_OBJECTS = \
"CMakeFiles/RICPlib.dir/CollectionReader.o" \
"CMakeFiles/RICPlib.dir/CollectionWriter.o" \
"CMakeFiles/RICPlib.dir/Document.o"

# External object files for target RICPlib
RICPlib_EXTERNAL_OBJECTS =

src/libRICPlib.a: src/CMakeFiles/RICPlib.dir/CollectionReader.o
src/libRICPlib.a: src/CMakeFiles/RICPlib.dir/CollectionWriter.o
src/libRICPlib.a: src/CMakeFiles/RICPlib.dir/Document.o
src/libRICPlib.a: src/CMakeFiles/RICPlib.dir/build.make
src/libRICPlib.a: src/CMakeFiles/RICPlib.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX static library libRICPlib.a"
	cd /home/cf/workspace/ri/code/build/src && $(CMAKE_COMMAND) -P CMakeFiles/RICPlib.dir/cmake_clean_target.cmake
	cd /home/cf/workspace/ri/code/build/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/RICPlib.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/RICPlib.dir/build: src/libRICPlib.a
.PHONY : src/CMakeFiles/RICPlib.dir/build

src/CMakeFiles/RICPlib.dir/requires: src/CMakeFiles/RICPlib.dir/CollectionReader.o.requires
src/CMakeFiles/RICPlib.dir/requires: src/CMakeFiles/RICPlib.dir/CollectionWriter.o.requires
src/CMakeFiles/RICPlib.dir/requires: src/CMakeFiles/RICPlib.dir/Document.o.requires
.PHONY : src/CMakeFiles/RICPlib.dir/requires

src/CMakeFiles/RICPlib.dir/clean:
	cd /home/cf/workspace/ri/code/build/src && $(CMAKE_COMMAND) -P CMakeFiles/RICPlib.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/RICPlib.dir/clean

src/CMakeFiles/RICPlib.dir/depend:
	cd /home/cf/workspace/ri/code/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/cf/workspace/ri/code /home/cf/workspace/ri/code/src /home/cf/workspace/ri/code/build /home/cf/workspace/ri/code/build/src /home/cf/workspace/ri/code/build/src/CMakeFiles/RICPlib.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/CMakeFiles/RICPlib.dir/depend

