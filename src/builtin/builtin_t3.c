/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_t3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbrahm <aelbrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 01:08:21 by aelbrahm          #+#    #+#             */
/*   Updated: 2023/06/16 04:46:32 by aelbrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	dp_point_skip(char *path)
{
	int	indx;

	indx = ft_strlen(path);
	while (indx > 0)
	{
		if (indx > 0 && path[indx - 1] == '/')
			indx--;
		while (indx > 0 && path[indx - 1] == '.')
			indx--;
		if (path[indx - 1] != '/' && path[indx - 1] != '.')
			break ;
	}
	return (indx);
}

short	is_export_var(char *str)
{
	t_hold	*hold;
	t_list	*lst_env;
	size_t	len;
	int		size;

	hold = set__get_option_variables(0, GET | GET_ENV);
	lst_env = hold->lst;
	len = ft_strlen(str);
	size = hold->size;
	while (size--)
	{
		if (!ft_strncmp(str, lst_env->content, len) \
		&& *((char *)lst_env->content + len) == '=')
			return (0);
		lst_env = lst_env->next;
	}
	while (lst_env)
	{
		if (!ft_strncmp(str, lst_env->content, ft_strlen(lst_env->content)))
			return (0);
		lst_env = lst_env->next;
	}
	return (1);
}

void	do_cmp(char	*val, char **lst_cnt, short opt, size_t len)
{
	t_hold	*hold;

	hold = set__get_option_variables(0, GET | GET_ENV);
	if (!*(*lst_cnt + len))
		hold->size++;
	if (!opt)
	{
		free(*lst_cnt);
		*lst_cnt = ft_strdup(val);
	}
	else
		*lst_cnt = ft_strjoin_free(*lst_cnt, ft_strdup(val));
}
