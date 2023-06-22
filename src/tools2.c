/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 23:41:20 by aelbrahm          #+#    #+#             */
/*   Updated: 2023/06/21 17:03:10 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static size_t	len(char *str)
{
	return (ft_strlen(str));
}

t_list	*lst_dup(t_list *lst)
{
	t_list	*lst_ret;

	lst_ret = NULL;
	if (!lst)
		return (lst_ret);
	while (lst)
	{
		ft_lstadd_back(&lst_ret, ft_lstnew(ft_strdup(lst->content)));
		lst = lst->next;
	}
	return (lst_ret);
}

t_list	*sort_list(t_list *lst, int (*cmp)(const char *, const char *, size_t))
{
	t_list	*tmp;
	t_list	*cur;
	t_list	*st;

	st = NULL;
	while (lst)
	{
		cur = lst;
		lst = lst->next;
		if (!st || ((*cmp)(cur->content, st->content, len(cur->content))) < 0)
		{
			cur->next = st;
			st = cur;
		}
		else
		{
			tmp = st;
			while (tmp->next && ((*cmp)(cur->content, \
			tmp->next->content, ft_strlen(cur->content))) > 0)
				tmp = tmp->next;
			cur->next = tmp->next;
			tmp->next = cur;
		}
	}
	return (st);
}

void	env_exp_print(t_list *sort_lst)
{
	t_list	*tmp;

	tmp = sort_lst;
	while (tmp)
	{
		write(g_glb.out, "declare -x ", 11);
		ft_putendl_fd(tmp->content, g_glb.out);
		tmp = tmp->next;
	}
}

char	**env_vars(t_hold *env)
{
	t_list	*tmp;
	char	**_env;
	int		size;

	size = env->size;
	tmp = env->lst;
	_env = (char **)malloc((size * sizeof(char *)) + 1);
	if (env)
	{
		while (size--)
		{
			*_env = (char *)tmp->content;
			_env++;
			tmp = tmp->next;
		}
		*_env = NULL;
		return (_env - env->size);
	}
	return (NULL);
}
