/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_signals.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbrahm <aelbrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 00:08:17 by aahlyel           #+#    #+#             */
/*   Updated: 2023/06/19 06:16:19 by aelbrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	cmd_sig_check(char *path, int status)
{
	if (WIFEXITED(status))
	{
		status = WEXITSTATUS(status);
		glo_exit = status;
		if (!status)
			return (free(path), 1);
	}
	else if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
			is_sig = 1;
		else if (WTERMSIG(status) == SIGQUIT)
			is_sig = 2;
	}
	if (is_sig == 1)
		glo_exit = 130;
	else if (is_sig == 2)
		glo_exit = 131;	
	return (free(path), 0);
}
