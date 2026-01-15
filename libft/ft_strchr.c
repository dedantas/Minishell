/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dedantas <dedantas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 14:18:03 by dedantas          #+#    #+#             */
/*   Updated: 2025/04/18 13:03:34 by dedantas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <stdio.h>
//#include <string.h>
#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	while (*s != '\0')
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if ((char)c == '\0')
		return ((char *)s);
	return (NULL);
}

/*
int	main(void)
{
	char	*s = "Bonjour";

	printf("%p\n", strchr(s, 'b'));
	printf("my func-> %p\n\n", ft_strchr(s, 'b'));

	printf("%p\n", strchr(s, 'j'));
	printf("%p\n\n", ft_strchr(s, 'j'));

	printf("%p\n", strchr(s, 's'));
	printf("%p\n\n", ft_strchr(s, 's'));

	printf("%p\n", strchr(s, '\0'));
	printf("%p\n\n", ft_strchr(s, '\0'));

	char	*s1 = "";
	printf("%p\n", strchr(s1, '\0'));
	printf("%p\n\n", ft_strchr(s1, '\0'));
}
*/
