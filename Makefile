# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akliek <akliek@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/20 12:19:35 by akliek            #+#    #+#              #
#    Updated: 2021/12/07 19:08:16 by akliek           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Name of the program
NAME = minishell

# Color codes
RESET	= \033[0m
GREEN	= \033[32m
YELLOW	= \033[33m
BLUE	= \033[34m

# Compiling flags
FLAGS = -Wall -Wextra -Werror
LFLAGS = -L$$HOME/.brew/opt/readline/lib -lreadline
CPFLAGS = -I$$HOME/.brew/opt/readline/include

#Libraries

LIBS = -lreadline

# Folders
SRC_DIR = ./src/
OBJ_DIR = ./obj/
INC_DIR = ./includes/
LIBFT_DIR = ./libft/

# Source files and object files
SRC_FILES = clean.c     	\
			env_vars_1.c	\
			env_vars_2.c	\
			error.c     	\
			executables.c 	\
			execute_cmd.c 	\
			minishell.c   	\
			parse_args.c  	\
			parse_cmd.c   	\
			parse_echo.c  	\
			parse_pipes.c 	\
			path.c        	\
			pipe.c        	\
			quotes.c      	\
			redirections.c 	\
			signals.c      	\
			spaces.c       	\
			str_arr.c      	\
			utils.c			

OBJ_FILES = $(SRC_FILES:.c=.o)

# Paths
SRC = $(addprefix $(SRC_DIR), $(SRC_FILES))
OBJ = $(addprefix $(OBJ_DIR), $(OBJ_FILES))
LIBFT = $(addprefix $(LIBFT_DIR), libft.a)

# all rule
all: obj $(LIBFT) $(NAME)

obj:
	@mkdir -p $(OBJ_DIR)
$(OBJ_DIR)%.o:$(SRC_DIR)%.c
	@gcc $(FLAGS) $(CPFLAGS) -I $(LIBFT_DIR) -I $(INC_DIR) -o $@ -c $<
$(LIBFT):
	@make -C $(LIBFT_DIR)

# Compiling
$(NAME): $(OBJ)
	@stty -echoctl
	@echo "$(YELLOW)\n      -> Building $(NAME) ...$(RESET)"
	@gcc $(LFLAGS) $(OBJ) $(LIBFT) -lm -o $(NAME) $(LIBS)
	@echo "$(GREEN)***   Project $(NAME) successfully compiled   ***\n$(RESET)"

# clean rule
clean:
	@echo "$(BLUE)***   Deleting all objects from $(NAME)   ...   ***$(RESET)"
	@rm -Rf $(OBJ_DIR)
	@make -C $(LIBFT_DIR) clean
	@echo

# fclean rule
fclean: clean
	@echo "$(BLUE)***   Deleting executable file from $(NAME)   ...   ***$(RESET)"
	@rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean
	@echo

# re rule
re: fclean all

# phony
.PHONY: all clean fclean re
