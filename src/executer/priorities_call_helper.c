/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   priorities_call_helper.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 20:40:48 by aahlyel           #+#    #+#             */
/*   Updated: 2023/06/19 19:18:49 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_arguments	*get_cmd(t_lsttoken *front, t_lsttoken *back)
{
	t_arguments	*arg;
	char		*line;
	size_t		len;

	if (front == back)
		return (NULL);
	len = get_lenght(front, back);
	line = get_line(front, back, len);
	arg = get_argument(line, 0, 1);
	return (free(line), arg);
}

void	subsh_call(t_lsttoken *head, t_components comp)
{
	int	pid;
	int	status;

	pid = fork();
	if (!pid)
	{
		operator(head->t_.down, ft_lstokenlast(head->t_.down), comp);
		exit (g_glb.exit_val);
	}
	else
	{
		waitpid(pid, &status, 0);
		cmd_sig_check(status);
	}
}

void	wait_pipes(void)
{
	while (wait(NULL) != -1)
		;
}

void	pipe_call(t_2ptr_t_lsttoken a, t_lsttoken *head, \
t_lsttoken *prev, t_components comp)
{
	int			fd[2];
	int			pid;

	g_glb.is_pipe = 1;
	pipe(fd);
	pid = redirection(a.front, prev, (t_components){fd, comp.infile, fd[1], 1});
	if (pid == -1)
		return (wait_pipes());
	if (comp.fd != NULL)
		close(comp.fd[0]);
	close(fd[1]);
	pid = pipe_(head->next, a.back, (t_components){fd, fd[0], comp.outfile, 1});
	if (pid == -1)
		return (wait_pipes());
	close(fd[0]);
	if (!pipe_left(head->next, a.back))
		return (wait_pipes());
}
