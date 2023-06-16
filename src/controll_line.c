/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controll_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 02:53:32 by aahlyel           #+#    #+#             */
/*   Updated: 2023/06/16 19:37:09 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"




int	a_and(t_lsttoken *front, t_lsttoken *back, t_components comp);


size_t	get_lenght(t_lsttoken *front, t_lsttoken *back)
{
	t_lsttoken *head;
	size_t		len;
	
	head = front;
	len = 0;
	while (head)
	{
		if (head->t_.type == E_AND || head->t_.type == E_OR || head->t_.type == E_PIPE)
			break ;
		else if (head->t_.type == E_SPACE)
			len++;
		else if (head->t_.type != E_EMPTY && head->t_.type != E_SPACE)
			len += head->t_.len;
		head = head->next;
	}
	return (len);
}

char	*get_line(t_lsttoken *front, t_lsttoken *back, size_t len)
{
	t_lsttoken *head;
	char		*line;
	size_t		i;
	size_t		j;
	
	i = 0;
	head = front;
	line = ft_calloc(1, len + 1);
	if (!line)
		return (NULL);
	while (head)
	{
		if (head->t_.type == E_AND || head->t_.type == E_OR || head->t_.type == E_PIPE)
			break ;
		else if (head->t_.type == E_SPACE)
			line[i++] = ' ';
		else if (head->t_.type != E_EMPTY && head->t_.type != E_SPACE)
		{
			j = 0;			
			while (head->t_.start + j < head->t_.start + head->t_.len)
				line[i++] = head->t_.line[head->t_.start + j++];
		}
		head = head->next;
	}
	return (line);
}

int	is_builtin(char *word)
{
	if (!ft_strncmp(word, "cd", 3))
		return (1);
	else if (!ft_strncmp(word, "echo", 5))
		return (1);
	else if (!ft_strncmp(word, "env", 4))
		return (1);
	else if (!ft_strncmp(word, "exit", 5))
		return (1);
	else if (!ft_strncmp(word, "export", 7))
		return (1);
	else if (!ft_strncmp(word, "pwd", 4))
		return (1);
	else if (!ft_strncmp(word, "unset", 6))
		return (1);
	return (0);
}

char	*get_path(char *cmd)
{
	char	**path;
	char	*cmd_path;
	char	*tmp_to_free;
	int		i;

	i = 0;
	if (cmd == NULL)
		return (NULL);
	if (!*cmd)
		return (pr_custom_err(ERR_CMD, NULL, cmd), NULL);
	if (!access(cmd, F_OK | X_OK))
		return (ft_strdup(cmd));
	path = (char **)set__get_option_variables(0, GET | GET_PATH);
	while (path && path[i])
	{
		tmp_to_free = ft_strjoin(path[i], "/");
		tmp_to_free = ft_strjoin_free(tmp_to_free, ft_strdup(cmd));
		if (!access(tmp_to_free, F_OK | X_OK))
			return (free(cmd), tmp_to_free);
		free(tmp_to_free);
		i++;
	}
	glo_exit = 127;
	return (pr_custom_err(ERR_CMD, NULL, cmd), NULL);
}

void	child(char **exec, char *path, t_components comp)
{
	char	**backup_env;

	backup_env = child_vars();
	if (comp.infile != STDIN_FILENO)
	{
		dup2(comp.infile, STDIN_FILENO);
		if (comp.is_pipe == 0)
			close(comp.infile);
	}
	if (comp.outfile != STDOUT_FILENO)
	{
		dup2(comp.outfile, STDOUT_FILENO);
		if (comp.is_pipe == 0)
			close(comp.outfile);
	}
	if (comp.is_pipe != 0)
	{
		close(comp.fd[0]);
		close(comp.fd[1]);
	}
	execve(path, exec, backup_env);
	ft_putendl_fd(ERR_EXVE, 2);
	exit(errno);
}
void	print_dstr(char **str)
{
	int i = 0;
	if (!str)
		return;
	while (str[i])
		printf("%s\n", str[i++]);
	return;
}

int	cmd_executers(char *path, char **cmd, t_components comp)
{
	int status;

	if (!path || !cmd)
		return (0);
	int pid = fork();
	if (pid == -1)
		return (perror(SHELL_NAME), 0);
	if (!pid)
		child(cmd, path, comp);
	if (comp.is_pipe != 0)
		return (pid);
	if (waitpid(pid, &status, 0) == -1)
		return (free(path), 0);
	if (cmd_sig_check(path, status))
		return 0;
	return -1;
}

char	*get_command_name(t_lsttoken **front, t_lsttoken *back)
{
	t_arguments	*arg;
	t_lsttoken	*head;
	int			start = 0;
	int			end = 0;
	int			a;
	char		*word;

	a = (back - *front);
	head = *front;
	while ((head->t_.type == E_SPACE || head->t_.type == E_EMPTY) && a--)
		head = head->next;
	word = head->t_.line;
	
	start = head->t_.start;
	end = head->t_.len;
	head = head->next;

	while (head && back - head + 1)
	{
		if (head->t_.type != E_STR && head->t_.type != E_QUOTE && head->t_.type != E_DQUOTE)
			break ;
		else
			end += head->t_.len;
		head = head->next;
	}
	*front = head;
	word = ft_substr(word + start, 0, end);
	if (!word)
		return (NULL);
	arg = get_argument(word, 0);
	free(word);
	transform_args(&arg);
	word = args_to_str(arg);
	return (arguments_destructor(&arg), word);
}

int	a_exec(t_lsttoken *front, t_lsttoken *back, t_components comp)
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

int	a_subsh(t_lsttoken *front, t_lsttoken *back, t_components comp)
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
				a_and(head->t_.down, ft_lstokenlast(head->t_.down), comp);
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
		return a_exec(front, back, comp);
	return (-1);
}

t_components get_red(t_lsttoken *redir, t_components comp)
{
	int		q;
	char	*delimiter;

	if (redir->t_.type == E_HEREDOC)
	{
		delimiter = skip_quote_heredoc_delimiters(redir->t_.down->t_.line + redir->t_.down->t_.start, redir->t_.down->t_.line + redir->t_.down->t_.start + redir->t_.down->t_.len, &q);
		comp.infile = read_heredocs(delimiter, q);
	}
	else
	{
		delimiter = get_filename(redir->t_.down->t_.line + redir->t_.down->t_.start, redir->t_.down->t_.line + redir->t_.down->t_.start + redir->t_.down->t_.len);
		if (!delimiter)
			return ((t_components){-1, -1, 0, NULL});
		printf("%d\n", comp.outfile);
		if (redir->t_.type == E_INRED)
			comp.infile = open(delimiter, O_RDONLY);
		else if (redir->t_.type == E_APPEND)
			comp.outfile = open(delimiter, O_CREAT | O_APPEND | O_WRONLY, 0644);
		else if (redir->t_.type == E_OUTRED)
			comp.outfile = open(delimiter, O_CREAT | O_TRUNC | O_WRONLY, 0644);
		printf("%d\n", comp.outfile);
	}
	return (free(delimiter), comp);
}

int	a_red(t_lsttoken *front, t_lsttoken *back, t_components comp)
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
			a_red(front, back, tmp);
			break ;
		}
		prev = head;
		if (head == back)
			break ;
		head = head->next;
	}
	if (!in)
		return a_subsh(front, back, comp);
	return (-1);
}

int pipe_left(t_lsttoken *head, t_lsttoken *back)
{
	t_lsttoken *tmp = head;
	while (tmp && tmp != back)
	{
		if (tmp->t_.type == E_PIPE)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

int	a_pipe(t_lsttoken *front, t_lsttoken *back, t_components comp)
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
			pid = a_red(front, prev, (t_components){comp.infile, fd[1], 1, fd});
			close(fd[1]);
			pid = a_pipe(head->next, back, (t_components){fd[0], comp.outfile, 1, fd});
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
		return a_red(front, back, comp);
	return (-1);
}

int	a_or(t_lsttoken *front, t_lsttoken *back, t_components comp)
{
	t_lsttoken *head = front;
	int			in = 0;
	t_lsttoken *prev = front;

	while (head)
	{
		if (head->t_.type == E_OR)
		{
			in = 1;
			a_pipe(front, prev, comp);
			if (glo_exit != 0)
				a_or(head->next, back, comp);
			break;
		}
		prev = head;
		if (head == back)
			break ;
		head = head->next;
	}
	if (!in)
	return	a_pipe(front, back, comp);
	return (-1);
}

int	a_and(t_lsttoken *front, t_lsttoken *back, t_components comp)
{
	t_lsttoken *head = front;
	t_lsttoken *prev = front;
	int			in = 0;
	
	while (head)
	{
		if (head->t_.type == E_AND)
		{
			in = 1;
			a_or(front, prev, comp);
			if (glo_exit == 0)
				a_and(head->next, back, comp);
			break ;
		}
		prev = head;
		if (head == back)
			break ;
		head = head->next;
	}
	if (!in)
		return a_or(front, back, comp);
	return (-1);
}

void	controll_line(char **line)
{
	int			len;
	int			stop;
	t_lsttoken	*new;
	t_lsttoken	*subs;
	stop = 0;
	complete_line(line, &stop);
	if (stop)
		return ;
	new = tokenize(*line);
	if (!new)
		return ;
	a_and(new, ft_lstokenlast(new), \
	(t_components){STDIN_FILENO, STDOUT_FILENO, 0, NULL});
}



	// 		while (new)
	// {
	// 	if (new->t_.type != E_SPACE && new->t_.type != E_EMPTY)
	// 	{
	// 		if (new->t_.down)
	// 		{
	// 			if (new->t_.type != E_SUBSH)
	// 			printf("[%d][%s]\n", new->t_.type, ft_substr(new->t_.line, new->t_.start, new->t_.len));
	// 			else if (new->t_.type == E_SUBSH)
	// 			printf("[%d]\n", new->t_.type);
	// 			printf("-----down_start------\n");
	// 			t_lsttoken	*tmp = new->t_.down;
	// 			while (tmp)
	// 			{
	// 				if (tmp->t_.type != E_SPACE && tmp->t_.type != E_EMPTY)
	// 					printf("[%d][%s]\n", tmp->t_.type, ft_substr(tmp->t_.line, tmp->t_.start, tmp->t_.len));
	// 				else if (tmp->t_.type == E_SPACE)
	// 					printf("[%d][ ]\n", tmp->t_.type);
	// 				tmp = tmp->next;
	// 			}
	// 			printf("-----down_end------\n");
	// 		}
	// 		else
	// 			printf("[%d][%s]\n", new->t_.type, ft_substr(new->t_.line, new->t_.start, new->t_.len));
	// 	}
	// 	else if (new->t_.type == E_SPACE)
	// 		printf("[%d][ ]\n", new->t_.type);
	// 	new = new->next;
	// }
	// exit(1);
