NAME	= philo
FLAGS	= -Wall -Wextra -Werror -pthread -g3 -Iinclude/ -fsanitize=thread

OBJ_PATH = objs/

Green = "\033[0;32m"
endCollor = "\033[0m"

SRCS = allocate_meta_data.c \
	   create_the_thinkers.c \
	   philo_thread_callback.c \
	   philosopher_actions.c \
	   ft_atoi.c \
	   ft_lst_circular.c \
	   get_time_in_ms.c \
	   monitor_the_thinkers.c \
	   output_state.c \
	   lock_unlock_forks.c \
	   am_i_dying.c \
	   main.c \

OBJS = $(SRCS:%.c=$(OBJ_PATH)%.o)

all: $(OBJ_PATH) $(NAME) 

$(OBJ_PATH)%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

$(OBJ_PATH):
	mkdir -p $(OBJ_PATH)

$(NAME): $(OBJS)
	@printf "\n";
	$(CC) $(FLAGS) $^ -o $@
	@printf "\nexecutable "$(Green)"philo"$(endCollor)" created\n";

clean:
	rm -rf $(OBJ_PATH)

fclean: clean
	rm -f $(NAME)

re: fclean all
