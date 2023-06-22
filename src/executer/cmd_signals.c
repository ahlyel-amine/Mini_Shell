/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_signals.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 00:08:17 by aahlyel           #+#    #+#             */
/*   Updated: 2023/06/21 18:19:13 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	cmd_sig_check(int status)
{
	if (WIFEXITED(status))
	{
		status = WEXITSTATUS(status);
		g_glb.exit_val = status;
		if (!status)
			return (1);
	}
	else if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
			g_glb.is_sig = 1;
		else if (WTERMSIG(status) == SIGQUIT)
			g_glb.is_sig = 2;
	}
	if (g_glb.is_sig == 1)
		g_glb.exit_val = 130;
	else if (g_glb.is_sig == 2)
		g_glb.exit_val = 131;
	return (0);
}

int	has_slash(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

char	*is_dir(char *cmd)
{
	DIR	*dir;

	dir = opendir(cmd);
	if (!dir)
		return (cmd);
	closedir(dir);
	g_glb.exit_val = 126;
	pr_custom_err("minishell: is a directory: ", cmd, cmd);
	return (NULL);
}

void	child_exit(void)
{
	if (errno == 2)
		exit(127);
	else if (errno == 13 || errno == 20)
		exit(126);
	else if (errno == 130)
		exit(1);
	exit(errno);
}
