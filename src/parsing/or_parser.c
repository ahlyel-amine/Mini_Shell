/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   or_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 19:41:27 by aahlyel           #+#    #+#             */
/*   Updated: 2023/06/09 18:46:41 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static t_cmd	*call_or(char **line, int i)
{
	t_cmd	*operator;

	operator = NULL;
	if ((*line)[i] == '|' && (*line)[i + 1] == '|')
	{
		operator = and_parser(remove_unused_parenthesis(\
		ft_substr((*line), 0, i)));
		operator = or_constructor(operator, and_parser(\
			remove_unused_parenthesis(\
			ft_substr((*line), i + 2, \
			ft_strlen((*line) + i + 2)))));
		free ((*line));
		*line = NULL;
	}
	return (operator);
}

void	*or_decide(char **line, int *i, int *doo, t_var var)
{
	t_cmd	*operator;
	int		k;

	k = 0;
	operator = NULL;
	if ((*line)[*i] == '(' && !var.quote && !var.dquote)
	{
		k = close_parenthise((*line) + *i + 1);
		if (k == -1)
			return (panic_recursive(ERR_UNCLSDP, line), *doo = -1, NULL);
		*i += k;
		*doo = 1;
	}
	if ((*line)[*i] == '|' && (*line)[*i + 1] == '|' && \
	!var.quote && !var.dquote)
	{
		operator = call_or(line, *i);
		*doo = 2;
	}
	else if ((*line)[*i] == '|' && !var.quote && !var.dquote)
	{
		operator = call_pipe(line, *i);
		*doo = 2;
	}
	return (operator);
}

void	*or_loop(char **line, int i, int *quit)
{
	int		doo;
	t_var	var;
	t_cmd	*operator;

	operator = NULL;
	ft_memset(&var, 0, sizeof(t_var));
	while ((*line)[i])
	{
		doo = 0;
		check_out_of_quotes((*line)[i], &var);
		operator = or_decide(line, &i, &doo, var);
		if (doo == -1)
			return (*quit = 1, NULL);
		else if (doo == 1)
			continue ;
		else if (doo == 2)
			break ;
		i++;
	}
	return (operator);
}

t_cmd	*or_parser(char *line)
{
	t_cmd	*operator;
	int		i;
	int		quit;
	t_var	var;

	if (!line)
		return (NULL);
	i = 0;
	quit = 0;
	operator = NULL;
	ft_memset(&var, 0, sizeof(t_var));
	i = skip_spaces_front(line);
	if (line[i] == ')' || line[i] == '&' || line[i] == '|')
		return (pr_custom_err("allo", line, line + i), NULL);
	operator = or_loop(&line, i, &quit);
	if (quit)
		return (NULL);
	if (!operator && line)
		operator = pipe_parser(remove_unused_parenthesis(line));
	return (operator);
}
