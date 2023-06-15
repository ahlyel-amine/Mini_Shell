/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbrahm <aelbrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 01:53:40 by aelbrahm          #+#    #+#             */
/*   Updated: 2023/06/15 21:04:32 by aelbrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	env_print(t_list *lst, int lst_size, void (*print)(char*, int))
{
	t_list	*tmp;
	int		size;

	size = lst_size;
	tmp = lst;
	while (tmp && size--)
	{
		(*print)(tmp->content, out);
		tmp = tmp->next;
	}
}

void	tt_env(t_cmd *cmd)
{
	char		**args;
	t_hold		*env;
	t_list		*lst;
	t_builtin	*env_;

	env_ = (t_builtin *)cmd;
	env = set__get_option_variables(0, GET | GET_ENV);
	lst = env->lst;
	args = args_to_dblstr_(env_->arguments);
	if (!args)
		env_print(lst, env->size, ft_putendl_fd);
	else if (args && *args)
	{
		glo_exit = 127;
		printf("Minishell: %s: no such file or directory\n", *args);
	}
}
