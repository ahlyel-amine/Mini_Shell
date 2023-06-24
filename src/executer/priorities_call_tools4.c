/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   priorities_call_tools4.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 23:52:36 by aahlyel           #+#    #+#             */
/*   Updated: 2023/06/24 20:22:28 by aahlyel          ###   ########.fr       */
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

int	skip_echo_option_down_up(t_arguments *front, int *has_option)
{
	char	*str;

	if (front->type & (IS_STR) && is_option(front->str, front->str + ft_strlen(front->str)))
	{
		*has_option |= ECHO_OPTION;
		return (1);	
	}
	if (front->type & (QUOTE | DQUOTE))
	{
		str = args_to_str(front->down);
		if (!is_option(str, str + ft_strlen(str)))
		{
			free(str);
			return (0);
		}
		free(str);
		*has_option |= ECHO_OPTION;
		return (1);
	}
	return (-1);
}

t_arguments	*skip_echo_option(t_arguments *front, int *has_option)
{
	int		ret;

	while (front)
	{
		if (front->type & IS_SEPARTOR)
		{
			front = front->next;
			continue ;
		}
		ret = skip_echo_option_down_up(front, has_option);
		if (!ret)
			break ;
		else if (ret == 1)
		{
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
