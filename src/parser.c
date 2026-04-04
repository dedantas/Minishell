/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dedantas <dedantas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 18:46:16 by dedantas          #+#    #+#             */
/*   Updated: 2026/01/15 18:58:22 by dedantas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

// parser.c - adicione esta função auxiliar no topo do arquivo

static char     *trim_whitespace(char *str)
{
        char    *start;
        char    *end;
        char    *result;
        int     len;

        if (!str)
                return (NULL);
        
        start = str;
        while (*start && ft_isspace(*start))
                start++;
        
        if (*start == '\0')
                return (ft_strdup(""));
        
        end = start + ft_strlen(start) - 1;
        while (end > start && ft_isspace(*end))
                end--;
        
        len = end - start + 1;
        result = malloc(len + 1);
        if (!result)
                return (NULL);
        
        ft_strlcpy(result, start, len + 1);
        return (result);
}

// parser.c - substitua a função handle_redir

static int handle_redir(t_cmd *current, t_token **tokens)
{
    char *delimiter;
    char *trimmed;
    
    if (!(*tokens)->next)
    {
        ft_putendl_fd("minishell: syntax error near unexpected token `newline'", 2);
        return (0);
    }
    if ((*tokens)->next->type != WORD)
    {
        ft_putendl_fd("minishell: syntax error near unexpected token", 2);
        return (0);
    }
    
    int do_expand = 1;
    if ((*tokens)->type == HEREDOC)
    {
        // Remove espaços do início e fim do delimiter
        trimmed = trim_whitespace((*tokens)->next->value);
        if (!trimmed || ft_strlen(trimmed) == 0)
        {
            ft_putendl_fd("minishell: syntax error near unexpected token `newline'", 2);
            free(trimmed);
            return (0);
        }
        
        delimiter = trimmed;
        do_expand = ((*tokens)->next->quote == NO);
        add_redir(current, (*tokens)->type, delimiter, do_expand);
        free(delimiter);
    }
    else
    {
        add_redir(current, (*tokens)->type, (*tokens)->next->value, do_expand);
    }
    
    *tokens = (*tokens)->next;
    return (1);
}

/*static int handle_redir(t_cmd *current, t_token **tokens)
{
    if (!(*tokens)->next)
    {
        ft_putendl_fd("minishell: syntax error near unexpected token `newline'", 2);
        return (0);
    }
    if ((*tokens)->next->type != WORD)
    {
        ft_putendl_fd("minishell: syntax error near unexpected token", 2);
        return (0);
    }
    int do_expand = 1;
    if ((*tokens)->type == HEREDOC)
        do_expand = ((*tokens)->next->quote == NO);
    add_redir(current, (*tokens)->type,
            (*tokens)->next->value, do_expand);
    *tokens = (*tokens)->next;
    return (1);
}*/

static int handle_pipe(t_cmd **current, t_token *tokens)
{
    if (!*current)
        return (0);
    if (!(*current)->args && !(*current)->redirs)  // CORRIGIDO: comando vazio antes do pipe
    {
        ft_putendl_fd("minishell: syntax error near unexpected token `|'", 2);
        return (0);
    }
    if (tokens->next && tokens->next->type == PIPE)
    {
        ft_putendl_fd("minishell: syntax error near unexpected token `|'", 2);
        return (0);
    }
    if (!tokens->next)
    {
        ft_putendl_fd("minishell: syntax error near unexpected token `|'", 2);
        return (0);
    }

    *current = NULL;
    return (1);
}

t_cmd *parser(t_token *tokens)
{
    t_cmd *cmds;
    t_cmd *current;

    if (!tokens)
        return (NULL);
    cmds = NULL;
    current = NULL;
    while (tokens)
    {
        if (!current)
        {
            current = new_cmd();
            add_cmd(&cmds, current);
        }
        if (tokens->type == WORD)
            add_arg(current, tokens->value, tokens->quote);
        else if (is_redir(tokens->type))
        {
            if (!handle_redir(current, &tokens))
            {
                free_cmds(cmds);
                return (NULL);
            }
        }
        else if (tokens->type == PIPE)
        {
            if (!handle_pipe(&current, tokens))
            {
                free_cmds(cmds);
                return (NULL);
            }
        }
        tokens = tokens->next;
    }
    // Verifica último comando
    if (current && !current->args && !current->redirs)
    {
        ft_putendl_fd("minishell: syntax error near unexpected token `newline'", 2);
        free_cmds(cmds);
        return (NULL);
    }
    return (cmds);
}
