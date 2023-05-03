/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbrahm <aelbrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 22:03:39 by aahlyel           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/05/01 13:28:59 by aelbrahm         ###   ########.fr       */
=======
/*   Updated: 2023/05/03 20:42:22 by aelbrahm         ###   ########.fr       */
>>>>>>> master
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
	t_hold	*env_var = NULL;
	env_var = env_dup(env_var, env);

	
	
	atexit(fun);
<<<<<<< HEAD
	set__get_option_variables(env, SET);
	int merged;
	read_line();
=======

	set__get_option_variables(env_var, SET);
	read_line(&(env_var->lst));
	// ft_lstclear(&(env_var->lst), free);
>>>>>>> master
	return (0);
}