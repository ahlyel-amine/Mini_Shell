/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 23:41:20 by aelbrahm          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/05/13 19:05:19 by aelbrahm         ###   ########.fr       */
=======
/*   Updated: 2023/05/13 18:28:47 by aahlyel          ###   ########.fr       */
>>>>>>> parsing
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_list  *lst_dup(t_list *lst)
{
    t_list  *lst_ret;

    lst_ret = NULL;
    if (!lst)
        return (lst_ret);
    while (lst)
    {
        ft_lstadd_back(&lst_ret, ft_lstnew(ft_strdup(lst->content)));
        lst = lst->next;
    } 
    return (lst_ret);
}

t_list  *sort_list(t_list *lst, int (*cmp)(const char *, const char *, size_t))
{
    t_list  *tmp;
    t_list  *cur;
    t_list  *sort_lst;

    sort_lst = NULL;
    while (lst)
    {
        cur = lst;
        lst = lst->next;
        if (!sort_lst || ((*cmp)(cur->content, sort_lst->content, ft_strlen(cur->content))) < 0)
        {
            cur->next = sort_lst;
            sort_lst = cur;
        }
        else
        {
            tmp = sort_lst;
            while (tmp->next && ((*cmp)(cur->content, tmp->next->content, ft_strlen(cur->content))) > 0)
                tmp = tmp->next;
            cur->next = tmp->next;
            tmp->next = cur;    
        }
    }
    return sort_lst;
}

void    env_exp_print(t_list *sort_lst, int (*print)(const char*, ...))
{
    t_list  *tmp;

    tmp = sort_lst;
    while (tmp)
    {
        (*print)("Madeclarsh -x %s\n", tmp->content);
        tmp = tmp->next;
    }
}

char    **env_vars(t_hold *env)
{
    t_list  *tmp;
    char    **_env;
    int     size;


    size = env->size;
    tmp = env->lst;

    _env = (char **)malloc((size * sizeof(char*)) + 1);
    if (env)
    {
        while (size--)
        {
            *_env = (char *)tmp->content;
            _env++;
            tmp = tmp->next;
        }
        *_env = NULL;
        return (_env - env->size);
    }
    return (NULL);
}