/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables_controll.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 19:27:25 by aahlyel           #+#    #+#             */
/*   Updated: 2023/06/19 11:26:16 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static t_arguments	*check_str(char *str, t_arguments *vars, int *i)
{
	*i = 0;
	while (str[*i] && (str[*i] != '$' || (str[*i] == '$' && \
	str[*i + 1] != '?' && (ft_isdigit(str[*i + 1]) || \
	!ft_isvariable(str[*i + 1]) || !str[*i + 1]))))
		(*i)++;
	if (*i)
		vars = arguments_constructor(vars, ft_substr(str, 0, *i), IS_STR, 0);
	return (vars);
}

static void	get_var_name(char *str, int i, int *j)
{
	if (str[i] == '$' && str[i + 1] == '?')
		(*j)++;
	else
		while (str[i + *j] && ft_isvariable(str[i + *j]))
			(*j)++;
}

static t_arguments	*get_vars(char *str, t_arguments *vars)
{
	int	i;
	int	j;

	vars = check_str(str, vars, &i);
	while (str[i])
	{
		if (str[i] == '$' && !(str[i] != '$' || (str[i] == '$' && \
		str[i + 1] != '?' && (ft_isdigit(str[i + 1]) || \
		!ft_isvariable(str[i + 1]) || !str[i + 1]))))
		{
			j = 1;
			get_var_name(str, i, &j);
			if ((j > 1))
				vars = arguments_constructor(vars, ft_substr(str, i, j), \
					IS_VARIABLE, 0);
			i += j;
		}
		else
		{
			vars = get_vars(str + i, vars);
			break ;
		}
	}
	return (vars);
}

void	tokenize_variables(t_arguments **arguments)
{
	t_arguments	*head;
	t_arguments	*new;
	t_arguments	*tmp;

	new = NULL;
	head = *arguments;
	while (head)
	{
		if (head->type & IS_STR)
		{
			new = get_vars(head->str, NULL);
			if (new)
			{
				tmp = head;
				replace_arg(arguments, &head, new);
				free(tmp->str);
				free(tmp);
			}
		}
		else if (head->type & DQUOTE)
			tokenize_variables(&head->down);
		head = head->next;
	}
}
