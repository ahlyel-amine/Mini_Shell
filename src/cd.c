/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 19:19:53 by aelbrahm          #+#    #+#             */
/*   Updated: 2023/05/12 17:36:35 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
//Need function to set env node if PWD changed
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
    // char    *cwd;
    // cwd = getcwd(cwd, 0);
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
        ft_lstadd_back(&env->lst, ft_lstnew(ft_strjoin("OLDPWD=", o_pwd)));
}

void    cd(t_cmd *cmd)
{
    t_builtin   *cd;
    char        *path;
    char        *home = get_owd("HOME=");
    char        *oldpwd = get_owd("OLDPWD=");
    char        cwd[1024];
    getcwd(cwd, sizeof(cwd));
    cd = (t_builtin *)cmd;
    path = nodes_join(expander(cd->arguments->str));
    if (!*path || !ft_strncmp(path, "~", 2))
    {
        if (!home)
            printf("cd: OLDPWD not set\n");
        else
        {
            chdir(home);
            reset_env(home, cwd);
        }
    }   
    else if (!ft_strncmp(path, "-", 2))
    {
        if (!oldpwd)
            printf("cd: OLDPWD not set\n");
        else
        {

            chdir(oldpwd);
            reset_env(oldpwd, cwd);
            // printf("<%s>\n", (char *)set__get_option_variables(0, (GET | GET_PWD)));
            // // set__get_option_variables(0, (SET_PWD));
            // // printf("<%s>\n", getenv("PWD"));
            // reset_env(oldpwd, getenv("PWD"));
            t_hold *env = set__get_option_variables(0, GET | GET_ENV);
            t_list *lst = env->lst;
            while (lst)
            {
                printf("[%s]\n", lst->content);
                lst = lst->next;
            }
            printf("<%s>\n", (char *)set__get_option_variables(0, (GET | GET_PWD)) + 1);
        }   
    }
    else
    {
        if (chdir(path) == -1)
            printf("cd: %s: %s\n", path, strerror(errno));
        else
        {
            reset_env(path, cwd);
            t_hold *env = set__get_option_variables(0, GET | GET_ENV);
            t_list *lst = env->lst;
            while (lst)
            {
                printf("[%s]\n", lst->content);
                lst = lst->next;
            }
            printf("<%s>\n", (char *)set__get_option_variables(0, (GET | GET_PWD)));
        }
        // eset_env(path, getenv("OLDPWD"));
    }
    // printf("%s\n", get_owd("OLDPWD="));
}