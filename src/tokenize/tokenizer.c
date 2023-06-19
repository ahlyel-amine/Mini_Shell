/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 17:54:06 by aahlyel           #+#    #+#             */
/*   Updated: 2023/06/19 18:53:22 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	subsh_token(t_lsttoken **head, char *line, int *i, int *fail)
{
	int	j;

	j = 0;
	if (line[*i] == '(')
	{
		j = close_parenthise(line + *i + 1);
		if (j == -1)
			return (panic_recursive(ERR_UNCLSDP, NULL), *fail = 1, -1);
		ft_lstokenadd_back(head, new_token((t_token){NULL, line, *i + 1, j
				- 1, E_SUBSH}));
		*i += j + 1;
		return (1);
	}
	return (0);
}

int	quote_token(t_lsttoken **head, char *line, int *i)
{
	int	j;

	j = 0;
	if (line[*i] == '\"')
	{
		j = 1;
		while (line[*i + j] && line[*i + j] != '\"')
			j++;
		ft_lstokenadd_back(head, new_token((t_token){NULL, line, *i, j + 1,
				E_DQUOTE}));
		*i += j + 1;
		return (1);
	}
	else if (line[*i] == '\'')
	{
		j = 1;
		while (line[*i + j] && line[*i + j] != '\'')
			j++;
		ft_lstokenadd_back(head, new_token((t_token){NULL, line, *i, j + 1,
				E_QUOTE}));
		*i += j + 1;
		return (1);
	}
	return (0);
}

int	operator_token(t_lsttoken **head, char *line, int *i, int *fail)
{
	int	j;

	j = 0;
	if (line[*i] == '&')
	{
		if (line[*i + 1] != '&')
			return (panic_recursive(ERR_1AND, NULL), *fail = 1, -1);
		ft_lstokenadd_back(head, new_token((t_token){NULL, line, *i, 2,
				E_AND}));
		*i += 2;
		return (1);
	}
	else if (line[*i] == '|' && line[*i + 1] == '|')
	{
		ft_lstokenadd_back(head, new_token((t_token){NULL, line, *i, 2, E_OR}));
		*i += 2;
		return (1);
	}
	else if (line[*i] == '|')
	{
		ft_lstokenadd_back(head, new_token((t_token){NULL, line, *i, 1, \
		E_PIPE}));
		return ((*i)++, 1);
	}
	return (0);
}

t_lsttoken	*tokenize(char *line, char *endline, int i)
{
	t_lsttoken	*new;
	int			fail;

	fail = 0;
	new = NULL;
	while (line[i])
	{
		if (!fail && subsh_token(&new, line, &i, &fail))
			continue ;
		else if (!fail && quote_token(&new, line, &i))
			continue ;
		else if (!fail && operator_token(&new, line, &i, &fail))
			continue ;
		else if (!fail && red_right_token(&new, line, &i))
			continue ;
		else if (!fail && red_left_token(&new, line, &i))
			continue ;
		else if (!fail)
			str_token(&new, line, &i);
		else if (fail)
			return (free_lsttoken(new), NULL);
		if (line + i >= endline)
			break ;
	}
	return (new);
}
