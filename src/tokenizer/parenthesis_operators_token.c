/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parenthesis_operators_token.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 15:30:16 by aahlyel           #+#    #+#             */
/*   Updated: 2023/04/30 17:35:34 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

typedef struct s_parenthesiss
{
	int	open;
	int	closed;
}	t_parenthesiss;

t_cmd	*get_token_parenthesis_operator(char *line)
{
	t_cmd			*operator;
	int				i;
	int				j;
	int				k;
	t_parenthesiss	is;
	t_var			var;

	set_zero_var(&var);
	i = 0;
	j = -1;
	is.open = 0;
	is.closed = 0;
	operator = NULL;
	while (line[i] && ft_isspace(line[i]))
		i++;
	if (line[i] && line[i] == '(')
	{
		is.open++;
		i++;
	}
	if (is.open)
	{
		while (line[i + ++j])
		{
			check_out_of_quotes(line[i + j], &var);
			if (line[i + j] == '(' && !var.quote && !var.dquote)
				is.open++;
			else if (line[i + j] == ')' && !var.quote && !var.dquote)
			{
				is.closed++;
				k = i + j++;
			}
			if (is.open == is.closed)
			{
				while (ft_isspace(line[i + j]))
					j++;
				if (line[i + j] == '&' && line[i + j + 1] == '&')
				{

					operator = and_constructor(
						get_token_parenthesis_operator(ft_substr(line, i, k - i)),
						get_token_parenthesis_operator(remove_unused_parenthesis(ft_substr(line, i + j + 2, ft_strlen(line + i + j + 2)))));
					free (line);
					break ;
				}
				else if (line[i + j] == '|' && line[i + j + 1] == '|')
				{

					operator = or_constructor(
						get_token_parenthesis_operator(ft_substr(line, i, k - i)),
						get_token_parenthesis_operator(remove_unused_parenthesis(ft_substr(line, i + j + 2, ft_strlen(line + i + j + 2)))));
					free (line);
					break ;
				}
				else
				{
					printf("don't freeeeeeee me\n");
					something_wrong("syntax error", line);
				}
			}
		}
	}
	else
		operator = get_token_operator(remove_unused_parenthesis(line));
	return (operator);
}
