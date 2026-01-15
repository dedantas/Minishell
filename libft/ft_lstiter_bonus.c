/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dedantas <dedantas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 15:05:08 by dedantas          #+#    #+#             */
/*   Updated: 2025/04/27 15:25:20 by dedantas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	if (!f)
		return ;
	while (lst)
	{
		f(lst->content);
		lst = lst->next;
	}
}

/*static void	print_str(void *content)
{
	if (content)
		printf("cont: %s\n", (char*)content);
}

int	main()
{
	t_list *list = NULL;

	ft_lstadd_back(&list, ft_lstnew(ft_strdup("Hello")));
	ft_lstadd_back(&list, ft_lstnew(ft_strdup("Word")));

	ft_lstiter(list, print_str);

	ft_lstclear(&list, free);
	return (0);
}*/
