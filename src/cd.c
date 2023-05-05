/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbrahm <aelbrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 14:39:32 by aelbrahm          #+#    #+#             */
/*   Updated: 2023/05/05 21:52:33 by aelbrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char    *replace_str(char *var, char *lst_cnt)
{
    char    *tmp;
    char    *expand;
    size_t     var_len = ft_strlen(var);
    size_t     lst_len = ft_strlen(lst_cnt);

    tmp = var;

    expand = ft_substr(lst_cnt, (var_len + 1), (lst_len - var_len));
    free(var);
    return (expand);
}

short   is_expandble(char *var)
{
    while (*var)
    {
        if (!(ft_isalnum(*var) || (*var == 0x5f)))
            return (1);
        var++;
    }  
    return (0);
}

short   is_var(char *var)
{
    short   iter;

    iter = -1;
    while (var[++iter])
        if (var[iter] == 0x22)
            return (0);
    return (1);
}

char    **vars(char *var)
{
    char    **tmp;
    t_hold  *env;
    t_list  *lst_tmp;
    int     iter = -1;
    int     flag = 0;
    env = set__get_option_variables(0, (GET | GET_ENV));
    tmp = ft_split(var, 0x22);
    if (is_var(var) || !tmp)
        return (NULL);
    while (tmp[++iter])
    {
        lst_tmp = env->lst;
        flag = 0;
        while (lst_tmp)
        {
            if (!ft_strncmp(tmp[iter], lst_tmp->content, ft_strlen(tmp[iter])) && ((char *)lst_tmp->content)[ft_strlen(tmp[iter])] == 0x3d)
            {
                flag = 1;
                tmp[iter] = replace_str(tmp[iter], lst_tmp->content);
            }   
            lst_tmp = lst_tmp->next;
        }
        if (!flag && !is_expandble(tmp[iter]))
        {
            free(tmp[iter]);
            tmp[iter] = ft_strdup("");
        }
    }
    return (tmp);
}

char    *dbl_join(char **vars)
{
    short   iter;
    char    *joined;

    iter = -1;
    joined = ft_strdup("");
    while (vars && vars[++iter])
    {
        joined = ft_strjoin_free(joined, vars[iter]);
        // if (*(joined + (ft_strlen(joined) - 1)) == 0x20 && vars[iter + 1])
        //     *(joined + (ft_strlen(joined) - 1)) = 0;
    }
    free(vars);
    return (joined);
}

void    cd(t_cmd *cmd)
{
    t_builtin *cd;
    cd = (t_builtin *)cmd;
    char    **var = NULL;
    // if (!is_var(cd->cmd))
        var = vars((cd->cmd));
    // if (!*cd->cmd)
    //     chdir(getenv("HOME"));
    // printf("<%s>\n", var);
    // free(var);
    // printf("%s\n", cd->cmd);
    // char *old = getenv("OLDPWD");
    // printf("<%s>\n", old);
    // char cwd[1024];
    // if (getcwd(cwd, sizeof(cwd)) != NULL) {
    //     setenv("OLDPWD", getenv("PWD"), 1);
    //     setenv("PWD", cwd, 1);
    // }
    // t_hold *env = (t_hold *)(set__get_option_variables(0, (GET | GET_ENV)));
    // char **path = set__get_
    // t_list *tmp = env->lst;
    // puts("alo\n");
	// while (tmp)
	// {
    //     printf(" «%s« \n", tmp->content);
    //     tmp = tmp->next;
    // }
    char *tt;
    char **t = var;
    while (var && *var)
    {
        tt = *var;
        printf("<%s>\n", *(var));
        free(tt);
        var++;
    }    
        
    free(t);
    // printf("%s\n", var);
}