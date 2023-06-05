/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbrahm <aelbrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 22:03:39 by aahlyel           #+#    #+#             */
/*   Updated: 2023/06/05 14:22:18 by aelbrahm         ###   ########.fr       */
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
	if (!env_var)
	{
		perror("Error while alocating memory.");
		write(1, "\n", 1);
		exit(errno);
	}
    env_var->size = 0;
    env_var->lst = NULL;

	while (env && *env)
    {
        ft_lstadd_back(&(env_var->lst), ft_lstnew(ft_strdup(*(env))));
        env_var->size += 1;
		env++;
    }
	return (env_var);
}

int	main(int ac, char **av, char **env)
{
	// atexit(fun);
	(void)ac;
	(void)av;
	t_hold	*env_var = NULL;

	env_var = env_dup(env_var, env);
	adjust_shlvl(env_var);
	glo_exit = 0;
	in_cmd = 0;
	set__get_option_variables(env_var, SET);
	read_line(&(env_var->lst));
	// ft_lstclear(&(env_var->lst), free);
	return (0);
}