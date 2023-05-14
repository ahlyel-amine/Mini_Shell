/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 12:45:24 by aahlyel           #+#    #+#             */
/*   Updated: 2023/05/14 22:55:55 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


void	read_line()
{
	char	*pwd;
	char	*line;

	while (1)
	{
		pwd = get_prompt_line();
		if (pwd)
			line = readline(pwd);
		else
			line = readline("#minishell> ");
		free(pwd);
		if (!line || !ft_strncmp(line, "exit", 5))
		{
			set__get_option_variables(0, FREE);
			// free(env_var);
			exit(0);
		}
		if (!*line)
		{
			free (line);
			continue ;
		}
		else
			add_history(line);
		parse_line(&line);
		free(line);
	}
}
