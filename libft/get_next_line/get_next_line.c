/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dedantas <dedantas@student.42porto.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 15:44:34 by dedantas          #+#    #+#             */
/*   Updated: 2025/05/22 15:59:51 by dedantas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	find_newline(char *buffer, ssize_t read_bytes)
{
	ssize_t	i;

	i = 0;
	while (i < read_bytes)
	{
		if (buffer[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

static int	store_buffer(t_list **stash, char *buffer, ssize_t read_bytes)
{
	t_list	*node;
	char	*content;
	ssize_t	i;

	i = 0;
	if (read_bytes <= 0)
		return (0);
	while (i < read_bytes)
	{
		content = (char *) malloc(sizeof(char));
		if (!content)
			return (-1);
		*content = buffer[i];
		node = ft_lstnew(content);
		if (!node)
			return (free(content), -1);
		ft_lstadd_back(stash, node);
		i++;
	}
	return (1);
}

static size_t	count_until_nextline(t_list **stash)
{
	t_list	*cursor;
	size_t	size;

	size = 0;
	cursor = *stash;
	while (cursor)
	{
		size++;
		if (*(char *)cursor->content == '\n')
			cursor = NULL;
		else
			cursor = cursor->next;
	}
	return (size);
}

static char	*extract_line(t_list **stash)
{
	char	*line;
	t_list	*temp;
	size_t	size;
	size_t	i;

	size = count_until_nextline(stash);
	if (size > 0)
	{
		line = (char *) malloc(size + 1);
		if (!line)
			return (ft_lstclear(stash, free), NULL);
		i = 0;
		while (i < size && *stash)
		{
			line[i] = *(char *)(*stash)->content;
			temp = *stash;
			*stash = (*stash)->next;
			ft_lstdelone(temp, free);
			i++;
		}
		line[i] = '\0';
		return (line);
	}
	return (NULL);
}

char	*get_next_line(int fd)
{
	static t_list	*stash[1024];
	ssize_t			read_bytes;
	char			*buffer;
	int				result;
	int				found_nl;

	buffer = (char *)malloc(BUFFER_SIZE);
	if (!buffer)
		return (ft_lstclear(&stash[fd], free), NULL);
	read_bytes = 1;
	found_nl = 0;
	while (read_bytes > 0 && found_nl == 0)
	{
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		result = store_buffer(&stash[fd], buffer, read_bytes);
		if (read_bytes == -1 || result == -1)
		{
			ft_lstclear(&stash[fd], free);
			return (free(buffer), NULL);
		}
		found_nl = find_newline(buffer, read_bytes);
	}
	free(buffer);
	return (extract_line(&stash[fd]));
}
