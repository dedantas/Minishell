/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dedantas <dedantas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 14:05:31 by dedantas          #+#    #+#             */
/*   Updated: 2025/04/17 19:25:46 by dedantas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t		srclen;
	size_t		i;

	i = 0;
	srclen = ft_strlen(src);
	if (dstsize == 0)
		return (srclen);
	while (i < (dstsize - 1) && src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (srclen);
}

/*#include <stdio.h>

int main() {
    char src[] = "Hello, world!";
    char dst[20]; // Destino com espaço suficiente para copiar

    size_t copied = ft_strlcpy(dst, src, sizeof(dst));

    printf("Fonte: %s\n", src);
    printf("Destino: %s\n", dst);
    printf("Tamanho da fonte: %zu\n", copied);

    return 0;
}*/
