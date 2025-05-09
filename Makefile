NAME	=	ps

SRC	=	main.c	\
		my_qsort_stack.c

CC	=	cc

CFLAGS	=	-Wall -Wextra -Werror -MMD -g3

INCLUDES	=	includes/
INCLUDES	+=	-I./Printf/libft/
INCLUDES	+=	-I./Printf/includes/

SRC_DIR	=	srcs/

BUILD	=	.build/

OBJ	=	$(addprefix $(BUILD), $(SRC:.c=.o))

DEPS	=	$(OBJ:.o=.d)

all:	$(NAME)

$(BUILD):
	@mkdir -p $@

$(NAME):	$(BUILD) $(OBJ)
	$(CC) $(OBJ) -o $@ -L./Printf -lftprintf

$(BUILD)%.o:	$(SRC_DIR)%.c Makefile
	$(CC) $(CFLAGS) -c $< -o $@ -I $(INCLUDES)

clean:
	rm -rf $(BUILD)

fclean:	clean
	rm -rf $(NAME)

re: fclean all

.PHONY: re all fclean clean

-include $(OBJ:.o=.d)

