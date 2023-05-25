/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 19:40:29 by aahlyel           #+#    #+#             */
/*   Updated: 2023/05/25 16:58:57 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static t_cmd	*call_and(char **line, int i)
{
	t_cmd	*operator;
	
	operator = NULL;
	if ((*line)[i] == '&' && (*line)[i + 1] == '&')
	{
		operator = and_parser(remove_unused_parenthesis(ft_substr((*line), 0, i)));
		operator = and_constructor(operator,
			and_parser(\
			remove_unused_parenthesis(\
			ft_substr((*line), i + 2, \
			ft_strlen((*line) + i + 2)))));
		free ((*line));
		*line = NULL;
	}
	return (operator);
}

t_cmd	*and_parser(char *line)
{
	t_cmd	*operator;
	int		i;
	int		j;
	int		k;
	t_var	var;
	
	if (!line)
		return (NULL);
	i = 0;
	operator = NULL;
	ft_memset(&var, 0, sizeof(t_var));
	i = skip_spaces_front(line);
	if (line[i] == ')' || line[i] == '&' || line[i] == '|')
			return (pr_custom_err(ERR_SNTX, line, line + i), NULL);
	while (line[i])
	{
		check_out_of_quotes(line[i], &var);
		if (line[i] == '(' && !var.quote && !var.dquote)
		{
			i += close_parenthise(line + i + 1);
			continue ;
		}
		if (line[i] == '&' && line[i + 1] == '&'  && !var.quote && !var.dquote)
		{
			operator = call_and(&line, i);
			break ;	
		}
		i++;
	}
	if (!operator && line)
		operator = or_parser(remove_unused_parenthesis(line));
	return (operator);
}
