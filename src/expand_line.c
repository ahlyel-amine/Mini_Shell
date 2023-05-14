/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbrahm <aelbrahm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 03:05:02 by aelbrahm          #+#    #+#             */
/*   Updated: 2023/05/14 06:46:03 by aelbrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*tilde_replace(char *arg)
{
	char	*ret;
	char	*_HOME;
	size_t	len;
	len = ft_strlen(arg);
	_HOME = getenv("HOME"); 
	if (len == 1)
	{	if (_HOME)
			return (ft_strdup(_HOME));
		return (ft_strdup(""));}
	else if (len > 1 && (*(arg + 1) == '+' || *(arg + 1) == '-'))
	{
		if ((*(arg + 1) == '+' && !*(arg + 2)) || (len > 2 && *(arg + 1) == '+' && *(arg + 2) == '/'))
		{
			_HOME = get_owd("PWD=");
			if (_HOME)
				return (ft_strjoin(_HOME, (arg + 2)));
			else
				return (ft_strdup(""));
		}
		else if ((*(arg + 1) == '-' && !*(arg + 2)) || (len > 2 && *(arg + 1) == '-' && *(arg + 2) == '/'))
		{
			_HOME = get_owd("OLDPWD=");
			if (_HOME)
				return (ft_strjoin(_HOME, (arg + 2)));
			else
				return (ft_strdup(""));
		}
		else
			return (ft_strdup(arg));
	}
}

void	tilde_expansion(t_arguments *arg)
{
	char	*tilde;

	tilde = arg->str;
	if (!*tilde || *tilde != '~')
		return ;
	else if (*tilde == '~')
	{
		arg->str = tilde_replace(tilde);
		free(tilde);
	}	
}
char	*is_env_var(char *str)
{
    t_hold  *hold;
    t_list  *lst_env;
    size_t  len;
    int size;
    hold = set__get_option_variables(0, GET | GET_ENV);
    lst_env = hold->lst;
    len = ft_strlen(str) - 1;
    size = hold->size;
    while (size--)
    {
        if (!ft_strncmp((str + 1), lst_env->content, len) && *((char *)lst_env->content + len) == '=')
            return (free(str), ft_strdup((char *)lst_env->content + len + 1));
        lst_env = lst_env->next;
    }
	return (free(str), ft_strdup(str));
}

void	var_expand(t_arguments *arg)
{
	t_arguments	*tmp;
	char		*arg_str;
	char		*store;
	tmp = arg;
	while (tmp)
	{
		arg_str = tmp->str;
		if (arg_str && tmp->type == 0x0)
		{
			tmp->str = is_env_var(tmp->str);
		}
		tmp = tmp->next; 
	}
}

void	*expand_line(t_arguments *arg)
{
	t_arguments	*expand;

	expand = arg;
	if (arg)
	{	
	printf(" === %s === \n", arg->str);
		tilde_expansion(arg);
	var_expand(arg);
	printf(" --- %s --- \n", arg->str);
	}
}