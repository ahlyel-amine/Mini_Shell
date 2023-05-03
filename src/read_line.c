/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbrahm <aelbrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 12:45:24 by aahlyel           #+#    #+#             */
/*   Updated: 2023/05/03 20:43:26 by aelbrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


void	read_line(t_list **env_var)
{
	char	*pwd;
	char	*line;

	while (1)
	{
		pwd = get_prompt_line();
		line = readline(pwd);
		free(pwd);
		if (!line || !ft_strncmp(line, "exit", 5))
		{
			ft_lstclear((env_var), free);
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