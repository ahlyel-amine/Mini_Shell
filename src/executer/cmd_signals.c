/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_signals.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 00:08:17 by aahlyel           #+#    #+#             */
/*   Updated: 2023/06/18 13:34:06 by aahlyel          ###   ########.fr       */
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
		write(2, "\n", 1);
	else if (is_sig == 2)
		ft_putendl_fd("Quit: (core dumped)", STDERR_FILENO);
	return (free(path), 0);
}
