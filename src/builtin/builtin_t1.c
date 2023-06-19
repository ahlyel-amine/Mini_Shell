/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_t1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 04:40:27 by aelbrahm          #+#    #+#             */
/*   Updated: 2023/06/19 16:37:24 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

size_t	args_len_(t_arguments *args)
{
	t_arguments	*tmp;
	t_arguments	*d_tmp;
	size_t		len;

	len = 0;
	tmp = args;
	while (tmp)
	{
		if (tmp->type & QUOTE || tmp->type & DQUOTE)
			len++;
		else if (!tmp->next || tmp->type & IS_SEPARTOR)
			len++;
		else if (tmp->type & IS_FILE)
			len++;
		tmp = tmp->next;
	}
	return (len);
}

static char	**args_dstr_alloc(t_arguments *args)
{
	t_arguments	*tmp;
	char		**str;
	size_t		len;

	tmp = args;
	len = args_len_(args);
	if (!len)
		return (NULL);
	str = ft_calloc(sizeof(char *), len + 1);
	if (!str)
		critical_err();
	return (str);
}

t_arguments	*ft_join_args_dstr(t_arguments *tmp, char **str, size_t *indx)
{
	char	*stack;

	stack = ft_strdup("");
	while ((tmp) && (tmp)->type != IS_SEPARTOR)
	{
		if (tmp->down)
			stack = ft_strjoin_free(stack, args_to_str((tmp)->down));
		else
			stack = ft_strjoin_free(stack, ft_strdup((tmp)->str));
		(tmp) = (tmp)->next;
	}
	str[*indx] = stack;
	*indx += 1;
	return (tmp);
}

char	**args_to_dblstr_(t_arguments *args)
{
	t_arguments	*tmp;
	char		**str;
	char		*tst;
	size_t		len;

	str = args_dstr_alloc(args);
	if (!str)
		return (NULL);
	len = 0;
	tmp = args;
	while (tmp)
	{
		if (tmp->type & IS_FILE)
		{
			str[len++] = ft_strdup(tmp->str);
			tmp = tmp->next;
		}
		else if (tmp->type & IS_STR || tmp->type & IS_VARIABLE)
			tmp = ft_join_args_dstr(tmp, str, &len);
		else if ((tmp->type & QUOTE || tmp->type & DQUOTE))
		{
			str[len++] = args_to_str(tmp->down);
			tmp = tmp->next;
		}
		else
			tmp = tmp->next;
	}
	return (str);
}
