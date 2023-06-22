/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   priorities_call_tools4.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 23:52:36 by aahlyel           #+#    #+#             */
/*   Updated: 2023/06/20 23:54:14 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_option(char *line, char *endline)
{
	int	i;
	int	is_op;

	i = 0;
	if (line[i] == '\'' || line[i] == '\"')
		i++;
	if (line[i] == '-')
		i++;
	else
		return (0);
	is_op = i;
	while (line[i] == 'n' && line + i != endline)
		i++;
	if (is_op == i)
		return (0);
	if (line + i == endline || ((line[i] == '\'' || line[i] == '\"') && \
	line + i + 1 == endline))
		return (1);
	return (0);
}

t_lsttoken	*skip_echo_option(t_lsttoken *front, int *has_option)
{
	*has_option = 0;
	while (front)
	{
		if (front->t_.type & (E_STR | E_QUOTE | E_DQUOTE))
		{
			if (!is_option(front->t_.line + front->t_.start, front->t_.line \
			+ front->t_.start + front->t_.len))
				break ;
			else
			{
				if (front && front->next && front->next->t_.type != E_SPACE)
					break ;
				*has_option = 1;
				front = front->next;
				while (front && front->t_.type == E_SPACE)
					front = front->next;
				if (front)
					continue ;
			}
		}
		break ;
	}
	return (front);
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
