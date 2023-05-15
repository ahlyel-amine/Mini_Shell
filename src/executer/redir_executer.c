/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_executer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 19:05:55 by aahlyel           #+#    #+#             */
/*   Updated: 2023/05/15 15:43:23 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

# include <fcntl.h>
char	*arguments_to_str(t_arguments *args)
{
	t_arguments *tmp;
	char		*str;
	int	i;
	int j;

	i = 0;
	tmp = args;
	while (tmp)
	{
		i += ft_strlen(tmp->str);
		tmp = tmp->next;
	}
	str = malloc(i + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (args)
	{
		j = 0;
		while (args->str[j])
			str[i++] = args->str[j++];
		args = args->next;
	}
	str[i] = 0;
	return (str);
}
int	redirect_executer(t_cmd *cmd, int infile, int outfile, int is_pipe)
{
	int	ret;
	char	*line;
	char	*file_name;
	t_arguments	*check;
	
	if (((t_redir *)cmd)->red.type != HEREDOC)
	{
		((t_redir *)cmd)->red.file_name =  wild_cards(((t_redir *)cmd)->red.file_name, NULL);
		if ((((t_redir *)cmd)->red.file_name)->next)
			return (ft_putendl_fd("minishell: ambiguous redirect", 2), 0);
	}
	file_name = arguments_to_str(((t_redir *)cmd)->red.file_name);
	if (((t_redir *)cmd)->red.type == HEREDOC)
	{
		((t_redir *)cmd)->red.fd = open("/tmp/.heredoc", O_CREAT | O_TRUNC | O_WRONLY, 0644);
		if (((t_redir *)cmd)->red.fd < 0)
			return (pr_custom_err(ERR_FILE, line, file_name), 0);
		while (1337)
		{
			line = readline("heredoc> ");
			if (!line)
				break ;
			if (!strncmp(line, file_name, ft_strlen(file_name)))
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
		if (infile < 0)
			return (pr_custom_err(ERR_FILE, file_name, file_name), 0);
	}
	else if (((t_redir *)cmd)->red.type == F_IN_RED)
	{
		infile = open(file_name, ((t_redir *)cmd)->red.mode);
		if (infile < 0)
			return (pr_custom_err(ERR_FILE, file_name, file_name), 0);
	}
	else
	{
		outfile = open(file_name, ((t_redir *)cmd)->red.mode, 0644);
		if (outfile < 0)
			return (pr_custom_err(ERR_FILE, file_name, file_name), 0);
	}
	if (((t_redir *)cmd)->cmd)
	{
		if (((t_redir *)cmd)->cmd->type == AND)
			ret = and_executer(((t_redir *)cmd)->cmd, infile, outfile, is_pipe);
		else if (((t_redir *)cmd)->cmd->type == OR)
			ret = or_executer(((t_redir *)cmd)->cmd, infile, outfile, is_pipe);
		else if (((t_redir *)cmd)->cmd->type == PIPE)
			ret = pipe_executer(((t_redir *)cmd)->cmd, infile, outfile, is_pipe);
		else if (((t_redir *)cmd)->cmd->type == REDIR)
			ret = redirect_executer(((t_redir *)cmd)->cmd, infile, outfile, is_pipe);
		else if (((t_redir *)cmd)->cmd->type == EXEC)
			ret = cmd_executer(((t_redir *)cmd)->cmd, infile, outfile, is_pipe);
		else if (((t_redir *)cmd)->cmd->type == BUILTIN)
			ret = builtin_executer(((t_redir *)cmd)->cmd, infile, outfile, is_pipe);
	}
	if (((t_redir *)cmd)->red.type == HEREDOC || (((t_redir *)cmd)->red.type == IN_REDIR))
		close(infile);
	else
		close(outfile);
	return (free(file_name), ret);
}
