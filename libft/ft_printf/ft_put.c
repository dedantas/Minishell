/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dedantas <dedantas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 16:43:12 by dedantas          #+#    #+#             */
/*   Updated: 2025/05/22 16:46:40 by dedantas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_putchar(char c)
{
	return (write(1, &c, 1));
}

int	ft_putstr(char *s)
{
	int	n;

	n = 0;
	if (s == NULL)
		n += ft_putstr("(null)");
	else
		while (*s)
			n += write(1, s++, 1);
	return (n);
}
