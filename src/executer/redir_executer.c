/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_executer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 19:05:55 by aahlyel           #+#    #+#             */
/*   Updated: 2023/05/11 00:54:20 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

# include <fcntl.h>

int	redirect_executer(t_cmd *cmd, int infile, int outfile)
{
	int	ret;
	char	*line;
		printf("{%d}\n",((t_redir *)cmd)->red.type);
	if (((t_redir *)cmd)->red.type == HEREDOC)
	{
		((t_redir *)cmd)->red.fd = open("/tmp/.heredoc", O_CREAT | O_TRUNC | O_WRONLY, 0644);
		while (1337)
		{
			line = readline("heredoc> ");
			if (!strncmp(line, ((t_redir *)cmd)->red.file_name, ft_strlen(((t_redir *)cmd)->red.file_name)))
			{
				free(line);
				break;
			}
			write(((t_redir *)cmd)->red.fd, line, ft_strlen(line));
			write(((t_redir *)cmd)->red.fd, "\n", 1);
			free(line);
		}
		close(((t_redir *)cmd)->red.fd);
		infile = open("/tmp/.heredoc", O_RDONLY);
	}
	else if (((t_redir *)cmd)->red.type == F_IN_RED)
		infile = open(((t_redir *)cmd)->red.file_name, ((t_redir *)cmd)->red.mode);
	else
	{
		printf("%d : [%d]\n",  ((t_redir *)cmd)->red.type, ((t_redir *)cmd)->red.mode);
		outfile = open(((t_redir *)cmd)->red.file_name, ((t_redir *)cmd)->red.mode, 0644);
	}
	if (((t_redir *)cmd)->cmd)
	{
		if (((t_redir *)cmd)->cmd->type == AND)
			ret = and_executer(((t_redir *)cmd)->cmd, infile, outfile);
		else if (((t_redir *)cmd)->cmd->type == OR)
			ret = or_executer(((t_redir *)cmd)->cmd, infile, outfile);
		else if (((t_redir *)cmd)->cmd->type == PIPE)
			ret = pipe_executer(((t_redir *)cmd)->cmd, infile, outfile);
		else if (((t_redir *)cmd)->cmd->type == REDIR)
			ret = redirect_executer(((t_redir *)cmd)->cmd, infile, outfile);
		else if (((t_redir *)cmd)->cmd->type == EXEC)
			ret = cmd_executer(((t_redir *)cmd)->cmd, infile, outfile);
		else if (((t_redir *)cmd)->cmd->type == BUILTIN)
			ret = builtin_executer(((t_redir *)cmd)->cmd, infile, outfile);
	}
	if (((t_redir *)cmd)->red.type == HEREDOC || (((t_redir *)cmd)->red.type == IN_REDIR))
		close(infile);
	else
		close(outfile);
	return (ret);
}
