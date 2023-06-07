/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 12:45:24 by aahlyel           #+#    #+#             */
/*   Updated: 2023/06/07 10:53:42 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	read_line()
{
	char	*pwd;
	char	*line;

	while (1)
	{
		is_sig = 0;
		sig_handl();
		rl_catch_signals = 0;
		// pwd = get_prompt_line();
		// if (pwd)
		// 	line = readline(pwd);
		// else
			line = readline(READLINE);
		free(pwd);
		if (!line || !ft_strncmp(line, "exit", 5))
		{
			free(line);
			set__get_option_variables(0, FREE);
			printf("%d\n", glo_exit);
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
		// parse_line(&line);
		free(line);
	}
	// rl_clear_history();
	//io_redirection leaks
	//double free cmd ""
}
