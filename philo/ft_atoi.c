/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcedraz- <vcedraz-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 14:27:22 by vcedraz-          #+#    #+#             */
/*   Updated: 2023/05/07 15:13:56 by vcedraz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	convert_recursively(const char *a, unsigned int toi);
static int	local_is_whitespace(const char c);
static int	is_digit(const char c);

int	ft_atoi(const char *str)
{
	int	sign;

	while (local_is_whitespace(*str))
		str++;
	sign = 1;
	if (*str == '-')
		sign *= -1;
	if (sign == -1 || *str == '+')
		str++;
	return (convert_recursively(str, 0) * sign);
}

static int	local_is_whitespace(const char c)
{
	return (c == ' ' || ('\t' <= c && c <= '\r'));
}

static int	is_digit(const char c)
{
	return ((c >= '0' && c <= '9'));
}

static int	convert_recursively(const char *a, unsigned int toi)
{
	int	single_digit;

	if (!*a || local_is_whitespace(*a) || !is_digit(*a))
		return (toi);
	single_digit = *a - '0';
	toi = toi * 10 + single_digit;
	return (convert_recursively(a + 1, toi));
}
