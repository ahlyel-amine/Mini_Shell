/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translate_arguments.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 17:44:08 by aahlyel           #+#    #+#             */
/*   Updated: 2023/06/13 01:01:57 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	args_move_next_down(t_arguments **args, t_arguments **prev)
{
	t_arguments	*tmp;
	t_arguments	*down;

	tmp = *args;
	if (!*prev && !((*args)->type & IS_SEPARTOR) && \
	!((*args)->type & QUOTE) && !((*args)->type & DQUOTE) && \
	((*args)->next->type & DQUOTE || (*args)->next->type & QUOTE))
	{
		tmp = *args;
		*args = (*args)->next;
		tmp->next = (*args)->down;
		(*args)->down = tmp;
		return ;
	}
	else if (*prev && !((*args)->type & IS_SEPARTOR) && \
	!((*args)->type & QUOTE) && !((*args)->type & DQUOTE) && \
	((*args)->next->type & DQUOTE || (*args)->next->type & QUOTE))
	{
		(*prev)->next = (*args)->next;
		tmp->next = (*args)->down;
		(*args)->down = tmp;
	}
}

static void	args_move_prev_down(t_arguments **args, t_arguments **prev)
{
	t_arguments	*tmp;
	t_arguments	*down;

	tmp = *args;
	if (((*args)->type & DQUOTE || (*args)->type & QUOTE) && \
	!((*args)->next->type & QUOTE) && !((*args)->next->type & DQUOTE) && \
	!((*args)->next->type & IS_SEPARTOR))
	{
		tmp = (*args)->next;
		(*args)->next = (*args)->next->next;
		tmp->next = NULL;
		arguments_add_back(&((*args)->down), tmp);
		return ;
	}
}

static void	args_join_next(t_arguments **args)
{
	t_arguments	*tmp;
	char		*tmp_str;

	if ((!((*args)->type & IS_SEPARTOR) && \
	!((*args)->type & QUOTE) && !((*args)->type & DQUOTE) && \
	!((*args)->next->type & IS_SEPARTOR) && \
	!((*args)->next->type & QUOTE) && !((*args)->next->type & DQUOTE)) && \
	(!((*args)->type & IS_FILE) && !((*args)->next->type & IS_FILE)))
	{
		tmp = (*args)->next;
		tmp_str = (*args)->str;
		(*args)->str = ft_strjoin((*args)->str, (*args)->next->str);
		(*args)->next = (*args)->next->next;
		free (tmp_str);
		free (tmp->str);
		free (tmp);
	}
}

void	args_join(t_arguments **args)
{
	if (*args && (*args)->next)
	{
		args_join_next(args);
		args_join(&((*args)->next));
	}
}

void	args_move_down(t_arguments **args, t_arguments **prev)
{
	if (*args && (*args)->next)
	{
		args_move_next_down(args, prev);
		if ((*args)->next)
			args_move_prev_down(args, prev);
		*prev = *args;
		args_move_down(&((*args)->next), prev);
	}
}
