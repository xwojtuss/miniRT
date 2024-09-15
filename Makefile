CC = cc

CFLAGS = -Wall -Wextra -Werror

INCLUDES = -Iincludes -Ilibs/mlx_linux -Ilibs/libft
LIBFT = libs/libft/libft.a
MLX_REPO = https://github.com/42Paris/minilibx-linux.git
LIBFT_REPO = https://github.com/xwojtuss/Libft.git
MINILIBX = libs/mlx_linux/libmlx.a
LIBS = ${LIBFT} ${MINILIBX} -lm -lX11 -lXext

NAME = miniRT
#NAME_BONUS = miniRT_bonus

SRCS = main.c misc.c math/vectors.c objects/cylinder.c \
	objects/plane.c objects/sphere.c objects/camera.c \
	objects/light.c objects/ambient.c check_scene.c \
	errors.c free.c parse.c render.c debug.c math/angles.c \
	debug2.c

SRCS_FILES = $(addprefix srcs/, ${SRCS})

OBJS = ${SRCS_FILES:.c=.o}
OBJSB = ${SRCSB_FILES:.c=.o}

all: ${NAME} ${NAME_BONUS}

bonus: ${NAME_BONUS}

${NAME}: ${LIBFT} ${MINILIBX} ${OBJS}
	${CC} ${CFLAGS} -o ${NAME} ${OBJS} ${LIBS} ${INCLUDES}

${NAME_BONUS}: ${LIBFT} ${MINILIBX} ${OBJSB}
	${CC} ${CFLAGS} -o ${NAME_BONUS} ${OBJSB} ${LIBS} ${INCLUDES}

%.o: %.c
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

.PHONY: all bonus clean fclean re
