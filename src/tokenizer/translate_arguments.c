/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translate_arguments.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 17:44:08 by aahlyel           #+#    #+#             */
/*   Updated: 2023/06/07 14:28:12 by aahlyel          ###   ########.fr       */
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
		if ((tmp->type & IS_STR) || (tmp->type & IS_VARIABLE) || (tmp->type & IS_SEPARTOR))
		{
			while (tmp->str[i])
			{
				i++;
				len++;
			}
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

char	*args_to_str(t_arguments *args)
{
	t_arguments	*tmp;
	t_arguments	*f_tmp;
	char		*str;
	size_t		len;
	size_t		i;

	tmp = args;
	len = args_strslen(args);
	str = ft_calloc(sizeof(char), (len + 1));
	if (!str)
		return (perror(""), NULL);
	len = 0;
	while (tmp)
	{
		i = 0;
		if ((tmp->type & IS_STR) || (tmp->type & IS_VARIABLE) || (tmp->type & IS_SEPARTOR))
			while (tmp->str[i])
				str[len++] = tmp->str[i++];
		else if (tmp->type & QUOTE || tmp->type & DQUOTE)
			down_to_str(tmp->down, &str, &len);
		tmp = tmp->next;
	}
	return (str);
}

void	args_move_next_down(t_arguments **args, t_arguments **prev)
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

void	args_move_prev_down(t_arguments **args, t_arguments **prev)
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

void	args_join_next(t_arguments **args)
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

char	**args_to_cmd_dstr(t_arguments *args, char *cmd)
{
	t_arguments	*tmp;
	char		**str;
	char		*tmp_str;
	size_t		len;

	tmp = args;
	len = args_len(args);
	str = malloc(sizeof(char *) * (len + 2));
	if (!str)
		return (perror(""), NULL);
	str[0] = cmd;
	if (!len)
		return (str[1] = NULL, str);
	printf("[[%s]]\n", cmd);
	while (tmp)
	{
		if ((tmp->type & IS_STR || tmp->type & IS_VARIABLE))
			str[len++] = tmp->str;
		else if ((tmp->type & QUOTE || tmp->type & DQUOTE))
			str[len++] = args_to_str(tmp->down);
		tmp = tmp->next;
	}
	str[len] = NULL;
	return (str);
}

char	**args_to_dblstr(t_arguments *args)
{
	t_arguments	*tmp;
	char		**str;
	size_t		len;

	tmp = args;
	len = args_len(args);
	if (!len)
		return (NULL);
	str = malloc(sizeof(char *) * (len + 1));
	if (!str)
		return (perror(""), NULL);
	len = 0;
	while (tmp)
	{
		if (tmp->type & IS_STR || tmp->type & IS_VARIABLE)
			str[len++] = ft_strdup(tmp->str);
		else if ((tmp->type & QUOTE || tmp->type & DQUOTE))
			str[len++] = args_to_str(tmp->down);
		tmp = tmp->next;
	}
	str[len] = NULL;
	return (str);
}

// size_t	args_cmd_len(t_arguments *args)
// {
// 	t_arguments	*tmp;
// 	size_t		len;

// 	len = 0;
// 	tmp = args;
// 	while (tmp)
// 	{
// 		if (!(tmp->type & IS_SEPARTOR))
// 		len++;
// 		tmp = tmp->next;
// 	}
// 	return (len);
// }

// char	**args_to_cmd_dstr(t_arguments *args, char *cmd)
// {
// 	t_arguments	*tmp;
// 	char		**str;
// 	size_t		len;

// 	tmp = args;
// 	len = args_len(args);
// 	if (!len)
// 		return (NULL);
// 	str = malloc(sizeof(char *) * (len + 2));
// 	if (!str)
// 	{
// 		perror("");
// 		return (NULL);
// 	}
// 	len = 0;
// 	str[len++] = cmd;
// 	while (tmp)
// 	{
// 		if (tmp->type & IS_SEPARTOR)
// 			;
// 		else if ((tmp->type & IS_STR || tmp->type & IS_VARIABLE))
// 			str[len++] = ft_strdup(tmp->str);
// 		else
// 			str[len++] = args_to_str(tmp->down);
// 		tmp = tmp->next;
// 	}
// 	str[len] = NULL;
// 	return (str);
// }

