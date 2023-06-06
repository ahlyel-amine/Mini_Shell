/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_executer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbrahm <aelbrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 19:06:04 by aahlyel           #+#    #+#             */
/*   Updated: 2023/06/06 08:05:30 by aelbrahm         ###   ########.fr       */
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
		tt_pwd(cmd);
	else if (!ft_memcmp(builtin->builtin, "unset", 5))
		tt_unset(cmd);
}

int	builtin_executer(t_cmd *cmd, int infile, int outfile)
{
	out = outfile;
	builtin_locat(cmd, outfile);
	if (glo_exit)
		return (0);
	return (1);
}