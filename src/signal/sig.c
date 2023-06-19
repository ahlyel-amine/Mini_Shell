/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbrahm <aelbrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 07:11:37 by aelbrahm          #+#    #+#             */
/*   Updated: 2023/06/19 09:50:29 by aelbrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	handel_sigint(int sig)
{
	(void)sig;
	if (waitpid(-1, NULL, WNOHANG) != -1)
		return ;
	e_glb.exit_val = 1;
	e_glb.is_sig = 0;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	sig_handl(void)
{
	if (signal(SIGINT, handel_sigint) == SIG_ERR)
		exit(EXIT_FAILURE);
	else if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		exit(EXIT_FAILURE);
}
