/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dedantas <dedantas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 15:03:33 by dedantas          #+#    #+#             */
/*   Updated: 2025/05/09 17:54:05 by dedantas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_putnbr(int n)
{
	int	t;

	t = 0;
	if (n == -2147483648)
	{
		return (write(1, "-2147483648", 11));
	}
	if (n < 0)
	{
		t += ft_putchar('-');
		n = -n;
	}
	if (n > 9)
		t += ft_putnbr(n / 10);
	t += ft_putchar(n % 10 + '0');
	return (t);
}

int	ft_putnbr_u(unsigned int n)
{
	int	t;

	t = 0;
	if (n > 9)
		t += ft_putnbr(n / 10);
	t += ft_putchar(n % 10 + '0');
	return (t);
}

int	ft_putnbr_base(unsigned int n, char *base)
{
	unsigned int	len;
	unsigned int	base_len;

	len = 0;
	base_len = 0;
	while (base[base_len])
	{
		base_len++;
	}
	if (base_len < 2)
		return (0);
	if (n >= base_len)
	{
		len += ft_putnbr_base(n / base_len, base);
	}
	len += ft_putchar(base[n % base_len]);
	return (len);
}

static int	ft_putnbr_hex(unsigned long n)
{
	char	*hex;
	int		len;

	hex = "0123456789abcdef";
	len = 0;
	if (n >= 16)
		len += ft_putnbr_hex(n / 16);
	len += ft_putchar(hex[n % 16]);
	return (len);
}

int	ft_putpointer(void *ptr)
{
	int	len;

	if (ptr == NULL)
		return (write(1, "(nil)", 5));
	len = ft_putstr("0x");
	len += ft_putnbr_hex((unsigned long)ptr);
	return (len);
}
