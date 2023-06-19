/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 12:45:24 by aahlyel           #+#    #+#             */
/*   Updated: 2023/06/19 10:36:43 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
 #include <sys/ioctl.h>
void	read_line(void)
{
	char	*pwd;
	char	*line;

	while (1)
	{
		sig_handl();
		rl_catch_signals = 0;
		line = readline(READLINE);
		if (!line || !ft_strncmp(line, "exit", 5))
		{
			free(line);
			set__get_option_variables(0, FREE);
			ft_putendl_fd("minishell: exit", STDERR_FILENO);
			exit(glo_exit);
		}
		if (!*line)
		{
			free (line);
			continue ;
		}
		controll_line(&line);
		if (line)
			add_history(line);
		free(line);
	}
}
