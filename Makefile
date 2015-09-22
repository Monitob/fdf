
CC = gcc

NAME = fdf

INC = /usr/include
CFLAGS = -Wall -Wextra -Werror -I$(INC) -O3 -Iminilibx/                                                                                                                                                           
LIBMLX	=  -L./minilibx/ -lmlx -lXext -lX11 -lm

PATH_SRC = ./src
PATH_OBJ = ./obj
PATH_INC = ./includes

SRC = main.c 

OBJ = $(patsubst %.c, $(PATH_OBJ)/%.o, $(SRC))

all:  lib $(NAME)

lib:
	@make -C libft

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) -L./libft/  \
		$(LIBMLX) -L/usr/lib/ -lft

$(PATH_OBJ)/%.o: $(addprefix $(PATH_SRC)/, %.c)
	@mkdir -p $(PATH_OBJ)
	@$(CC) $(CFLAGS) -o $@ -I $(PATH_INC) -Ilibft -c $<
	@echo Compiling object : $<

clean:
	@$(MAKE) -C libft $@
	@rm -f $(OBJ)

fclean:	clean
	@$(MAKE) -C libft $@
	@rm -f $(OBJ)
	@rm -rf $(PATH_OBJ)
	@rm -f $(NAME)

re: fclean all

.PHONY: re, clean, fclean
