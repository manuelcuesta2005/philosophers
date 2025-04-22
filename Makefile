NAME = philo

CC = cc
CFLAGS = -Wall -Wextra -Werror 
AR = ar
ARFLAGS = rcs

SRC = src/init.c \
		src/parse.c\
		src/utils.c\
		src/philo_routine.c \
		src/monitor_philo.c \
		philo.c

SRCBJS = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(SRCBJS)
	$(CC) $(CFLAGS) $(SRCBJS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(SRCBJS)

fclean:
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re