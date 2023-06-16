/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   priorities_call_tools.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 19:54:15 by aahlyel           #+#    #+#             */
/*   Updated: 2023/06/16 20:00:39 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**child_vars(void)
{
	char	**backup_env;
	t_hold	*env;
	t_list	*lst;
	int		size;
	int		iter;

	is_sig = 0;
	env = set__get_option_variables(0, GET | GET_ENV);
	lst = env->lst;
	size = env->size;
	backup_env = ft_calloc(sizeof(char *), (size + 1));
	iter = 0;
	while (size--)
	{
		backup_env[iter] = ft_strdup(lst->content);
		lst = lst->next;
		iter++;
	}
	return (backup_env);
}

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
		if (redir->t_.type == E_INRED)
			comp.infile = open(delimiter, O_RDONLY);
		else if (redir->t_.type == E_APPEND)
			comp.outfile = open(delimiter, O_CREAT | O_APPEND | O_WRONLY, 0644);
		else if (redir->t_.type == E_OUTRED)
			comp.outfile = open(delimiter, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	}
	return (free(delimiter), comp);
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

