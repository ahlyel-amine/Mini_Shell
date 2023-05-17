/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbrahm <aelbrahm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 19:19:53 by aelbrahm          #+#    #+#             */
/*   Updated: 2023/05/17 14:08:24 by aelbrahm         ###   ########.fr       */
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

int ft_go_to(int opt, char *path, char *cwd)
{
    char        *env_path;
    int         ret;

    env_path = NULL;
    env_path = path;
    if (!opt)
    {
        env_path = get_owd("HOME=");
        if (!env_path)
            return (ft_putendl_fd("minishell : cd: HOME not set", STDERR_FILENO), (-1));
        if (!*cwd)
            reset_env(env_path, get_owd("PWD="));
        else    
            reset_env(env_path, cwd);
    }   
    else if (opt == 1)
    {
        env_path = get_owd("OLDPWD=");
        if (env_path && !*env_path)
            env_path = get_owd("PWD=");
        printf("<<<%s>>>\n", env_path);
        if (!env_path)
            return (ft_putendl_fd("minishell : cd: OLDPWD not set", STDERR_FILENO), (-1));
        if (!*cwd)
            reset_env(env_path, get_owd("PWD="));
        else    
            reset_env(env_path, cwd);
    }
    ret = chdir(env_path);
    return (ret);
}
int     prev_drictory_count(char *wd)
{
    int count;
    int indx;
    char    **splited;
    count = 0;
    indx = 0;
    splited = ft_split(wd, '/');
    while (splited && splited[indx])
    {
        if (!ft_memcmp(splited[indx], "..", 2))
            count++;
        indx++;
    }
    sp_free(splited);
    return (count);
}
int     d_point_check(char *path)
{
        int is_valid;
    int indx;
    char    **splited;
    is_valid = 1;
    indx = 0;
    splited = ft_split(path, '/');
    while (splited && splited[indx])
    {
        if (ft_memcmp(splited[indx], "..", 2))
            is_valid = 0;
        indx++;
    }
    sp_free(splited);
    return (is_valid);
}
int     d_point_validat(char *path, int count)
{
    char    *dir;
    int indx;
    int ret;

    indx = ft_strlen(path) - 1;
    while (indx > 0)
    {
        if (indx > 0 && path[indx] == '/')
            indx--;
        while (indx > 0 && path[indx] != '/' && path[indx] == '.')
            indx--;
        if (path[indx] != '/' && path[indx] != '.')
            break;
    }
    while (count)
    {
        if (indx > 0 && path[indx] == '/')
            indx--;
        while (indx > 0 && path[indx] != '/')
            indx--;
        count--;
    }
    dir = ft_substr(path, 0, indx);
    ret = chdir(dir);
    if (!ret)
        reset_env(dir, get_owd("OLDPWD="));
    return (free(dir), ret);
}
int    d_point_extend(char  *path, char *cwd)
{
    char    *pwd;
    int     ret;
    int     count;
    pwd = get_owd("PWD=");
    if (!pwd)
        pwd = ft_strdup("");
    else if (pwd && pwd[ft_strlen(pwd) - 1] != '/')
        pwd = ft_strjoin(pwd, "/");
    else
        pwd = ft_strdup(pwd);
    if (!*cwd && d_point_check(path))
    {
        // int ret = chdir(path);
        // printf("--[%d]--\n", ret);
        count = prev_drictory_count(path);
        if (count >= 3)
            return (free(pwd), printf("cd: %s: No such file or directory", path), -1);
        count += prev_drictory_count(pwd);
        ret = d_point_validat(pwd, count);
        if (ret == -1)
        {
            pwd = ft_strjoin_free(pwd, ft_strdup(path));
            reset_env(pwd, get_owd("PWD="));
            return  (free(pwd), printf("cd: error retrieving current directory: getcwd: cannot access parent directories: %s\n", strerror(errno)), -1);
        }
    }    
    
}

int    tt_cd(t_cmd *cmd)
{
    t_builtin   *cd;
    char        *path;
    int         ret;
    char        cwd[1024];
    char        cwd2[1024];
    ret = 0;
    cd = (t_builtin *)cmd;
    if (!getcwd(cwd, sizeof(cwd)))
        cwd[0] = '\0';
    (expand_line(cd->arguments));
    path = nodes_join_b(cd->arguments);
    // if (!getcwd(cwd, sizeof(cwd)))
    //     return (printf("cd: %s\n", strerror(errno)), 1);
    // else
    // {
        
        // printf("cd : arg = %s exec_val = %d\n", path, ret);
    // }
    if (!*path)
        ret = ft_go_to(0, path, cwd);
    else if (!ft_memcmp(path, "-", 2))
        ret = ft_go_to(1, path, cwd);
    else
    {
        if (!ft_memcmp(path, "..", 2))
            ret = d_point_extend(path, cwd);
        // else if (!ft_memcmp(path, ".", 1))
        //     path = extend_option(path, ft_strdup(cwd), 1);
        // ret = chdir(path);
        // if (ret == -1)
        //     printf("cd: %s: %s\n", path, strerror(errno));
        // else
        //     reset_env(path, cwd);
    }

    // printf("cd : PWD = %s OLDPWD = %s\n", get_owd("PWD="), get_owd("OLDPWD="));
    // printf("{%d}\n", ret);
    t_hold  *env = set__get_option_variables(0, GET | GET_ENV);
    t_list *lst = env->lst;
    while (lst)
    {
        printf("[%s]\n", lst->content);
        lst = lst->next;
    }
    return (free(path),ret);
}