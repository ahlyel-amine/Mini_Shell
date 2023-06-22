/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translate_arguments2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 22:20:09 by aahlyel           #+#    #+#             */
/*   Updated: 2023/06/20 16:18:01 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	replace_arg_first_element(t_arguments **head, \
t_arguments **old, t_arguments *new, \
t_arguments *replace_old)
{
	t_arguments	*tmp;

	if (*head == (*old))
	{
		tmp = (*head)->next;
		*head = new;
		while (new->next)
			new = new->next;
		new->next = tmp;
		*old = replace_old;
	}
}

void	replace_arg(t_arguments **head, t_arguments **old, t_arguments *new)
{
	t_arguments	*tmp;
	t_arguments	*replace_old;

	if (!new)
		return ;
	replace_old = new;
	replace_arg_first_element(head, old, new, replace_old);
	tmp = *head;
	while (tmp)
	{
		if (tmp->next == (*old))
		{
			tmp->next = new;
			while (new->next)
				new = new->next;
			new->next = (*old)->next;
			*old = replace_old;
		}
		tmp = tmp->next;
	}
}

void	merge_arguments(t_arguments **arguments, int is_dquote)
{
	t_arguments	*head;
	t_arguments	*new;
	t_arguments	*tmp;

	if (!*arguments)
		return ;
	new = NULL;
	head = *arguments;
	while (head)
	{
		if (head->type & IS_STR)
		{
			new = ft_split_str_to_args(head->str, is_dquote);
			if (new)
			{
				tmp = head;
				replace_arg(arguments, &head, new);
				free (tmp->str);
				free(tmp);
			}
		}
		else if (head->type & DQUOTE)
			merge_arguments(&head->down, 1);
		head = head->next;
	}
}

void	args_join_down(t_arguments **args)
{
	t_arguments	*tmp;
	t_arguments	*d_tmp;

	tmp = *args;
	while (tmp && tmp->next)
	{
		if (tmp->down && tmp->next->down)
		{
			d_tmp = tmp->down;
			while (d_tmp->next)
				d_tmp = d_tmp->next;
			d_tmp->next = tmp->next->down;
			d_tmp = tmp->next;
			tmp->next = tmp->next->next;
			free(d_tmp);
			tmp = *args;
			continue ;
		}
		tmp = tmp->next;
	}
}
