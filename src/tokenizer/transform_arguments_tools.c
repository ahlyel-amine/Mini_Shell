/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_arguments_tools.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbrahm <aelbrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 22:03:38 by aahlyel           #+#    #+#             */
/*   Updated: 2023/06/24 20:17:49 by aelbrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

size_t	args_len(t_arguments *args)
{
	t_arguments	*tmp;
	size_t		len;

	len = 0;
	tmp = args;
	while (tmp)
	{
		len++;
		tmp = tmp->next;
	}
	return (len);
}

size_t	args_strslen(t_arguments *args)
{
	t_arguments	*tmp;
	size_t		len;
	size_t		i;

	len = 0;
	tmp = args;
	while (tmp)
	{
		i = 0;
		if ((tmp->type & IS_STR) || (tmp->type & IS_VARIABLE) || \
		(tmp->type & IS_SEPARTOR))
		{
			while (tmp->str[i])
			{
				i++;
				len++;
			}
			if (tmp->type & IS_FILE)
				len++;
		}
		else if (tmp->type & QUOTE || tmp->type & DQUOTE)
			len += args_strslen(tmp->down);
		tmp = tmp->next;
	}
	return (len);
}

void	down_to_str(t_arguments *args, char **str, size_t *len)
{
	t_arguments	*tmp;
	size_t		i;

	tmp = args;
	while (tmp)
	{
		i = 0;
		while (tmp->str[i])
			(*str)[(*len)++] = tmp->str[i++];
		tmp = tmp->next;
	}
}

void	transform_args(t_arguments **args)
{
	t_arguments	*nl;

	if (!*args)
		return ;
	if ((*args)->type == IS_SEPARTOR)
	{
		nl = *args;
		*args = (*args)->next;
		free(nl->str);
		free(nl);
	}
	nl = NULL;
	expand_line(args);
	wild_cards(args);
	args_join(args);
	args_move_down(args, &nl);
	args_join_down(args);
}
