/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbrahm <aelbrahm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 17:51:00 by aelbrahm          #+#    #+#             */
/*   Updated: 2023/05/24 12:47:50 by aelbrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	handel_sigint(int sig)
{
	if (sig == SIGINT)
	{
		glo_exit = 130;
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	else
		return ;
}

void	sig_hand()
{
	signal(SIGINT, handel_sigint);
	signal(SIGQUIT, handel_sigint);
}

void	handle_exec_sig(int sig)
{
	if (sig == SIGINT)
	{
		glo_exit = 130;
		// g_quit = 1;
		write(2, "\n", 1);
	}
	else if (sig == SIGQUIT)
	{
		glo_exit = 131;
		ft_putstr_fd("Quit: (core dumped)\n", 2);
	}
}

void	sig_exec_init(void)
{
	if (signal(SIGINT, handle_exec_sig) == SIG_ERR)
		exit(EXIT_FAILURE);
	else if (signal(SIGQUIT, handle_exec_sig) == SIG_ERR)
		exit(EXIT_FAILURE);
}