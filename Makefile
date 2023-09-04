all:
	make -C libft_gnl --no-print-directory
	cc -g3 -lpthread -Wall -Wextra -Werror *.c libft_gnl/libft.a  -o philo

clean:
	rm -f philo

fclean: clean
	make clean -C libft_gnl

