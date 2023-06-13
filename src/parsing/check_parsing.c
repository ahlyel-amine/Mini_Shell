/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 01:15:02 by aahlyel           #+#    #+#             */
/*   Updated: 2023/06/13 01:16:20 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	check_and_parsing(t_cmd *cmd)
{
	if (!((t_and *)cmd)->left || !((t_and *)cmd)->right)
		return (0);
	else
		return (check_parsing(((t_and *)cmd)->left) & \
		check_parsing(((t_and *)cmd)->right));
	return (1);
}

static int	check_or_parsing(t_cmd *cmd)
{
	if (!((t_or *)cmd)->left || !(((t_or *)cmd)->right))
		return (0);
	else
		return (check_parsing(((t_or *)cmd)->left) & \
		check_parsing(((t_or *)cmd)->right));
	return (1);
}

static int	check_pipe_parsing(t_cmd *cmd)
{
	if (!((t_pipe *)cmd)->left || !(((t_pipe *)cmd)->right))
		return (0);
	else
		return (check_parsing(((t_pipe *)cmd)->left) & \
		check_parsing(((t_pipe *)cmd)->right));
	return (1);
}

static int	check_redir_parsing(t_cmd *cmd)
{
	char	*file_name;
	char	*line;

	if (((t_redir *)cmd)->cmd && ((t_redir *)cmd)->cmd->type == INVALID)
	{
		file_name = args_to_str(((t_redir *)cmd)->red.file_name);
		while (1337)
		{
			line = readline("heredoc> ");
			if (!line)
				break ;
			if (!strncmp(line, file_name, ft_strlen(file_name)))
			{
				free(line);
				break ;
			}
			free(line);
		}
		pr_custom_err(ERR_SNTX, NULL,
			((t_invalid *)((t_redir *)cmd)->cmd)->str);
		free(file_name);
		return (0);
	}
	return (1);
}

int	check_parsing(t_cmd *cmd)
{
	if (!cmd)
		return (0);
	if (cmd->type == AND)
		return (check_and_parsing(cmd));
	else if (cmd->type == OR)
		return (check_or_parsing(cmd));
	else if (cmd->type == PIPE)
		return (check_pipe_parsing(cmd));
	else if (cmd->type == REDIR)
		return (check_redir_parsing(cmd));
	return (1);
}