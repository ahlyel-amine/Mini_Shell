/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 02:53:32 by aahlyel           #+#    #+#             */
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
/*   Updated: 2023/05/07 19:06:46 by aelbrahm         ###   ########.fr       */
=======
/*   Updated: 2023/05/07 20:09:31 by aahlyel          ###   ########.fr       */
>>>>>>> parsing
=======
/*   Updated: 2023/05/07 21:36:23 by aelbrahm         ###   ########.fr       */
>>>>>>> exec
=======
/*   Updated: 2023/05/07 22:41:07 by aahlyel          ###   ########.fr       */
>>>>>>> parsing
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
	cd(cmd);
	if (cmd)
		free_line(cmd);
}
