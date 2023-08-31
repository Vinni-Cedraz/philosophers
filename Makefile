all:
	make -C libft_gnl
	cc -g -lpthread -Wall -w -Wextra -Werror *.c libft_gnl/libft.a  -o philo

clean:
	rm -f philo

fclean: clean
	make clean -C libft_gnl

