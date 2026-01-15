/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dedantas <dedantas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 14:20:00 by dedantas          #+#    #+#             */
/*   Updated: 2025/04/17 19:22:08 by dedantas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

/*int	main(void)
{
	char *s = "Hello !";
	char *s1 = "1";
	char *s2 = "lorem\tipsum\tdolor\nsit\namet\n";
	char *s3 = "";
	char *s4 = "\n\n\f\r\t  ";

	printf("7  Len of %s -> %zu\n", s, ft_strlen(s));
	printf("1  Len of %s -> %zu\n", s, ft_strlen(s1));
	printf("27 Len of %s -> %zu\n", s, ft_strlen(s2));
	printf("0  Len of %s -> %zu\n", s, ft_strlen(s3));
	printf("7  Len of %s -> %zu\n", s, ft_strlen(s4));
}*/
