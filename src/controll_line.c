/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controll_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 02:53:32 by aahlyel           #+#    #+#             */
/*   Updated: 2023/06/15 01:13:56 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

typedef struct s_lsttoken t_lsttoken;

typedef struct s_token
{
	int			type;
	char		*line;
	int			start;
	int			len;
	t_lsttoken	*down;
}	t_token;

typedef struct s_components
{
	int	infile;
	int	outfile;
	int is_pipe:2;
	int	*fd;
}	t_components;

struct s_lsttoken
{
	t_token				t_;
	struct s_lsttoken	*next;
};

typedef enum e_token
{
	E_P_OPEN,
	E_P_CLOSE,
	E_DQUOTE,
	E_QUOTE,
	E_AND,
	E_OR,
	E_PIPE,
	E_HEREDOC,
	E_OUTRED,
	E_INRED,
	E_APPEND,
	E_STR,
	E_SPACE,
	E_FD_NAME,
	E_EMPTY
}	enum_token;

t_lsttoken	*new_token(t_token t_)
{
	t_lsttoken	*node;

	node = (t_lsttoken *)malloc(sizeof(t_lsttoken));
	if (node)
	{
		node->t_ = t_;
		node->next = NULL;
	}
	return (node);
}
t_lsttoken	*ft_lstokenlast(t_lsttoken *lst)
{
	if (lst)
	{
		while (lst->next)
			lst = lst->next;
	}
	return (lst);
}

void	ft_lstokenadd_back(t_lsttoken **lst, t_lsttoken *new, int *len)
{
	t_lsttoken	*tmp;

	tmp = NULL;
	if (!new || !lst)
		return ;
	if (!*lst)
	{
		*lst = new;
		*len = 0;
	}
	else
	{
		tmp = ft_lstokenlast(*lst);
		tmp->next = new;
		(*len)++;
	}
}

t_lsttoken	*tokenize(char *line, int *len)
{
	t_lsttoken	*new = NULL;
	int i = 0, j;
	while (line[i])
	{
		j = 0;
		if (line[i] == '(')
		{
			j = close_parenthise(line + i + 1);
			if (j == -1)
				return (panic_recursive(ERR_UNCLSDP, NULL), NULL);
			ft_lstokenadd_back(&new, new_token((t_token){E_P_OPEN, line, i + 1, j - 1, NULL}), len);
			i += j + 1;
			continue;
		}
		else if (line[i] == '\"')
		{
			j = 1;
			while (line[i + j] && line[i + j] != '\"')
				j++;
			ft_lstokenadd_back(&new, new_token((t_token){E_DQUOTE, line, i, j + 1, NULL}), len);
			i += j + 1;
			continue;
		}
		else if (line[i] == '\'')
		{
			j = 1;
			while (line[i + j] && line[i + j] != '\'')
				j++;
			ft_lstokenadd_back(&new, new_token((t_token){E_QUOTE, line, i, j + 1, NULL}), len);
			i += j + 1;
			continue;
		}
		else if (line[i] == '&')
		{
			if (line[i + 1] != '&')
				return (panic_recursive(ERR_1AND, NULL), NULL);
			ft_lstokenadd_back(&new, new_token((t_token){E_AND, line, i, 2, NULL}), len);
			i += 2;
			continue;
		}
		else if (line[i] == '|' && line[i + 1] == '|')
		{
			ft_lstokenadd_back(&new, new_token((t_token){E_OR, line, i, 2, NULL}), len);
			i += 2;
			continue;
		}
		else if (line[i] == '|')
		{
			ft_lstokenadd_back(&new, new_token((t_token){E_PIPE, line, i, 1, NULL}), len);
			i++;
			continue;
		}
		else if (line[i] == '>' && line[i + 1] == '>')
		{
			ft_lstokenadd_back(&new, new_token((t_token){E_APPEND, line, i, 2, NULL}), len);
			i += 2;
			continue;
		}
		else if (line[i] == '>')
		{
			ft_lstokenadd_back(&new, new_token((t_token){E_OUTRED, line, i, 1, NULL}), len);
			i++;
			continue;
		}
		else if (line[i] == '<' && line[i + 1] == '<')
		{
			ft_lstokenadd_back(&new, new_token((t_token){E_HEREDOC, line, i, 2, NULL}), len);
			i += 2;
			continue;
		}
		else if (line[i] == '<')
		{
			ft_lstokenadd_back(&new, new_token((t_token){E_INRED, line, i, 1, NULL}), len);
			i++;
			continue;
		}
		else
		{
			while (line[i + j] && line[i + j] != '<' && line[i + j] != '>' && line[i + j] != '|' && line[i + j] != '&' && line[i + j] != '\'' && line[i + j] != '\"' && line[i + j] != ')' && line[i + j] != '(' && line[i + j] != ' ')
				j++;
			if (j)
				ft_lstokenadd_back(&new, new_token((t_token){E_STR, line, i, j, NULL}), len);
			i += j;
			j = 0;
			while (line[i + j] == ' ')
				j++;
			if (j)
				ft_lstokenadd_back(&new, new_token((t_token){E_SPACE, 0, 0, 0, NULL}), len);
			i += j;
			while (line[i] == ')')
				i++;
		}
	}
	return (new);
}
void	a_and(t_lsttoken *front, t_lsttoken *back, t_components comp);

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
		return (pr_custom_err(ERR_CMD, cmd, cmd), NULL);
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
	return (pr_custom_err(ERR_CMD, cmd, cmd), NULL);
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

void	cmd_executers(char *path, char **cmd, t_components comp)
{
	int status;

	if (!path)
		return (sp_free(cmd));
	else if (!cmd)
		return (free(path));
	int pid = fork();
	if (pid == -1)
		return (perror(SHELL_NAME));
	if (!pid)
		child(cmd, path, comp);
	if (comp.is_pipe != 0)
		return ;
	if (waitpid(pid, &status, 0) == -1)
		return (free(path));
	if (cmd_sig_check(path, status))
		return ;
}

void	a_exec(t_lsttoken *front, t_lsttoken *back, t_components comp)
{
	t_lsttoken *head = front;
	int			current_len = 0;
	int			i = 0, in = 0;

	size_t len = get_lenght(front, back);
	char *line = get_line(front, back, len);
	i = skip_spaces_front(line);
	while (line[i + in] && line[i + in] != ' ')
		in++;
	char *cmd = ft_substr(line, i, in);
	
	if (!is_builtin(cmd))
	{
		cmd_executers(get_path(cmd), ft_split(line, ' '), comp);
	}
	// while (head != back)
	// {
	// 	if (head->t_.type != E_EMPTY && head->t_.type != E_SPACE)
	// 	printf("[%d][%s]\n",head->t_.type, ft_substr(head->t_.line, head->t_.start, head->t_.len));
	// 	// if (head->t_.type == E_AND)
	// 	// {
	// 	// 	in = 1;
	// 	// 	a_subsh(front, prev);
	// 	// }
	// 	head = head->next;
	// }
	// if (head == back)
	// {
	// 	if (head->t_.type != E_EMPTY && head->t_.type != E_SPACE)
	// 	printf("[%d][%s]\n",head->t_.type, ft_substr(head->t_.line, head->t_.start, head->t_.len));
	// }
	// printf("---------^END^----------\n");
	// if (!in)
	// 	a_exec(front, back, comp);
}


	
void	a_subsh(t_lsttoken *front, t_lsttoken *back, t_components comp)
{
	t_lsttoken *head;
	t_lsttoken *prev;
	int			in;
	int			pid;

	in = 0;
	head = front;
	prev = front;
	while (head != back)
	{
		if (head->t_.type == E_P_OPEN)
		{
			in = 1;
			pid = fork();
			if (!pid)
			{
				a_and(head->t_.down, ft_lstokenlast(head->t_.down), comp);
			}
			else
				waitpid(pid, NULL, 0);
			break ;
		}
		prev = head;
		head = head->next;
	}
	if (!in)
		a_exec(front, back, comp);
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
		if (redir->t_.type == E_INRED)
			comp.infile = open(delimiter, O_RDONLY);
		else if (redir->t_.type == E_APPEND)
			comp.outfile = open(delimiter, O_CREAT | O_APPEND | O_WRONLY, 0644);
		else if (redir->t_.type == E_OUTRED)
			comp.outfile = open(delimiter, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	}
	return (free(delimiter), comp);
}

void	a_red(t_lsttoken *front, t_lsttoken *back, t_components comp)
{
	t_lsttoken *head = front;
	int			in = 0;
	t_lsttoken *prev = front;
	
	while (head != back)
	{
		if (head->t_.type == E_OUTRED || head->t_.type == E_INRED || head->t_.type == E_APPEND || head->t_.type == E_HEREDOC)
		{
			in = 1;
			t_components tmp = get_red(head, comp);
			
			head->t_.type = E_EMPTY;			
			a_red(front, back, tmp);
			break ;
		}
		prev = head;
		head = head->next;
	}
	if (!in)
		a_subsh(front, back, comp);
}

void	a_pipe(t_lsttoken *front, t_lsttoken *back, t_components comp)
{
	t_lsttoken *head = front;
	int fd[2];
	int			in = 0;
	t_lsttoken *prev = front;
	while (head != back)
	{
		if (head->t_.type == E_PIPE)
		{
			in = 1;
			pipe(fd);
			a_red(front, prev, (t_components){comp.infile, fd[1], 1, fd});
			close(fd[1]);
			a_pipe(head->next, back, (t_components){fd[0], comp.outfile, 1, fd});
			close(fd[0]);
			if (!pipes_left)
			break;
		}
		prev = head;
		head = head->next;
	}
	if (!in)
		a_red(front, back, comp);
}

void	a_or(t_lsttoken *front, t_lsttoken *back, t_components comp)
{
	t_lsttoken *head = front;
	int			in = 0;
	t_lsttoken *prev = front;

	while (head != back)
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
		head = head->next;
	}
	if (!in)
		a_pipe(front, back, comp);
}

void	a_and(t_lsttoken *front, t_lsttoken *back, t_components comp)
{
	t_lsttoken *head = front;
	t_lsttoken *prev = front;
	int			in = 0;
	
	while (head != back)
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
		head = head->next;
	}
	if (!in)
		a_or(front, back, comp);
}

int	a_check(t_lsttoken	*new)
{
	if (!new)
		return (0);
	t_lsttoken	*check = new;
	if (check->t_.type == E_AND || check->t_.type == E_OR || check->t_.type == E_PIPE)
	{
		return (panic_recursive(ERR_O_SNTX, NULL), 0);
	}
	while (check)
	{
		if (check->t_.type == E_OUTRED || check->t_.type == E_INRED || check->t_.type == E_APPEND || check->t_.type == E_HEREDOC)
		{
			if (!check->next)
				return (panic_recursive(ERR_O_SNTX, NULL), 0);
			else if (check->next && check->next->next && check->next->t_.type == E_SPACE && check->next->next->t_.type != E_STR && check->next->next->t_.type != E_QUOTE && check->next->next->t_.type != E_DQUOTE)
				return (panic_recursive(ERR_O_SNTX, NULL), 0);
			else if (check->next && check->next->t_.type != E_SPACE && check->next->t_.type != E_STR  && check->next->t_.type != E_QUOTE && check->next->t_.type != E_DQUOTE)
				return (panic_recursive(ERR_O_SNTX, NULL), 0);
			
		}
		else if (check->t_.type == E_AND && (check->next->t_.type == E_OR || check->next->t_.type == E_PIPE))
				return (panic_recursive(ERR_O_SNTX, NULL), 0);
		else if (check->t_.type == E_OR && (check->next->t_.type == E_AND || check->next->t_.type == E_PIPE))
				return (panic_recursive(ERR_O_SNTX, NULL), 0);
		else if (check->t_.type == E_PIPE && (check->next->t_.type == E_OR || check->next->t_.type == E_AND))
				return (panic_recursive(ERR_O_SNTX, NULL), 0);
		check = check->next;
	}
	check = new;
	t_lsttoken	*check_2;
	while (check)
	{
		if (check->t_.type == E_OUTRED || check->t_.type == E_INRED || check->t_.type == E_APPEND || check->t_.type == E_HEREDOC)
		{
			check_2 = check->next;
			while (check_2)
			{
				if (check_2->t_.type == E_PIPE || check_2->t_.type == E_AND || check_2->t_.type == E_OR || check_2->t_.type == E_OUTRED || check_2->t_.type == E_INRED || check_2->t_.type == E_APPEND || check_2->t_.type == E_HEREDOC)
					break ;
				else if (check_2->t_.type == E_P_OPEN)
					return (panic_recursive(ERR_O_SNTX, NULL), 0);
				check_2 = check_2->next;
			}
		}
		check = check->next;
	}
	return (1);
}

void	get_fds(t_lsttoken	*fds)
{
	t_lsttoken	*head;
	t_lsttoken	*tmp;
	int			start;
	int			end;

	head = fds;
	while (head)
	{
		if (head->t_.type == E_OUTRED || head->t_.type == E_INRED || head->t_.type == E_APPEND || head->t_.type == E_HEREDOC)
		{
			tmp = head->next;
			if (tmp->t_.type == E_SPACE)
			{
				tmp->t_.type = E_EMPTY;
				tmp = tmp->next;
			}
			start = tmp->t_.start;
			end = 0;
			while (tmp)
			{
				if (tmp->t_.type == E_STR || tmp->t_.type == E_DQUOTE || tmp->t_.type == E_QUOTE)
				{
					tmp->t_.type = E_EMPTY;
					end += tmp->t_.len;
				}
				else
					break ;
				tmp = tmp->next;
			}
			head->t_.down = new_token((t_token){E_FD_NAME, head->t_.line, start, end, NULL});
		}
		head = head->next;
	}
}

void	controll_line(char **line)
{
	t_cmd	*cmd;
	int		stop;

	stop = 0;
	cmd = NULL;
	complete_line(line, &stop);
	if (stop)
		return ;
	int len;
	t_lsttoken	*new = tokenize(*line, &len);
	if (!a_check(new))
		return ;
	t_lsttoken	*subs = new;
	while (subs)
	{
		if (subs->t_.type == E_P_OPEN)
		{
			t_lsttoken	*pop = tokenize(ft_substr(subs->t_.line, subs->t_.start, subs->t_.len), &len);
			if (!a_check(pop))
				return ;
			subs->t_.down = pop;
		}
		subs = subs->next;
	}
	get_fds(new);
	// get_fds(new);
	a_and(new, ft_lstokenlast(new), (t_components){STDIN_FILENO, STDOUT_FILENO, 0, NULL});
	// while (new)
	// {
	// 	if (new->t_.type != E_SPACE && new->t_.type != E_EMPTY)
	// 	{
	// 		if (new->t_.down)
	// 		{
	// 			if (new->t_.type != E_P_OPEN)
	// 			printf("[%d][%s]\n", new->t_.type, ft_substr(new->t_.line, new->t_.start, new->t_.len));
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
	exit(1);	
	// if (line && *line)
	// 	cmd = parse_line(*line);
	// if (cmd && !check_parsing(cmd))
	// 	;
	// else if (cmd)
	// 	execute_line(cmd);
	// free_line(cmd);
}
