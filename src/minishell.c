/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbrahm <aelbrahm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 22:03:39 by aahlyel           #+#    #+#             */
/*   Updated: 2023/05/14 05:38:41 by aelbrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	fun()
{
	system("leaks minishell");
}

t_hold	*env_dup(t_hold *env_var, char **env)
{
	env_var = (t_hold *)malloc(sizeof(t_hold));
    env_var->size = 0;
    env_var->lst = NULL;

	while (env && *env)
    {
        ft_lstadd_back(&(env_var->lst), ft_lstnew(ft_strdup(*(env))));
        if (env_var)
            env_var->size += 1;
		env++;
    }
	return (env_var);
}


int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	atexit(fun);
	t_hold	*env_var = NULL;
	env_var = env_dup(env_var, env);
	set__get_option_variables(env_var, SET);
	read_line(&(env_var->lst));
	// ft_lstclear(&(env_var->lst), free);
	return (0);
}