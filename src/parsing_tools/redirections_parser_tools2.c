/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_parser_tools2.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 18:04:15 by aahlyel           #+#    #+#             */
/*   Updated: 2023/06/12 20:23:53 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_isname(char c)
{
	return (c != '&' && c != '|' && c != '<' && c != '>' && c != ' ');
}

t_arguments	*get_names(char *line, int *i)
{
	t_arguments	*arguments;
	t_var		var;
	int			j;

	ft_memset(&var, 0, sizeof(t_var));
	arguments = NULL;
	j = 0;
	while (line[*i + j])
	{
		check_out_of_quotes(line[*i + j], &var);
		if (var.dquote && line[*i + j] == '\"')
		{
			if (j)
				arguments = arguments_constructor(arguments, ft_substr(line, *i, \
						j), IS_STR, 0);
			*i += j + 1;
			*i += close_dquote(&arguments, line, *i) + 1;
			var.dquote = 0;
			j = 0;
			continue ;
		}
		else if (var.quote && line[*i + j] == '\'')
		{
			if (j)
				arguments = arguments_constructor(arguments, ft_substr(line, *i, \
						j), IS_STR, 0);
			*i += j + 1;
			*i += close_quote(&arguments, line, *i) + 1;
			var.quote = 0;
			j = 0;
			continue ;
		}
		else if (!var.dquote && !var.quote && !ft_isname(line[*i + j]))
			break ;
		j++;
	}
	if (j)
	{
		arguments = arguments_constructor(arguments, ft_substr(line, *i, j), \
			IS_STR, 0);
		*i += j;
	}
	merge_arguments(&arguments, 0);
	tokenize_variables(&arguments);
	return (arguments);
}
