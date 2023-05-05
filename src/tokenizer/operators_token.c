/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operators_token.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 12:31:40 by aahlyel           #+#    #+#             */
/*   Updated: 2023/05/05 15:13:30 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static t_cmd	*call_and_constructor(char *line, int i);
static t_cmd	*call_or_constructor(char *line, int i);
static t_cmd	*check_for_operators(char *line, int i, t_var var);

t_cmd	*get_token_operator(char *line)
{
	t_cmd	*operator;
	int		i;
	int		operator_true;
	t_var	var;

	set_zero_var(&var);
	i = -1;
	operator_true = 0;
	while (line[++i])
	{
		check_out_of_quotes(line[i], &var);
		operator = check_for_operators(line, i, var);
		if (operator)
		{
			operator_true = 1;
			break ;
		}
	}
	if (!operator_true)
	{
		operator = get_token_operator_pipe(ft_strdup(line));
		free (line);
	}
	return (operator);
}

static t_cmd	*call_and_constructor(char *line, int i)
{
	t_cmd	*operator;
	char	*tmp;

	operator = NULL;
	if (i - 1 >= 0)
	{
		tmp = ft_substr_skip_space(line, 0, i - 1);
		if (!*tmp)
			return (free (tmp), panic_recursive(ERR_AND, line), NULL);
		else
		{
			operator = get_token_operator(tmp);
			if (operator)
				operator = and_constructor(operator, \
				get_token_operator(\
				ft_substr(line, i + 2, ft_strlen(line + i + 2))));
		}
		free (line);
	}
	else
		return (panic_recursive(ERR_AND, line), NULL);
	return (operator);
}

static t_cmd	*call_or_constructor(char *line, int i)
{
	t_cmd	*operator;
	char	*tmp;

	operator = NULL;
	if (i - 1 >= 0)
	{
		tmp = ft_substr_skip_space(line, 0, i - 1);
		if (!*tmp)
			return (free (tmp), \
			panic_recursive(ERR_OR, line), NULL);
		else
		{
			operator = get_token_operator(tmp);
			operator = or_constructor(operator, \
			get_token_operator(\
			ft_substr(line, i + 2, ft_strlen(line + i + 2))));
		}
		free (line);
	}
	else
		return (panic_recursive(ERR_OR, line), NULL);
	return (operator);
}

static t_cmd	*check_for_operators(char *line, int i, t_var var)
{
	t_cmd	*operator;

	operator = NULL;
	if (!var.quote && !var.dquote && line[i] == '&' && line[i + 1] == '&')
	{
		operator = call_and_constructor(line, i);
		if (!operator)
			return (NULL);
	}
	else if (!var.quote && !var.dquote && line[i] == '|' && line[i + 1] == '|')
	{
		operator = call_or_constructor(line, i);
		if (!operator)
			return (NULL);
	}
	return (operator);
}


