/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_executer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 19:06:04 by aahlyel           #+#    #+#             */
/*   Updated: 2023/06/13 00:00:35 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	builtin_locat(t_cmd *cmd, int out)
{
	t_builtin	*builtin;

	builtin = (t_builtin *)cmd;
	if (!ft_memcmp(builtin->builtin, "cd", 2))
		tt_cd(cmd);
	else if (!ft_memcmp(builtin->builtin, "echo", 4))
		tt_echo(cmd);
	else if (!ft_memcmp(builtin->builtin, "env", 3))
		tt_env(cmd);
	else if (!ft_memcmp(builtin->builtin, "exit", 4))
		tt_exit(cmd);
	else if (!ft_memcmp(builtin->builtin, "export", 6))
		tt_export(cmd);
	else if (!ft_memcmp(builtin->builtin, "pwd", 3))
		tt_pwd();
	else if (!ft_memcmp(builtin->builtin, "unset", 5))
		tt_unset(cmd);
}

// void	quantum_box(t_cmd *cmd, int out)
// {
// 	// if (in != STDIN_FILENO)
// 	// {
// 	// 	dup2(in, STDIN_FILENO);
// 	// 	close(in);
// 	// }
// 	if (out != STDOUT_FILENO)
// 	{
// 		dup2(out, STDOUT_FILENO);
// 		close(out);
// 	}
// 	builtin_locat(cmd);
// }

int	builtin_executer(t_cmd *cmd, int infile, int outfile, int *fd)
{
	out = outfile;
	builtin_locat(cmd, outfile);
	if (!glo_exit)
		return (1);
	return (0);
}
