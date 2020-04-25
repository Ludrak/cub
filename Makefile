# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lrobino <lrobino@student.le-101.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/28 00:13:18 by lrobino           #+#    #+#              #
#    Updated: 2020/04/25 13:10:50 by lrobino          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

##	AUTHOR
AUTHOR			= lrobino

##	VERSION
VERSION			= 1.1

##	GRAPHICS
GRAPHICS		= #-D HIGH_GRAPHICS

##	THE DIRECTORY OF YOUR FINAL TARGET
TARGET_DIR		= .

##	TARGET NAMES FOR BOTH EXECUTABLE AND LIBRARY COMPILATION
TARGET_LIB		= -
TARGET_EXE		= cub.out

##	CHOOSE WHICH TARGET TO USE BY DEFAULT
TARGET			= $(TARGET_EXE)

##	SOURCES DIRECTORY OF YOUR PROJECT (USE '.' IF THEY ARE IN THE CURRENT FOLDER)
SRC_DIR			= srcs

##	SOURCES OF YOUR PROJECT
SRCS			=	main.c			\
					process.c		\
					map_utils.c		\
					graphics.c		\
					color_utils.c	\
					map_parser.c	\
					raycast.c		\
					raycast_utils.c	\
					math_utils.c	\
					input.c			\
					cube.c
					

##	BINARIES DIRECTORY OF YOUR PROJECT
BIN_DIR			= bin


##	PUT THE DIRECTORIES OF YOUR HEADER FILES HERE
HEADERS_DIR		= inc lib/libft lib/libvector lib/libmlx lib/libgnl

##	HEADERS OF YOUR PROJET /!\ USE FULL PATH FROM CURRENT FOLDER /!\ 
HEADERS			= inc/engine.h inc/process.h inc/map_utils.h inc/map_parser.h inc/graphics.h

##	LIBS DIRECTORY OF YOUR PROJECT (USE '-' IF YOUR PROJECT DO NOT USE LIBRARY)
LIB_DIR			= lib

##	LIBS THAT YOU ARE USING
LIBS			= libft lib2

################################################################################
####					DO NOT EDIT THINGS BELOW THIS						####
################################################################################

##

OBJS			= $(addprefix $(BIN_DIR)/,$(SRCS:.c=.o))

INCLUDES		= $(addprefix -I,$(HEADERS_DIR))

ifneq	($(LIB_DIR), -)
LIBFILES		= lib/libft/libft.a lib/libvector/libvector.a lib/libmlx/libmlx.a lib/libgnl/libgnl.a#$(addprefix $(LIB_DIR)/,$(addsuffix .a,$(addprefix $(LIBS)/,$(LIBS))))
endif

##

RM				= rm -rf
CC				= gcc -c
GCC				= gcc
AR				= ar rcus
CFLAGS			= -Wall -Wextra -Werror -g3 -fsanitize=address
LINKER_FLAGS	=  -framework AppKit -framework OpenGL -lz
OUT				= --output

C_RESET= \033[0m

BGREEN = \033[1;32m
GREEN = \033[0;32m
YELLOW	= \033[0;33m
BYELLOW = \033[1;33m
PURPLE = \033[0;35m
BPURPLE = \033[1;35m
BRED	= \033[1;31m
RED		= \033[0;31m
BLUE	= \033[0;34m
BBLUE	= \033[1;34m

m_MAKE		= $(C_RESET)[$(BBLUE) $(TARGET) $(C_RESET)] [$(PURPLE)MAKE$(C_RESET)] :
m_INFO		= $(C_RESET)[$(BBLUE) $(TARGET) $(C_RESET)] [$(PURPLE)INFO$(C_RESET)] :
m_LINK		= $(C_RESET)[$(BBLUE) $(TARGET) $(C_RESET)] [$(PURPLE)LINK$(C_RESET)] :
m_COMP		= $(C_RESET)[$(BBLUE) $(TARGET) $(C_RESET)] [$(PURPLE)COMP$(C_RESET)] :

m_WARN		= $(C_RESET)[$(BBLUE) $(TARGET) $(C_RESET)] [$(BYELLOW)WARN$(C_RESET)] :$(YELLOW)
m_REMV		= $(C_RESET)[$(BBLUE) $(TARGET) $(C_RESET)] [$(BRED)CLEAN$(C_RESET)] :$(BYELLOW)
m_ERR		= $(C_RESET)[$(BRED) $(TARGET) $(C_RESET)] [$(BRED)ERROR$(C_RESET)] :$(BYELLOW)



all : version $(TARGET)
	
	@echo "$(C_RESET) Done."

##
##	LIB TARGET COMPILER	
##
lib : $(TARGET_LIB)
$(TARGET_LIB) : $(LIB_DIR)/ $(LIBFILES) $(BIN_DIR) $(OBJS)
	@echo "$(m_LINK) Linking library : $(TARGET_LIB)"
	@$(AR) $(TARGET_LIB) $(OBJS) $(LIBFILES)
	@echo "$(m_LINK) Link success !"


##
##	EXECUTABLE TARGET COMPILER
##
exe : $(TARGET_EXE)
$(TARGET_EXE) : $(LIB_DIR)/ $(LIBFILES) $(BIN_DIR) $(OBJS)
	@echo "$(m_LINK) Making target $(TARGET_EXE)"
	@$(GCC) $(OUT) $(TARGET_EXE) $(CFLAGS) $(OBJS) $(LINKER_FLAGS) $(LIBFILES)
	@echo "$(m_LINK) Link success !"

##
##	BINS
##
$(BIN_DIR) :
	@mkdir -p $(BIN_DIR)
	@echo "$(m_WARN) $(BIN_DIR)/ Not found, created one.$(C_RESET)";



$(BIN_DIR)/%.o : $(SRC_DIR)/%.c $(HEADERS)
	@printf "$(m_COMP) Compiling : $<"
	@$(CC) $< $(CFLAGS) $(OUT) $@ $(INCLUDES) $(GRAPHICS)
	@echo "\r$(m_COMP) Compiled : $<   "



##
##	LIB
##
$(LIB_DIR)/ :
ifneq	($(LIB_DIR), -)
	@echo "$(m_ERR) Could not find $(LIB_DIR)/ directory !"
endif


$(LIB_DIR)/%/libft.a : $(LIB_DIR)/%
	@echo "$(m_MAKE) COMPILING LIB : $<$(C_RESET)"
	@$(MAKE) -C $<

$(LIB_DIR)/%/libvector.a : $(LIB_DIR)/%
	@echo "$(m_MAKE) COMPILING LIB : $<$(C_RESET)"
	@$(MAKE) -C $<

$(LIB_DIR)/%/libmlx.a : $(LIB_DIR)/%
	@echo "$(m_MAKE) COMPILING LIB : $<$(C_RESET)"
	@$(MAKE) -C $<

$(LIB_DIR)/%/libgnl.a : $(LIB_DIR)/%
	@echo "$(m_MAKE) COMPILING LIB : $<$(C_RESET)"
	@$(MAKE) -C $<




##
##	CLEAN
##
cl : clean
clean :
	@$(MAKE) -C lib/libft clean
	@$(MAKE) -C lib/libvector clean
	@$(MAKE) -C lib/libgnl clean
	@$(MAKE) -C lib/libmlx clean
	@$(RM) $(BIN_DIR)
	@echo "$(m_REMV) Removed .o files."



fc : fclean
fclean : clean
	@$(RM) $(TARGET_EXE)
	@$(RM) $(TARGET_EXE).dSYM
	@$(MAKE) -C lib/libft fclean
	@$(MAKE) -C lib/libvector fclean
	@$(MAKE) -C lib/libgnl fclean
	@$(MAKE) -C lib/libmlx clean
	@echo "$(m_REMV) Removed target : '$(TARGET)'"



##
##	UTILS
##
norm : version
	@echo "$(m_INFO) Norme for : '$(TARGET_LIB)'\n-->"
	@norminette



v : version
version :
	@printf "\e[1;1H\e[2J"
	@echo "$(BBLUE)#################################################################################"
	@echo "#                                                                               #"
	@echo "#           :::      ::::::::                                                   #"
	@echo "#         :+:      :+:    :+:                                                   #"
	@echo "#       +:+ +:+         +:+                                                     #"
	@echo "#     +#+  +:+       +#+                                                        #"
	@echo "#   +#+#+#+#+#+   +#+                                                           #"
	@echo "#         #+#    #+#                                                            #"
	@echo "#        ###   ######## - Lyon                                                  #"
	@echo "#                                                                               #"
	@echo "#$(C_RESET)>-----------------------------------------------------------------------------<$(BBLUE)#"
	@printf "#$(C_RESET)   Project : %-20.20s                                              $(BBLUE)#\n" $(TARGET)
	@printf "#$(C_RESET)   Version : %-15.15s                       Author : %-10.10s         $(BBLUE)#\n" $(VERSION) $(AUTHOR)
	@echo "#################################################################################$(C_RESET)\n\n"

##
##	SHORTCUTS
##
re : version fclean all

################################################################################

.PHONY	: all re fclean fc clean version v exe lib
