/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_executer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 19:05:55 by aahlyel           #+#    #+#             */
/*   Updated: 2023/06/09 21:26:03 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <fcntl.h>

t_arguments	*transform_args_fd_name(t_arguments **args)
{
	char		*str;
	t_arguments	*nl;

	nl = NULL;
	expand_line(*args);
	args_join(args);
	args_move_down(args, &nl);
	str = args_to_str(*args);
	if (ft_strchr(str, '*'))
	{
		nl = *args;
		while (nl->next)
			nl = nl->next;
		nl->next = arguments_constructor(NULL, str, IS_STR, 0);
		wild_cards(&nl->next);
		if (nl->next->next)
			return (ft_putstr_fd("minishell: ambiguous redirect\n", 2), NULL);
		return (nl->next);
	}
	else
		return (free (str), *args);
}

int	open_files(t_cmd *cmd, int *infile, int *outfile)
{
	char	*file_name;
	t_arguments	*fd_nm;
	char	*line;
	if (((t_redir *)cmd)->red.type != HEREDOC)
	{
		fd_nm = transform_args_fd_name(&(((t_redir *)cmd)->red.file_name));
		if (!fd_nm)
			return (0);
		file_name = args_to_str(fd_nm);
	}
	else
		file_name = ((t_redir *)cmd)->red.delimiter;
	
	if (((t_redir *)cmd)->red.type == HEREDOC)
	{
		*infile = open(((t_redir *)cmd)->red.delimiter, O_RDONLY);
		if (*infile < 0)
			return (pr_custom_err(ERR_FILE, file_name, file_name), 0);
	}
	else if (((t_redir *)cmd)->red.type == F_IN_RED)
	{
		*infile = open(file_name, ((t_redir *)cmd)->red.mode);
		if (*infile < 0)
			return (pr_custom_err(ERR_FILE, file_name, file_name), 0);
	}
	else
	{
		*outfile = open(file_name, ((t_redir *)cmd)->red.mode, 0644);
		if (*outfile < 0)
			return (pr_custom_err(ERR_FILE, file_name, file_name), 0);
	}
	return (free(file_name), 1);
}

void	close_files(t_cmd *cmd, int infile, int outfile)
{
	if (((t_redir *)cmd)->red.type == HEREDOC
		|| (((t_redir *)cmd)->red.type == IN_REDIR))
		close(infile);
	else
		close(outfile);
}

int	redirect_executer(t_cmd *cmd, int infile, int outfile, int *fd)
{
	int			ret;
	char		*file_name;
	t_arguments	*check;

	if (!open_files(cmd, &infile, &outfile))
		return (0);
	if (((t_redir *)cmd)->cmd)
	{
		if (((t_redir *)cmd)->cmd->type == AND)
			ret = and_executer(((t_redir *)cmd)->cmd, infile, outfile, fd);
		else if (((t_redir *)cmd)->cmd->type == OR)
			ret = or_executer(((t_redir *)cmd)->cmd, infile, outfile, fd);
		else if (((t_redir *)cmd)->cmd->type == PIPE)
			ret = pipe_executer(((t_redir *)cmd)->cmd, infile, outfile, fd);
		else if (((t_redir *)cmd)->cmd->type == REDIR)
			ret = redirect_executer(((t_redir *)cmd)->cmd, infile, outfile, fd);
		else if (((t_redir *)cmd)->cmd->type == EXEC)
			ret = cmd_executer(((t_redir *)cmd)->cmd, infile, outfile, fd);
		else if (((t_redir *)cmd)->cmd->type == BUILTIN)
			ret = builtin_executer(((t_redir *)cmd)->cmd, infile, outfile, fd);
	}
	else
		ret = 1;
	close_files(cmd, infile, outfile);
	return (ret);
}
