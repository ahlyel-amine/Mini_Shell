/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbrahm <aelbrahm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 12:45:24 by aahlyel           #+#    #+#             */
/*   Updated: 2023/05/25 13:25:14 by aelbrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


void	read_line()
{
	char	*pwd;
	char	*line;

	while (1)
	{
		sig_handl();
		rl_catch_signals = 0;
		pwd = get_prompt_line();
		// if (pwd)
		// 	line = readline(pwd);
		// else
			line = readline("#minishell> ");
		free(pwd);
		if (!line)
		{
			free(line);
			set__get_option_variables(0, FREE);
			exit(0);
		}
		if (!*line)
		{
			free (line);
			continue ;
		}
		controll_line(&line);
		add_history(line);
		// parse_line(&line);
		free(line);
	}
	// rl_clear_history();
}
