 # **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gselyse <gselyse@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/01 16:51:38 by ndeana            #+#    #+#              #
#    Updated: 2020/12/11 12:33:51 by gselyse          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	philo_two
DIR			=	./srcs
HEAD_DIR	=	./includes

FILES		=	philo_two.c	starting.c print_mess.c utils.c parsing.c

HEAD_FILE	=	philo_two.h			

SRCS		=	$(addprefix $(DIR)/, $(FILES))
HEADERS		=	$(addprefix $(HEAD_DIR)/, $(HEAD_FILE))
INCLUDES	=	-I$(HEAD_DIR)
OBJS		=	$(SRCS:.c=.o)
TAIL		=	-pthread

M_FLAGS		=	--no-print-directory
CC			=	gcc
CFLAGS		=	-Wall -Wextra -Werror -mcmodel=medium -g -O0 $(INCLUDES) 

all: $(NAME)

%.o: %.c $(HEADERS)
	@$(CC) $(CFLAGS) -c $< $(TAIL) -o $@
	@$(PRINT) "\r$(FGREEN)COMPILE: $<                   $(PNULL)"

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(TAIL)
	@$(PRINT) "\r$(FGREEN)MAKE: ${NAME}                 $(PNULL)\n"

clean:
	@$(PRINT) "$(addprefix \n$(FRED)REMOVE: $(FYELLOW), $(FILES:.c=.o))$(PNULL)"
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)
	@$(PRINT) "\n$(FRED)REMOVE: $(FYELLOW)$(NAME)$(PNULL)"

re:	fclean lib all

norme:
	@norminette $(SRCS) $(HEADERS) | awk '{sub(/Norme/,"$(FGREEN)Norme$(PNULL)")}1'\
								| awk '{sub(/Error/,"$(FRED)Error$(PNULL)")}1'

run: all
	@./$(NAME)

.PHONY: all clean fclean re norme run lib

# **************************************************************************** #
#								Utilits										   #
# **************************************************************************** #

# Цвета шрифта
FBLACK		= \033[30m
FRED		= \033[31m
FGREEN		= \033[32m
FYELLOW		= \033[33m
FBLUE		= \033[34m
FMAGENTA	= \033[35m
FCYAN		= \033[36m
FGREY		= \033[37m

# Цвета фона
BGBLACK		= \033[40m
BGRED		= \033[41m
BGGREEN		= \033[42m
BGYELLOW	= \033[43m
BGBLUE		= \033[44m
BGMAGENTA	= \033[45m
BGCYAN		= \033[46m
BGGREY		= \033[47m

# Свойства текста
PBOLD		= \033[1m#	жирный шрифт
PDBOLD		= \033[2m#	полу яркий цвет
PNBOLD		= \033[22m#	нормальная интенсивность
PUNDERLINE	= \033[4m#	подчеркивание
PBLINK		= \033[5m#	мигание
PINVERSE	= \033[7m#	инверсия
PNULL		= \033[0m#	отмена

PRINT		= printf
