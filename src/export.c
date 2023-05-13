/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbrahm <aelbrahm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 18:55:07 by aelbrahm          #+#    #+#             */
/*   Updated: 2023/05/13 03:14:28 by aelbrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
    int size= hold->size;
    while (size--)
    {
        if (!ft_strncmp(str, lst_env->content, len) && *((char *)lst_env->content + len) == '=')
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
        if(!ft_strncmp(str, lst_tmp->content, len) && (*((char *)lst_tmp->content + len) == '=' || !*((char *)lst_tmp->content + len)) && !opt)
        {
            if (!*((char *)lst_tmp->content + len))
                hold->size++;
            free(lst_tmp->content);
            lst_tmp->content = val;
            return (free(str), 1);
        }
        else if (!ft_strncmp(str, lst_tmp->content, len) && (*((char *)lst_tmp->content + len) == '=' || !*((char *)lst_tmp->content + len)) && opt)
        {
            if (!*((char *)lst_tmp->content + len))
                hold->size++;
            lst_tmp->content = ft_strjoin_free(lst_tmp->content, val);
            return (free(str), 1);
        }
        lst_tmp = lst_tmp->next;
    }
    return (free(str), free(val), 0);
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
    {
        if(!(re_env_var(ft_substr(arg, 0, (replace - arg)), ft_strdup(arg), 0)))
        {
            ft_lstadd_back(&env->lst, ft_lstnew(ft_strdup(arg)));
            env->size++;
        }    
    }
    else if (append)
    {
        if(!(re_env_var(ft_substr(arg, 0, ((append) - arg)), ft_substr(arg, (append - arg) + 2, (len - 1) - (append - arg)), 1)))
        {
            ft_lstadd_back(&env->lst, ft_lstnew(app_dup(arg)));
            env->size++;
        }   
    }    
    else
    {
        if (is_export_var(arg))
            ft_lstadd_back(&env->lst, ft_lstnew(ft_strdup(arg)));
    }
}

int get_operator(char *arg)
{
    int iter;
    char    **arg_s;
    int ret;
    iter = -1;
    arg_s = ft_split(arg, ' ');
    ret = 0;
    while (arg_s[++iter])
    {
        if (valid_id(arg_s[iter]))
        {
            printf("minishell: export: '%s': not a valid identifier\n", arg_s[iter]);
            ret = 1; 
            continue;
        }
        val(arg_s[iter]);
    }
    sp_free(arg_s);
    return (ret);
}

int tt_export(t_cmd *cmd)
{
    t_builtin   *export;
    t_hold      *hold;
    t_list      *lst_tmp;
    int         ret;

    ret = 0;
    export = (t_builtin *)cmd;
    if (!*export->cmd)
    {
        hold = set__get_option_variables(0, GET | GET_ENV);
        lst_tmp = lst_dup(hold->lst);
        lst_tmp = sort_list(lst_tmp, ft_strncmp);
        env_exp_print(lst_tmp, printf);
        ft_lstclear(&lst_tmp, free);
    }
    else
        ret = get_operator(export->cmd);
    return (ret);
}