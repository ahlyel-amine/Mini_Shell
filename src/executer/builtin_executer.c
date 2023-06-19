/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_executer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 19:06:04 by aahlyel           #+#    #+#             */
/*   Updated: 2023/06/19 19:47:44 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// static void	builtin_locat(t_arguments *args, int out)
// {
// 	t_builtin	*builtin;

// 	builtin = (t_builtin *)cmd;
// 	if (!ft_memcmp(builtin->builtin, "cd", 2))
// 		tt_cd(cmd);
// 	else if (!ft_memcmp(builtin->builtin, "echo", 4))
// 		tt_echo(cmd);
// 	else if (!ft_memcmp(builtin->builtin, "env", 3))
// 		tt_env(cmd);
// 	else if (!ft_memcmp(builtin->builtin, "exit", 4))
// 		tt_exit(cmd);
// 	else if (!ft_memcmp(builtin->builtin, "export", 6))
// 		tt_export(cmd);
// 	else if (!ft_memcmp(builtin->builtin, "pwd", 3))
// 		tt_pwd();
// 	else if (!ft_memcmp(builtin->builtin, "unset", 5))
// 		tt_unset(cmd);
// }

// int	builtin_executer(t_cmd *cmd, int infile, int outfile, int *fd)
// {
// 	out = outfile;
// 	builtin_locat(cmd, outfile);
// 	if (!g_glb.exit_val)
// 		return (1);
// 	return (0);
// }

int	builtin_executer(t_arguments *args, char *cmd, \
int outfile, int echo_has_option)
{
	g_glb.out = outfile;
	if (!ft_memcmp(cmd, "cd", 2))
		tt_cd(args);
	else if (!ft_memcmp(cmd, "echo", 4))
		tt_echo(args, echo_has_option);
	else if (!ft_memcmp(cmd, "env", 3))
		tt_env(args);
	else if (!ft_memcmp(cmd, "exit", 4))
		tt_exit(args);
	else if (!ft_memcmp(cmd, "export", 6))
		tt_export(args);
	else if (!ft_memcmp(cmd, "pwd", 3))
		tt_pwd();
	else if (!ft_memcmp(cmd, "unset", 5))
		tt_unset(args);
	if (!g_glb.exit_val)
		return (0);
	return (-1);
}
