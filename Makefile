# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ckurt <ckurt@student.42lyon.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/08 10:31:23 by ckurt             #+#    #+#              #
#    Updated: 2021/03/09 13:39:31 by ckurt            ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

_END=\033[0m
_BOLD=\033[1m
_UNDER=\033[4m
_REV=\033[7m

_RED=\033[31m
_GREEN=\033[32m
_YELLOW=\033[33m
_BLUE=\033[34m
_PURPLE=\033[35m
_CYAN=\033[36m
_WHITE=\033[37m

_IGREY=\033[40m
_IRED=\033[41m
_IGREEN=\033[42m
_IYELLOW=\033[43m
_IBLUE=\033[44m
_IPURPLE=\033[45m
_ICYAN=\033[46m
_IWHITE=\033[47m

NAME = miniRT
CC = gcc
CFLAGS = -Wall -Wextra -Werror -Iminilibx -O3 -fno-builtin
LDFLAGS = -lmlx -lm -framework OpenGL -framework AppKit -L. -lft
LIBC = ar rcs
SRCS =	srcs/utils/utils.c srcs/utils/cylinder_utils.c srcs/utils/utils2.c srcs/utils/cylinder_utils2.c \
		srcs/utils/operations2.c srcs/utils/operations.c srcs/utils/rgb.c srcs/utils/utils3.c srcs/utils/cylinder_utils3.c \
		srcs/raytracing/raytrace_sphere.c srcs/raytracing/raytrace_triangle.c srcs/render/multithreading.c srcs/render/render.c \
		srcs/raytracing/raytracing.c srcs/raytracing/raytrace_plane.c srcs/raytracing/raytrace_cylinder.c \
		srcs/raytracing/raytrace_square.c srcs/raytracing/raytracing_utils.c \
		srcs/parsing/parsing.c srcs/parsing/checks.c srcs/parsing/getters.c \
		srcs/scene/objects.c srcs/scene/scene.c srcs/scene/objects2.c\
		srcs/minirt.c srcs/vector.c srcs/errors.c \
		srcs/events.c srcs/window.c srcs/inits.c srcs/save.c \
		srcs/vector2.c srcs/render/render_utils.c \
		
OBJS = $(SRCS:.c=.o)

%.o: %.c ./includes/minirt.h
	@printf "$(_PURPLE)[$(NAME)] $(_END)$(_CYAN)[+] $(_END)Compiling $(_BLUE)owo$(_END) | $(_CYAN)$<$(_END)\n" | tr "lr" "w"
	@$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

all: $(NAME)

bonus: CFLAGS += -DBONUS
bonus: rebonus
bonus: all

rebonus:
	@$(RM) srcs/render/*.o srcs/raytracing/raytrace_cylinder.o

$(NAME): $(OBJS)
	@$(MAKE) -C ./libft
	#@$(MAKE) -C ./minilibx
	@cp ./libft/libft.a ./
	#@cp ./minilibx/libmlx.dylib ./
	@$(CC) $(CFLAGS) $(LDFLAGS) -o $(NAME) $(OBJS)
	@printf "$(_GREEN)[$(NAME)][DONE]$(_END) Fiwniwshed uwu!\n"

test: $(OBJS)
	@$(MAKE) -C ./libft
	@$(MAKE) -C ./minilibx
	@cp ./libft/libft.a ./
	@cp ./minilibx/libmlx.dylib ./
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(NAME) $(OBJS) && ./$(NAME)

re: fclean
	@$(MAKE) re -C ./libft
	@$(MAKE) all
	
clean:
	@rm -rf $(OBJS)
	@$(MAKE) clean -C ./libft
	@$(MAKE) clean -C ./minilibx
	@printf "$(_RED) [-] $(_END) Cleaned libft, minilibx and objects\n" | tr "lr" "w"

fclean: 
	@rm -f $(NAME)
	@rm -rf $(OBJS)
	@rm -f libmlx.a
	@rm -f libft.a
	@$(MAKE) fclean -C ./libft
	@$(MAKE) clean -C ./minilibx
	@printf "$(_CYAN)[$(NAME)] [-] $(_END)$(_UNDER)$(_GREEN)Everything clean now uwu$(_END)\n" | tr "lr" "w"

norme:
	@norminettev2 srcs/ includes libft/