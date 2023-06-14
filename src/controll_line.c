/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controll_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 02:53:32 by aahlyel           #+#    #+#             */
/*   Updated: 2023/06/14 18:49:18 by aahlyel          ###   ########.fr       */
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

t_lsttoken	*a_parse(char *line, int *len)
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
			ft_lstokenadd_back(&new, new_token((t_token){E_P_OPEN, line, i + 1, j, NULL}), len);
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
			while (line[i + j] && line[i + j] != '<' && line[i + j] != '>' && line[i + j] != '|' && line[i + j] != '&' && line[i + j] != '\'' && line[i + j] != '\"' && line[i + j] != ')' && line[i + j] != '(')
				j++;
			ft_lstokenadd_back(&new, new_token((t_token){E_STR, line, i, j, NULL}), len);
			i += j;
			while (line[i] == ')')
				i++;
		}
	}
	return (new);
}
void	a_and(t_lsttoken *front, t_lsttoken *back);

void	a_exec(t_lsttoken *front, t_lsttoken *back)
{
	t_lsttoken *head = front;
	int			current_len = 0;
	int			in = 0;
	printf("---------^START^----------\n");
	while (head != back)
	{
		printf("[%d][%s]\n",head->t_.type, ft_substr(head->t_.line, head->t_.start, head->t_.len));
		// if (head->t_.type == E_AND)
		// {
		// 	in = 1;
		// 	a_subsh(front, prev);
		// }
		head = head->next;
	}
	if (head == back)
	{
		printf("[%d][%s]\n",head->t_.type, ft_substr(head->t_.line, head->t_.start, head->t_.len));
	}
	printf("---------^END^----------\n");
	// if (!in)
	// 	a_exec(front, back);
}

void	a_subsh(t_lsttoken *front, t_lsttoken *back)
{
	t_lsttoken *head = front;
	int			current_len = 0;
	t_lsttoken *prev = front;
	int			in = 0;
	while (head != back)
	{
		if (head->t_.type == E_P_OPEN)
		{
			in = 1;
			a_and(head->t_.down, ft_lstokenlast(head->t_.down));
		}
		prev = head;
		head = head->next;
	}
	if (!in)
		a_exec(front, back);
}

void	a_red(t_lsttoken *front, t_lsttoken *back)
{
	t_lsttoken *head = front;
	int			in = 0;
	t_lsttoken *prev = front;
	
	while (head != back)
	{
		if (head->t_.type == E_OUTRED || head->t_.type == E_INRED || head->t_.type == E_APPEND || head->t_.type == E_HEREDOC)
		{
			in = 1;
			a_subsh(front, prev);
			a_red(head->next, back);
		}
		prev = head;
		head = head->next;
	}
	if (!in)
		a_subsh(front, back);
}

void	a_pipe(t_lsttoken *front, t_lsttoken *back)
{
	t_lsttoken *head = front;
	int			in = 0;
	t_lsttoken *prev = front;
	while (head != back)
	{
		if (head->t_.type == E_PIPE)
		{
			in = 1;
			a_red(front, prev);
			a_pipe(head->next, back);
		}
		prev = head;
		head = head->next;
	}
	if (!in)
		a_red(front, back);
}

void	a_or(t_lsttoken *front, t_lsttoken *back)
{
	t_lsttoken *head = front;
	int			in = 0;
	t_lsttoken *prev = front;

	while (head != back)
	{
		if (head->t_.type == E_OR)
		{
			in = 1;
			a_pipe(front, prev);
			a_or(head->next, back);
		}
		prev = head;
		head = head->next;
	}
	if (!in)
		a_pipe(front, back);
}

void	a_and(t_lsttoken *front, t_lsttoken *back)
{
	t_lsttoken *head = front;
	t_lsttoken *prev = front;
	int			in = 0;
	
	while (head != back)
	{
		if (head->t_.type == E_AND)
		{
			in = 1;
			a_or(front, prev);
			a_and(head->next, back);
		}
		prev = head;
		head = head->next;
	}
	if (!in)
		a_or(front, back);
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
			if (!check->next || check->next->t_.type != E_STR)
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
	return (1);
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
	t_lsttoken	*new = a_parse(*line, &len);
	if (!a_check(new))
		return ;
	t_lsttoken	*subs = new;
	while (subs)
	{
		if (subs->t_.type == E_P_OPEN)
		{
			t_lsttoken	*pop = a_parse(ft_substr(subs->t_.line, subs->t_.start, subs->t_.len), &len);
			if (!a_check(pop))
				return ;
			subs->t_.down = pop;
		}
		subs = subs->next;
	}
	a_and(new, ft_lstokenlast(new));
	// while (new)
	// {
		// printf("[%d][%s]\n", new->t_.type, ft_substr(new->t_.line, new->t_.start, new->t_.len));
		// new = new->next;
	// }
	exit(1);
	if (line && *line)
		cmd = parse_line(*line);
	if (cmd && !check_parsing(cmd))
		;
	else if (cmd)
		execute_line(cmd);
	free_line(cmd);
}
