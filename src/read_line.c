/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 12:45:24 by aahlyel           #+#    #+#             */
/*   Updated: 2023/04/27 18:04:35 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	read_line(char	**line)
{
	char	*pwd;
	char	*tmp;

	while (1)
	{
		pwd = get_prompt_line();
		(*line) = readline(pwd);
		free(pwd);
		if (!(*line) || !ft_strncmp((*line), "exit", 5))
		{
			set__get_option_variables(0, FREE);
			exit(0);
		}
		if (!*(*line))
			continue ;
		else
			add_history((*line));
		tmp = parse_line((*line));
		if (tmp != *line)
			free (tmp);
		free(*line);
	}
}