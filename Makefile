CC		= clang
CFLAGS	= -Wall -Wextra -Werror -g
NAME	= minishell
LIBFT = ./libft/libft.a
LIBS = -L./libft -lft

SRC =	minishell.c \
		init.c \
		builtins/cmd_cd.c \
		builtins/cmd_echo.c \
		builtins/cmd_env.c \
		builtins/cmd_exit.c \
		builtins/cmd_export.c \
		builtins/cmd_export_2.c \
		builtins/cmd_export_3.c \
		builtins/cmd_pwd.c \
		builtins/cmd_unset.c \
		error.c \
		proces.c \
		lexer.c \
		lexer_part2.c \
		print/ft_printf.c \
		print/ft_printf_utils.c \
		print/ft_printf_error.c \
		print/ft_printf_utils_error.c \
		utils/utils.c \
		utils/utils_expand.c \
		utils/utils_str.c \
		utils/utils_split.c \
		utils/utils_split_p2.c \
		utils/utils_free.c \
		signaux.c \
		expand.c \
		expand_2.c

SRC_PATH = src/
OBJ_PATH = obj/

SRCS	= $(addprefix $(SRC_PATH), $(SRC))
OBJ		= $(SRC:.c=.o)
OBJS	= $(addprefix $(OBJ_PATH), $(OBJ))
INCS	= -I ./includes/

##========== COLORS ==========##

BASE_COLOR 	=		\033[0;39m
GRAY 		=		\033[0;90m
RED 		=		\033[0;91m
GREEN 		=		\033[0;92m
YELLOW 		=		\033[0;93m
BLUE 		=		\033[0;94m
MAGENTA		=		\033[0;95m
CYAN 		=		\033[0;96m
WHITE		=		\033[0;97m

##========== MODES ==========##

TIMER = 0.0
IS_PRINT = 1

ifdef DEBUG
    CFLAGS += -g
	DEBUG_MODE = 1
endif

ifdef FAST
	J4 = -j4
endif

NUM_SRC = $(words $(SRC))
$(eval NUM_SRC=$(shell expr $(NUM_SRC) - 1))
INDEX = 0
NUM_LINES_TO_CLEAR = 1

all: $(NAME) 

$(LIBFT):
	make bonus -C ./libft

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIBS) -lreadline

clean:
	make clean -C ./libft
	rm -f $(OBJ)
	rm -rf $(OBJ_PATH)

fclean: clean
	make fclean -C ./libft
	rm -f $(NAME)

re: fclean all

$(OBJ_PATH)%.o : $(SRC_PATH)%.c
##	@echo -e "\033[$(shell expr $(NUM_LINES_TO_CLEAR));H\033[K"
	@mkdir -p $(OBJ_PATH) / $(OBJ_PATH)/builtins / $(OBJ_PATH)/print / $(OBJ_PATH)/utils
ifeq ($(IS_PRINT),1)
	@sleep $(TIMER)
	@clear
	@echo "$(CYAN)Compiling MiniShell$(BASE_COLOR)"
	@echo "╔═══════════════════════════════════════════════════╗"
	@echo -n "║$(CYAN)"
	@echo -n "▓"
	@for i in $$(seq 1 $$(expr $(INDEX) \* 50 / $(NUM_SRC))); do \
        echo -n "▓"; \
	done
	@for i in $$(seq 1 $$(expr 50 - $(INDEX) \* 50 / $(NUM_SRC))); do \
        echo -n " "; \
	done
	@echo "$(BASE_COLOR)║" $(shell expr $(INDEX) \* 100 / $(NUM_SRC))%
	@echo "╚═══════════════════════════════════════════════════╝"
	@$(eval INDEX=$(shell expr $(INDEX) + 1))
	@echo "Compiling : $<"
	$(CC) $(CFLAGS) -c $< -o $@
else
	@$(CC) $(CFLAGS) -c $< -o $@
endif

.PHONY: all clean fclean re
