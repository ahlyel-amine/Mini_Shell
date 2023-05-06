/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 14:39:32 by aelbrahm          #+#    #+#             */
/*   Updated: 2023/05/06 19:40:16 by aahlyel          ###   ########.fr       */
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

int    replace(t_list **lst, char *var)
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
    return (i);
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
        while (var[iter] && var[iter] == 0x24)
        {
            ft_lstadd_back(&expend, ft_lstnew(ft_strdup("$")));
            iter++;
        }   
        j = iter;
        if (var[j] && var[j] == 0x22)
            iter += replace(&expend, &var[j]);
        if (iter >= ft_strlen(var))
            break;
    }
    return (expend);
}

void    cd(t_cmd *cmd)
{
    t_builtin *cd;
    cd = (t_builtin *)cmd;
    t_list *lst = expander(cd->cmd);
    t_list *lst_tmp = lst;
    while (lst)
    {
        printf("<%s>\n", lst->content);
        lst = lst->next;
    }
    // printf("<%d>\n", getpid());
    // printf("%d\n", var_count(cd->cmd));
    // char    **var = ft_split(cd->cmd, 0x22);
    // if (!is_var(cd->cmd))
        // var = ft_split(cd->cmd, 0x22);
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
    ft_lstclear(&lst_tmp, free);
    // printf("%s\n", var);
}