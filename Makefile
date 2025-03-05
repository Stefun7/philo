NAME = philo

CC = cc

CFLAGS = -Wall -Wextra -Werror -I${INC} -g

LIBFT = ./Libft/libft.a

INC = inc/philo.h

SRCS = $(wildcard src/*.c)

OBJS = $(SRCS:.c=.o)

all : $(NAME)

%.o : %.c
	${CC} ${CFLAGS} -c -o $@ $<

$(LIBFT):
	@make -C ./Libft

$(NAME) : $(OBJS) $(LIBFT)
	${CC} $(OBJS) ${LIBFT} -o ${NAME}

clean :
	$(RM) $(OBJS)
	@make clean -C ./Libft
fclean : clean
	$(RM) $(NAME)
	@make fclean -C ./Libft
re : fclean all


.PHONY : all clean fclean re