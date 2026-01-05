#include "../minishell.h"

t_token *new_token(t_type type, char *value)
{
    t_token *token = malloc(sizeof(t_token));
    if (!token) return NULL;
    token->type = type;
    token->value = ft_strdup(value);  // Copiar a string
    token->next = NULL;
    return token;
}

void add_token(t_token **tokens, t_token *new)
{
    t_token *tmp = *tokens;
    if (!tmp)
    {
        *tokens = new;
    }
    else
    {
        while (tmp->next)
            tmp = tmp->next;
        tmp->next = new;
    }
}

int	ft_isspace(int c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

void skip_whitespace(char **line)
{
    while (**line && ft_isspace(**line))
        (*line)++;
}

int is_operator(char c)
{
    return (c == '|' || c == '<' || c == '>' || c == '\0');
}

t_token *lexer(char *line)
{
    t_token *tokens = NULL;
    char *start;
    
    while (*line)
    {
        skip_whitespace(&line);  // Pular espaços em branco
        
        if (*line == '|')
        {
            add_token(&tokens, new_token(PIPE, "|"));
            line++;
        }
        else if (*line == '<')
        {
            if (*(line + 1) == '<')  // HEREDOC
            {
                add_token(&tokens, new_token(HEREDOC, "<<"));
                line += 2;
            }
            else  // IN
            {
                add_token(&tokens, new_token(IN, "<"));
                line++;
            }
        }
        else if (*line == '>')
        {
            if (*(line + 1) == '>')  // APPEND
            {
                add_token(&tokens, new_token(APPEND, ">>"));
                line += 2;
            }
            else  // OUT
            {
                add_token(&tokens, new_token(OUT, ">"));
                line++;
            }
        }
        else if (*line == '"')  // Tratamento de aspas duplas
        {
            start = ++line;  // Pular a aspa inicial
            while (*line && *line != '"')
                line++;
            if (*line == '"')
            {
                add_token(&tokens, new_token(WORD, strndup(start, line - start)));
                line++;  // Pular a aspa final
            }
            else
            {
                // Erro: aspas não fechadas
                return NULL;
            }
        }
        else if (*line == '\'')  // Tratamento de aspas simples
        {
            start = ++line;  // Pular a aspa inicial
            while (*line && *line != '\'')
                line++;
            if (*line == '\'')
            {
                add_token(&tokens, new_token(WORD, strndup(start, line - start)));
                line++;  // Pular a aspa final
            }
            else
            {
                // Erro: aspas não fechadas
                return NULL;
            }
        }
        else if (*line == '$')  // Para expandir variáveis
        {
            start = ++line;  // Pular o $
            while (*line && (isalnum(*line) || *line == '_'))
                line++;
            add_token(&tokens, new_token(DOLLAR, strndup(start, line - start)));
        }
        else if (is_operator(*line) || isspace(*line))  // Pular operadores e espaços
        {
            // Ignorar operadores ou espaços após já terem sido processados
            continue;
        }
        else
        {
            start = line;
            while (*line && !is_operator(*line) && !isspace(*line))  // Detecta uma palavra
                line++;
            add_token(&tokens, new_token(WORD, strndup(start, line - start)));
        }
    }
    return tokens;
}

