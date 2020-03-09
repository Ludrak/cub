
NAME			= cub3d
OUT_PATH		= .

SRCS			=	main.c	\
					process.c	\
					map_utils.c

SRC_DIR			= srcs

PATH_INC		= inc/engine.h inc/process.h inc/map_utils.h

BIN_DIR			= bin
OBJS			= $(addprefix $(BIN_DIR)/,$(SRCS:.c=.o))

LIBS			= libft.a libmlx.a libvector.a
LIB_DIR			= lib

#GCC
CC				= gcc -c
LNK				= gcc
OUT				= -o 
CFLAGS			= -Wall -Wextra -Werror# -g3 -fsanitize=address
INCLUDES		= -Iinc -Ilibft -Ilibvector -Ilibmlx

MINFO			= [\033[1;32m$(NAME)\033[0m] : 

all : lib_comp $(OUT_PATH)/$(NAME)
	@echo "Done."

$(OUT_PATH)/$(NAME) : $(BIN_DIR) $(OBJS)
	@echo "$(MINFO) Linking to lib $@"
	@$(LNK) $(OUT) $@ -framework AppKit -framework OpenGL $(OBJS) $(addprefix $(LIB_DIR)/,$(LIBS)) 
	
	@###$(addprefix $(LIB_DIR)/$(LIBS),.a)

$(BIN_DIR)/%.o : $(SRC_DIR)/%.c $(PATH_INC)
	@echo "$(MINFO) Compiling \033[0;32m$<\033[0m"
	@$(CC) $(OUT) $@ $(CFLAGS) $(INCLUDES) $<

$(BIN_DIR) :
	@echo "$(MINFO) Creating $(BIN_DIR)/ folder."
	@mkdir -p $(BIN_DIR)

$(LIB_DIR) :
ifdef LIBS
	@echo "$(MINFO) Creating $(LIB_DIR)/ folder."
	@mkdir -p $(LIB_DIR)
endif

lib_comp : $(LIB_DIR)
	@clear
	@echo "$(MINFO) CHECK \033[1;35mlibft\033[0m"
	@make -C libft PATH=../$(LIB_DIR)
	@mv libft/libft.a $(LIB_DIR)/libft.a

	@echo "$(MINFO) CHECK \033[1;35mlibvector\033[0m"
	@make -C libvector PATH=../$(LIB_DIR)
	@mv libvector/libvector.a $(LIB_DIR)/libvector.a

	@echo "$(MINFO) CHECK \033[1;35mlibmlx\033[0m"
	@make -C libmlx PATH=../$(LIB_DIR)
	@mv libmlx/libmlx.a $(LIB_DIR)/libmlx.a

clean :
	@echo "$(MINFO) Removing .o"
	@rm -rf $(BIN_DIR)
	@make -C libft clean
	@make -C libvector clean
	@make -C libmlx clean

lclean :
	@echo "$(MINFO) Removing $(LIB_DIR) folder."
	@rm -rf $(LIB_DIR);

fclean : clean lclean
	@rm -rf $(NAME)
	@echo "$(MINFO) Removing $(PATH_OUT)/$(NAME)"

re : fclean all

.PHONY : all clean re fclean clean
