/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parenthesis_operators_token.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 15:30:16 by aahlyel           #+#    #+#             */
/*   Updated: 2023/05/09 18:11:48 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int		parhenthises_closed(char *line, int *k, int *i);
static t_cmd	*call_and_constructor(char *line, int i, int j, int k);
static t_cmd	*call_or_constructor(char *line, int i, int j, int k);
static t_cmd	*call_redir_constructor(char *line, int i, int j, int k);

t_cmd	*check_for_operators(char *line, int i, int j, int k)
{
	t_cmd	*operator;

	j += skip_spaces_front(line + i + j);
	operator = call_and_constructor(line, i, j, k);
	if (!operator)
		operator = call_or_constructor(line, i, j, k);
	if (!operator)
		return (pr_custom_err(ERR_TOKEN, line, line + i + j), NULL);
	return (operator);
}

t_cmd	*get_token_parenthesis_operator(char *line)
{
	t_cmd	*operator;
	int		i;
	int		j;
	int		k;

	i = 0;
	operator = NULL;
	i = skip_spaces_front(line);
	if (line[i] == ')')
			return (panic_recursive(ERR_ClSD_PARNETHISE, line), NULL);
	if (line[i] && line[i] == '(' && ++i)
	{
		if (parhenthises_closed(line + i, &k, &j))
		{
			j += skip_spaces_front(line + i + j);
			operator = call_and_constructor(line, i, j, k);
			if (!operator)
				operator = call_or_constructor(line, i, j, k);
			if (!operator)
				operator = call_redir_constructor(line, i, j, k);
			if (!operator)
				return (pr_custom_err(ERR_TOKEN, line, line + i + j), NULL);
		}
		else
			return (panic_recursive(ERR_UNLCSD_PARNETHISE, line), NULL);
	}
	else
		operator = get_token_operator(remove_unused_parenthesis(line));
	return (operator);
}

static int	parhenthises_closed(char *line, int *k, int *i)
{
	int		is_closed;
	int		is_open;
	t_var	var;

	set_zero_var(&var);
	*i = -1;
	is_open = 1;
	is_closed = 0;
	while (line[++(*i)])
	{
		check_out_of_quotes(line[*i], &var);
		if (line[*i] == '(' && !var.quote && \
		!var.dquote && is_open != is_closed)
			is_open++;
		else if (line[*i] == ')' && !var.quote && \
		!var.dquote && is_open != is_closed)
		{
			is_closed++;
			*k = *i;
			continue ;
		}
		if (is_open == is_closed)
			return (1);
	}
	return (0);
}

static t_cmd	*call_and_constructor(char *line, int i, int j, int k)
{
	t_cmd	*operator;
	
	operator = NULL;
	if (line[i + j] == '&' && line[i + j + 1] == '&')
	{
		operator = get_token_parenthesis_operator(remove_unused_parenthesis(ft_substr(line, i, k)));
			operator = and_constructor(operator,
				get_token_parenthesis_operator(\
				remove_unused_parenthesis(\
				ft_substr(line, i + j + 2, \
				ft_strlen(line + i + j + 2)))));
		free (line);
	}
	return (operator);
}

static t_cmd	*call_or_constructor(char *line, int i, int j, int k)
{
	t_cmd	*operator;
	
	operator = NULL;
	if (line[i + j] == '|' && line[i + j + 1] == '|')
	{
		operator = get_token_parenthesis_operator(remove_unused_parenthesis(ft_substr(line, i, k)));
		operator = or_constructor(operator,
			get_token_parenthesis_operator(\
			remove_unused_parenthesis(\
			ft_substr(line, i + j + 2, \
			ft_strlen(line + i + j + 2)))));
		free (line);
	}
	else if (line[i + j] == '|')
	{
		operator = get_token_parenthesis_operator(remove_unused_parenthesis(ft_substr(line, i, k)));
		operator = pipe_constructor(operator,
			get_token_parenthesis_operator(\
			remove_unused_parenthesis(\
			ft_substr(line, i + j + 1, \
			ft_strlen(line + i + j + 1)))));
		free (line);
		// operator = get_token_operator(remove_unused_parenthesis(line));
	}
	return (operator);
}

static t_cmd	*call_redir_constructor(char *line, int i, int j, int k)
{
	t_cmd	*operator;
	t_redir_content	red;

	operator = NULL;
	if (line[i + j] == '<' && line[i + j + 1] == '<')
	{
		if (!check_for_syntax(line, i + j))
			return (NULL);
		operator = get_token_parenthesis_operator(remove_unused_parenthesis(ft_substr(line, i, k)));
		k = fill_redir_content(line, i + j, &red, F_HEREDOC);
		j = skip_spaces_front(line + k);
		if (line[k + j])
			return (NULL);
		operator = redir_constructor(operator, red);
		free (line);
	}
	else if (line[i + j] == '<')
	{
		if (!check_for_syntax(line, i + j))
			return (NULL);
		operator = get_token_parenthesis_operator(remove_unused_parenthesis(ft_substr(line, i, k)));
		k = fill_redir_content(line, i + j, &red, F_IN_RED);
		j = skip_spaces_front(line + k);
		if (line[k + j])
			return (NULL);
		operator = redir_constructor(operator, red);
		free (line);
	}
	else if (line[i + j] == '>'  && line[i + j + 1] == '>')
	{
		if (!check_for_syntax(line, i + j))
			return (NULL);
		operator = get_token_parenthesis_operator(remove_unused_parenthesis(ft_substr(line, i, k)));
		k = fill_redir_content(line, i + j, &red, F_APPEND);
		j = skip_spaces_front(line + k);
		if (line[k + j])
			return (NULL);
		operator = redir_constructor(operator, red);
		free (line);
	}
	else if (line[i + j] == '>')
	{
		if (!check_for_syntax(line, i + j))
			return (NULL);
		operator = get_token_parenthesis_operator(remove_unused_parenthesis(ft_substr(line, i, k)));
		k = fill_redir_content(line, i + j, &red, F_OUT_RED);
		j = skip_spaces_front(line + k);
		if (line[k + j])
			return (NULL);
		operator = redir_constructor(operator, red);
		free (line);
	}
	else if (line[i + j] == '|')
	{
		operator = get_token_parenthesis_operator(remove_unused_parenthesis(ft_substr(line, i, k)));
		operator = pipe_constructor(operator,
			get_token_parenthesis_operator(\
			remove_unused_parenthesis(\
			ft_substr(line, i + j + 1, \
			ft_strlen(line + i + j + 1)))));
		free (line);
		// operator = get_token_operator(remove_unused_parenthesis(line));
	}
	return (operator);
}
