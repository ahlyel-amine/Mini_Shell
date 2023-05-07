/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 02:53:32 by aahlyel           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/05/07 18:49:27 by aelbrahm         ###   ########.fr       */
=======
/*   Updated: 2023/05/06 19:54:07 by aahlyel          ###   ########.fr       */
>>>>>>> 4a2f53b42a5b4ef4ba82793c0184b512c7d858e9
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	parse_line(char **line)
{
	t_cmd	*cmd;

	cmd = NULL;
	complete_line(line);
	// printf("[%s]\n", line);
	if (line && *line)
		cmd = tokenize_line(*line);
<<<<<<< HEAD
		// if (cmd)
	// cd(cmd);
=======
	// if (cmd)
	// 	cd(cmd);
>>>>>>> 4a2f53b42a5b4ef4ba82793c0184b512c7d858e9
	if (cmd)
		free_line(cmd);
}
