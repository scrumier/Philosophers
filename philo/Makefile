# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: scrumier <scrumier@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/21 15:05:40 by scrumier          #+#    #+#              #
#    Updated: 2024/07/16 16:55:37 by scrumier         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= philo
SRC_DIR	= src
SRC	= $(addprefix $(SRC_DIR)/, \
			check_args.c \
			dinner.c \
			error_handler.c \
			get.c \
			init_philo.c \
			message.c \
			monitor.c \
			one_philo.c \
			main.c \
			set.c \
			synchro.c \
			ft_usleep.c \
			utils.c)
OBJ_DIR	= .philo_obj
OBJ		= $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
CC		= cc
FLAGS	= -Wall -Wextra -Werror -O3 -Iincludes
RM		= rm -rf

all: $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c Makefile | $(OBJ_DIR)
	$(CC) $(FLAGS) -MMD -MP -c $< -o $@

$(OBJ_DIR):
	mkdir -p $@

-include $(OBJ:.o=.d)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) -o $@ $^

clean:
	$(RM) $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
