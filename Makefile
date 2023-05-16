all:
	make -C printf_libft_gnl lib
	cc -g -Wall -Wextra -Werror -Iprintf_libft_gnl/includes/ *.c printf_libft_gnl/libftprintf.a 
