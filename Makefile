NAME	=	minishell
CC		=	@cc
AR		=	@ar rcs
CFLAGS	=	-Wall -Wextra -Werror -MMD -MP #-g

BIN_DIR	=	bin/
SRC_DIR	=	src/
INC_DIR	=	inc/
LIB_DIR	=	lib/
OBJ_DIR	=	obj/
DEP_DIR	=	dep/
LIBFT_DIR = $(LIB_DIR)/libft/

SRC 	=	main.c \
			commands/cd.c \
			commands/echo.c \
			commands/env.c \
			commands/execve.c \
			commands/export.c \
			commands/pwd.c \
			commands/unset.c \
			execution/command_exec.c \
			execution/execute_cmd.c \
			parser/aux.c \
			parser/cmd_spliter.c \
			parser/expand_question.c \
			parser/expand.c \
			parser/lstsort.c \
			parser/op_parser.c \
			parser/parser.c \
			parser/q_parser.c \
			parser/validator.c \
			utils/env_utils.c \
			utils/export_utils.c \
			utils/free_utils.c \
			utils/heredoc_mng.c \
			utils/input_mng.c \
			utils/main_utils.c \
			utils/main_utils2.c \
			utils/main_utils3.c \
			utils/output_mng.c \
			utils/selectors.c
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


all: $(BIN_DIR)$(NAME)

$(OBJ_DIR) $(DEP_DIR) $(BIN_DIR):
	@mkdir -p $@

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(dir $@) $(dir $(DEP_DIR)$*.d)
	$(CC) $(CFLAGS) ${INCS} -c $< -o $@ -MF $(DEP_DIR)$*.d || { echo "$(RED)Failed to create obj/dep$(RESET)"; exit 1;}

$(LIBFT):
	@echo "$(BOLD)$(YELLOW)Building libft$(RESET)"
	@$(MAKE) -C $(LIBFT_DIR) all

$(BIN_DIR)$(NAME): $(OBJS) $(LIBFT) | $(BIN_DIR)
	@echo "$(BOLD)$(YELLOW)Creating program$(RESET)"
	$(CC) $(CFLAGS) ${INCS} $(OBJS) $(LIBFT) -o $@ $(RDLINE_FLAG) || { echo "$(RED)Failed to create program$(RESET)"; exit 1; }
	@echo "$(BOLD)$(GREEN)Program compiled succesfully$(RESET)"

clean:
	@echo "$(BOLD)$(YELLOW)Deleting objs and deps$(RESET)"
	@rm -rf $(OBJ_DIR) $(DEP_DIR)
	@echo "$(BOLD)$(GREEN)Completed clean$(RESET)"

fclean: clean	
	@rm -rf $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all re clean fclean

-include ${DEPS}
