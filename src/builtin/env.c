/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbrahm <aelbrahm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 01:53:40 by aelbrahm          #+#    #+#             */
/*   Updated: 2023/05/27 02:11:31 by aelbrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void    env_print(t_list *lst, int lst_size,int (*print)(const char*, ...))
{
    t_list  *tmp;
    int     size;

    size = lst_size;
    tmp = lst;
    while (tmp && size--)
    {
        (*print)(" %s\n", tmp->content);
        tmp = tmp->next;
    }
}

void	tt_env(t_cmd *cmd)
{
	char	**args;
	t_hold	*env;
	t_list	*lst;
	t_builtin	*env_;
	
	env_ = (t_builtin *)cmd;
	env = set__get_option_variables(0, GET | GET_ENV);
	lst = env->lst;
	args = args_to_dblstr(env_->arguments);
	if (!args)
		env_print(lst, env->size, printf);
	else if (args && *args)
	{
		glo_exit = 127;
		printf("Minishell: %s: no such file or directory\n", *args);
	}
}