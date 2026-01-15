/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dedantas <dedantas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 15:07:26 by dedantas          #+#    #+#             */
/*   Updated: 2025/04/15 15:07:29 by dedantas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	if (n == -2147483648)
	{
		write(fd, "-2147483648", 11);
		return ;
	}
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		n = -n;
	}
	if (n > 9)
		ft_putnbr_fd(n / 10, fd);
	ft_putchar_fd(n % 10 + '0', fd);
}

/*int     main(void)
{
        ft_putnbr_fd(404, 1);
        write(1, "\n", 1);
        ft_putnbr_fd(-2147483648, 1);
        write(1, "\n", 1);
        ft_putnbr_fd(2147483647, 1);
        write(1, "\n", 1);
        ft_putnbr_fd(0, 1);
}*/
