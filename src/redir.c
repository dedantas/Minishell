#include "../minishell.h"

void	add_redir(t_cmd *cmd, t_type type, char *file, int expand)
{
	t_redir	*redir;
	t_redir	*tmp;

	redir = malloc(sizeof(t_redir));
	redir->type = type;
	redir->file = ft_strdup(file);
	redir->heredoc_fd = -1;
	redir->expand = expand;
	redir->next = NULL;
	if (!cmd->redirs)
		cmd->redirs = redir;
	else
	{
		tmp = cmd->redirs;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = redir;
	}
}

int	is_redir(t_type type)
{
	return (type == IN || type == OUT
		|| type == APPEND || type == HEREDOC);
}

int	par_handle_heredoc(t_cmd *current, t_token *token)
{
	char	*trimmed;
	int		do_expand;

	trimmed = trim_whitespace(token->next->value);
	if (!trimmed || ft_strlen(trimmed) == 0)
	{
		ft_putendl_fd(
			"minishell: syntax error near unexpected token `newline'", 2);
		free(trimmed);
		return (0);
	}
	do_expand = (token->next->quote == NO);
	add_redir(current, token->type, trimmed, do_expand);
	free(trimmed);
	return (1);
}

int	handle_redir(t_cmd *current, t_token **tokens)
{
	if (!(*tokens)->next)
	{
		ft_putendl_fd(
			"minishell: syntax error near unexpected token `newline'", 2);
		return (0);
	}
	if ((*tokens)->next->type != WORD)
	{
		ft_putendl_fd(
			"minishell: syntax error near unexpected token", 2);
		return (0);
	}
	if ((*tokens)->type == HEREDOC)
	{
		if (!par_handle_heredoc(current, *tokens))
			return (0);
	}
	else
		add_redir(current, (*tokens)->type, (*tokens)->next->value, 1);
	*tokens = (*tokens)->next;
	return (1);
}
