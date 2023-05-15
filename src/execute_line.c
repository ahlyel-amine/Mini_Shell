/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 12:19:52 by aahlyel           #+#    #+#             */
/*   Updated: 2023/05/15 16:00:25 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	execute_line(t_cmd *cmd)
{
	if (cmd->type == AND)
		and_executer(cmd, STDIN_FILENO, STDOUT_FILENO, 0);
	else if (cmd->type == OR)
		or_executer(cmd, STDIN_FILENO, STDOUT_FILENO, 0);
	else if (cmd->type == REDIR)
		redirect_executer(cmd, STDIN_FILENO, STDOUT_FILENO, 0);
	else if (cmd->type == EXEC)
		cmd_executer(cmd, STDIN_FILENO, STDOUT_FILENO, 0);
	else if (cmd->type == BUILTIN)
		builtin_executer(cmd, STDIN_FILENO, STDOUT_FILENO, 0);
	else if (cmd->type == PIPE)
		pipe_executer(cmd, STDIN_FILENO, STDOUT_FILENO, 0);
	puts("doooooooooooooooooooooooone");
	while (wait(NULL) != -1)
		;
	puts("doooooooooooooooooooooooone");
}