/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbrahm <aelbrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 14:39:32 by aelbrahm          #+#    #+#             */
/*   Updated: 2023/05/05 21:03:14 by aelbrahm         ###   ########.fr       */
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
    short   iter = -1;
    char    *joined;
    // char    *tmp;
    joined = ft_strdup("");
    while (vars && vars[++iter])
    {
        
        joined = ft_strjoin_free(joined, vars[iter]);
        if (*(joined + (ft_strlen(joined) - 1)) == 0x20 && vars[iter + 1])
        {
            *(joined + (ft_strlen(joined) - 1)) = 0;
        }    

    }
    free(vars);
    return (joined);
}

// char    *var_expand(char *arg)
// {
//     char    *var;
//     char    buf[1024];
//     short   iter = 0;
//     int i = 0;
//     var = ft_memchr(arg, 0x22, ft_strlen(arg)) + 1;
//     while (*arg)
//     {
//         if (*arg != 0x22 && *arg)
//             buf[iter] = *arg;
//         arg++;
//     }
//     while(var && *(var + (iter)))
//         if (ft_isalnum(*(var + iter)) || *(var + iter) == 0x5f)
//             iter++;
//         else
//             break;
//     t_hold *env = (t_hold *)set__get_option_variables(0, (GET | GET_ENV));
//     var = ft_substr(arg, (var) - (arg), iter);
//     t_list *tmp = env->lst;
//     while (tmp)
//     {
//         if (ft_strncmp(var, tmp->content, ft_strlen(var)))
//             tmp = tmp->next;
//         else
//             while(((char *)(tmp->content)) && ((char *)tmp->content)[i])
//                 buf[iter++] = ((char *)tmp->content)[i++];
//     }
//     return (buf);
//     // if (!var)
//     //     return (NULL);
//     // return (ft_strdup(var + iter));
// }
void    cd(t_cmd *cmd)
{
    t_builtin *cd;
    cd = (t_builtin *)cmd;
    char    *var = dbl_join(vars((cd->cmd + 1)));
    printf("<%s>\n", var);
    free(var);
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
    // char *tt;
    // char **t = var;
    // while (var && *var)
    // {
    //     tt = *var;
    //     printf("<%s>\n", *(var));
    //     free(tt);
    //     var++;
    // }    
        
    // free(t);
    // printf("%s\n", var);
}