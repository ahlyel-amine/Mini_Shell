/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
<<<<<<< HEAD
/*   Created: 2023/04/17 02:53:32 by aahlyel           #+#    #+#             */
/*   Updated: 2023/05/07 23:01:00 by aahlyel          ###   ########.fr       */
=======
/*   Created: 2023/05/07 21:46:25 by aelbrahm          #+#    #+#             */
/*   Updated: 2023/05/07 21:46:28 by aelbrahm         ###   ########.fr       */
>>>>>>> exec
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
	if (cmd)
		free_line(cmd);
}
