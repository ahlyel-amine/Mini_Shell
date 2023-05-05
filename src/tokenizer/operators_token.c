/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operators_token.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 12:31:40 by aahlyel           #+#    #+#             */
/*   Updated: 2023/05/05 12:46:37 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static t_cmd	*call_and_constructor(char *line, int i, int *operator_and)
{
	t_cmd	*operator;
	char	*tmp;

	operator = NULL;
	*operator_and = 1;
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

static t_cmd	*call_or_constructor(char *line, int i, int *operator_or)
{
	t_cmd	*operator;
	char	*tmp;

	operator = NULL;
	*operator_or = 1;
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

t_cmd	*check_for_operators(char *line, int i, \
int *operator_and, int *operator_or)
{
	t_cmd	*operator;
	t_var	var;

	set_zero_var(&var);
	operator = NULL;
	check_out_of_quotes(line[i], &var);
	if (!var.quote && !var.dquote && line[i] == '&' && line[i + 1] == '&')
	{
		operator = call_and_constructor(line, i, operator_and);
		if (!operator)
			return (NULL);
	}
	else if (!var.quote && !var.dquote && line[i] == '|' && line[i + 1] == '|')
	{
		operator = call_or_constructor(line, i, operator_or);
		if (!operator)
			return (NULL);
	}
	return (operator);
}

t_cmd	*get_token_operator(char *line)
{
	t_cmd	*operator;
	int		i;
	int		operator_and;
	int		operator_or;
	t_var	var;

	set_zero_var(&var);
	i = -1;
	operator_and = 0;
	operator_or = 0;
	while (line[++i])
	{
		operator = check_for_operators(line, i, &operator_and, &operator_or);
		if (operator_or || operator_and)
			break ;
	}
	if (!operator_and && ! operator_or)
	{
		operator = get_token_operator_pipe(ft_strdup(line));
		free (line);
	}
	return (operator);
}
