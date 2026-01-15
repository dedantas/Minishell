/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dedantas <dedantas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 14:12:06 by dedantas          #+#    #+#             */
/*   Updated: 2025/04/17 18:54:34 by dedantas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	needle_len;

	if (*needle == '\0')
		return ((char *)haystack);
	needle_len = ft_strlen(needle);
	while (*haystack != '\0' && len >= needle_len)
	{
		if (ft_memcmp(haystack, needle, needle_len) == 0)
			return ((char *)haystack);
		haystack++;
		len--;
	}
	return (NULL);
}

/*int	main()
{
	printf("%s\n", ft_strnstr("lorem ipsum dolor sit amet", "ipsum", 15));
	printf("%s\n", ft_strnstr("lorem ipsum dolor sit amet", "dolor", 15));
	printf("%s\n", ft_strnstr("lorem ipsum dolor sit amet", "", 10));
	printf("%s\n", ft_strnstr("lorem ipsum dolor sit amet", "sit", 10));
	printf("%s\n", ft_strnstr("lorem ipsum dolor sit amet", "dolor", 0));

}*/
