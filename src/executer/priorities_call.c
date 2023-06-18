/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   priorities_call.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 19:53:34 by aahlyel           #+#    #+#             */
/*   Updated: 2023/06/18 16:26:42 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_option(char *line, char *endline)
{
	int	i;

	i = 0;
	if (line[i] == '\'' || line[i] == '\"')
		i++;
	if (line[i] == '-')
		i++;
	else
		return (0);
	while (line[i] == 'n' && line + i != endline)
		i++;	
	if (line  + i == endline || ((line[i] == '\'' || line[i] == '\"') && line  + i + 1 == endline))
		return (1);
	return (0);
}

t_lsttoken *skip_echo_option(t_lsttoken *front, t_lsttoken *back, int *has_option)
{
	*has_option = 0;
	while (front)
	{
		if ((front->t_.type == E_STR || front->t_.type == E_QUOTE || front->t_.type == E_DQUOTE))
		{
			if (!is_option(front->t_.line + front->t_.start, front->t_.line + front->t_.start + front->t_.len))
				break ;
			else
			{
				if (front && front->next && front->next->t_.type != E_SPACE)
					break ;
				*has_option = 1;
				front = front->next;
				while (front && front->t_.type == E_SPACE)
					front = front->next;
				if (front == back)
					break ;
				continue ;
			}
		}
		break ;
	}
	return (front);
}
static int	exec_call(t_lsttoken *front, t_lsttoken *back, t_components comp)
{
	char		*cmd;
	t_arguments	*arg;
	int			ret;

	cmd = get_command_name(&front, back);
	if (cmd)
		ret = is_builtin(cmd);
	else
		return (glo_exit = 0, 1);
	if (!ret)
	{
		arg = get_cmd(front, back);
		transform_args(&arg);
		ret = cmd_executers(get_path(cmd), args_to_cmd_dstr(arg, cmd), comp);
		return (arguments_destructor(&arg), ret);
	}
	else if (ret == 1)
	{
		while (front && front->t_.type == E_SPACE)
			front = front->next;
		if (!ft_strncmp(cmd, "echo", 5))
			front = skip_echo_option(front, back, &ret);
		arg = get_cmd(front, back);
		ret = builtin_executer(arg, cmd, comp.outfile, ret);
		return (arguments_destructor(&arg), free(cmd), ret);
	}
	return (-1);
}

static int	subsh(t_lsttoken *front, t_lsttoken *back, t_components comp)
{
	t_lsttoken	*head;
	int			in;

	in = 0;
	head = front;
	while (head)
	{
		if (head->t_.type == E_SUBSH)
		{
			in = 1;
			subsh_call(head, comp);
			break ;
		}
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
	t_lsttoken		*head;
	int				in;
	t_components	tmp;

	in = 0;
	head = front;
	while (head)
	{
		if (head->t_.type == E_OUTRED || head->t_.type == E_INRED || \
		head->t_.type == E_APPEND || head->t_.type == E_HEREDOC)
		{
			in = 1;
			tmp = get_red(head, comp);
			if (tmp.infile == -1 && tmp.outfile == -1 && tmp.is_pipe == 0 && !tmp.fd)
				return (0);
			head->t_.type = E_EMPTY;
			redirection(front, back, tmp);
			break ;
		}
		if (head == back)
			break ;
		head = head->next;
	}
	if (!in)
		return subsh(front, back, comp);
	return (0);
}

int	pipe_(t_lsttoken *front, t_lsttoken *back, t_components comp)
{
	t_lsttoken	*head;
	t_lsttoken	*prev;
	int			in;

	in = 0;
	head = front;
	prev = front;
	while (head)
	{
		if (head->t_.type == E_PIPE)
		{
			in = 1;
			pipe_call((t_2ptr_t_lsttoken){front, back}, head, prev, comp);
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

int	last_operaotr(t_lsttoken *front, t_lsttoken *back)
{
	t_lsttoken	*head;

	head = front;
	while (head)
	{
		if ((head->t_.type == E_AND || head->t_.type == E_OR))
			return (0);
		if (head == back)
			break ;
		head = head->next;
	}
	return (1);
}

int	operator(t_lsttoken *front, t_lsttoken *back, t_components comp)
{
	t_lsttoken	*head;
	t_lsttoken	*prev;
	int			in;

	in = 0;
	head = front;
	prev = front;
	while (head)
	{
		if ((head->t_.type == E_AND || head->t_.type == E_OR) && last_operaotr(head->next, back))
		{
			in = 1;
			operator(front, prev, comp);
			if ((glo_exit == 0 && head->t_.type == E_AND) || (glo_exit != 0 && head->t_.type == E_OR))
				operator(head->next, back, comp);
			break ;
		}
		prev = head;
		if (head == back)
			break ;
		head = head->next;
	}
	if (!in)
		return pipe_(front, back, comp);
	return (-1);
}
