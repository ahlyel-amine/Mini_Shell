/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbrahm <aelbrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 17:51:00 by aelbrahm          #+#    #+#             */
/*   Updated: 2023/06/19 07:13:14 by aelbrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	event(void)
{
	return (0x0);
}

void	her_sig(int sig)
{
	(void)sig;
	glo_exit = 1;
	if (in_cmd == 1)
	{
		Ctrl_c = 1;
		rl_replace_line("", 0);
		rl_redisplay();
		rl_done = 1;
		return ;
	}
}

void	sig_here(void)
{
	rl_event_hook = event;
	signal(SIGINT, her_sig);
	signal(SIGQUIT, SIG_IGN);
}

void	handle_exec_sig(int sig)
{
	if (sig == SIGINT)
		write(STDERR_FILENO, "\b", 1);
	else if (sig == SIGQUIT)
		write(STDOUT_FILENO, "\b", 1);
}

void	sig_exec_init(void)
{
	if (signal(SIGINT, handle_exec_sig) == SIG_ERR)
		exit(EXIT_FAILURE);
	else if (signal(SIGQUIT, handle_exec_sig) == SIG_ERR)
		exit(EXIT_FAILURE);
}
