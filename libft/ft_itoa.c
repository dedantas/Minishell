/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dedantas <dedantas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 14:22:03 by dedantas          #+#    #+#             */
/*   Updated: 2025/04/10 14:22:05 by dedantas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_num_len(int n)
{
	int	len;

	len = 1;
	if (n < 0)
		len++;
	while (n / 10 != 0)
	{
		len++;
		n /= 10;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		len;
	int		is_neg;
	long	num;

	num = n;
	len = get_num_len(num);
	is_neg = (num < 0);
	if (is_neg)
		num = -num;
	str = (char *)malloc(len + 1);
	if (!str)
		return (NULL);
	str[len] = '\0';
	while (len-- > is_neg)
	{
		str[len] = (num % 10) + '0';
		num /= 10;
	}
	if (is_neg)
		str[0] = '-';
	return (str);
}
