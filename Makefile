NAME = fdf

SRC = fdf.c \
	fdf_parser.c \
	fdf_utils.c	\
	fdf_projection.c \
	fdf_drawline.c \
	fdf_mlx.c

SRC_TEST = test01.c \
	fdf_parser.c \
	fdf_utils.c	\
	fdf_projection.c \
	fdf_drawline.c

LIBDIR = ../libft
LIB = $(LIBDIR)/libft.a

MLXDIR = mlx_linux
MLX = $(MLXDIR)/libmlx.a

OBJDIR = .obj
OBJ = $(SRC:.c=.o)
OBJ := $(addprefix $(OBJDIR)/, $(OBJ))

OBJ_TEST = $(SRC_TEST:.c=.o)
OBJ_TEST := $(addprefix $(OBJDIR)/, $(OBJ_TEST))

CC = cc

CFLAGS = -Wall -Wextra -Werror -g
LDFLAGS = -I $(LIBDIR)/ -I $(MLXDIR)/
MLXFLAGS = -L$(MLX_DIR) -lmlx -L/user/include -lXext -lX11 -lm -lbsd

$(NAME): $(LIB) $(MLX) $(OBJ)
	$(CC) -o $(NAME) $(CFLAGS) $(OBJ) $(LIB) $(MLX) $(LDFLAGS) $(MLXFLAGS)

all: $(LIB) $(OBJ) $(MLX) $(NAME)

$(OBJDIR)/%.o:%.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -c -o $@ $^ $(LDFLAGS)

$(LIB):
	make -sC $(LIBDIR)

$(MLX):
	make -sC $(MLXDIR)

test: $(LIB) $(MLX) $(OBJ_TEST)
	$(CC) -o fdf_test $(CFLAGS) $(OBJ_TEST) $(LIB) $(MLX) $(LDFLAGS) $(MLXFLAGS)

clean:
	rm -rf $(OBJDIR)
	make -sC $(LIBDIR) clean
	make -sC $(MLXDIR) clean

fcelan: clean
	rm -f $(NAME)
	make -sC $(LIBDIR) fclean
	rm -f fdf_test

re: fclean all

.PHONY: all clean fclean re test