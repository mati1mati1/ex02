# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.29

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
CMAKE_COMMAND = /opt/homebrew/Cellar/cmake/3.29.6/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/Cellar/cmake/3.29.6/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/matanamichy/TAU/2024/cppPrograming/Ex02ProgramingTopics

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/matanamichy/TAU/2024/cppPrograming/Ex02ProgramingTopics/build

# Include any dependencies generated for this target.
include CMakeFiles/HouseLocationTest.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/HouseLocationTest.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/HouseLocationTest.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/HouseLocationTest.dir/flags.make

CMakeFiles/HouseLocationTest.dir/src/HouseLocation.cpp.o: CMakeFiles/HouseLocationTest.dir/flags.make
CMakeFiles/HouseLocationTest.dir/src/HouseLocation.cpp.o: /Users/matanamichy/TAU/2024/cppPrograming/Ex02ProgramingTopics/src/HouseLocation.cpp
CMakeFiles/HouseLocationTest.dir/src/HouseLocation.cpp.o: CMakeFiles/HouseLocationTest.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/matanamichy/TAU/2024/cppPrograming/Ex02ProgramingTopics/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/HouseLocationTest.dir/src/HouseLocation.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/HouseLocationTest.dir/src/HouseLocation.cpp.o -MF CMakeFiles/HouseLocationTest.dir/src/HouseLocation.cpp.o.d -o CMakeFiles/HouseLocationTest.dir/src/HouseLocation.cpp.o -c /Users/matanamichy/TAU/2024/cppPrograming/Ex02ProgramingTopics/src/HouseLocation.cpp

CMakeFiles/HouseLocationTest.dir/src/HouseLocation.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/HouseLocationTest.dir/src/HouseLocation.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/matanamichy/TAU/2024/cppPrograming/Ex02ProgramingTopics/src/HouseLocation.cpp > CMakeFiles/HouseLocationTest.dir/src/HouseLocation.cpp.i

CMakeFiles/HouseLocationTest.dir/src/HouseLocation.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/HouseLocationTest.dir/src/HouseLocation.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/matanamichy/TAU/2024/cppPrograming/Ex02ProgramingTopics/src/HouseLocation.cpp -o CMakeFiles/HouseLocationTest.dir/src/HouseLocation.cpp.s

CMakeFiles/HouseLocationTest.dir/test/HouseLocationTest.cpp.o: CMakeFiles/HouseLocationTest.dir/flags.make
CMakeFiles/HouseLocationTest.dir/test/HouseLocationTest.cpp.o: /Users/matanamichy/TAU/2024/cppPrograming/Ex02ProgramingTopics/test/HouseLocationTest.cpp
CMakeFiles/HouseLocationTest.dir/test/HouseLocationTest.cpp.o: CMakeFiles/HouseLocationTest.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/matanamichy/TAU/2024/cppPrograming/Ex02ProgramingTopics/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/HouseLocationTest.dir/test/HouseLocationTest.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/HouseLocationTest.dir/test/HouseLocationTest.cpp.o -MF CMakeFiles/HouseLocationTest.dir/test/HouseLocationTest.cpp.o.d -o CMakeFiles/HouseLocationTest.dir/test/HouseLocationTest.cpp.o -c /Users/matanamichy/TAU/2024/cppPrograming/Ex02ProgramingTopics/test/HouseLocationTest.cpp

CMakeFiles/HouseLocationTest.dir/test/HouseLocationTest.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/HouseLocationTest.dir/test/HouseLocationTest.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/matanamichy/TAU/2024/cppPrograming/Ex02ProgramingTopics/test/HouseLocationTest.cpp > CMakeFiles/HouseLocationTest.dir/test/HouseLocationTest.cpp.i

CMakeFiles/HouseLocationTest.dir/test/HouseLocationTest.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/HouseLocationTest.dir/test/HouseLocationTest.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/matanamichy/TAU/2024/cppPrograming/Ex02ProgramingTopics/test/HouseLocationTest.cpp -o CMakeFiles/HouseLocationTest.dir/test/HouseLocationTest.cpp.s

# Object files for target HouseLocationTest
HouseLocationTest_OBJECTS = \
"CMakeFiles/HouseLocationTest.dir/src/HouseLocation.cpp.o" \
"CMakeFiles/HouseLocationTest.dir/test/HouseLocationTest.cpp.o"

# External object files for target HouseLocationTest
HouseLocationTest_EXTERNAL_OBJECTS =

HouseLocationTest: CMakeFiles/HouseLocationTest.dir/src/HouseLocation.cpp.o
HouseLocationTest: CMakeFiles/HouseLocationTest.dir/test/HouseLocationTest.cpp.o
HouseLocationTest: CMakeFiles/HouseLocationTest.dir/build.make
HouseLocationTest: lib/libgtest_main.a
HouseLocationTest: lib/libgtest.a
HouseLocationTest: CMakeFiles/HouseLocationTest.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/Users/matanamichy/TAU/2024/cppPrograming/Ex02ProgramingTopics/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable HouseLocationTest"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/HouseLocationTest.dir/link.txt --verbose=$(VERBOSE)
	/opt/homebrew/Cellar/cmake/3.29.6/bin/cmake -D TEST_TARGET=HouseLocationTest -D TEST_EXECUTABLE=/Users/matanamichy/TAU/2024/cppPrograming/Ex02ProgramingTopics/build/HouseLocationTest -D TEST_EXECUTOR= -D TEST_WORKING_DIR=/Users/matanamichy/TAU/2024/cppPrograming/Ex02ProgramingTopics/build -D TEST_EXTRA_ARGS= -D TEST_PROPERTIES= -D TEST_PREFIX= -D TEST_SUFFIX= -D TEST_FILTER= -D NO_PRETTY_TYPES=FALSE -D NO_PRETTY_VALUES=FALSE -D TEST_LIST=HouseLocationTest_TESTS -D CTEST_FILE=/Users/matanamichy/TAU/2024/cppPrograming/Ex02ProgramingTopics/build/HouseLocationTest[1]_tests.cmake -D TEST_DISCOVERY_TIMEOUT=5 -D TEST_XML_OUTPUT_DIR= -P /opt/homebrew/Cellar/cmake/3.29.6/share/cmake/Modules/GoogleTestAddTests.cmake

# Rule to build all files generated by this target.
CMakeFiles/HouseLocationTest.dir/build: HouseLocationTest
.PHONY : CMakeFiles/HouseLocationTest.dir/build

CMakeFiles/HouseLocationTest.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/HouseLocationTest.dir/cmake_clean.cmake
.PHONY : CMakeFiles/HouseLocationTest.dir/clean

CMakeFiles/HouseLocationTest.dir/depend:
	cd /Users/matanamichy/TAU/2024/cppPrograming/Ex02ProgramingTopics/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/matanamichy/TAU/2024/cppPrograming/Ex02ProgramingTopics /Users/matanamichy/TAU/2024/cppPrograming/Ex02ProgramingTopics /Users/matanamichy/TAU/2024/cppPrograming/Ex02ProgramingTopics/build /Users/matanamichy/TAU/2024/cppPrograming/Ex02ProgramingTopics/build /Users/matanamichy/TAU/2024/cppPrograming/Ex02ProgramingTopics/build/CMakeFiles/HouseLocationTest.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/HouseLocationTest.dir/depend

