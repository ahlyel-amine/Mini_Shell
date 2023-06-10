/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 19:41:57 by aahlyel           #+#    #+#             */
/*   Updated: 2023/06/09 21:22:42 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_cmd	*call_pipe(char **line, int i)
{
	t_cmd	*operator;

	operator = NULL;
	if ((*line)[i] == '|')
	{
		operator = and_parser(remove_unused_parenthesis(\
		ft_substr((*line), 0, i)));
		operator = pipe_constructor(operator, and_parser(\
			remove_unused_parenthesis(\
			ft_substr((*line), i + 1, \
			ft_strlen((*line) + i + 1)))));
		free ((*line));
		*line = NULL;
	}
	return (operator);
}

void	*pipe_loop(char **line, int i, int *quit)
{
	t_cmd	*operator;
	t_var	var;
	int		k;

	operator = NULL;
	ft_memset(&var, 0, sizeof(t_var));
	while ((*line)[i])
	{
		check_out_of_quotes((*line)[i], &var);
		if ((*line)[i] == '(' && !var.quote && !var.dquote)
		{
			k = close_parenthise(*line + i + 1);
			if (k == -1)
				return (panic_recursive(ERR_UNCLSDP, line), *quit = 1, NULL);
			i += k;
			continue ;
		}
		else if ((*line)[i] == '|' && !var.quote && !var.dquote)
		{
			operator = call_pipe(line, i);
			break ;
		}
		i++;
	}
	return (operator);
}

t_cmd	*pipe_parser(char *line)
{
	t_cmd	*operator;
	int		i;
	int		quit;
	int		k;
	t_var	var;

	if (!line)
		return (NULL);
	i = 0;
	quit = 0;
	operator = NULL;
	i = skip_spaces_front(line);
	if (line[i] == ')' || line[i] == '&' || line[i] == '|')
		return (pr_custom_err("allo", line, line + i), NULL);
	operator = pipe_loop(&line, i, &quit);
	if (quit)
		return (NULL);
	if (!operator && line)
		operator = redirections_parser_has_parenthesis(\
		remove_unused_parenthesis(line));
	return (operator);
}
