/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dedantas <dedantas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 14:17:18 by dedantas          #+#    #+#             */
/*   Updated: 2025/04/18 12:53:46 by dedantas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <stdio.h>
//#include <string.h>
#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s;

	d = (unsigned char *)dst;
	s = (const unsigned char *)src;
	if (!d && !s)
		return (0);
	while (n--)
		*d++ = *s++;
	return (dst);
}

/*int	main(void)
{
	char	v[] = "hello";
	char	v1[] = "World";

	printf("%s ->%p\n", v,  ft_memcpy(((void*)0), ((void*)0), 3));
	printf("%s ->%p\n", v,  memcpy(((void*)0), ((void*)0), 3));

}*/
