/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 03:05:02 by aelbrahm          #+#    #+#             */
/*   Updated: 2023/06/20 16:21:18 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*is_env_var(char *str)
{
	t_hold	*hold;
	t_list	*lst_env;
	size_t	len;
	int		size;

	if (!ft_strncmp(str, "$?", 3))
		return (free(str), ft_itoa(g_glb.exit_val));
	hold = set__get_option_variables(0, GET | GET_ENV);
	lst_env = hold->lst;
	len = ft_strlen(str);
	size = hold->size;
	while (size--)
	{
		if (!ft_strncmp((str + 1), lst_env->content, len - 1) && \
				*((char *)lst_env->content + (len - 1)) == '=')
			return (free(str), ft_strdup((char *)lst_env->content + len));
		lst_env = lst_env->next;
	}
	return (free(str), ft_strdup(""));
}

void	var_expand(t_arguments *arg)
{
	t_arguments	*tmp;
	t_arguments	*down;
	char		*arg_str;

	tmp = arg;
	while (tmp)
	{
		arg_str = tmp->str;
		if (tmp->type & IS_VARIABLE)
			tmp->str = is_env_var(tmp->str);
		else if (tmp->type == DQUOTE)
		{
			down = tmp->down;
			var_expand(down);
		}
		tmp = tmp->next;
	}
}

void	expand_line(t_arguments *arg)
{
	t_arguments	*expand;
	t_arguments	*tmp;

	expand = arg;
	if (arg)
	{	
		var_expand(arg);
		tmp = arg;
		while (tmp)
		{
			if (tmp->type == IS_STR)
				tmp->str = tilde_expansion(tmp->str, tmp->type, tmp->next);
			tmp = tmp->next;
		}	
	}
}
