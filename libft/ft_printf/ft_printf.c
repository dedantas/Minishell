/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dedantas <dedantas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 13:27:40 by dedantas          #+#    #+#             */
/*   Updated: 2025/04/29 20:36:09 by dedantas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	ft_putvalue(const char *str, va_list ap, int i, int t)
{
	if (str[i] == 'd' || str[i] == 'i')
		t += ft_putnbr(va_arg(ap, int));
	else if (str[i] == 's')
		t += ft_putstr(va_arg(ap, char *));
	else if (str[i] == 'c')
		t += ft_putchar(va_arg(ap, int));
	else if (str[i] == 'p')
		t += ft_putpointer(va_arg(ap, void *));
	else if (str[i] == 'u')
		t += ft_putnbr_u(va_arg(ap, unsigned int));
	else if (str[i] == 'x')
		t += ft_putnbr_base(va_arg(ap, int), "0123456789abcdef");
	else if (str[i] == 'X')
		t += ft_putnbr_base(va_arg(ap, int), "0123456789ABCDEF");
	else if (str[i] == '%')
		t += ft_putchar('%');
	else
		return (-1);
	return (t);
}

int	ft_printf(const char *str, ...)
{
	va_list	ap;
	int		i;
	int		t;

	t = 0;
	i = -1;
	va_start(ap, str);
	while (str[++i])
	{
		if (str[i] == '%')
			t += ft_putvalue(str, ap, ++i, 0);
		else
			t += ft_putchar(str[i]);
	}
	va_end(ap);
	return (t);
}

/*#include <stdio.h>
#include <limits.h>
#include "ft_printf.h"

int main(void)
{
    int count_ft, count_std;

    // 1. Teste de caracteres
    count_ft = ft_printf("Char: %c\n", 'A');
    count_std = printf("Char: %c\n", 'A');
    printf("ft: %d vs std: %d\n", count_ft, count_std);

    // 2. Teste de strings
    count_ft = ft_printf("String: %s\n", "Hello World!");
    count_std = printf("String: %s\n", "Hello World!");
    printf("ft: %d vs std: %d\n", count_ft, count_std);

    // 3. Teste de ponteiros
    int x = 42;
    count_ft = ft_printf("Pointer: %p\n", &x);
    count_std = printf("Pointer: %p\n", &x);
    printf("ft: %d vs std: %d\n", count_ft, count_std);

    // 4. Teste de inteiros decimais
    count_ft = ft_printf("Decimal: %d\n", 12345);
    count_std = printf("Decimal: %d\n", 12345);
    printf("ft: %d vs std: %d\n", count_ft, count_std);

    // 5. Teste de inteiros (base 10)
    count_ft = ft_printf("Integer: %i\n", -6789);
    count_std = printf("Integer: %i\n", -6789);
    printf("ft: %d vs std: %d\n", count_ft, count_std);

    // 6. Teste de unsigned
    count_ft = ft_printf("Unsigned: %u\n", UINT_MAX);
    count_std = printf("Unsigned: %u\n", UINT_MAX);
    printf("ft: %d vs std: %d\n", count_ft, count_std);

    // 7. Teste hexadecimal (minúsculas)
    count_ft = ft_printf("Hex: %x\n", 255);
    count_std = printf("Hex: %x\n", 255);
    printf("ft: %d vs std: %d\n", count_ft, count_std);

    // 8. Teste hexadecimal (maiúsculas)
    count_ft = ft_printf("HEX: %X\n", 255);
    count_std = printf("HEX: %X\n", 255);
    printf("ft: %d vs std: %d\n", count_ft, count_std);

    // 9. Teste de porcentagem
    count_ft = ft_printf("100%% completo\n");
    count_std = printf("100%% completo\n");
    printf("ft: %d vs std: %d\n", count_ft, count_std);

    // 1. String vazia
    ft_printf("Empty: '%s'\n", "");
    printf("Empty: '%s'\n", "");

    // 2. Ponteiro NULL
    char *t = NULL;
    ft_printf("NULL string: %s\n", NULL);
    printf("NULL string: %s\n", t);
    ft_printf("NULL pointer: %p\n", NULL);
    printf("NULL pointer: %p\n", NULL);

    // 3. Valores limites
    ft_printf("INT_MIN: %d\n", INT_MIN);
    ft_printf("INT_MAX: %d\n", INT_MAX);
    ft_printf("UINT_MAX: %u\n", UINT_MAX);
    printf("INT_MIN: %d\n", INT_MIN);
    printf("INT_MAX: %d\n", INT_MAX);
    printf("UINT_MAX: %u\n", UINT_MAX);

    // 4. Múltiplos especificadores
    ft_printf("Multi: %c %s %p %d %i %u %x %X %%\n",
             'A', "test", &x, 42, -42, 100, 255, 255);
    printf("Multi: %c %s %p %d %i %u %x %X %%\n",
             'A', "test", &x, 42, -42, 100, 255, 255);

    // 5. Caracteres especiais
    ft_printf("Especiais: \\n \\t \\0 \\v \\f \\r\n");
    printf("Especiais: \\n \\t \\0 \\v \\f \\r\n");

    // 1. Combinação de texto e especificadores
    ft_printf("User %s (ID: %d) has %u points in 0x%X\n",
             "JohnDoe", 12345, 1000, 0xABCDEF);
    printf("User %s (ID: %d) has %u points in 0x%X\n",
             "JohnDoe", 12345, 1000, 0xABCDEF);

    // 2. Múltiplas instâncias do mesmo tipo
    ft_printf("%d + %d = %d\n", 5, 7, 5+7);
    printf("%d + %d = %d\n", 5, 7, 5+7);

    // 3. Strings longas
    ft_printf("Long string: %s\n", "Lorem ipsum dolor sit amet...");
    printf("Long string: %s\n", "Lorem ipsum dolor sit amet...");

    // 4. Formatação complexa
    ft_printf("Data: %p | %d | %x | %c\n", &x, x, x, 'X');
    printf("Data: %p | %d | %x | %c\n", &x, x, x, 'X');

    int count;

    // 1. File descriptor inválido
    count = ft_printf("Teste %d\n", 42); // FD padrão (1) é válido
    printf("Retorno válido: %d\n", count);

    // 2. Especificador inválido
    count = ft_printf("Inválido: %z\n");
    printf("Retorno inválido: %d (deve ser -1)\n", count);

    // 3. Buffer overflow potencial
    count = ft_printf("%s", "String extremamente longa...");
    printf("Retorno: %d\n", count);

    return (0);
}*/
