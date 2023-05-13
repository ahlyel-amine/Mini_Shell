/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbrahm <aelbrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 19:19:53 by aelbrahm          #+#    #+#             */
/*   Updated: 2023/05/12 19:27:19 by aelbrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char    *get_owd(char *env_var)
{
    t_hold  *env;
    t_list  *lst_tmp;
    size_t  size;
    size = ft_strlen(env_var);
    env = set__get_option_variables(0, GET | GET_ENV);
    lst_tmp = env->lst;
    while (lst_tmp)
    {
        if (!ft_strncmp(env_var, lst_tmp->content, size))
            return ((char *)lst_tmp->content + size);
        lst_tmp = lst_tmp->next;
    }
    return (NULL);
}

void    reset_env(char *pwd, char *o_pwd)
{
    t_hold  *env;
    t_list  *lst;
    short   flg = 0;

    env = set__get_option_variables(0, (GET | GET_ENV));
    lst = env->lst;
    while (lst)
    {
        if (!ft_strncmp("PWD=", lst->content, 4))
        {
            free(lst->content);
            lst->content = ft_strjoin("PWD=", pwd);
        }
        if (!ft_strncmp("OLDPWD=", lst->content, 7))
        {
            flg = 1;
            free(lst->content);
            lst->content = ft_strjoin("OLDPWD=", o_pwd);
        }
        lst = lst->next;
    }
    if (!flg)
    {
        ft_lstadd_back(&env->lst, ft_lstnew(ft_strjoin("OLDPWD=", o_pwd)));
        env->size++;
    }    
}

char    *extend_option(char *arg, char *ex_with, int opt)
{
    char    *ret;
    char    *past;
    char    *tmp;

    ret = NULL;
    past = NULL;
    if (!opt)
    {
        tmp = ft_substr(arg, 2, (ft_strlen(arg) - 2));
        printf("{{%s}}\n", tmp);
    }    
    else if (opt == 1)
        tmp = ft_substr(arg, 1, (ft_strlen(arg) - 1));
    ret = ft_strjoin_free(ex_with, tmp);
        printf("{{%s}}\n", ret);
    return (free(arg), ret);
}

char    *get_prev_path(char *path)
{
    int iter;
    int len;
    char    *tmp;
    
    len = ft_strlen(path);
    len--;
    iter = len;
    while (path[iter] != '/' && iter >= 0)
        iter--;
    if (path[iter] == '/' && iter == 0)
        return (ft_strdup("/"));
    else if (iter != len)
       tmp = ft_substr(path, 0, iter);
    return (tmp);
}

int ft_go_to(int opt)
{
    char        *env_path;
    char        cwd[1024];
    int         ret;

    env_path = NULL;
    getcwd(cwd, sizeof(cwd));
    if (!opt)
    {
        env_path = get_owd("HOME=");
        if (!env_path)
            return (ft_putendl_fd("minishell : cd: HOME not set", STDERR_FILENO), (-1));
        reset_env(env_path, cwd);
    }   
    else if (opt == 1)
    {
        env_path = get_owd("OLDPWD=");
        if (!env_path)
            return (ft_putendl_fd("minishell : cd: OLDPWD not set", STDERR_FILENO), (-1));
        reset_env(env_path, cwd);
    }
    ret = chdir(env_path);
    return (ret);
}

int    tt_cd(t_cmd *cmd)
{
    t_builtin   *cd;
    char        *path;
    int         ret;
    char        cwd[1024];
    char        cwd2[1024];

    getcwd(cwd, sizeof(cwd));
    cd = (t_builtin *)cmd;
    path = nodes_join(expander(cd->cmd));
    if (!*path)
        ret = ft_go_to(0);
    else if (!ft_memcmp(path, "-", 2))
        ret = ft_go_to(1);   
    else
    {
        if (!ft_memcmp(path, "..", 2))
            path = extend_option(path, get_prev_path(cwd), 0);
        else if (!ft_memcmp(path, ".", 1))
            path = extend_option(path, ft_strdup(cwd), 1);  
        ret = chdir(path);
        getcwd(cwd2, sizeof(cwd2));
        if (ret == -1)
            printf("cd: %s: %s\n", path, strerror(errno));
        else
            reset_env(cwd2, cwd); 
    }
    return (free(path),ret);
}