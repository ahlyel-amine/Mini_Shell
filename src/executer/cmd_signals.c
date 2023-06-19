/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_signals.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 00:08:17 by aahlyel           #+#    #+#             */
/*   Updated: 2023/06/19 12:53:55 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	cmd_sig_check(char *path, int status)
{
	if (WIFEXITED(status))
	{
		status = WEXITSTATUS(status);
		g_glb.exit_val = status;
		if (!status)
			return (free(path), 1);
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
	return (free(path), 0);
}
