/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   priorities_call_tools.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 14:32:10 by aahlyel           #+#    #+#             */
/*   Updated: 2023/06/25 15:38:39 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	last_operaotr(t_lsttoken *front, t_lsttoken *back)
{
	t_lsttoken	*head;

	head = front;
	while (head)
	{
		if ((head->t_.type == E_AND || head->t_.type == E_OR))
			return (0);
		if (head == back)
			break ;
		head = head->next;
	}
	return (1);
}

t_lsttoken	*skip_tokens(t_lsttoken *head, t_lsttoken *back, int *start, \
int *end)
{
	while (head && (head->t_.type & (E_EMPTY | E_SPACE)))
	{
		if (head == back)
			break ;
		head = head->next;
	}
	if (!head || (head->t_.type & (E_EMPTY | E_SPACE)))
		return (NULL);
	*start = head->t_.start;
	*end = head->t_.len;
	return (head);
}

int	pipe_left(t_lsttoken *head, t_lsttoken *back)
{
	t_lsttoken	*tmp;

	tmp = head;
	while (tmp && tmp != back)
	{
		if (tmp->t_.type == E_PIPE)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

t_lsttoken	*skip_space_front_token(t_lsttoken *front)
{
	while (front && front->t_.type == E_SPACE)
		front = front->next;
	return (front);
}

void	init_2ptr(t_lsttoken **head, t_lsttoken **prev, t_lsttoken *front)
{
	*head = front;
	*prev = front;
}
