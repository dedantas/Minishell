#include "../minishell.h"

char	*read_quote(char **line, char quote)
{
	char	*start;
	char	*end;

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

void	handle_quotes(char **line, int *in_quote, char *quote_char)
{
	if ((**line == '\'' || **line == '"') && !(*in_quote))
	{
		*in_quote = 1;
		*quote_char = **line;
		(*line)++;
	}
	else if (**line == *quote_char && *in_quote)
	{
		*in_quote = 0;
		*quote_char = 0;
		(*line)++;
	}
}

/*char	*append_char(char *buffer, char c)
{
	char	*temp;
	char	str[2];

	str[0] = c;
	str[1] = '\0';
	temp = ft_strjoin(buffer, str);
	free(buffer);
	return (temp);
}*/

char	*read_word(char **line)
{
	char	*buffer;
	int		in_quote;
	char	quote_char;

	buffer = ft_strdup("");
	in_quote = 0;
	quote_char = 0;
	while (**line && (!ft_isspace(**line) || in_quote))
	{
		if ((**line == '\'' || **line == '"')
			|| (**line == quote_char && in_quote))
		{
			handle_quotes(line, &in_quote, &quote_char);
			continue ;
		}
		if (!in_quote && is_operator(**line))
			break ;
		buffer = append_char(buffer, **line);
		(*line)++;
	}
	return (buffer);
}

int	handle_operators(t_token **tokens, char **line)
{
	if (**line == '|' )
		return (add_token(tokens, new_token(PIPE, "|", NO)), (*line)++, 1);
	if (**line == '<' && *(*line + 1) == '<' && *(*line + 2) == '-')
		return (add_token(tokens, new_token(HEREDOC, "<<", NO)), *line += 3, 1);
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
