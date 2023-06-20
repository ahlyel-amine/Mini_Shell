/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_executer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 19:06:04 by aahlyel           #+#    #+#             */
/*   Updated: 2023/06/20 17:06:27 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	builtin_executer(t_arguments **args, char *cmd, \
int outfile, int echo_has_option)
{
	g_glb.out = outfile;
	if (!ft_memcmp(cmd, "cd", 2))
		tt_cd(args);
	else if (!ft_memcmp(cmd, "echo", 4))
		tt_echo(args, echo_has_option);
	else if (!ft_memcmp(cmd, "env", 3))
		tt_env(*args);
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
