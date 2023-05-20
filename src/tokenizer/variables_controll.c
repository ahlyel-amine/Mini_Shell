/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables_controll.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 19:27:25 by aahlyel           #+#    #+#             */
/*   Updated: 2023/05/20 19:31:45 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_arguments	*get_vars(char *str)
{
	t_arguments	*vars;
	int			i;
	int			j;

	i = 0;
	vars = NULL;
	while (str[i])
	{
		if (str[i] == '$')
		{
			j = 1;
			if (ft_isdigit(str[i + 1]) || !ft_isvariable(str[i + 1]))
			{
				i++;
				continue ;
			}
			while (ft_isvariable(str[i + j]))
				j++;
			vars = arguments_constructor(vars, ft_substr(str, i, j), IS_VARIABLE);
			i += j;
		}
		else
		{
			j = 0;
			while (str[i + j] && str[i + j] != '$')
				j++;
			if (j)
				vars = arguments_constructor(vars, ft_substr(str, i, j), IS_STR);
			i += j;
		}
	}
	return (vars);
}

void	tokenize_variables(t_arguments **arguments)
{
	t_arguments	*head;
	t_arguments	*prev;
	t_arguments	*new;
	
	new = NULL;
	head = *arguments;
	prev = *arguments;
	while (head)
	{
			// printf("head|%d|%d|%s|\n", head->type & QUOTE, head->type & DQUOTE, head->str);
			// printf("prev|%d|%d|%s|\n", head->type & QUOTE, head->type & DQUOTE, head->str);
		if (head->type & IS_STR && head->str[0] == '$' && ft_isdigit(head->str[1]))
		{
			new = get_vars(head->str);
			if (head == prev)
				head = new;
			else
				prev->next = new;
			prev = new;
			while (new)
				new = new->next;
			if (new)
			new->next = head->next;
			// free (head);
			// free (head->str);
			head = prev;
		}
		prev = head;
		head = head->next;
	}
}