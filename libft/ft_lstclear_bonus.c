/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dedantas <dedantas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 15:04:39 by dedantas          #+#    #+#             */
/*   Updated: 2025/04/27 15:19:35 by dedantas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*current;
	t_list	*next;

	if (!lst || !del)
		return ;
	current = *lst;
	while (current)
	{
		next = current->next;
		ft_lstdelone(current, del);
		current = next;
	}
	*lst = NULL;
}

/*void	del_str(void *content)
{
	free(content);
}

int	main()
{
	t_list	*list = NULL;

	ft_lstadd_back(&list, ft_lstnew(ft_strdup("Hello")));
	ft_lstadd_back(&list, ft_lstnew(ft_strdup("Word")));

	ft_lstclear(&list, del_str);
	return (0);
}*/
