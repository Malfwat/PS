NAME	=	push_swap

NAME_B	=	checker

SRC_M	=	main.c	\
			resolve.c	\
			cost.c	\
			push.c	\
			swap.c	\
			rotate.c\
			pair.c

SRC		=	utils.c	\
			lis.c	\
			my_qsort_stack.c\
			nb_parsing.c	\
			init.c

SRC_B	=	gnl/get_next_line.c	\
			gnl/get_next_line_utils.c	\
			swap_bonus.c	\
			push_bonus.c	\
			rotate_bonus.c	\
			main_bonus.c

CC	=	cc

CFLAGS	=	-Wall -Wextra -Werror -MMD -g3

INCLUDES	=	includes/
INCLUDES	+=	-I./printf/libft/
INCLUDES	+=	-I./printf/includes/

SRC_DIR	=	srcs/

BUILD	=	.build/

OBJ	=	$(addprefix $(BUILD), $(SRC:.c=.o))

OBJ_B	=	$(addprefix $(BUILD), $(SRC_B:.c=.o))

OBJ_M	=	$(addprefix $(BUILD), $(SRC_M:.c=.o))

DEPS	=	$(OBJ:.o=.d)

all:	$(NAME) $(NAME_B)

bonus:	$(NAME_B)

$(BUILD):
	@mkdir -p $@
	@mkdir -p $@/gnl

printf/libftprintf.a:
	make bonus -C printf

$(NAME_B):	$(BUILD) $(OBJ_B) $(OBJ) printf/libftprintf.a
	$(CC) $(OBJ) $(OBJ_B) -o $@ -L./printf -lftprintf

$(NAME):	$(BUILD) $(OBJ) $(OBJ_M) printf/libftprintf.a
	$(CC) $(OBJ) $(OBJ_M) -o $@ -L./printf -lftprintf

$(BUILD)%.o:	$(SRC_DIR)%.c Makefile
	$(CC) $(CFLAGS) -c $< -o $@ -I $(INCLUDES) -I./srcs/gnl/

clean:
	make clean -C printf
	rm -rf $(BUILD)

fclean:	clean
	make fclean -C printf
	rm -rf $(NAME) $(NAME_B)

re: fclean all

tester:	script.sh

script.sh:
	wget https://github.com/Malfwat/PS/blob/main/script.sh

.PHONY: re all fclean clean bonus

-include $(OBJ:.o=.d)
-include $(OBJ_B:.o=.d)
-include $(OBJ_M:.o=.d)

