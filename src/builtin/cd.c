/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbrahm <aelbrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 19:19:53 by aelbrahm          #+#    #+#             */
/*   Updated: 2023/06/09 19:43:17 by aelbrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../include/minishell.h"

int     stat_check(char *path)
{
    struct  stat file_info;
    if (stat(path, &file_info) == 0)
    {
        if (!(file_info.st_mode & S_IRUSR))
            return (printf("cd: permission denied: %s\n", path), (0));
        else
            return (1);       
    }
    else
        return (1);
}

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
    char    *tmp;
    short   flg = 0;
    short   p_flg = 0;
    env = set__get_option_variables(0, (GET | GET_ENV));
    lst = env->lst;
    while (lst)
    {
        if (!ft_strncmp("PWD=", lst->content, 4))
            env_key_cmp(pwd, "PWD=", &(lst->content), &p_flg);
        if (!ft_strncmp("OLDPWD=", lst->content, 7))
            env_key_cmp(o_pwd, "OLDPWD=", &lst->content, &flg);
        lst = lst->next;
    }
    if (!flg)
    {
        ft_lstadd_node(&env->lst, ft_lstnew(ft_strjoin("OLDPWD=", o_pwd)), (env->size >> 1));
        env->size++;
    }
    if (!p_flg)
    {
        ft_lstadd_node(&env->lst, ft_lstnew(ft_strjoin("PWD=", pwd)), (env->size >> 1));
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
        tmp = ft_substr(arg, 2, (ft_strlen(arg) - 2));   
    else if (opt == 1)
        tmp = ft_substr(arg, 1, (ft_strlen(arg) - 1));
    ret = ft_strjoin_free(ex_with, tmp);
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
    if (!opt)
    {
        env_path = get_owd("HOME=");
        if (!stat_check(env_path))
            return (1);
        if (!env_path)
            return (ft_putendl_fd("minishell : cd: HOME not set", STDERR_FILENO), (1));
        if (!*cwd)
            reset_env(env_path, get_owd("PWD="));
        else    
            reset_env(env_path, cwd);
        ret = chdir(env_path);
    }   
    else if (opt == 1)
        ret = go_to_oldpwd(cwd, path);
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
        if (ft_memcmp(splited[indx], ".", 1) && ft_memcmp(splited[indx], "..", 2))
            is_valid = 0;
        indx++;
    }
    sp_free(splited);
    return (is_valid);
}
int     d_point_validat(char *path, char *o_pwd, int count)
{
    char    *dir;
    int indx;
    int ret;

    indx = ft_strlen(path);
    while (indx > 0)
    {
        if (indx > 0 && path[indx - 1] == '/')
            indx--;
        while (indx > 0 && path[indx - 1] == '.')
            indx--;
        if (path[indx - 1] != '/' && path[indx - 1] != '.')
            break;
    }
    while (count)
    {
        if (indx > 0 && path[indx - 1] == '/')
            indx--;
        while (indx > 0 && path[indx - 1] != '/')
            indx--;
        count--;
    }
    dir = ft_substr(path, 0, indx);
    ret = chdir(dir);
    if (!ret)
        reset_env(dir, o_pwd);
    return (free(dir), ret);
}

int    d_point_extend(char  *path, char *cwd)
{
    char    *pwd;
    int     ret;
    int     count;
    
    pwd = prepare_pwd();
    if (!*cwd && d_point_check(path))
    {
        if (pwd && pwd[ft_strlen(pwd) - 1] != '/')
            pwd = ft_strjoin_free(pwd, ft_strdup("/"));
        count = prev_drictory_count(path);
        if (count >= 3)
            return (free(pwd), printf("cd: %s: No such file or directory\n", path), 1);
        count += prev_drictory_count(pwd);
        ret = d_point_validat(pwd, get_owd("OLDPWD="), count);
        if (ret == -1)
        {
            pwd = ft_strjoin_free(pwd, ft_strdup(path));
            reset_env(pwd, get_owd("PWD="));
            return  (free(pwd), printf("cd: error retrieving current directory: getcwd: cannot access parent directories: %s\n", strerror(errno)), 1);
        }
    }
    else if (cwd)
        ret = d_point_pwd(path, pwd);
    return (free(pwd), ret); // update it  
}

void    nr_cd(char *path, char *cwd)
{
    int     ret;
    char    cwd2[PATH_MAX];
    ret = 0;

    if (!stat_check(path))
        ret = 1;
    ret = chdir(path);
    if (ret == -1)
    {
        printf("cd: %s: %s\n", path, strerror(errno));
        ret = 1;
    }
    else
    {
        getcwd(cwd2, sizeof(cwd2));
        reset_env(cwd2, cwd); 
    }
    glo_exit = ret;
}
char    *args(t_arguments *cmd)
{
    char        *ret;
    t_arguments *tmp;

    ret = ft_strdup("");
    tmp = cmd;
    if (!tmp)
        return (NULL);
    if (tmp->type == QUOTE || tmp->type == DQUOTE)
    {
        tmp = tmp->down;
        while (tmp && tmp->str)
        {
            ret = ft_strjoin_free(ret, ft_strdup(tmp->str));
            tmp = tmp->next;
        }
    }
    else
    {
        while (tmp && tmp->type != IS_SEPARTOR)
        {
            ret = ft_strjoin_free(ret, ft_strdup(tmp->str));
            tmp = tmp->next;
        }
    }
    return (ret);
}
void    tt_cd(t_cmd *cmd)
{
    t_builtin   *cd;
    char        *path;
    int         ret;
    char        cwd[PATH_MAX];

    ret = 0;
    cd = (t_builtin *)cmd;
    if (!getcwd(cwd, sizeof(cwd)))
        cwd[0] = '\0';
    (transform_args(&cd->arguments));
    path = args(cd->arguments);
    if (!path)
        glo_exit = ft_go_to(0, path, cwd);
    else if (!ft_memcmp(path, "-", 2))
        glo_exit = ft_go_to(1, path, cwd), free(path);   
    else
    {
        if (!ft_memcmp(path, "..", 2) || !ft_memcmp(path, ".", 1))
            glo_exit = d_point_extend(path, cwd);
        else
            nr_cd(path, cwd);
        free(path);
    }
}
