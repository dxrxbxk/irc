# -- M A K E F I L E -----------------------------------------------------------

###############################################################################
#        ▁▁▁▁▁▁▁▁  ▁▁▁▁▁▁▁▁  ▁▁▁▁ ▁▁▁  ▁▁▁▁▁▁▁▁                               #
#       ╱        ╲╱        ╲╱    ╱   ╲╱        ╲    language: makefile        #
#      ╱         ╱         ╱         ╱         ╱    author:   @tutur          #
#     ╱         ╱         ╱        ▁╱       ▁▁╱     created: 2020-05-01       #
#     ╲▁▁╱▁▁╱▁▁╱╲▁▁▁╱▁▁▁▁╱╲▁▁▁▁╱▁▁▁╱╲▁▁▁▁▁▁▁▁╱      updated: 2020-05-01       #
#                                                                             #
###############################################################################

# -- S E T T I N G S ----------------------------------------------------------

# set default target
.DEFAULT_GOAL := all

# use one shell for all commands
.ONESHELL:

# delete intermediate files on error
#.DELETE_ON_ERROR:

# silent mode
#.SILENT:

# set shell program
override SHELL := $(shell which zsh)

# set shell flags
.SHELLFLAGS := -d -f -c -e -o pipefail -u

# set make flags
override MAKEFLAGS += --warn-undefined-variables --no-builtin-rules


# -- O P E R A T I N G  S Y S T E M -------------------------------------------

override THREAD    := $(shell nproc)




# -- D I R E C T O R I E S ----------------------------------------------------

# source directory
override SRCDIR := src

# include directory
override INCDIR := inc

# build directory
override BLDDIR := build

# object directory
override OBJDIR := $(BLDDIR)/object

# dependency directory
override DEPDIR := $(BLDDIR)/dependency

# current directory
override ROOT := $(shell pwd)



# -- T A R G E T S ------------------------------------------------------------

# project name
override PROJECT := ircserv

# main executable
override NAME := $(PROJECT)

# hook script
override HOOK := $(ROOT)/.git/hooks/pre-commit



# -- S O U R C E S ------------------------------------------------------------

# get all source files
override SRC := $(shell find $(SRCDIR) -type f -name "*.cpp")

# get all header files
override HDR := $(shell find $(INCDIR) -type f -name "*.hpp")

# get all header directories
override HDRDIR := $(sort $(dir $(HDR)))

# pattern substitution for object files
override OBJ := $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o,    $(SRC))

# pattern substitution for dependency files
override DEP := $(patsubst $(OBJDIR)/%.o,   $(DEPDIR)/%.d,    $(OBJ))

override HIR := $(sort $(dir $(SRC)))
override OBJHIR := $(HIR:$(SRCDIR)/%=$(OBJDIR)/%)
override DEPHIR := $(HIR:$(SRCDIR)/%=$(DEPDIR)/%)



# -- C O M P I L E R  S E T T I N G S -----------------------------------------

# make directory if not exists
override MKDIR := mkdir -pv

# remove recursively force
override RM := rm -rfv

# leaks detection program
override VALGRIND := $(shell which valgrind)

# valgrind flags
override VFLAGS := valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes

# compiler
override CXX := $(shell which c++)

# compiler standard
override STD := -std=c++98

# compiler optimization
override OPT := -O0 -g3

# compiler flags
override CXXFLAGS := -Wall -Wextra -Werror -Wpedantic -Wno-unused -Wno-unused-variable -Wno-unused-parameter

# dependency flags
override DEPFLAGS = -MT $@ -MMD -MP -MF $(DEPDIR)/$*.d

# all include subdirs with -I prefix
override INCLUDES := $(addprefix -I, $(HDRDIR))

DEF ?=

override DEFINES := $(addprefix -D, $(DEF))




# -- P H O N Y  T A R G E T S -------------------------------------------------

.PHONY: all clean fclean re obj logger leaks


# -- M A I N  T A R G E T S ---------------------------------------------------

all: $(HOOK) obj $(NAME)


# -- E X E C U T A B L E  T A R G E T -------------------------------------------

$(NAME): $(OBJ)
	@echo "  linking -> \x1b[34m"$@"\x1b[0m"
	@$(CXX) $^ -o $@;


# -- C O M P I L A T I O N ------------------------------------------------------

# self call with threads
obj:
	@$(MAKE) --silent -j$(THREAD) $(OBJ)

-include $(DEP)

$(OBJDIR)/%.o : $(SRCDIR)/%.cpp Makefile | $(OBJHIR) $(DEPHIR)
	@echo "compiling -> \x1b[33m"$(<F)"\x1b[0m"
	@$(CXX) $(STD) $(OPT) $(CXXFLAGS) $(DEFINES) $(DEPFLAGS) $(INCLUDES) -c $< -o $@

# -- D I R E C T O R I E S  C R E A T I O N -------------------------------------

$(OBJHIR) $(DEPHIR) :
	@$(MKDIR) $@

# -- C L E A N I N G ------------------------------------------------------------

clean:
	@$(RM) $(BLDDIR)


fclean: clean
	@$(RM) $(NAME)



# -- R E C O M P I L E --------------------------------------------------------

re: fclean all


leaks: all
	$(VALGRIND) $(VFLAGS) ./$(NAME) 8080 pass

logger:
	@echo "     mode -> \x1b[36m"IRC_LOGGER"\x1b[0m"
	@$(MAKE) --silent re DEF=IRC_LOGGER

$(HOOK):
	ln -s $(ROOT)/config/pre-commit $@






#invite.hpp
#join.hpp
#kick.hpp
#mode.hpp
#nick.hpp
#part.hpp
#pass.hpp
#ping.hpp
#pong.hpp
#privmsg.hpp
#quit.hpp
#topic.hpp
#user.hpp
#who.hpp
