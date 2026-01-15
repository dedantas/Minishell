/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dedantas <dedantas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 15:20:49 by dedantas          #+#    #+#             */
/*   Updated: 2025/04/27 15:03:36 by dedantas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*new_node;

	new_node = (t_list *)malloc(sizeof(t_list));
	if (!new_node)
		return (NULL);
	new_node->content = content;
	new_node->next = NULL;
	return (new_node);
}

/*int	main(void)
{
	int	*num = malloc(sizeof(int));
	*num = 42;

	t_list *node = ft_lstnew(num);
	t_list *node1 = ft_lstnew(ft_strdup("Hello"));
	if (node && node1)
	{
		printf("cont: %d\n", *(int *)(node->content));
		free(node->content);
		free(node);
		printf("cont: %s\n", (char *)(node1->content));
		free(node1->content);
		free(node1);
	}

	return (0);
}*/
