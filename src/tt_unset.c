/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tt_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 06:14:21 by aelbrahm          #+#    #+#             */
/*   Updated: 2023/05/13 09:33:32 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void ft_list_remove(t_list **lst_tmp, char *data, int (*cmp)())
{
	if (lst_tmp == NULL || *lst_tmp == NULL)
		return;

	t_list *cur = *lst_tmp;
    t_hold  *env = set__get_option_variables(0, GET | GET_ENV);
	if (cmp(cur->content, data, ft_strlen(data)) == 0 && (*((char *)cur->content + ft_strlen(data)) == '='))
	{
		*lst_tmp = cur->next;
        free(cur->content);
		free(cur);
        env->size--;
		ft_list_remove(lst_tmp, data, cmp);
	}
    else if (cmp(cur->content, data, ft_strlen(data)) == 0 && (!*((char *)cur->content + ft_strlen(data))))
	{
		*lst_tmp = cur->next;
        free(cur->content);
		free(cur);
		ft_list_remove(lst_tmp, data, cmp);
	}
	cur = *lst_tmp;
	ft_list_remove(&cur->next, data, cmp);
}

int tt_unset(t_cmd *cmd)
{
    t_builtin   *unset;
    unset = (t_builtin *)cmd;
    if (!*(unset->arguments->str + 1))
        return (0);
    t_hold  *env = set__get_option_variables(0, GET | GET_ENV);
    t_list  *tmp = env->lst;
    ft_list_remove(&tmp, (unset->arguments->str + 1), ft_strncmp);
    env_exp_print(env->lst, printf);
    return (1337);
}