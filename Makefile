# Filename   : Makefile
# Author     : Connor Billings
# Course     : CSCI 476-01
# Assignment : 7 - It's All in the Game (Cellular Automata, Grid Computations)
# Description: Makefile

# It'd be nice to have a more generic makefile, also my .gitignore has to ignore 'main' due to the executable build rules, it would be nice to have that removed


# TODO This needs to be set up with rules that let me do a normal and test build


########################################################
# Variable definitions
########################################################
# C++ compiler
CXX      = g++

# C++ compiler flags
# Use this first configuration for debugging
#CXXFLAGS := -ggdb -Wall -std=c++14
# Use the following  configuration for release
CXXFLAGS := -O3 -Wall -pedantic -std=c++17

# Linker: for C++ should be $(CXX)
LINK     := $(CXX)

# Linker flags. Usually none.
LDFLAGS  :=

# Library paths, prefaced with "-L". Usually none.
LDPATHS :=

# Libraries we're using, prefaced with "-l".
#LDLIBS :=
LDLIBS :=

# Executable name. Needs to be the basename of your driver
#   file. I.e., your driver must be named $(EXEC).cc
EXEC := driver

#############################################################
# Rules
#   Rules have the form
#   target : prerequisites
#   	  recipe
#############################################################

# Add additional object files if you're using more than one
#   source file.
$(EXEC) : driver.o tests.o
	$(LINK) $(LDFLAGS) $^ $(LDLIBS) -o $@

# Add rules for each object file
# No recipes are typically needed
driver.o : driver.cc catch.hpp
tests.o : tests.cc catch.hpp Graph.hpp

#############################################################

clean :
	@$(RM) $(EXEC) a.out core
	@$(RM) *.o
	@$(RM) *.d
	@$(RM) *~

#############################################################
