# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jbartosi <jbartosi@student.42prague.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/15 13:56:55 by jbartosi          #+#    #+#              #
#    Updated: 2023/03/21 15:31:46 by jbartosi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g

LIBFT_FOL = Libft/
LIBFT = ${addprefix ${LIBFT_FOL}, libft.a}

PIPEX_FOL = pipex/
PIPEX = ${addprefix ${PIPEX_FOL}, pipex.a}

LIBS = ${LIBFT}

SRCS	=	minishell \
			prompt \
			commands \
			split_utils \
			animation \
			animation_utils

OBJ_FOL	=	objs/

SRC_FILES = ${addsuffix .c, ${SRCS}}

MAKE_FLGS = --no-print-directory --silent

# Colors
	NRM_COLOR = \033[0;39m

	GREEN = \033[0;92m
	YELLOW = \033[0;93m

##################################################################
##################################################################

all: ${NAME}

${LIBS}:
	@ make ${MAKE_FLGS} -C ${LIBFT_FOL}
	@ make ${MAKE_FLGS} -C ${PIPEX_FOL}
	@ echo "${GREEN}Finished making libraries :D${NRM_COLOR}"

${NAME}: ${LIBS} ${SRC_FILES}
	cc ${CFLAGS} ${SRC_FILES} ${LIBS} -I${LIBFT_FOL} -lreadline -o $@
	@ echo "${GREEN}${NAME} compiled :D${NRM_COLOR}"

clean:
	@ make ${MAKE_FLGS} fclean -C ${LIBFT_FOL}
	@ make ${MAKE_FLGS} fclean -C ${PIPEX_FOL}
	@ echo "${YELLOW}Cleaning Libs...${NRM_COLOR}"


fclean: clean
	@ rm -f ${NAME}
	@ echo "${YELLOW}Deleting ${NAME}... ${NRM_COLOR}"

re:	fclean all

.PHONY: re, fclean, clean
