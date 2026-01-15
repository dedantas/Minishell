/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dedantas <dedantas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 15:06:19 by dedantas          #+#    #+#             */
/*   Updated: 2025/04/27 15:09:21 by dedantas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int	count;

	count = 0;
	while (lst)
	{
		count++;
		lst = lst->next;
	}
	return (count);
}

/*int	main()
{
	t_list *list = NULL;

	ft_lstadd_front(&list, ft_lstnew(strdup("Hello")));
	ft_lstadd_front(&list, ft_lstnew(strdup("Word")));

	int	size = ft_lstsize(list);
	printf("Tamanho: %d\n", size);

	while (list)
	{
		t_list	*temp = list;
		list = list->next;
		free(temp->content);
		free(temp);
	}
	return (0);
}*/
