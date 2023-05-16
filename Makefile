all:
	make -C libft_gnl
	cc -g -Wall -Wextra -Werror -Ilibft_gnl/includes/ *.c libft_gnl/libft.a  -o philo

clean:
	rm -f philo

fclean: clean
	make clean -C libft_gnl

