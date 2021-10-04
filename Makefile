# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akliek <akliek@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/20 12:19:35 by akliek            #+#    #+#              #
#    Updated: 2021/10/02 15:28:07 by akliek           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = gcc

CFLAGS = -Wall -Werror -Wextra

LFLAGS = -L$$HOME/.brew/opt/readline/lib -lreadline
CPFLAGS = -I$$HOME/.brew/opt/readline/include

LIBS = -lreadline

LIBFT_DIR = ./libft

SRC = *.c

OBJ :=  $(SRC:.c=.o)

all: $(NAME)

$(NAME):
		stty -echoctl 
		make -C $(LIBFT_DIR)
		$(CC) -c $(CFLAGS) $(CPFLAGS) $(SRC)
		$(CC) $(CFLAGS) $(LFLAGS) $(OBJ) $(LIBFT_DIR)/libft.a -o $(NAME) $(LIBS)

clean:
		make -C $(LIBFT_DIR) clean
		rm -rf $(OBJ)

fclean: clean
		make -C $(LIBFT_DIR) fclean
		rm -rf $(NAME)

re:	
		make fclean
		make all
