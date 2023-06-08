/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   or_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 19:41:27 by aahlyel           #+#    #+#             */
/*   Updated: 2023/06/08 12:10:08 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static t_cmd	*call_or(char **line, int i)
{
	t_cmd	*operator;
	
	operator = NULL;
	if ((*line)[i] == '|' && (*line)[i + 1] == '|')
	{
		operator = and_parser(remove_unused_parenthesis(ft_substr((*line), 0, i)));
		operator = or_constructor(operator,
			and_parser(\
			remove_unused_parenthesis(\
			ft_substr((*line), i + 2, \
			ft_strlen((*line) + i + 2)))));
		free ((*line));
		*line = NULL;
	}
	return (operator);
}

t_cmd	*or_parser(char *line)
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
			return (pr_custom_err("allo", line, line + i), NULL);
	while (line[i])
	{
		check_out_of_quotes(line[i], &var);
		if (line[i] == '(' && !var.quote && !var.dquote)
		{
			k = close_parenthise(line + i + 1);
			if (k == -1)
				return (panic_recursive(ERR_UNLCSD_PARNETHISE, &line), NULL);
			i += k; 
			continue ;
		}
		if (line[i] == '|' && line[i + 1] == '|'  && !var.quote && !var.dquote)
		{
			operator = call_or(&line, i);
			break ;	
		}
		else if (line[i] == '|'  && !var.quote && !var.dquote)
		{
			operator = call_pipe(&line, i);
			break ;	
		}
		i++;
	}
	if (!operator && line)
		operator =  pipe_parser(remove_unused_parenthesis(line));
	return (operator);
}