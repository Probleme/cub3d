# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ataouaf <ataouaf@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/07 23:49:52 by ataouaf           #+#    #+#              #
#    Updated: 2023/10/11 05:58:21 by ataouaf          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= cub3D
CFLAGS	= -Wextra -Wall -Werror -Ofast
SANITIZE = #-g -fsanitize=address,undefined
LIBMLX	= ./MLX42

INCLUDE = ./inc
OBJECTS = ./obj
PARSING = $(addprefix parsing/, parse.c parse_map2.c utils.c extract.c parse_map1.c 2dmap.c)
DISPLAY = $(addprefix display/, draw.c utils.c minimap.c raycasting.c doors.c)
GNL = $(addprefix get_next_line/, get_next_line.c get_next_line_utils.c)

HEADERS	= -I ./include -I $(LIBMLX)/include
LIBS	= $(LIBMLX)/build/libmlx42.a -ldl $(GFLWFLAGS) -lglfw -pthread -lm

FILES = $(PARSING) $(GNL) $(DISPLAY) main.c ft_dprintf.c
OBJS = $(addprefix $(OBJECTS)/, $(FILES:.c=.o))

all: libmlx $(NAME)

libmlx:
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

$(OBJECTS)/%.o: %.c $(INCLUDE)/cub3d.h
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(SANITIZE) -o $@ -c $< $(HEADERS)

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(LIBS) $(HEADERS) $(SANITIZE) -o $(NAME)

clean:
	rm -rf $(OBJECTS)
	rm -rf $(LIBMLX)/build

fclean: clean
	rm -rf $(NAME)

re: clean all

.PHONY: all libmlx clean fclean re