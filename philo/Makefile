# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marvin <marvin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/03 02:23:29 by marvin            #+#    #+#              #
#    Updated: 2023/04/03 02:23:29 by marvin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME                    = philo
CC						= cc
SRCS                    = ./srcs/main.c \
						  ./srcs/check_philo.c \
						  ./srcs/philo_function.c \
						  ./srcs/philo_utils_1.c \
						  ./srcs/philo_utils_2.c \
						  ./srcs/philo_utils_3.c \
						  ./srcs/initialize_watcher.c
OBJS                    = $(SRCS:%.c=%.o)
FLAGS                   = -Wall -Wextra -Werror

all :   $(NAME)

$(NAME)     :   $(OBJS)
	$(CC) $(FLAGS) -o $(NAME) $(SRCS) -lpthread -I ./include/

clean   :
	rm -f $(OBJS)

fclean  :   clean
	rm -f $(NAME)

re  :   fclean all

.PHONY  :   all clean fclean re