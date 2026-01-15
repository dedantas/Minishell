/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dedantas <dedantas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 10:10:33 by dedantas          #+#    #+#             */
/*   Updated: 2025/04/17 19:24:33 by dedantas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	*ft_strdup(const char *src)
{
	char	*str;
	int		buf_size;

	buf_size = ft_strlen(src) + 1;
	str = malloc(buf_size);
	if (NULL == str)
		return (NULL);
	ft_strlcpy(str, src, buf_size);
	return (str);
}

/*int main() 
{
    const char *original = "Olá, Mundo!";
   
    // Chama a função ft_strdup
    char *copia = ft_strdup(original);
    
    if (copia != NULL) {
        printf("String original: %s\n", original);
        printf("Cópia da string: %s\n", copia);
        
        // Lembre-se de liberar a memória alocada
        free(copia);
    } else {
        printf("Erro na alocação de memória!\n");
    }

    return 0;
}*/
