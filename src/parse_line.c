/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 02:53:32 by aahlyel           #+#    #+#             */
/*   Updated: 2023/04/28 08:36:31 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*parse_line(char *line)
{
	t_cmd	*cmd;

	cmd = NULL;
	complete_line(&line);
	if (line)
		cmd = tokenize_line(line);
	free_line(cmd);
	return (line);
}
