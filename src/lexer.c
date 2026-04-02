/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dedantas <dedantas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 18:45:34 by dedantas          #+#    #+#             */
/*   Updated: 2026/01/15 19:20:26 by dedantas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char    *read_quote(char **line, char quote)
{
    char    *start;
    char    *end;

    start = *line + 1;
    end = start;
    while (*end && *end != quote)
        end++;
    
    if (*end == quote)
    {
        *line = end + 1;
        return (ft_substr(start, 0, end - start));
    }
    *line = end;
    return (NULL);
}

// Substitua a função read_word no lexer.c

char    *read_word(char **line)
{
    char    *buffer;
    char    *temp;
    char    quote_char;
    int     in_quote;

    buffer = ft_strdup("");
    in_quote = 0;
    quote_char = 0;
    
    while (**line && (!ft_isspace(**line) || in_quote))
    {
        // Entrou/saiu de aspas
        if ((**line == '\'' || **line == '"') && !in_quote)
        {
            in_quote = 1;
            quote_char = **line;
            (*line)++;
            continue;
        }
        else if (**line == quote_char && in_quote)
        {
            in_quote = 0;
            quote_char = 0;
            (*line)++;
            continue;
        }
        
        // Operadores fora de aspas quebram a palavra
        if (!in_quote && is_operator(**line))
            break;
        
        // Adiciona caractere ao buffer
        temp = ft_strjoin(buffer, (char[]){**line, 0});
        free(buffer);
        buffer = temp;
        (*line)++;
    }
    
    return (buffer);
}

static int	handle_operators(t_token **tokens, char **line)
{
	if (**line == '|' )
		return (add_token(tokens, new_token(PIPE, "|", NO)), (*line)++, 1);
	if (**line == '<' && *(*line + 1) == '<')
		return (add_token(tokens, new_token(HEREDOC, "<<", NO)), *line += 2, 1);
	if (**line == '>' && *(*line + 1) == '>')
		return (add_token(tokens, new_token(APPEND, ">>", NO)), *line += 2, 1);
	if (**line == '<')
		return (add_token(tokens, new_token(IN, "<", NO)), (*line)++, 1);
	if (**line == '>')
		return (add_token(tokens, new_token(OUT, ">", NO)), (*line)++, 1);
	return (0);
}

static void	handle_word(t_token **tokens, char **line)
{
	char	*value;

	value = read_word(line);
	add_token(tokens, new_token(WORD, value, NO));
	free(value);
}

t_token *lexer(char *line)
{
    t_token *tokens;
    char    *value;

    tokens = NULL;
    while (*line)
    {
        skip_whitespace(&line);
        if (!*line)
            break;
            
        if (*line == '\'')
        {
            value = read_quote(&line, '\'');
            if (!value)  // Verifica se retornou NULL (aspa não fechada)
            {
                ft_putendl_fd("minishell: unclosed quote", 2);
                free_tokens(tokens);  // Libera tokens já criados
                return (NULL);
            }
            add_token(&tokens, new_token(WORD, value, SINGLE));
            free(value);
        }
        else if (*line == '"')
        {
            value = read_quote(&line, '"');
            if (!value)  // Verifica se retornou NULL (aspa não fechada)
            {
                ft_putendl_fd("minishell: unclosed quote", 2);
                free_tokens(tokens);  // Libera tokens já criados
                return (NULL);
            }
            add_token(&tokens, new_token(WORD, value, DOUBLE));
            free(value);
        }
        else if (handle_operators(&tokens, &line))
            continue;
        else
            handle_word(&tokens, &line);
    }
    return (tokens);
}
