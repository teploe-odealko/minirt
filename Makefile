# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bashleig <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/16 12:28:49 by bashleig          #+#    #+#              #
#    Updated: 2020/12/01 13:17:19 by bashleig         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = miniRT

# directories
SRC_DIR  = srcs
HEADER  = includes
OBJ_DIR  = obj
INSLUDES = -I $(HEADER) -I $(LIBFT)

SRCS = main.c \
		parser.c \
		parser_utils.c \
		utils.c \
		math_utils.c \
		general_elements_parser.c \
		shapes_parser.c \
		errors_handler.c

OBJ		= $(addprefix $(OBJ_DIR)/,$(SRCS:.c=.o))

includes = $(wildcard includes/*.h)

# compiler
CC		= gcc
CFLAGS	= -Wall -Wextra -Werror -I$(HEADER)
LFLAGS			= -L libft -lft

LIBFT 			= libft

# rules
all: $(NAME)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o:$(SRC_DIR)/%.c $(includes)
	$(CC) $(CFLAGS) -o $@ -c $<

$(NAME): $(OBJ_DIR) $(OBJ)
	ar rcs $(NAME) $(OBJ)


%.o: %.c
				$(CC) $(CFLAGS) -I $(HEADER) -o $@ -c $<
test:
	make -s -C $(LIBFT)
	$(CC) -g $(CFLAGS)  $(INSLUDES) $(LFLAGS) $(addprefix $(SRC_DIR)/,$(SRCS)) -o $(NAME) -lmlx -framework OpenGL -framework AppKit

debug:
	make -s -C $(LIBFT)
	$(CC) -g $(CFLAGS)  $(INSLUDES) $(LFLAGS) $(addprefix $(SRC_DIR)/,$(SRCS)) -o main.c -lmlx -framework OpenGL -framework AppKit


clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclen re test
