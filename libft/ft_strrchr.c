/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dedantas <dedantas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 14:18:42 by dedantas          #+#    #+#             */
/*   Updated: 2025/04/17 12:54:42 by dedantas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	unsigned char	buscado;
	const char		*ultima;

	ultima = NULL;
	buscado = (unsigned char)c;
	while (1)
	{
		if (*s == buscado)
		{
			ultima = s;
		}
		if (*s == '\0')
		{
			break ;
		}
		s++;
	}
	return ((char *)ultima);
}
