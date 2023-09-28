CC := gcc
NAME := cub
CFLAGS := -Wextra -Wall -g -fsanitize=address -Ofast
LIBMLX := $(HOME)/MLX42
LIBS := libmlx42.a -ldl -lglfw -pthread -lm -lX11 -lXrandr -lXi -lXxf86vm -lXinerama -lXcursor
SRCS := parsing/parse.c\
		parsing/parse_map2.c\
		parsing/utils.c\
		parsing/rgb.c\
    	parsing/fill_map.c\
		parsing/parse_map1.c\
		display/raycasting.c\
		display/images.c\
    	display/utils.c\
		display/main.c\
		display/minimap.c\
		get_next_line/get_next_line.c\
		get_next_line/get_next_line_utils.c


OBJS := ${SRCS:.c=.o}

all: $(NAME)

%.o: %.c cub3d.h
	@$(CC) $(CFLAGS) -Imlx -o $@ -c $<

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBS) $(framework) -L"/usr/lib64/libglfw.so.3" -o $(NAME)

clean:
	@rm -rf $(OBJS)

fclean: clean
	@rm -rf $(NAME)

re: clean all
