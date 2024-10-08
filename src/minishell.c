/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabato <sabato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 22:03:39 by aahlyel           #+#    #+#             */
/*   Updated: 2024/08/05 20:48:59 by sabato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_globe	g_glb;

static t_hold	*env_dup(t_hold *env_var, char **env)
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
	t_hold	*env_var;

	(void)ac;
	(void)av;
	env_var = NULL;
	if (!isatty(STDIN_FILENO))
		return (ft_putendl_fd(INVALID_INPT, 2), 1);
	env_var = env_dup(env_var, env);
	adjust_shlvl(env_var);
	g_glb.exit_val = 0;
	g_glb.in_cmd = 0;
	set__get_option_variables(env_var, SET);
	read_line();
	return (0);
}
