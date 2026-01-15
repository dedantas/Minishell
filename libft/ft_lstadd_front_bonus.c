/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dedantas <dedantas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 14:59:38 by dedantas          #+#    #+#             */
/*   Updated: 2025/04/27 15:08:12 by dedantas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (!lst || !new)
		return ;
	new->next = *lst;
	*lst = new;
}

/*int	main()
{
	t_list *list = NULL;

	ft_lstadd_front(&list, ft_lstnew(ft_strdup("Hello")));
	ft_lstadd_front(&list, ft_lstnew(ft_strdup("Word")));

	t_list *current = list;
	while (current)
	{
		printf("%s\n", (char *)current->content);
		current = current->next;
	}
	while (list)
	{
		t_list *temp = list;
		list = list->next;
		free(temp);
	}
	return (0);
}*/
