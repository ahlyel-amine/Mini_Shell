/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   priorities_call_tools4.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 23:52:36 by aahlyel           #+#    #+#             */
/*   Updated: 2023/06/22 23:24:45 by aahlyel          ###   ########.fr       */
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

t_arguments	*skip_echo_option(t_arguments *front, int *has_option)
{
	char	*str;
	while (front)
	{
		if (front->type & IS_SEPARTOR)
		{
			front = front->next;
			continue ;
		}
		if (front->type & (IS_STR) && is_option(front->str, front->str + ft_strlen(front->str)))
		{
			*has_option |= ECHO_OPTION;
			front = front->next;
			continue ;	
		}
		else if (front->type & (QUOTE | DQUOTE))
		{
			str = args_to_str(front->down);
			if (!is_option(str, str + ft_strlen(str)))
			{
				free(str);
				break ;
			}
			free(str);
			*has_option |= ECHO_OPTION;
			front = front->next;
			continue ;
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
