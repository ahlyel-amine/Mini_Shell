/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbrahm <aelbrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 03:05:02 by aelbrahm          #+#    #+#             */
/*   Updated: 2023/06/24 20:14:42 by aelbrahm         ###   ########.fr       */
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

t_arguments	*args_cat(char *args, t_arguments *tmp, \
t_arguments	*prev, t_arguments **arg)
{
	t_arguments	*new;

	new = get_argument_no_tknz(args, 0);
	free (args);
	if (prev != *arg || tmp != prev)
		prev->next = new;
	else if (prev == *arg && tmp == prev)
		*arg = new;
	while (new->next)
		new = new->next;
	new->next = tmp->next;
	free(tmp);
	return (new);
}

void	var_expand(t_arguments **arg)
{
	t_arguments	*prev;
	t_arguments	*tmp;
	char		*arg_str;

	tmp = *arg;
	prev = *arg;
	while (tmp)
	{
		if (tmp->type & IS_VARIABLE)
		{
			arg_str = is_env_var(tmp->str);
			if (!*arg_str)
			{
				tmp->str = arg_str;
				prev = tmp;
				tmp = tmp->next;
				continue ;
			}
			tmp = args_cat(arg_str, tmp, prev, arg);
		}
		else if (tmp->type == DQUOTE)
			var_expand(&tmp->down);
		prev = tmp;
		tmp = tmp->next;
	}
}

void	expand_line(t_arguments **arg)
{
	t_arguments	*expand;
	t_arguments	*tmp;

	expand = *arg;
	if (*arg)
	{	
		var_expand(arg);
		tmp = *arg;
		while (tmp)
		{
			if (tmp->type == IS_STR)
				tmp->str = tilde_expansion(tmp->str, tmp->type, tmp->next);
			tmp = tmp->next;
		}	
	}
}
