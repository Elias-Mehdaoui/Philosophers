# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: emehdaou <emehdaou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/25 20:38:19 by emehdaou          #+#    #+#              #
#    Updated: 2024/12/04 18:11:29 by emehdaou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	philo

DIR_SRCS		=	srcs/

DIR_OBJS		=	objs

SRCS_NAMES		=	main.c	utils.c routine.c actions.c

OBJS_NAMES		=	${SRCS_NAMES:.c=.o}

SRCS			=	$(addprefix $(DIR_SRCS)/,$(SRCS_NAMES))

OBJS			=	$(addprefix $(DIR_OBJS)/,$(OBJS_NAMES))

HEAD			=	-Iincludes/ -Ilibft/includes

CC				=	cc

CFLAGS			=	-g3 -Wall -Werror -Wextra -pthread #-fsanitize=thread

MAKEFLAGS		=	--no-print-directory

all				:	${NAME}

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) ${HEAD} -o $(NAME)
	@echo "\033[34;5mphilo\033[0m"

$(DIR_OBJS)/%.o: $(DIR_SRCS)/%.c | $(DIR_OBJS)
	$(CC) $(CFLAGS) -c $< -o $@ $(HEAD)

$(DIR_OBJS):
	mkdir -p $(DIR_OBJS)

clean:
	rm -rf ${DIR_OBJS}
	rm -rf ${OBJS}

fclean:	clean
	rm -rf ${LIBFT}
	rm -rf ${NAME}

re:	fclean all

stop:
	rm -f ${NAME}

.PHONY:	all clean fclean re bonus
# .SILENT