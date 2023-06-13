/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controll_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 02:53:32 by aahlyel           #+#    #+#             */
/*   Updated: 2023/06/13 01:15:20 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	controll_line(char **line)
{
	t_cmd	*cmd;
	int		stop;

	stop = 0;
	cmd = NULL;
	complete_line(line, &stop);
	if (stop)
		return ;
	if (line && *line)
		cmd = parse_line(*line);
	if (cmd && !check_parsing(cmd))
		;
	else if (cmd)
		execute_line(cmd);
	free_line(cmd);
}
