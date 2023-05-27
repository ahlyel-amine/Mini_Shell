/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tt_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbrahm <aelbrahm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 06:14:21 by aelbrahm          #+#    #+#             */
/*   Updated: 2023/05/27 01:51:21 by aelbrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
short	valid_var(char *var)
{
	if (!(ft_isalpha(*var) || *var == '_'))
		return (1);
	while (*var)
	{
		if (!(ft_isalnum(*var) || *var == '_'))
			return (1);
		var++;
	}
	return (0);
}
void	nr_unset(char	**args, t_list **tmp)
{
	int	idx;

	idx = 0;
	while (args[idx])
	{
		if (valid_var(args[idx]))
		{
			printf("Minishell: unset: %s: not a valid identifier\n", args[idx++]);
			glo_exit = 1;
			continue;
		}
		ft_list_remove(tmp, args[idx++], ft_strncmp);
	}
}
void	tt_unset(t_cmd *cmd)
{
    t_builtin   *unset;
	t_hold		*env;
	t_list		*tmp;
	char		**args;

    unset = (t_builtin *)cmd;
	transform_args(&unset->arguments);
	args = args_to_dblstr(unset->arguments);
    if (!args || !*args)
        glo_exit = 0;
	else
	{
		t_hold  *env = set__get_option_variables(0, GET | GET_ENV);
		tmp = env->lst;
		nr_unset(args, &tmp);
		sp_free(args);
	}	
}