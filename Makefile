##
##		-- Makefile by lrobino --
##		Used to compile basic c project
##		Using exernal or local libs

## TARGET_TYPE
TARGET_EXE	= cub3D
TARGET_LIB	= lib.a

## PROJECT NAME (Choose target)
NAME	= $(TARGET_EXE)

## SCREENSHOTS FOLDER
SCREENSHOTS = ./screenshots

## SRCS
SRC_DIR= srcs

SRCS=	main.c						\
		process.c					\
		map/map_utils.c				\
		graphics/graphics.c			\
		graphics/color_utils.c		\
		map/map_checker.c			\
		graphics/raycast.c			\
		graphics/raycast_utils.c	\
		util/math_utils.c			\
		input/input.c				\
		input/input_handler.c		\
		gameobjects/cube.c			\
		gameobjects/sprite.c		\
		gameobjects/sprite_utils.c	\
		gameobjects/camera.c		\
		gameobjects/player.c		\
		util/register_handler.c		\
		util/image_loader.c			\
		util/unloader_handler.c		\
		util/screenshot_handler.c	\
		parser/parser_map.c			\
		parser/parser_register.c	\
		parser/checker.c			\
		parser/parse_line.c			\
		bmp_parser/parse_bmp.c

## HEADER FILES
HEADER_FILES =	engine.h		\
				graphics.h		\
				map_parser.h	\
				map_utils.h		\
				parser.h		\
				process.h		\
				raycast.h		\
				sprite.h		\
				cube.h			\
				color.h

## HEADERS
HEADERS = inc/

## BINS
BIN_DIR = bin
OBJS	= $(addprefix $(BIN_DIR)/, $(SRCS:.c=.o))

## LIBS
LIB				= lib
## Make sure that libft is in $(LIB) and that it outputs libft.a
LIB_HEADER		= libft/inc libvector libgnl/inc libprintf/includes
LOCAL_LIB_DIRS	= libft libgnl libvector libprintf
ifeq ($(shell uname), Linux)
	LOCAL_LIB_DIRS += libmlx_Linux
	LIB_HEADER += libmlx_Linux
endif
ifeq ($(shell uname), Darwin)
	LOCAL_LIB_DIRS += libmlx
	LIB_HEADER += libmlx
endif
## Use this to add external libs to your project (ex: libm)
## !! You have to use the "lib" prefix anyway !! 
EXTERN_LIBS		= libm
ifeq ($(shell uname), Linux)
	EXERN_LIBS += libX11 libXext libm
endif
ifeq ($(shell uname), Darwin)
	EXTERN_LIBS += libz libm
	FRAMEWORKS = -framework AppKit -framework OpenGL
endif

## GCC
CC			= gcc -c
GCC			= gcc
OUT			= --output
CFLAGS		= -Werror -Wextra -Wall # -g3 -fsanitize=address

##
##			---- COLORS ----
##


#							--> Regular Colors
BLACK=		\033[0;30m
RED=		\033[0;31m
GREEN=		\033[0;32m
YELLOW=		\033[0;33m
BLUE=		\033[0;34m
PURPLE=		\033[0;35m
CYAN=		\033[0;36m
WHITE=		\033[0;37m

#							--> Bold
BBLACK=		\033[1;30m
BRED=		\033[1;31m
BGREEN=		\033[1;32m
BYELLOW=	\033[1;33m
BBLUE=		\033[1;34m
BPURPLE=	\033[1;35m
BCYAN=		\033[1;36m
BWHITE=		\033[1;37m



##
##			---- RULES ----
##



## Require NAME and prints descritpion(42 norm)
all: desc libs $(SCREENSHOTS) $(TARGET_EXE)
	@echo "$(BWHITE)[$(BBLUE)$(NAME)$(BWHITE)] \033[0mDone."


## Prints a short description of what is compiling.
desc :
	@printf "$(BPURPLE)>>> Making target $(CYAN)"
	@if [ $(NAME) = $(TARGET_EXE) ] ; then \
		printf "exe $(BPURPLE)-> '$(NAME)'\n$(WHITE)" ; \
	else \
		printf "lib $(BPURPLE)-> '$(NAME)'\n$(WHITE)" ; \
	fi



## EXE
## Require all .a
## Require bin dir and objs
## Require headers
## -> Links the objs with libs.
$(TARGET_EXE) : $(BIN_DIR) $(OBJS) $(HEADER_FILES:%=$(HEADERS)%)
	@echo "$(BWHITE)[$(BBLUE)$(NAME)$(BWHITE)] $(BGREEN)Linked program $(CYAN)'$(NAME)'$(WHITE)."
	@$(GCC) $(OUT) $(TARGET_EXE) $(CFLAGS) $(LOCAL_LIB_DIRS:%=-L$(LIB)/%) $(OBJS) $(LOCAL_LIB_DIRS:lib%=-l%) $(EXERN_LIBS:lib%=-l%) $(FRAMEWORKS)



## LIB
## Require all .a
## Require bin dir and objs
## Require headers
## -> Links the objs with libs.
$(TARGET_LIB) : $(foreach D, $(LOCAL_LIB_DIRS), $(LIB)/$D/$D.a) $(BIN_DIR) $(OBJS) $(HEADERS)
	@echo "$(BWHITE)[$(BBLUE)$(NAME)$(BWHITE)] $(BGREEN)Linked library $(CYAN)'$(NAME)'$(WHITE)."
	@ar rcs $(NAME) $(OBJS) $(foreach D, $(LOCAL_LIB_DIRS), $(LIB)/$D/$D.a)



## Makes the bin dir.
$(BIN_DIR) :
	@echo "$(BYELLOW)Warning : no $(BIN_DIR) found.\ncreating one..."
	@mkdir -p $(BIN_DIR)



## Makes the screenshots dir
$(SCREENSHOTS) :
	@echo "$(BYELLOW)Warning : no $(SCREENSHOTS) found.\ncreating one..."
	@mkdir -p $(SCREENSHOTS)



## Require a C source
## -> Compiles a c source to a bin o file
$(BIN_DIR)/%.o : $(SRC_DIR)/%.c $(HEADER_FILES:%=$(HEADERS)/%)
	@printf$D "$(BWHITE)[$(BBLUE)$(NAME)$(BWHITE)] $(BWHITE)[$(BGREEN)✔️$(BWHITE)] Compiled : $(BGREEN)$<$(WHITE)\n"
	@mkdir -p $(shell dirname $@)
	@$(CC) $(OUT) $@ $(LIB_HEADER:%=-I$(LIB)/%) $(HEADERS:%=-I%) -I/usr/include $< $(CFLAGS)



## Require libs .a (is they exist ?)
## -> Makes libs.
libs :
	@for lib in $(LOCAL_LIB_DIRS) ; do \
		make -C $(LIB)/$${lib} ; \
	done



## -> Cleans the binarys
clean :
	@echo "$(BRED)Cleaning o files"
	@rm -rf $(BIN_DIR)
	@for lib in $(LOCAL_LIB_DIRS) ; do \
		make -C $(LIB)/$${lib} clean ; \
	done



## Requires clean
## -> Cleans the executable
fclean : clean
	@echo "$(BRED)Cleaning all"
	@rm -rf $(NAME)
	@for lib in $(LOCAL_LIB_DIRS) ; do \
		if [ $${lib} != "libmlx_Linux" ] ; then \
		make -C $(LIB)/$${lib} fclean ; \
		fi \
	done
	@make -C $(LIB)/libmlx_Linux clean



re : clean fclean all

.PHONY : all re clean fclean libs desc
