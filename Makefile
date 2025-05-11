NAME	=	push_swap

SRC	=	main.c	\
		push.c	\
		print.c	\
		swap.c	\
		rotate.c	\
		my_qsort_stack.c

CC	=	cc

CFLAGS	=	-Wall -Wextra -Werror -MMD -g3

INCLUDES	=	includes/
INCLUDES	+=	-I./printf/libft/
INCLUDES	+=	-I./printf/includes/

SRC_DIR	=	srcs/

BUILD	=	.build/

OBJ	=	$(addprefix $(BUILD), $(SRC:.c=.o))

DEPS	=	$(OBJ:.o=.d)

all:	$(NAME)

$(BUILD):
	@mkdir -p $@

printf/libftprintf.a:
	make bonus -C printf

$(NAME):	$(BUILD) $(OBJ) printf/libftprintf.a
	$(CC) $(OBJ) -o $@ -L./printf -lftprintf

$(BUILD)%.o:	$(SRC_DIR)%.c Makefile
	$(CC) $(CFLAGS) -c $< -o $@ -I $(INCLUDES)

clean:
	make clean -C printf
	rm -rf $(BUILD)

fclean:	clean
	make fclean -C printf
	rm -rf $(NAME)

re: fclean all

.PHONY: re all fclean clean

-include $(OBJ:.o=.d)

