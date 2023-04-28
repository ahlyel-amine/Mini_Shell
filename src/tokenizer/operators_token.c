/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operators_token.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 12:31:40 by aahlyel           #+#    #+#             */
/*   Updated: 2023/04/28 08:28:59 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_cmd	*get_token_operator(char *line)
{
	t_cmd	*operator;
	int		i;
	int		operator_and;
	int		operator_or;
	int		quote;
	int		dquote;
	
	quote = 0;
	dquote = 0;
	i = 0;
	operator_and = 0;
	operator_or = 0;
	while (line[i])
	{
		check_out_of_quotes(line[i], &quote, &dquote);
		if (i - 2 >= 0 && !quote && !dquote)
		{
			if (line[i - 1] == '&' && line[i] == '&')
			{
				operator_and = 1;
				operator = and_constructor(get_token_operator(ft_substr(line, 0, i - 1)), 
				get_token_operator(ft_substr(line, i + 1, ft_strlen(line + i + 1))));
				free (line);
				break ;
			}
			else if (line[i - 1] == '|' && line[i] == '|')
			{
				operator_or = 1;
				operator = or_constructor(get_token_operator(ft_substr(line, 0, i - 1)), 
				get_token_operator(ft_substr(line, i + 1, ft_strlen(line + i + 1))));
				free (line);
				break ;
			}
		}
		if (i - 1 >= 0)
		{
			if (line[i - 1] == '&' && line[i] == '&')
			{
				operator_and = 1;
				operator = and_constructor(get_token_operator(ft_substr(line, 0, i - 1)), 
				get_token_operator(ft_substr(line, i + 1, ft_strlen(line + i + 1))));
				free (line);
				break ;
			}
			else if (line[i - 1] == '|' && line[i] == '|')
			{
				operator_or = 1;
				operator = or_constructor(get_token_operator(ft_substr(line, 0, i - 1)), 
				get_token_operator(ft_substr(line, i + 1, ft_strlen(line + i + 1))));
				free (line);
				break ;
			}
		}
		i++;
	}
	if (!operator_and && ! operator_or)
	{
		operator = get_token_operator_pipe(ft_strdup(line));
		free (line);
	}
	return (operator);
}