/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc_parser_tools2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 15:39:50 by aahlyel           #+#    #+#             */
/*   Updated: 2023/06/21 19:00:21 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*get_herdoc_name(void)
{
	static int	call;

	return (ft_strjoin_free(ft_strdup(HERDOC_FILE), ft_itoa(call++)));
}

char	*her_expand(char *line)
{
	t_arguments	*args;
	char		*r_str;
	int			i;

	i = 0;
	args = get_argument(line, i, 0);
	free(line);
	expand_line(args);
	r_str = args_to_str(args);
	return (arguments_destructor(&args), r_str);
}

static int	read_heredoc_inside_loops(char **line, \
char *delimiter, int fd, int q)
{
	int	i;

	i = 0;
	if (!strncmp(*line, delimiter, ft_strlen(delimiter) + 1))
	{
		free(*line);
		return (1);
	}
	if (!q)
		*line = her_expand(*line);
	write(fd, *line, ft_strlen(*line));
	write(fd, "\n", 1);
	free(*line);
	*line = readline(HERDOC);
	return (0);
}

int	read_heredocs(char *delimiter, int q)
{
	char	*name;
	char	*line;
	int		fd;

	g_glb.in_cmd = 1;
	sig_here();
	name = get_herdoc_name();
	fd = open(name, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (fd < 0)
		return (pr_custom_err(ERR_FILE, name, name), -1);
	line = readline(HERDOC);
	while (line && !g_glb.ctrl_c)
	{
		if (read_heredoc_inside_loops(&line, delimiter, fd, q))
			break ;
	}
	if (g_glb.ctrl_c)
		return (unlink(name), free(name), \
		g_glb.ctrl_c = 0, close(fd), free (line), -1);
	g_glb.in_cmd = 0;
	close(fd);
	fd = open(name, O_RDONLY, 0644);
	if (fd < 0)
		return (pr_custom_err(ERR_FILE, name, name), -1);
	return (unlink(name), free(name), fd);
}
