/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbrahm <aelbrahm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2023/05/13 03:42:15 by aelbrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	parse_line(char **line)
{
	t_cmd	*cmd;

	cmd = NULL;
	complete_line(line);
	if (line && *line)
		cmd = tokenize_line(*line);
	printf("\n\n\n\n");
	if (cmd && cmd->type == AND)
		and_executer(cmd, STDIN_FILENO, STDOUT_FILENO);
	else if (cmd && cmd->type == OR)
		or_executer(cmd, STDIN_FILENO, STDOUT_FILENO);
	else if (cmd && cmd->type == REDIR)
		redirect_executer(cmd, STDIN_FILENO, STDOUT_FILENO);
	else if (cmd && cmd->type == EXEC)
		cmd_executer(cmd, STDIN_FILENO, STDOUT_FILENO);
	else if (cmd && cmd->type == BUILTIN)
		builtin_executer(cmd, STDIN_FILENO, STDOUT_FILENO);
	else if (cmd && cmd->type == PIPE)
		pipe_executer(cmd, STDIN_FILENO, STDOUT_FILENO);
	printf("\n\n\n\n");
	if (cmd)
		free_line(cmd);
}
