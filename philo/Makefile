# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bberthod <bberthod@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/01 16:01:44 by blandineber       #+#    #+#              #
#    Updated: 2023/09/19 17:00:47 by bberthod         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	philo
CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror
RM			=	rm -f
HEADDIR		=	./includes/
SRCDIR		=	./srcs/

GREEN=\033[0;32m
RED=\033[0;31m
YELLOW=\033[0;43m
PINK=\033[0;35m
BLUE=\033[0;34m
END=\033[0m

SRCS		=	$(SRCDIR)main.c\
				$(SRCDIR)utils.c\
				$(SRCDIR)init.c\
				$(SRCDIR)threads.c\
				$(SRCDIR)eat_sleep.c\
				$(SRCDIR)death.c\

OBJS			=	$(SRCS:.c=.o)

%.o:		%.c
		@$(CC) $(CFLAGS) -c $< -o $(<:.c=.o) -I$(HEADDIR)

$(NAME):	$(OBJS)
		@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -I$(HEADDIR)
		@echo "	$(GREEN)-- $(NAME) compiled --$(END)"

all:	$(NAME)

clean:
		@$(RM) $(OBJS) $(BONUSOBJS)
		@echo "	$(PINK)--   All objects removed   --$(END)"

fclean:		clean
		@$(RM) $(NAME) $(BNAME)
		@echo "	$(RED)-- All executables removed --$(END)"

re:			fclean all

.PHONY:		all re clean fclean bonus
