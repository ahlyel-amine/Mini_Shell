/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_parser_tools4.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 18:05:51 by aahlyel           #+#    #+#             */
/*   Updated: 2023/06/13 03:08:14 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*get_herdoc_name(void)
{
	static int	call;

	return (ft_strjoin_free(ft_strdup("/tmp/.heredoc_"), ft_itoa(call++)));
}

static int	read_heredoc_inside_loop(char **line, t_redir_content *red, int fd)
{
	if (!strncmp(*line, red->delimiter, ft_strlen(red->delimiter) + 1))
	{
		free(*line);
		return (1);
	}
	if (!red->file_name->q)
		*line = data_analyse(*line);
	write(fd, *line, ft_strlen(*line));
	write(fd, "\n", 1);
	free(*line);
	*line = readline(HERDOC);
	return (0);
}

static void	read_heredoc(t_redir_content *red, t_arguments *args)
{
	char	*name;
	char	*line;
	int		fd;

	in_cmd = 1;
	sig_here();
	name = get_herdoc_name();
	fd = open(name, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (fd < 0)
		return (pr_custom_err(ERR_FILE, NULL, name));
	line = readline(HERDOC);
	while (line && !Ctrl_c)
	{
		if (read_heredoc_inside_loop(&line, red, fd))
			break ;
	}
	// Ctrl_c = 0;
	in_cmd = 0;
	free(red->delimiter);
	red->delimiter = name;
	close(fd);
}

int	get_name(char *line, t_redir_content *red, int type)
{
	t_arguments	*args;
	int			k;
	int			q;

	args = NULL;
	k = red->fd;
	if (type == F_HEREDOC)
	{
		red->file_name = arguments_constructor(args, \
		skip_quote_heredoc_delimiter(line, &k, red->fd, &q), IS_STR, q);
		red->delimiter = args_to_str(red->file_name);
		read_heredoc(red, args);
	}
	else
		red->file_name = get_names(line, &k);
	return (k);
}
