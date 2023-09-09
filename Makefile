# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ataouaf <ataouaf@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/07 23:49:52 by ataouaf           #+#    #+#              #
#    Updated: 2023/09/09 05:27:27 by ataouaf          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:= cub3D
CFLAGS	:= -Wextra -Wall -Werror -Wunreachable-code -Ofast
LIBMLX	:= MLX42/

INCLUDE = ./inc
OBJECTS = ./obj
PARSING = $(addprefix parsing/, parse.c utils.c rgb.c fill_map.c parse_map1.c free.c ft_utils.c)
GNL = $(addprefix get_next_line/, get_next_line.c get_next_line_utils.c)

HEADERS	:= -I ./include -I $(LIBMLX)/include
LIBS	:= $(LIBMLX)/build/libmlx42.a -ldl -L$(glfw_path) -pthread -lm

FILES = $(PARSING) $(GNL) src/main.c
OBJS = $(addprefix $(OBJECTS)/, $(FILES:.c=.o))

all: $(NAME)

$(OBJECTS)/%.o: %.c $(INCLUDE)/cub3d.h
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS)

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(LIBS) $(HEADERS) -o $(NAME)

clean:
	rm -rf $(OBJECTS)

fclean: clean
	rm -rf $(NAME)

re: clean all

.PHONY: all clean fclean re