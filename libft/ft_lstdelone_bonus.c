/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dedantas <dedantas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 15:05:25 by dedantas          #+#    #+#             */
/*   Updated: 2025/04/27 15:17:23 by dedantas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (!lst || !del)
		return ;
	del(lst->content);
	free(lst);
}

/*static void	del_str(void *content)
{
	free(content);
}

int	main()
{
	t_list	*node = ft_lstnew(strdup("Hello"));

	ft_lstdelone(node, del_str);
	return (0);
}*/
