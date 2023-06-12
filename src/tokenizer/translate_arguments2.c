/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translate_arguments2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 22:20:09 by aahlyel           #+#    #+#             */
/*   Updated: 2023/06/12 22:21:37 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	replace_arg(t_arguments **head, t_arguments **old, t_arguments *new)
{
	t_arguments	*tmp;
	t_arguments	*replace_old;
	t_arguments	*prev;

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

void	remove_arg(t_arguments **arguments, t_arguments **to_remove)
{
	t_arguments	*tmp;
	t_arguments	*rem;

	tmp = *arguments;
	while (tmp)
	{
		if (!tmp->next && tmp == *to_remove)
		{
			tmp = NULL;
			break ;
		}
		else if (tmp->next == *to_remove)
		{
			tmp = tmp->next->next;
			break ;
		}
	}
	free ((*to_remove)->str);
	free (*to_remove);
	*to_remove = tmp;
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
