# Filename   : Makefile
# Author     : Connor Billings
# Course     : CSCI 476-01
# Assignment : 7 - It's All in the Game (Cellular Automata, Grid Computations)
# Description: Makefile

########################################################
# Variable definitions
########################################################
# C++ compiler
CXX      = g++

# C++ compiler flags
# Use this first configuration for debugging
#CXXFLAGS := -ggdb -Wall -std=c++14
# Use the following  configuration for release
CXXFLAGS := -O3 -g -Wall -Wextra -pedantic -pedantic-errors -std=c++17

# Linker: for C++ should be $(CXX)
LINK     := $(CXX)

# Linker flags. Usually none.
LDFLAGS  :=

# Library paths, prefaced with "-L". Usually none.
LDPATHS :=

# Libraries we're using, prefaced with "-l".
#LDLIBS :=
LDLIBS := -lpthread -lboost_thread -lboost_system

# Executable name. Needs to be the basename of your driver
#   file. I.e., your driver must be named $(EXEC).cc
EXEC := main

#############################################################
# Rules
#   Rules have the form
#   target : prerequisites
#   	  recipe
#############################################################

# Add additional object files if you're using more than one
#   source file.
$(EXEC) : $(EXEC).o
	$(LINK) $(LDFLAGS) $^ $(LDLIBS) -o $@

# Add rules for each object file
# No recipes are typically needed
$(EXEC).o : $(EXEC).cc Graph.hpp Floyd.hpp Node.hpp

#############################################################

clean :
	@$(RM) $(EXEC) a.out core
	@$(RM) *.o
	@$(RM) *.d
	@$(RM) *~

#############################################################
