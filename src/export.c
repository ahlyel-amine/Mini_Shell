/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbrahm <aelbrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 18:55:07 by aelbrahm          #+#    #+#             */
/*   Updated: 2023/05/12 03:40:06 by aelbrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
void	sp_free(char **splt)
{
	int	iter;

	iter = -1;
	while (splt[++iter])
		free(splt[iter]);
	free(splt);
}

int valid_id(char *var)
{
    if (!(ft_isalpha(*var) || *var == '_'))
        return (1);
    while (*var && *var != '=' && *var != '+')
    {    
        if (!(ft_isalnum(*var) || *var == '_'))
            return (1);
        var++;
    }
    if (*var && *var == '+' && !*(var + 1))
        return (1);
    else if (*var && *var == '+' && *(var + 1) != '=')
        return (1);
    return (0);
}
short is_export_var(char *str)
{
    t_hold  *hold;
    t_list  *lst_tmp;
    t_list  *lst_env;
    size_t  len;

    hold = set__get_option_variables(0, GET | GET_ENV);
    lst_tmp = hold->lst_ex;
    lst_env = hold->lst;
    len = ft_strlen(str);
    while (lst_tmp)
    {
        if (!ft_strncmp(str, lst_tmp->content, len))
            return (0);
        lst_tmp = lst_tmp->next;
    }
    while (lst_env)
    {
        if (!ft_strncmp(str, lst_env->content, len) && *((char *)lst_env->content + len) == '=')
            return (0);
        lst_env = lst_env->next;
    }
    return (1);
}

short re_env_var(char *str, char *val, int opt)
{
    t_hold  *hold;
    t_list  *lst_tmp;
    size_t  len;

    hold = set__get_option_variables(0, GET | GET_ENV);
    lst_tmp = hold->lst;
    len = ft_strlen(str);
    while (lst_tmp)
    {
        if(!ft_strncmp(str, lst_tmp->content, len) && *((char *)lst_tmp->content + len) == '=' && !opt)
        {
            free(lst_tmp->content);
            lst_tmp->content = val;
            return (free(str), 1);
        }
        else if (!ft_strncmp(str, lst_tmp->content, len) && *((char *)lst_tmp->content + len) == '=' && opt)
        {
            
            lst_tmp->content = ft_strjoin_free(lst_tmp->content, val);
            return (free(str), 1);
        }
        lst_tmp = lst_tmp->next;
    }
    return (free(str), free(val), 0);
}

char    *app_dup(char *arg)
{
    char    *buf;
    int     iter;
    buf = (char *)malloc((ft_strlen(arg)) * sizeof(char));
    iter = 0;
    while (*arg)
    {
        if (*arg == '+')
            arg++;
        buf[iter] = *arg;
        iter++;
        arg++;
    }
    return (buf);
}

void    val(char *arg)
{
    t_hold  *env;
    char    *append;
    char    *replace;
    size_t  len;

    len = ft_strlen(arg);
    append = ft_memchr(arg, '+', len);
    replace = ft_memchr(arg, '=', len);
    env = set__get_option_variables(0, GET | GET_ENV);
    if (!append && replace)
    {    if(!(re_env_var(ft_substr(arg, 0, (replace - arg)), ft_strdup(arg), 0)))
            ft_lstadd_back(&env->lst, ft_lstnew(ft_strdup(arg)));}
    else if (append)
    {
        if(!(re_env_var(ft_substr(arg, 0, ((append) - arg)), ft_substr(arg, (append - arg) + 2, (len - 1) - (append - arg)), 1)))
            ft_lstadd_back(&env->lst, ft_lstnew(app_dup(arg)));
    }    
    else
    {
        if (is_export_var(arg))
            ft_lstadd_back(&env->lst_ex, ft_lstnew(ft_strdup(arg)));
    }
}

int get_operator(char *arg)
{
    int iter;
    char    **arg_s;
    iter = -1;
    arg_s = ft_split(arg, ' ');
    while (arg_s[++iter])
    {
        if (valid_id(arg_s[iter]))
        {
            printf("minishell: export: '%s': not a valid identifier\n", arg_s[iter]);    
            continue;
        }
        val(arg_s[iter]);
    }
    sp_free(arg_s);
    return (1);
}

int tt_export(t_cmd *cmd)
{
    t_builtin   *export;
    t_hold  *hold;
    t_list  *lst_tmp;
    t_list  *lst_tmp2;
    export = (t_builtin *)cmd;
    int ret = get_operator(export->cmd);
    
    hold = set__get_option_variables(0, GET | GET_ENV);
    lst_tmp = hold->lst;
    lst_tmp2 = hold->lst_ex;
    while (lst_tmp)
    {
        printf("Madeclarsh -x %s\n", lst_tmp->content);
        lst_tmp = lst_tmp->next;
    }
    while (lst_tmp2)
    {
        printf("Madeclarsh -x %s\n", lst_tmp2->content);
        lst_tmp2 = lst_tmp2->next;
    }
}