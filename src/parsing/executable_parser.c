/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executable_parser.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 19:44:04 by aahlyel           #+#    #+#             */
/*   Updated: 2023/06/07 11:40:23 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_cmd	*executable_parser(char *line)
{
	t_cmd	*cmd;
	int		i;
	int		j;
	int		has_option;

	if (!line)
		return (NULL);
	i = 0;
	j = 0;
	has_option = 0;
	cmd = NULL;
	if (!*line)
		return (free(line), NULL);
	while (ft_isspace(line[i]))
		i++;
	while (line[i + j] && !ft_isspace(line[i + j]))
		j++;
	cmd = get_token_builtins(ft_strdup(line + i), j);
	if (!cmd)
		cmd = get_token_cmd(ft_strdup(line + i), j);
	free (line);
	return (cmd);
}