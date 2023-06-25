/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tt_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbrahm <aelbrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 06:14:21 by aelbrahm          #+#    #+#             */
/*   Updated: 2023/06/25 16:18:16 by aelbrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_list_remove(t_list **lst_tmp, char *data, int (*cmp)())
{
	t_hold	*env;
	t_list	*cur;

	if (lst_tmp == NULL || *lst_tmp == NULL)
		return ;
	env = set__get_option_variables(0, GET | GET_ENV);
	cur = *lst_tmp;
	if (cmp(cur->content, data, ft_strlen(data)) == 0 \
	&& (*((char *)cur->content + ft_strlen(data)) == '='))
	{
		*lst_tmp = cur->next;
		ft_lstdelone(cur, free);
		env->size--;
		ft_list_remove(lst_tmp, data, cmp);
	}
	else if (cmp(cur->content, data, ft_strlen(data)) == 0 \
	&& (!*((char *)cur->content + ft_strlen(data))))
	{
		*lst_tmp = cur->next;
		ft_lstdelone(cur, free);
		ft_list_remove(lst_tmp, data, cmp);
	}
	cur = *lst_tmp;
	if (cur)
		ft_list_remove(&cur->next, data, cmp);
}

void	nr_unset(char	**args, t_list **tmp)
{
	int	idx;

	idx = 0;
	while (args[idx])
	{
		if (valid_var(args[idx]))
		{
			err_print("Minishell: unset: ", \
			args[idx++], ": not a valid identifier");
			g_glb.exit_val = 1;
			continue ;
		}
		ft_list_remove(tmp, args[idx++], ft_strncmp);
	}
}

void	tt_unset(t_arguments **cmd_args)
{
	t_hold		*env;
	t_list		*tmp;
	char		**args;

	transform_args(cmd_args);
	args = args_to_dblstr(*cmd_args);
	if (!args || !*args)
		g_glb.exit_val = 0;
	else
	{
		env = set__get_option_variables(0, GET | GET_ENV);
		tmp = env->lst;
		nr_unset(args, &tmp);
		if (!env->size)
			env->lst = NULL;
		else
			env->lst = tmp;
		sp_free(args);
	}
}
