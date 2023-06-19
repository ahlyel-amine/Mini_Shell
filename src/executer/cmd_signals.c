/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_signals.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbrahm <aelbrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 00:08:17 by aahlyel           #+#    #+#             */
/*   Updated: 2023/06/19 09:50:29 by aelbrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	cmd_sig_check(char *path, int status)
{
	if (WIFEXITED(status))
	{
		status = WEXITSTATUS(status);
		e_glb.exit_val = status;
		if (!status)
			return (free(path), 1);
	}
	else if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
			e_glb.is_sig = 1;
		else if (WTERMSIG(status) == SIGQUIT)
			e_glb.is_sig = 2;
	}
	if (e_glb.is_sig == 1)
		e_glb.exit_val = 130;
	else if (e_glb.is_sig == 2)
		e_glb.exit_val = 131;	
	return (free(path), 0);
}
