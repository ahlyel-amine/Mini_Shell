/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_executer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 19:06:04 by aahlyel           #+#    #+#             */
/*   Updated: 2023/06/25 15:40:56 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	builtin_executer(t_arguments **args, int outfile, int falg)
{
	g_glb.out = outfile;
	if (falg & CD)
		tt_cd(args);
	else if (falg & ECHO)
		tt_echo(args, falg & ECHO_OPTION);
	else if (falg & ENV)
		tt_env(*args);
	else if (falg & EXIT)
		tt_exit(args);
	else if (falg & EXPORT)
		tt_export(args);
	else if (falg & PWD)
		tt_pwd();
	else if (falg & UNSET)
		tt_unset(args);
	if (!g_glb.exit_val)
		return (0);
	return (1);
}

int	builtin(t_arguments **args, int outfile, int falg)
{
	int	pid;
	int	status;

	if (!g_glb.is_pipe)
		return (builtin_executer(args, outfile, falg));
	else
	{
		g_glb.is_pipe = 0;
		pid = fork();
		if (pid == -1)
			return (perror("minishell: "), -1);
		if (pid == 0)
		{
			pid = builtin_executer(args, outfile, falg);
			exit (pid);
		}
		waitpid(pid, &status, 0);
		return (cmd_sig_check(status));
	}
}
