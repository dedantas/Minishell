/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dedantas <dedantas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 15:42:32 by dedantas          #+#    #+#             */
/*   Updated: 2025/05/22 15:42:56 by dedantas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_extract_line_from_buffer(char **buffer, size_t *line_len)
{
	char	*line;
	size_t	i;

	if (!buffer || !*buffer || !**buffer)
		return (NULL);
	i = 0;
	while ((*buffer)[i] && (*buffer)[i] != '\n')
		i++;
	if ((*buffer)[i] == '\n')
		i++;
	*line_len = i;
	line = malloc(i + 1);
	if (!line)
		return (NULL);
	return (line);
}

char	*ft_extract_line(char **buffer)
{
	char	*line;
	char	*new_buf;
	size_t	line_len;
	size_t	i;

	if (!buffer || !*buffer || !**buffer)
		return (NULL);
	line = ft_extract_line_from_buffer(buffer, &line_len);
	if (!line)
		return (cleanup_buffer(buffer));
	i = 0;
	while (i < line_len)
	{
		line[i] = (*buffer)[i];
		i++;
	}
	line[i] = '\0';
	new_buf = ft_strdup(*buffer + line_len);
	if (!new_buf)
		return (cleanup_buffer(buffer));
	free(*buffer);
	*buffer = new_buf;
	return (line);
}
