/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dedantas <dedantas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 15:01:14 by dedantas          #+#    #+#             */
/*   Updated: 2025/04/27 15:11:01 by dedantas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

/*int	main()
{
	t_list	*list = NULL;
	
	ft_lstadd_front(&list, ft_lstnew(strdup("Hello")));
	ft_lstadd_front(&list, ft_lstnew(strdup("Word")));

	t_list	*last = ft_lstlast(list);
	if (last)
	{
		printf("last: %s\n", (char *)last->content);
	}
	while (list)
	{
		t_list *temp = list;
		list = list->next;
		free(temp->content);
		free(temp);
	}
	return (0);
}*/
