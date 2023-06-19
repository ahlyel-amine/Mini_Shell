/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 01:53:40 by aelbrahm          #+#    #+#             */
/*   Updated: 2023/06/19 19:50:40 by aahlyel          ###   ########.fr       */
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
		(*print)(tmp->content, g_glb.out);
		tmp = tmp->next;
	}
}

void	tt_env(t_arguments *cmd_args)
{
	char		**args;
	t_hold		*env;
	t_list		*lst;

	env = set__get_option_variables(0, GET | GET_ENV);
	lst = env->lst;
	args = args_to_dblstr_(cmd_args);
	if (!args)
		env_print(lst, env->size, ft_putendl_fd);
	else if (args && *args)
	{
		g_glb.exit_val = 127;
		printf("Minishell: %s: no such file or directory\n", *args);
	}
}
