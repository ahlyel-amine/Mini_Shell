/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbrahm <aelbrahm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 03:05:02 by aelbrahm          #+#    #+#             */
/*   Updated: 2023/05/25 16:21:44 by aelbrahm         ###   ########.fr       */
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
	else if (len > 1 && (*(arg + 1) == '/' || *(arg + 1) == ' '))
	{
		if (_HOME)
			return (ft_strjoin(_HOME, (arg + 1)));
		return (ft_strjoin("", (arg + 1)));
	}
	else if (len > 1 && (*(arg + 1) == '+' || *(arg + 1) == '-'))
	{
		if ((*(arg + 1) == '+' && !*(arg + 2)) || (len >= 2 && *(arg + 1) == '+' && (*(arg + 2) == '/' || *(arg + 2) == 0x20)))
		{
			_HOME = get_owd("PWD=");
			if (_HOME)
				return (ft_strjoin(_HOME, (arg + 2)));
			else
				return (ft_strdup(""));
		}
		else if ((*(arg + 1) == '-' && !*(arg + 2)) || (len > 2 && *(arg + 1) == '-' && (*(arg + 2) == '/') || *(arg + 2) == 0x20))
		{
			_HOME = get_owd("OLDPWD=");
			if (_HOME)
				return (ft_strjoin(_HOME, (arg + 2)));
			else
				return (ft_strdup(""));
		}
		// else
		// 	return (ft_strdup(arg));
	}
	return (ft_strdup(arg));
}
int	space_skip(char	*str)
{
	int	iter;

	iter = 0;
	while (str[iter] && str[iter] == ' ')
		iter++;
	return (iter);
	
}
// void	tilde_expansion(t_arguments *arg)
// {
// 	char	*tilde;
// 	char	*tmp;

// 	tmp = arg->str;
// 	if (arg->type == 1)
// 		arg->str = ft_strdup(tmp + space_skip(arg->str)); 
// 	tilde = arg->str;
// 	if (!*tilde || *tilde != '~')//spaceskip
// 		return ;
// 	else if (*tilde == '~' && arg->type != 3)
// 	{
// 		arg = tilde_replace(tilde);
// 		free(tilde);
// 		return (arg);
// 	}
// 	return (arg);
// 		puts("HERE");
// 		arg = (t_arguments *)tilde_replace(tilde);
// 		free(tilde);
// 		printf("tilde => %p\n", arg);
// 		// return (arg);
// 	}	
// }
char	*tilde_expansion(char *arg, unsigned short type)
{
	char	*tilde;
	tilde = (arg);
	if (!*tilde || *tilde != '~')
		return (arg);
	else if (*tilde == '~' && !(type & QUOTE))
	{
		arg = tilde_replace(tilde);
		free(tilde);
		return (arg);
	}
	return (arg);
}

char	*is_env_var(char *str)
{
    t_hold  *hold;
    t_list  *lst_env;
    size_t  len;
    int size;
    hold = set__get_option_variables(0, GET | GET_ENV);
    lst_env = hold->lst;
    len = ft_strlen(str);
    size = hold->size;
    while (size--)
    {
        if (!ft_strncmp((str + 1), lst_env->content, len - 1) && *((char *)lst_env->content + (len - 1)) == '=')
            return (free(str), ft_strdup((char *)lst_env->content + len));
        lst_env = lst_env->next;
    }
	//SEGV::ABoRT
	return (free(str), ft_strdup(""));
}

// int		var_len(char *str)
// {
// 	int	iter = 0;
// 	while (str[iter] && (ft_isalnum(str[iter]) || str[iter] == '_'))
// 		iter++;
// 	return (iter);
// }
char	*var_str(char *arg)
{
	int	iter;
	char	*tmp;

	iter = 1;
	if (*arg && arg[iter] == '$')
		return (arg);
	if (arg[iter] == '?')
	{
		tmp = ft_strjoin("", ft_itoa(glo_exit));
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
// char	*data_manipulate(char *str)
// {
// 	int	iter = 0;
// 	char	*tmp = str + 1;
// 	while (tmp[iter] && !ft_isalpha(tmp[iter]) && tmp[iter] != '_')
// 		iter++;
// 	if (!tmp[iter])
// 	{
// 		tmp = ft_strdup("");
// 		free(str);
// 		return ((tmp));
// 	}
// 	else if (iter)
// 	{
// 		tmp = ft_strndup(tmp + iter, ft_strlen(tmp + iter));
// 		free(str);
// 		return ((tmp));
// 	}
// 	else
// 	{
// 		tmp = is_env_var(str);
// 		free(str);
// 		return ((tmp));
// 	}
// }
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
// char	*data_analyse(char *arg)
// {
// 	char	*tmp;
// 	char	*symbol;
// 	t_list	*lst;
// 	size_t	len;

// 	lst = NULL;
// 	tmp = arg;
// 	symbol = ft_strchr(tmp, '$');
// 	if (!symbol)
// 		return (arg);
// 	len = 0;
// 	while (len < ft_strlen(arg))
// 	{
// 		symbol = ft_strchr(tmp + len, '$');
// 		if (symbol)
// 		{
// 			if (symbol != (tmp + len))
// 				ft_lstadd_back(&lst, ft_lstnew(ft_strndup(tmp + len, (symbol - (tmp + len)))));
// 			ft_lstadd_back(&lst, ft_lstnew(data_manipulate(ft_strndup(symbol, var_len(symbol + 1) + 1))));
// 		}
// 		else
// 		{
// 			ft_lstadd_back(&lst, ft_lstnew(ft_strndup(tmp + len, ft_strlen(tmp + len))));
// 			break ;
// 		}
// 			len += (symbol - (tmp + len)) + (var_len(symbol + 1) + 1);
// 	}
// 	return (free(arg), nodes_join(lst));
// }

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
		else if (tmp->type == IS_STR)
		{
			tmp->str = data_analyse(tmp->str);
		}	
		else if (tmp->type == DQUOTE)
		{
			down = tmp->down;
			var_expand(down);
		}
		tmp = tmp->next;
	}
}

void	*expand_line(t_arguments *arg)
{
	t_arguments	*expand;
	t_arguments	*tmp;
	expand = arg;
	if (arg)
	{	
	// printf(" %d --- %s --- \n", arg->type, arg->str);
	// tilde_expansion(expand);
		var_expand(arg);
		tmp = arg;
		while (tmp)
		{
			if (tmp->type == IS_STR)
				tmp->str = tilde_expansion(tmp->str, tmp->type);	
			tmp= tmp->next;
		}
		puts("<<-------------------------------->>");	
	}
	return (NULL);
}
