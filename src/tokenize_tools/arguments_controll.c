/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments_controll.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 19:25:56 by aahlyel           #+#    #+#             */
/*   Updated: 2023/06/19 19:19:57 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_arguments	*arguments_constructor(t_arguments *arguments, char *str, \
unsigned short type, unsigned short q)
{
	t_arguments	*new;
	t_arguments	*tmp;

	new = malloc(sizeof(t_arguments));
	if (!new)
		return (NULL);
	new->str = NULL;
	new->q = q;
	if (type != DQUOTE && type != QUOTE)
		new->str = str;
	new->type = type;
	new->next = NULL;
	new->down = NULL;
	if (type == DQUOTE || type == QUOTE)
		new->down = arguments_constructor(new->down, str, IS_STR | type, 0);
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
		if (head->type & IS_STR || head->type & IS_VARIABLE || \
		head->type & IS_SEPARTOR)
		{
			tmp = head;
			head = head->next;
			free (tmp->str);
			free (tmp);
		}
		else if (head->type & DQUOTE || head->type & QUOTE)
		{
			tmp = head;
			head = head->next;
			arguments_destructor(&tmp->down);
			free(tmp);
		}
	}
	*arguments = NULL;
}

void	arguments_add_back(t_arguments **head, t_arguments *new)
{
	t_arguments	*tmp;

	tmp = *head;
	if (!*head)
	{
		*head = new;
		return ;
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

t_arguments	*still_args(char *str, int *j, int *i, t_arguments *args)
{
	static int	is_dquote;

	if (!str && !i && !args)
	{
		is_dquote = *j;
		return (NULL);
	}
	if (ft_isspace(str[*i + *j - 1]) && !is_dquote)
		args = arguments_constructor(args, ft_strdup(" "), IS_SEPARTOR, 0);
	else
		args = arguments_constructor(args, ft_substr(str, *i, *j), IS_STR, 0);
	*i += *j;
	return (args);
}
