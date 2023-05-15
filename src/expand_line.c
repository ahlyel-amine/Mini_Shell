/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbrahm <aelbrahm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 03:05:02 by aelbrahm          #+#    #+#             */
/*   Updated: 2023/05/15 08:56:11 by aelbrahm         ###   ########.fr       */
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
	{
		if (_HOME)
			return (ft_strdup(_HOME));
		return (ft_strdup(""));
	}
	else if (len > 1 && *(arg + 1) == '/')
	{
		if (_HOME)
			return (ft_strjoin(_HOME, (arg + 1)));
		return (ft_strjoin("", (arg + 1)));
	}
	else if (len > 1 && (*(arg + 1) == '+' || *(arg + 1) == '-'))
	{
		if ((*(arg + 1) == '+' && !*(arg + 2)) || (len >= 2 && *(arg + 1) == '+' && *(arg + 2) == '/'))
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
	return (NULL);
}
int	space_skip(char	*str)
{
	int	iter;

	iter = 0;
	while (str[iter] && str[iter] == ' ')
		iter++;
	return (iter);
	
}
void	tilde_expansion(t_arguments *arg)
{
	char	*tilde;
	char	*tmp;

	tmp = arg->str;
	if (arg->type == 1)
		arg->str = ft_strdup(tmp + space_skip(arg->str)); 
	tilde = arg->str;
	if (!*tilde || *tilde != '~')
		return ;
	else if (*tilde == '~' && arg->type != 3)
	{
		if (arg->type == 1)
			free(tmp);
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
	//SEGV::ABoRT
	return (free(str), ft_strdup(str));
}
char	*data_analyse(char *arg)
{
	char	*tmp;
	char	*symbol;
	t_list	*lst;
	
	lst = NULL;
	tmp = arg;
	
	// while (*tmp)
	// {
		symbol = ft_strchr(tmp, '$');
		if (symbol)
		{
			ft_lstadd_back(&lst, ft_lstnew(ft_strndup(tmp, (symbol - tmp))));
		}
			tmp += (symbol - tmp);
	// 		puts("ALO");
	// }
	return (lst->content);
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
		if (arg_str && tmp->type == IS_VARIABLE)
			tmp->str = is_env_var(tmp->str);
		if (arg_str && tmp->type == IS_STR)
		{
			printf("[÷÷ %s ÷÷]\n", data_analyse(arg_str));
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
	printf(" %d --- %s --- \n", arg->type, arg->str);
		tilde_expansion(expand);
	var_expand(arg);
	puts("<<tst>>");
	while (expand)
	{
		printf(" %d --- %s --- \n", expand->type, (expand->str));
		expand = expand->next;
	}	
	}
	return (NULL);
}