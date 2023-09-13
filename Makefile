# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ataouaf <ataouaf@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/07 23:49:52 by ataouaf           #+#    #+#              #
#    Updated: 2023/09/13 08:14:17 by ataouaf          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:= cub3D
CFLAGS	:= -Wextra -Wall -Werror -g -Wunreachable-code -Ofast
LDFLAGSss := -g -fsanitize=address,undefined
LIBMLX	:= ./MLX42

INCLUDE = ./inc
OBJECTS = ./obj
PARSING = $(addprefix parsing/, parse.c player.c parse_map2.c utils.c rgb.c fill_map.c parse_map1.c free.c ft_utils.c)
GNL = $(addprefix get_next_line/, get_next_line.c get_next_line_utils.c)

HEADERS	:= -I ./include -I $(LIBMLX)/include
LIBS	:= $(LIBMLX)/build/libmlx42.a -ldl -L/Users/ataouaf/homebrew/Cellar/glfw/3.3.8/lib -lglfw -pthread -lm

FILES = $(PARSING) $(GNL) display/main.c
OBJS = $(addprefix $(OBJECTS)/, $(FILES:.c=.o))

all: libmlx $(NAME)

libmlx:
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

$(OBJECTS)/%.o: %.c $(INCLUDE)/cub3d.h
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS)

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(LIBS) $(HEADERS) $(LDFLAGSss) -o $(NAME)

clean:
	rm -rf $(OBJECTS)
	rm -rf $(LIBMLX)/build

fclean: clean
	rm -rf $(NAME)

re: clean all

.PHONY: all libmlx clean fclean re