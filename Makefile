# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abizyane <abizyane@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/07 23:49:52 by ataouaf           #+#    #+#              #
<<<<<<< HEAD
#    Updated: 2023/09/21 09:25:24 by ataouaf          ###   ########.fr        #
=======
#    Updated: 2023/10/05 08:24:07 by abizyane         ###   ########.fr        #
>>>>>>> ca246a9c0555e22559a5a417e874b1675d44c3f7
#                                                                              #
# **************************************************************************** #

NAME	:= cub3D
<<<<<<< HEAD
CFLAGS	:= -Wextra -Wall -Werror #-g -Wunreachable-code -Ofast
=======
CFLAGS	:= -Wextra -Wall -Werror -g -Wunreachable-code -Ofast
>>>>>>> ca246a9c0555e22559a5a417e874b1675d44c3f7
SANITIZE := -g -fsanitize=address,undefined
LIBMLX	:= ./MLX42

INCLUDE = ./inc
OBJECTS = ./obj
PARSING = $(addprefix parsing/, parse.c parse_map2.c utils.c rgb.c fill_map.c parse_map1.c)
<<<<<<< HEAD
DISPLAY = $(addprefix display/, raycasting.c draw.c utils.c images.c)
=======
DISPLAY = $(addprefix display/, draw.c utils.c images.c minimap.c)
>>>>>>> ca246a9c0555e22559a5a417e874b1675d44c3f7
GNL = $(addprefix get_next_line/, get_next_line.c get_next_line_utils.c)

HEADERS	:= -I ./include -I $(LIBMLX)/include
LIBS	:= $(LIBMLX)/build/libmlx42.a -ldl $(GFLWFLAGS) -lglfw -pthread -lm

FILES = $(PARSING) $(GNL) $(DISPLAY) display/main.c
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