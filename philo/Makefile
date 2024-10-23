# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aklimchu <aklimchu@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/24 11:18:05 by aklimchu          #+#    #+#              #
#    Updated: 2024/10/22 10:28:38 by aklimchu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#Colors
DEF_COLOR = \033[0;39m
GRAY = \033[0;90m
RED = \033[0;91m
GREEN = \033[0;92m
YELLOW = \033[0;93m
BLUE = \033[0;94m
MAGENTA = \033[0;95m
CYAN = \033[0;96m
WHITE = \033[0;97m

# Program name
NAME		= philo

# Compiler
CC 			= cc
CFLAGS		= -Wall -Wextra -Werror
RM			= rm -f

# Source / OBJ files / Includes
SRC 		=	main.c \
				fill_struct.c \
				threads_tools.c \
				philo.c \
				mutex_tools.c \
				eating.c \
				free.c \
				threads_tools_extra.c
OBJ 		= $(SRC:.c=.o)
INCLUDE		= -I "./inc"

# Rules
all:		$(NAME)

%.o: %.c 
	$(CC) $(CFLAGS) $(INCLUDE) $^ -c -o $@

$(NAME):	$(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -lpthread $(INCLUDE) -o $(NAME)
	@echo "$(GREEN)SUCCESS, PHILO IS READY $(DEF_COLOR)"

clean:
	@echo "$(GREEN)Deleting object files... $(DEF_COLOR)"
	$(RM) $(OBJ)

fclean:		clean
	@echo "$(GREEN)Deleting philo... $(DEF_COLOR)"
	$(RM) $(NAME)
	@echo "$(GREEN)CLEAR $(DEF_COLOR)"

re: 		fclean all

.PHONY: 	all clean fclean re
