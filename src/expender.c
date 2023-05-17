/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expender.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbrahm <aelbrahm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 14:39:32 by aelbrahm          #+#    #+#             */
/*   Updated: 2023/05/16 23:13:32 by aelbrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char    *replace_str(char *var, char *lst_cnt)
{
    char    *expand;
    size_t     var_len = ft_strlen(var);
    size_t     lst_len = ft_strlen(lst_cnt);

    expand = ft_substr(lst_cnt, (var_len + 1), (lst_len - var_len));
    return (expand);
}

int    replace(t_list **lst, char *var)
{
    int i = 1;
    t_hold *env = set__get_option_variables(0, (GET | GET_ENV));
    char    *tmp;
    t_list  *lst_tmp;
    while (var[i] != '\"')
        i++;
    tmp = ft_substr(var, 1, i - 1);
    lst_tmp = env->lst;
    while (lst_tmp)
    {
        if (!ft_strncmp(tmp, lst_tmp->content, ft_strlen(tmp)) && ((char *)lst_tmp->content)[ft_strlen(tmp)] == '=')
        {
            ft_lstadd_back(lst ,ft_lstnew(replace_str(tmp, lst_tmp->content)));
            env->size++;
            break;
        }
        lst_tmp = lst_tmp->next;
    } 
    return (free(tmp), (i));
}

int dolr_check(t_list **lst, char *str, int iter)
{
    int i;

    i = 0;
    while (str[iter + (i)] && str[iter + (i)] == '$')
    {
        ft_lstadd_back(lst, ft_lstnew(ft_strdup("$")));
        i++;
    }   
    return (i - 1);
}

t_list  *expander(char *var)
{
    t_list  *expend;
    int     iter;
    int     j;

    iter = -1;
    expend = NULL;
    while (var[++iter])
    {
        j = iter;
        while (var[j] && var[j] != '$' && var[j] != '\"')
            j++;
        if (iter != j)
        {
            ft_lstadd_back(&expend, ft_lstnew(ft_substr(&var[iter], 0, (j - iter))));
            iter = j;
        }
        if (var[iter] == '$')
            iter += dolr_check(&expend, var, iter);  
        j = iter;
        if (var[j] && var[j] == '\"')
            iter += replace(&expend, &var[j]);
        if (iter >= ft_strlen(var))
            break;
    }
    return (expend);
}

char    *nodes_join_b(t_arguments *lst)
{
    char    *tmp;
    t_arguments  *lst_tmp;

    tmp = ft_strdup("");
    lst_tmp = lst;
    while (lst)
    {
        lst_tmp = lst;
        tmp = ft_strjoin_free(tmp, lst_tmp->str);
        lst = lst->next;
        free(lst_tmp);
    }
    return (tmp);
}
char    *nodes_join(t_list *lst)
{
    char    *tmp;
    t_list  *lst_tmp;

    tmp = ft_strdup("");
    lst_tmp = lst;
    while (lst)
    {
        lst_tmp = lst;
        tmp = ft_strjoin_free(tmp, lst_tmp->content);
        lst = lst->next;
        free(lst_tmp);
    }
    return (tmp);
}
// void    expend_line(t_cmd *cmd)
// {
//     t_builtin *cmnd;
//     cmnd = (t_builtin *)cmd;
//     t_list  *lst = expander("$HOME lol -");
//     while (lst)
//     {
//         printf("%s\n", lst->content);
//         lst = lst->next;
//     }
// }
// void    cd(t_cmd *cmd)
// {
//     t_builtin *cd;
//     cd = (t_builtin *)cmd;
//     char    *var = nodes_join(expander(cd->cmd));
//     printf("<%s>\n", var);
//     free(var);
 

// }
