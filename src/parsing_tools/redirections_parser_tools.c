/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_parser_tools.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbrahm <aelbrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 15:39:50 by aahlyel           #+#    #+#             */
/*   Updated: 2023/06/19 09:49:28 by aelbrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	skip_quote_heredoc_delimiter_conditions(char *line, \
char **tmp, t_2ptr_int a, t_var var)
{
	if (ft_isspace(line[*(a.i)]) && !var.quote && !var.dquote)
		return (1);
	if ((var.quote || var.dquote) && ft_isspace(line[*(a.i)]))
		(*tmp)[(*(a.k))++] = line[*(a.i)];
	else if ((line[*(a.i)] == '\"' && var.quote) || (line[*(a.i)] == '\''\
			&& var.dquote))
		(*tmp)[(*(a.k))++] = line[*(a.i)];
	else if (!var.quote && !var.dquote && !ft_isvariable(line[*(a.i)])
		&& line[*(a.i)] != '\"' && line[*(a.i)] != '\'')
		return (1);
	else if (line[*(a.i)] != '\'' && line[*(a.i)] != '\"')
		(*tmp)[(*(a.k))++] = line[*(a.i)];
	return (0);
}

char	*skip_q_hrdc_delim(char *line, char *end_line, int *q)
{
	int		i;
	int		k;
	char	*tmp;
	t_var	var;

	i = 0;
	ft_memset(&var, 0, sizeof(t_var));
	tmp = ft_calloc(1, (end_line - line) + 1);
	k = 0;
	*q = 0;
	if (line[i] == '$' && (line[i + 1] == '\'' || line[i + 1] == '\"'))
		i++;
	while (line[i] && line + i != end_line)
	{
		check_out_of_quotes(line[i], &var);
		if (var.dquote || var.quote)
			*q = 1;
		if (skip_quote_heredoc_delimiter_conditions(line, &tmp, \
		(t_2ptr_int){&i, &k}, var))
			break ;
		i++;
	}
	return (tmp);
}

static char	*get_herdoc_name(void)
{
	static int	call;

	return (ft_strjoin_free(ft_strdup(HERDOC_FILE), ft_itoa(call++)));
}
void	print_arguments(t_arguments *args, char *ref)
{
	t_arguments	*tmp;
	t_arguments	*tmp2;

	tmp = args;
	printf("--------------------arguments_START----%s--------\n", ref);
	while (tmp)
	{
		if (tmp->type & IS_STR || tmp->type & IS_VARIABLE
			|| tmp->type & IS_SEPARTOR)
			printf("%d[%s]\n", tmp->type, tmp->str);
		else
		{
			tmp2 = tmp->down;
			printf("{%d}\n", tmp->type);
			while (tmp2)
			{
				printf("%d]%s[\n", (tmp2)->type, (tmp2)->str);
				tmp2 = (tmp2)->next;
			}
		}
		tmp = tmp->next;
	}
	printf("--------------------arguments_END------%s----------------\n", ref);
}
char	*her_expand(char *line)
{
	t_arguments *args;
	char		*r_str;
	int			i;

	i = 0;
	args = get_argument(line, i, 0);
	print_arguments(args, "df");
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

	e_glb.in_cmd = 1;
	sig_here();
	name = get_herdoc_name();
	fd = open(name, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (fd < 0)
		return (pr_custom_err(ERR_FILE, name, name), -1);
	line = readline(HERDOC);
	while (line && !e_glb.Ctrl_c)
	{
		if (read_heredoc_inside_loops(&line, delimiter, fd, q))
			break ;
	}
	e_glb.Ctrl_c = 0;
	e_glb.in_cmd = 0;
	close(fd);
	fd = open(name, O_RDONLY, 0644);
	if (fd < 0)
		return (pr_custom_err(ERR_FILE, name, name), -1);
	return (free(name), fd);
}
