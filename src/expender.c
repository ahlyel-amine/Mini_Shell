/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expender.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 14:39:32 by aelbrahm          #+#    #+#             */
<<<<<<< HEAD:src/expender.c
/*   Updated: 2023/05/07 18:44:52 by aelbrahm         ###   ########.fr       */
=======
/*   Updated: 2023/05/06 19:40:16 by aahlyel          ###   ########.fr       */
>>>>>>> 4a2f53b42a5b4ef4ba82793c0184b512c7d858e9:src/cd.c
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char    *replace_str(char *var, char *lst_cnt)
{
    char    *expand;
    size_t     var_len = ft_strlen(var);
    size_t     lst_len = ft_strlen(lst_cnt);

    expand = ft_substr(lst_cnt, (var_len + 1), (lst_len - var_len));
    return (expand);
}

static int    replace(t_list **lst, char *var)
{
    int i = 1;
    t_hold *env = set__get_option_variables(0, (GET | GET_ENV));
    char    *tmp;
    t_list  *lst_tmp;
    while (var[i] != 0x22)
        i++;
    tmp = ft_substr(var, 1, i - 1);
    lst_tmp = env->lst;
    while (lst_tmp)
    {
        if (!ft_strncmp(tmp, lst_tmp->content, ft_strlen(tmp)) && ((char *)lst_tmp->content)[ft_strlen(tmp)] == 0x3d)
        {
            ft_lstadd_back(lst ,ft_lstnew(replace_str(tmp, lst_tmp->content)));
            break;
        }
        lst_tmp = lst_tmp->next;
    } 
    return (free(tmp), (i));
}

static  int dolr_check(t_list **lst, char *str, int iter)
{
    int i;

    i = 0;
    while (str[iter + (i)] && str[iter + (i)] == 0x24)
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
        while (var[j] && var[j] != 0x24 && var[j] != 0x22)
            j++;
        if (iter != j)
        {
            ft_lstadd_back(&expend, ft_lstnew(ft_substr(&var[iter], 0, (j - iter))));
            iter = j;
        }
        if (var[iter] == 0x24)
            iter += dolr_check(&expend, var, iter);  
        j = iter;
        if (var[j] && var[j] == 0x22)
            iter += replace(&expend, &var[j]);
        if (iter >= ft_strlen(var))
            break;
    }
    return (expend);
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

// void    cd(t_cmd *cmd)
// {
//     t_builtin *cd;
//     cd = (t_builtin *)cmd;
//     char    *var = nodes_join(expander(cd->cmd));
//     printf("<%s>\n", var);
//     free(var);
 

// }