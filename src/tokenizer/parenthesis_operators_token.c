/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parenthesis_operators_token.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 15:30:16 by aahlyel           #+#    #+#             */
/*   Updated: 2023/05/05 12:58:55 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
			*k = *i + 1;
			continue ;
		}
		if (is_open == is_closed)
			return (1);
	}
	return (0);
}

t_cmd	*call_and_constructor(char *line, int i, int j, int k)
{
	t_cmd	*operator;
	
	operator = NULL;
	if (line[i + j] == '&' && line[i + j + 1] == '&')
	{
		operator = and_constructor(
			get_token_parenthesis_operator(\
			remove_unused_parenthesis(\
			ft_substr(line, i, k - i))),
			get_token_parenthesis_operator(\
			remove_unused_parenthesis(\
			ft_substr(line, i + j + 2, \
			ft_strlen(line + i + j + 2)))));
		free (line);
	}
	return (operator);
}

t_cmd	*call_or_constructor(char *line, int i, int j, int k)
{
	t_cmd	*operator;
	
	operator = NULL;
	if (line[i + j] == '|' && line[i + j + 1] == '|')
	{
		operator = or_constructor(
			get_token_parenthesis_operator(\
			remove_unused_parenthesis(\
			ft_substr(line, i, k - i))),
			get_token_parenthesis_operator(\
			remove_unused_parenthesis(\
			ft_substr(line, i + j + 2, \
			ft_strlen(line + i + j + 2)))));
		free (line);
	}
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
	if (line[i] && line[i] == '(' && ++i)
	{
		if (parhenthises_closed(line + i, &k, &j))
		{
			j += skip_spaces_front(line + i + j);
			operator = call_and_constructor(line, i, j, k);
			if (!operator)
				operator = call_or_constructor(line, i, j, k);
			if (!operator)
				return (pr_custom_err(line + i + j, line), NULL);
		}
		else
			return (panic_recursive(ERR_UNLCSD_PARNETHISE, line), NULL);
	}
	else
		operator = get_token_operator(remove_unused_parenthesis(line));
	return (operator);
}
