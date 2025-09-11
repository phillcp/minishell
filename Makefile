NAME	=	minishell
CC		=	@cc
AR		=	@ar rcs
CFLAGS	=	-Wall -Wextra -Werror -MMD -MP -g

BIN_DIR	=	bin/
SRC_DIR	=	src/
INC_DIR	=	inc/
LIB_DIR	=	lib/
OBJ_DIR	=	obj/
DEP_DIR	=	dep/
LIBFT_DIR = $(LIB_DIR)libft/

SRC 	=	main.c \
			builtins/cd.c \
			builtins/echo.c \
			builtins/env.c \
			builtins/execve_aux.c \
			builtins/execve.c \
			builtins/export_aux.c \
			builtins/export.c \
			builtins/pwd.c \
			builtins/exit.c \
			builtins/unset.c \
			execution/cmd_selectors.c \
			execution/exec_aux.c \
			execution/exec_aux2.c \
			execution/exec_error.c \
			execution/exec.c \
			parsing/create_tokens_aux.c \
			parsing/create_tokens_word.c \
			parsing/create_tokens.c \
			parsing/expand_word.c \
			parsing/expand.c \
			parsing/free_parse.c \
			parsing/parse_cmd.c \
			parsing/parser.c \
			parsing/redirections.c \
			parsing/validate.c \
			utils/env_utils.c \
			utils/env_utils2.c \
			utils/file_input.c \
			utils/file_output.c \
			utils/free_utils.c \
			utils/heredoc.c \
			utils/heredoc_aux.c \
			utils/main_utils.c \
			utils/main_utils2.c
SRCS	= $(addprefix $(SRC_DIR), $(SRC))
OBJS	= $(patsubst $(SRC_DIR)%, $(OBJ_DIR)%,$(SRCS:.c=.o))
DEPS	= $(patsubst $(SRC_DIR)%, $(DEP_DIR)%,$(SRCS:.c=.d))

LIBFT	= $(LIBFT_DIR)$(BIN_DIR)/libft.a
INC_DIRS = $(INC_DIR)
INC_DIRS += $(LIBFT_DIR)$(INC_DIR)
INCS	= $(addprefix -I, $(INC_DIRS))

RDLINE_FLAG = -lreadline
INCS	+= -I/usr/include/readline

RESET	= \033[0m
BOLD	= \033[1m
RED		= \033[31m
GREEN	= \033[32m
YELLOW	= \033[33m
BLUE	= \033[34m


all: $(BIN_DIR)$(NAME)

$(OBJ_DIR) $(DEP_DIR):
	@mkdir -p $@

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(dir $@) $(dir $(DEP_DIR)$*.d)
	$(CC) $(CFLAGS) ${INCS} -c $< -o $@ -MF $(DEP_DIR)$*.d || { echo "$(RED)Failed to create obj/dep$(RESET)"; exit 1;}
	@echo "$(BOLD)$(YELLOW)File $< compiled$(RESET)"

$(LIBFT):
	@echo "$(BOLD)$(YELLOW)Building libft$(RESET)"
	@$(MAKE) -s -C $(LIBFT_DIR) all

$(BIN_DIR)$(NAME): $(OBJS) $(LIBFT)
	@echo "$(BOLD)$(YELLOW)Creating program$(RESET)"
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) ${INCS} $(OBJS) $(LIBFT) -o $@ $(RDLINE_FLAG) || { echo "$(RED)Failed to create program$(RESET)"; exit 1; }
	@echo "$(BOLD)$(GREEN)Program compiled succesfully$(RESET)"

clean:
	@if [ -d $(OBJ_DIR) ] || [ -d $(DEP_DIR) ]; then \
		echo "$(BOLD)$(YELLOW)Cleaning$(RESET)"; \
		rm -rf $(OBJ_DIR) $(DEP_DIR); \
		echo "$(BOLD)$(GREEN)Clean$(RESET)"; \
	else \
		echo "$(BOLD)$(BLUE)No objs or deps to clean$(RESET)"; \
	fi

fclean: clean
	@rm -rf $(BIN_DIR)
	@$(MAKE) -s -C $(LIBFT_DIR) fclean
	
re: fclean all

.PHONY: all re clean fclean

-include ${DEPS}
