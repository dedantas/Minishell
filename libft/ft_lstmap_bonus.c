/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dedantas <dedantas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 15:03:23 by dedantas          #+#    #+#             */
/*   Updated: 2025/04/27 15:41:56 by dedantas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	t_list	*new_node;
	void	*content;

	if (!lst || !f)
		return (NULL);
	new_list = NULL;
	while (lst)
	{
		content = f(lst->content);
		new_node = ft_lstnew(content);
		if (!new_node)
		{
			del(content);
			ft_lstclear(&new_list, del);
			return (NULL);
		}
		ft_lstadd_back(&new_list, new_node);
		lst = lst->next;
	}
	return (new_list);
}

/*static void	*to_uppercase(void *content)
{
	char	*str = (char *)content;
	char	*new_str = ft_strdup(str);
	for (int i = 0; new_str[i]; i++)
	{
		new_str[i] = ft_toupper(new_str[i]);
	}
	return new_str;
}

int	main()
{
	t_list	*list = NULL;

	ft_lstadd_back(&list, ft_lstnew(ft_strdup("Hello")));
	ft_lstadd_back(&list, ft_lstnew(ft_strdup("Word")));

	t_list	*upper = ft_lstmap(list, to_uppercase, free);

	ft_lstiter(list, print_str);
	ft_lstiter(upper, print_str);
	ft_lstclear(&list, free);
	ft_lstclear(&upper, free);

	return (0);
}*/
