# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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
CMAKE_SOURCE_DIR = /home/kostas/Desktop/Teeworlds

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/kostas/Desktop/Teeworlds/build

# Utility rule file for package_tar_gz.

# Include any custom commands dependencies for this target.
include CMakeFiles/package_tar_gz.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/package_tar_gz.dir/progress.make

CMakeFiles/package_tar_gz: teeworlds-0.6.5-linux_x86_64.tar.gz

teeworlds-0.6.5-linux_x86_64.tar.gz: teeworlds
teeworlds-0.6.5-linux_x86_64.tar.gz: teeworlds_srv
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/kostas/Desktop/Teeworlds/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Generating teeworlds-0.6.5-linux_x86_64.tar.gz"
	/usr/bin/cmake -E remove_directory pack_teeworlds-0.6.5-linux_x86_64_tar_gz/teeworlds-0.6.5-linux_x86_64
	/usr/bin/cmake -E make_directory pack_teeworlds-0.6.5-linux_x86_64_tar_gz/teeworlds-0.6.5-linux_x86_64
	/usr/bin/cmake -E copy /home/kostas/Desktop/Teeworlds/license.txt pack_teeworlds-0.6.5-linux_x86_64_tar_gz/teeworlds-0.6.5-linux_x86_64/
	/usr/bin/cmake -E copy /home/kostas/Desktop/Teeworlds/storage.cfg pack_teeworlds-0.6.5-linux_x86_64_tar_gz/teeworlds-0.6.5-linux_x86_64/
	/usr/bin/cmake -E copy_directory /home/kostas/Desktop/Teeworlds/data pack_teeworlds-0.6.5-linux_x86_64_tar_gz/teeworlds-0.6.5-linux_x86_64/data
	/usr/bin/cmake -E copy /home/kostas/Desktop/Teeworlds/build/teeworlds pack_teeworlds-0.6.5-linux_x86_64_tar_gz/teeworlds-0.6.5-linux_x86_64/
	/usr/bin/cmake -E copy /home/kostas/Desktop/Teeworlds/build/teeworlds_srv pack_teeworlds-0.6.5-linux_x86_64_tar_gz/teeworlds-0.6.5-linux_x86_64/
	/usr/bin/cmake -E chdir pack_teeworlds-0.6.5-linux_x86_64_tar_gz /usr/bin/cmake -E tar cz ../teeworlds-0.6.5-linux_x86_64.tar.gz -- teeworlds-0.6.5-linux_x86_64/

package_tar_gz: CMakeFiles/package_tar_gz
package_tar_gz: teeworlds-0.6.5-linux_x86_64.tar.gz
package_tar_gz: CMakeFiles/package_tar_gz.dir/build.make
.PHONY : package_tar_gz

# Rule to build all files generated by this target.
CMakeFiles/package_tar_gz.dir/build: package_tar_gz
.PHONY : CMakeFiles/package_tar_gz.dir/build

CMakeFiles/package_tar_gz.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/package_tar_gz.dir/cmake_clean.cmake
.PHONY : CMakeFiles/package_tar_gz.dir/clean

CMakeFiles/package_tar_gz.dir/depend:
	cd /home/kostas/Desktop/Teeworlds/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/kostas/Desktop/Teeworlds /home/kostas/Desktop/Teeworlds /home/kostas/Desktop/Teeworlds/build /home/kostas/Desktop/Teeworlds/build /home/kostas/Desktop/Teeworlds/build/CMakeFiles/package_tar_gz.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/package_tar_gz.dir/depend

