#
#
#                          M A K E F I L E
################################################################################

.DELETE_ON_ERROR:
.DEFAULT_GOAL			:= all

### C O M P I L E R   F L A G S ################################################

CC						:= clang++
STD						:= -std=c++98
CFLAGS					:= -Wall -Wextra -Werror -g3 -gdwarf-4
LDFLAGS					?= -MMD -MF

override MKDIR			:= mkdir -pv
override RM				:= rm -rvf

### D I R E C T O R Y ' S ######################################################

NAME					:= ircserv

override FILES			:= main.cpp \
							server.cpp \
							utils.cpp \
							epoll.cpp \
							signal.cpp \
							connexion.cpp \
							sharedfd.cpp \
							socketserver.cpp \
							parser.cpp

SRCDIR					:= src
INCDIR					:= inc
OBJDIR					:= _obj
DEPDIR					:= _dep

### P A T T E R N   R U L E S ##################################################

override SUB			:= $(shell find $(SRCDIR) -type d)
override OBJ			:= $(FILES:%.cpp=$(OBJDIR)/%.o)
override DEP			:= $(patsubst $(OBJDIR)/%.o, $(DEPDIR)/%.d, $(OBJ))

### U T I L I T Y ##############################################################

### C O M P I L A T I O N   F U N C T I O N ####################################

define COMPILE_RULE
$(OBJDIR)/%.o:			$(1)/%.cpp Makefile | $(OBJDIR) $(DEPDIR)
	$$(CC) $$(STD) -I$$(INCDIR) $$(CFLAGS) \
	-c $$< -o $$@ \
	$$(LDFLAGS) $$(DEPDIR)/$$(*F).d;
endef

### R E C I P E S ##############################################################

.PHONY:					all clean fclean re

all:					$(NAME)

$(NAME):				$(OBJ)
						$(CC) $^ -o $@

-include $(DEP)
$(foreach DIR, $(SUB), $(eval $(call COMPILE_RULE, $(DIR))))

$(OBJDIR) $(DEPDIR):
						@$(MKDIR) $@

clean:					;
						@$(RM) $(OBJDIR) $(DEPDIR)

fclean:					clean
						@$(RM) $(NAME)

re:						fclean all
