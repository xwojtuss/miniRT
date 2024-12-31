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

SRCS = main.c misc.c math/vectors.c math/vectors2.c objects/cylinder.c \
	objects/plane.c objects/sphere.c objects/camera.c \
	objects/light.c objects/ambient.c check_scene.c \
	errors.c free.c parse.c raytracing/render.c debug/debug.c math/angles.c \
	debug/debug2.c debug/debug3.c initialize.c mlx/mlx_misc.c mlx/mlx_hooks.c \
	mlx/mlx_init.c math/vectors3.c math/vectors4.c raytracing/normal_vectors.c \
	raytracing/phong.c raytracing/check_intersections.c raytracing/intersection_misc.c \
	colors.c raytracing/find_t.c mlx/textures.c raytracing/constants.c \
	raytracing/get_texture.c objects/cone.c objects/divide.c

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
