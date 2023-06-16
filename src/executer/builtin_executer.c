/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_executer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 19:06:04 by aahlyel           #+#    #+#             */
/*   Updated: 2023/06/16 17:51:04 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	builtin_locat(t_cmd *cmd, int out)
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

int	builtin_executer(t_cmd *cmd, int infile, int outfile, int *fd)
{
	out = outfile;
	builtin_locat(cmd, outfile);
	if (!glo_exit)
		return (1);
	return (0);
}

int	builtin_execiter(t_arguments *args, char *cmd, int outfile)
{
	exit(1);
	if (!ft_memcmp(cmd, "cd", 2))
		tt_cd((t_cmd *)args);
	else if (!ft_memcmp(cmd, "echo", 4))
		tt_echo((t_cmd *)args);
	else if (!ft_memcmp(cmd, "env", 3))
		tt_env((t_cmd *)args);
	else if (!ft_memcmp(cmd, "exit", 4))
		tt_exit((t_cmd *)args);
	else if (!ft_memcmp(cmd, "export", 6))
		tt_export((t_cmd *)args);
	else if (!ft_memcmp(cmd, "pwd", 3))
		tt_pwd();
	else if (!ft_memcmp(cmd, "unset", 5))
		tt_unset((t_cmd *)args);
	else 
		return (-1);
}
