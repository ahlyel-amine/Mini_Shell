/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 12:45:24 by aahlyel           #+#    #+#             */
/*   Updated: 2023/04/27 13:16:26 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	read_line(char	**line)
{
	char	*homedir;
	char	*pwd;

	homedir = set__get_option_variables(0, GET | GET_HOME);
	pwd = NULL;
	while (1)
	{
		free(pwd);
		pwd = NULL;

		pwd = getcwd(pwd, 0);
		pwd = get_prompt_line(pwd);
		(*line) = readline(pwd);
		if (!(*line) || !ft_strncmp((*line), "exit", 5))
			exit(0);
		if (!*(*line))
			continue ;
		else
			add_history((*line));
		parse_line((*line));
	}
}