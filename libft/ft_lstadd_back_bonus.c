/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dedantas <dedantas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 15:01:39 by dedantas          #+#    #+#             */
/*   Updated: 2025/04/27 15:13:50 by dedantas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last;

	if (!lst || !new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	last = ft_lstlast(*lst);
	last->next = new;
}

/*int	main()
{
	t_list	*list = NULL;

	ft_lstadd_back(&list, ft_lstnew(ft_strdup("Hello")));
	ft_lstadd_back(&list, ft_lstnew(ft_strdup("Word")));

	t_list *current = list;
	while (current)
	{
		printf("%s\n", (char *)current->content);
		current = current->next;
	}
	while (list)
	{
		t_list	*temp = list;
		list = list->next;
		free(temp->content);
		free(temp);
	}
	return (0);
}*/
