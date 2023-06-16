/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 19:53:34 by aahlyel           #+#    #+#             */
/*   Updated: 2023/06/16 19:54:10 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	exec_call(t_lsttoken *front, t_lsttoken *back, t_components comp)
{
	char		*line;
	char		*cmd;
	size_t		len;
	t_arguments	*arg;
	int			ret;

	cmd = get_command_name(&front, back);
	if (cmd)
		ret = is_builtin(cmd);
	if (!ret)
	{
		len = get_lenght(front, back);
		line = get_line(front, back, len);
		arg = get_argument(line, 0);
		transform_args(&arg);
		ret = cmd_executers(get_path(cmd), args_to_cmd_dstr(arg, cmd), comp);
		return (arguments_destructor(&arg), ret);
	}
	else if (ret == 1)
	{
		len = get_lenght(front, back);
		line = get_line(front, back, len);
		arg = get_argument(line, 0);
		ret = builtin_execiter(arg, cmd, comp.outfile);
		return (arguments_destructor(&arg), free(cmd), ret);
	}
	return (-1);
}

int	subsh(t_lsttoken *front, t_lsttoken *back, t_components comp)
{
	t_lsttoken *head;
	t_lsttoken *prev;
	int			pid;
	int			in;

	in = 0;
	head = front;
	prev = front;
	while (head)
	{
		if (head->t_.type == E_SUBSH)
		{
			in = 1;
			pid = fork();
			if (!pid)
			{
				and(head->t_.down, ft_lstokenlast(head->t_.down), comp);
				exit (EXIT_SUCCESS);
			}
			else
				waitpid(pid, NULL, 0);
			break ;
		}
		prev = head;
		if (head == back)
			break ;
		head = head->next;
	}
	if (!in)
		return exec_call(front, back, comp);
	return (-1);
}

int	redirection(t_lsttoken *front, t_lsttoken *back, t_components comp)
{
	t_lsttoken *head = front;
	int			in = 0;
	t_lsttoken *prev = front;
	
	while (head)
	{
		if (head->t_.type == E_OUTRED || head->t_.type == E_INRED || head->t_.type == E_APPEND || head->t_.type == E_HEREDOC)
		{
			in = 1;
			t_components tmp = get_red(head, comp);
			if (tmp.infile == -1 && tmp.outfile == -1 && tmp.is_pipe == 0 && !tmp.fd)
				return (0);
			head->t_.type = E_EMPTY;			
			redirection(front, back, tmp);
			break ;
		}
		prev = head;
		if (head == back)
			break ;
		head = head->next;
	}
	if (!in)
		return subsh(front, back, comp);
	return (-1);
}

int	pipe_(t_lsttoken *front, t_lsttoken *back, t_components comp)
{
	t_lsttoken *head = front;
	int			in = 0;
	t_lsttoken *prev = front;

	
	while (head)
	{
		if (head->t_.type == E_PIPE)
		{
			// is_pipe = 1;
			in = 1;
			int fd[2];
			int pid;
			pipe(fd);
			if (comp.fd != NULL)
				close(comp.fd[0]);
			pid = redirection(front, prev, (t_components){comp.infile, fd[1], 1, fd});
			close(fd[1]);
			pid = pipe_(head->next, back, (t_components){fd[0], comp.outfile, 1, fd});
			close(fd[0]);
			if (!pipe_left(head->next, back))
			{
				waitpid(pid, NULL, 0);
				while (wait(NULL) != -1)
					;
			}
			break;
		}
		prev = head;
		if (head == back)
			break ;
		head = head->next;
	}
	if (!in)
		return redirection(front, back, comp);
	return (-1);
}

int	or(t_lsttoken *front, t_lsttoken *back, t_components comp)
{
	t_lsttoken *head = front;
	int			in = 0;
	t_lsttoken *prev = front;

	while (head)
	{
		if (head->t_.type == E_OR)
		{
			in = 1;
			pipe_(front, prev, comp);
			if (glo_exit != 0)
				or(head->next, back, comp);
			break;
		}
		prev = head;
		if (head == back)
			break ;
		head = head->next;
	}
	if (!in)
	return	pipe_(front, back, comp);
	return (-1);
}

int	and(t_lsttoken *front, t_lsttoken *back, t_components comp)
{
	t_lsttoken *head = front;
	t_lsttoken *prev = front;
	int			in = 0;
	
	while (head)
	{
		if (head->t_.type == E_AND)
		{
			in = 1;
			or(front, prev, comp);
			if (glo_exit == 0)
				and(head->next, back, comp);
			break ;
		}
		prev = head;
		if (head == back)
			break ;
		head = head->next;
	}
	if (!in)
		return or(front, back, comp);
	return (-1);
}
