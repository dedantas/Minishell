/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dedantas <dedantas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 15:16:10 by dedantas          #+#    #+#             */
/*   Updated: 2025/04/10 15:16:12 by dedantas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_in_set(char c, char const *set)
{
	while (*set)
		if (c == *set++)
			return (1);
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*start;
	char	*end;
	char	*new_str;
	size_t	len;

	if (!s1 || !set)
		return (NULL);
	start = (char *)s1;
	end = start + ft_strlen(s1);
	while (*start && is_in_set(*start, set))
		start++;
	while (end > start && is_in_set(*(end - 1), set))
		end--;
	len = end - start;
	new_str = malloc(len + 1);
	if (!new_str)
		return (NULL);
	ft_memcpy(new_str, start, len);
	new_str[len] = '\0';
	return (new_str);
}
