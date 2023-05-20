/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments_controll.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 19:25:56 by aahlyel           #+#    #+#             */
/*   Updated: 2023/05/20 19:33:01 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_arguments	*arguments_constructor(t_arguments *arguments, char *str, unsigned short type)
{
	t_arguments	*new;
	t_arguments	*tmp;


	new = malloc(sizeof(t_arguments));
	if (!new)
		return (NULL);
	new->str = NULL;
	if (type != DQUOTE && type != QUOTE)
		new->str = str;
	new->type = type;
	new->next = NULL;
	new->down = NULL;
	if (type == DQUOTE || type == QUOTE)
	{
		new->down = arguments_constructor(new->down, str, IS_STR | type);
		// if (!(type & QUOTE))
		// 	new->down = tokenize_variables(new->down, type);
	}
	// else
	// 	new = tokenize_variables(new, type);
	if (!arguments)
		return (new);
	tmp = arguments;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	return (arguments);
}

void	arguments_destructor(t_arguments **arguments)
{
	t_arguments	*tmp;
	t_arguments	*head;

	tmp = *arguments;
	head = *arguments;
	while (head)
	{
		tmp = head;
		head = head->next;
		free (tmp->str);
		free (tmp);
	}
	*arguments = NULL;
}

t_arguments	*str_to_arguments(char *str)
{
	char		**splited;
	t_arguments	*arguments;

	arguments = NULL;
	return (arguments);
}

