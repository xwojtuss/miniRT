CC = cc

CFLAGS = -Wall -Wextra -Werror -g -O3 -D DEBUG_TOOLS=1

HEADERS = includes/mini_rt.h includes/phong_reflection.h
INCLUDES = -Iincludes -Ilibs/mlx_linux -Ilibs/libft
LIBFT = libs/libft/libft.a
MLX_REPO = https://github.com/42Paris/minilibx-linux.git
LIBFT_REPO = https://github.com/xwojtuss/Libft.git
MINILIBX = libs/mlx_linux/libmlx.a
LIBS = ${LIBFT} ${MINILIBX} -lm -lX11 -lXext

NAME = miniRT

S_DATA = check_scene.c errors.c free.c initialize.c misc.c parse.c
S_DEBUG = debug.c debug2.c debug3.c
S_MATH = angles.c colors.c vectors.c vectors2.c vectors3.c vectors4.c
S_MLX = mlx_hooks.c mlx_init.c mlx_misc.c textures.c
S_OBJECTS = ambient.c camera.c cone.c cylinder.c divide.c light.c plane.c sphere.c
S_RAYTRACING = check_intersections.c constants.c find_t.c intersection_misc.c \
		normal_vectors.c phong.c render.c uv_translate.c

SRCS = main.c $(addprefix data/, ${S_DATA}) \
		$(addprefix debug/, ${S_DEBUG}) \
		$(addprefix math/, ${S_MATH}) \
		$(addprefix mlx/, ${S_MLX}) \
		$(addprefix objects/, ${S_OBJECTS}) \
		$(addprefix raytracing/, ${S_RAYTRACING})

SRCS_FILES = $(addprefix srcs/, ${SRCS})

OBJS = ${SRCS_FILES:.c=.o}

all: ${NAME} ${NAME_BONUS}

${NAME}: ${LIBFT} ${MINILIBX} ${OBJS}
	${CC} ${CFLAGS} -o ${NAME} ${OBJS} ${LIBS} ${INCLUDES}

%.o: %.c ${HEADERS}
	${CC} ${CFLAGS} -c $< -o $@ ${INCLUDES}

$(SRCSB_DIR)/%.o: $(SRCSB_DIR)/%.c
	${CC} ${CFLAGS} -c $< -o $@ ${INCLUDES}

${LIBFT}:
	@if [ ! -d libs/libft ]; then \
		git clone ${LIBFT_REPO} libs/libft; \
	fi
	make -C libs/libft

${MINILIBX}:
	@if [ ! -d libs/mlx_linux ]; then \
		git clone ${MLX_REPO} libs/mlx_linux; \
		cd libs/mlx_linux; \
		bash configure; \
	fi
	make -C libs/mlx_linux

clean:
	rm -f ${OBJS} ${OBJSB}
	make -C libs/libft clean
	make -C libs/mlx_linux clean

fclean:
	rm -f ${OBJS} ${OBJSB}
	rm -f ${NAME} ${NAME_BONUS}
	rm -dfr libs/mlx_linux
	rm -dfr libs/libft

re: fclean all

remove_objects:
	rm -f ${OBJS} ${OBJSB}

again: remove_objects all

.PHONY: all clean fclean re again remove_objects
