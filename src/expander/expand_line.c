/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbrahm <aelbrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 03:05:02 by aelbrahm          #+#    #+#             */
/*   Updated: 2023/06/18 22:59:56 by aelbrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*is_env_var(char *str)
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
		if (!ft_strncmp((str + 1), lst_env->content, len - 1) && \
				*((char *)lst_env->content + (len - 1)) == '=')
			return (free(str), ft_strdup((char *)lst_env->content + len));
		lst_env = lst_env->next;
	}
	return (free(str), ft_strdup(""));
}

char	*var_str(char *arg)
{
	int		iter;
	char	*tmp;

	iter = 1;
	if (*arg && arg[iter] == '$')
		return (arg);
	if (arg[iter] == '?')
	{
		tmp = ft_strjoin_free(ft_strdup(""), ft_itoa(glo_exit));
		if (!arg[++iter])
			return (free(arg), tmp);
		else
		{
			tmp = ft_strjoin_free(tmp, ft_strdup(arg + iter));
			return (free(arg), tmp);
		}	
	}	
	else if ((arg[iter] != '_' && !ft_isalpha(arg[iter])))
		iter++;
	tmp = arg;
	if (arg[iter])
		arg = ft_strdup((arg + iter));
	else
		arg = ft_strdup("");
	return (free(tmp), arg);
}

char	*data_analyse(char *arg)
{
	char	*tmp;

	tmp = ft_strchr(arg, '$');
	if (!tmp || tmp != arg || (tmp && ft_strlen(arg) == 1))
		return (arg);
	else
	{
		if (ft_strlen(arg) > 1 && arg[1] == '$')
			return (arg);
		else
		{
			if (ft_isalpha(arg[1]) || arg[1] == '_')
				return (is_env_var(arg));
			else
				return (var_str(arg));
		}
	}
}

void	var_expand(t_arguments *arg)
{
	t_arguments	*tmp;
	t_arguments	*down;
	char		*arg_str;
	char		*store;

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
