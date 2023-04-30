/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operators_token.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 12:31:40 by aahlyel           #+#    #+#             */
/*   Updated: 2023/04/30 22:13:37 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_cmd	*get_token_operator(char *line)
{
	t_cmd	*operator;
	int		i;
	int		operator_and;
	int		operator_or;
	t_var	var;
	char	*tmp;

	set_zero_var(&var);
	i = 0;
	operator_and = 0;
	operator_or = 0;
	while (line[i])
	{
		check_out_of_quotes(line[i], &var);
		if (!var.quote && !var.dquote && line[i] == '&' && line[i + 1] == '&')
		{
			operator_and = 1;
			tmp = ft_substr_skip_space(line, 0, i);
			if (!*tmp)
			{
				free (line);
				free (tmp);
				ft_putendl_fd("minishell: syntax error near unexpected token `&&'\n", 2);
				return (NULL);
			}
			else
			{
				operator = get_token_operator(tmp);
				if (operator)
					operator = and_constructor(operator,
					get_token_operator(ft_substr(line, i + 2, ft_strlen(line + i + 2))));
			}
			free (line);
			break ;
		}
		else if (!var.quote && !var.dquote && line[i] == '|' && line[i + 1] == '|')
		{
			operator_or = 1;
			tmp = ft_substr_skip_space(line, 0, i);
			if (!*tmp)
			{
				free (line);
				free (tmp);
				ft_putendl_fd("minishell: syntax error near unexpected token `||'\n", 2);
				return (NULL);
			}
			else
			{
				operator = get_token_operator(tmp);
				operator = or_constructor(operator, 
				get_token_operator(ft_substr(line, i + 2, ft_strlen(line + i + 2))));
			}
			free (line);
			break ;
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