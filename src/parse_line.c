/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 02:53:32 by aahlyel           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/05/11 01:36:53 by aelbrahm         ###   ########.fr       */
=======
/*   Updated: 2023/05/11 00:31:22 by aahlyel          ###   ########.fr       */
>>>>>>> parsing
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
<<<<<<< HEAD
	tt_cd(cmd);
=======
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
>>>>>>> parsing
	if (cmd)
		free_line(cmd);
}
