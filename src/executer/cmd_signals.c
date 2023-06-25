/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_signals.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 00:08:17 by aahlyel           #+#    #+#             */
/*   Updated: 2023/06/25 15:49:25 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	cmd_sig_check(int status)
{
	if (WIFEXITED(status))
	{
		g_glb.exit_val = WEXITSTATUS(status);
		if (!g_glb.exit_val)
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
	if (cmd && (cmd[0] && cmd[0] == '.' && \
	(!cmd[1] || (cmd[1] && cmd[1] == '.' && !cmd[2]))))
		return (g_glb.exit_val = 127, \
		pr_custom_err(ERR_CMD, NULL, cmd), 1);
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

	if (cmd && (cmd[0] && cmd[0] == '.' && \
	(!cmd[1] || (cmd[1] && cmd[1] == '.' && !cmd[2]))))
		return (NULL);
	dir = opendir(cmd);
	if (!dir)
		return (ft_strdup(cmd));
	closedir(dir);
	g_glb.exit_val = 126;
	pr_custom_err("minishell: is a directory: ", NULL, cmd);
	return (NULL);
}
