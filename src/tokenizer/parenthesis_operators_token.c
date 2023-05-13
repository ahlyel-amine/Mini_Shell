/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parenthesis_operators_token.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 15:30:16 by aahlyel           #+#    #+#             */
/*   Updated: 2023/05/13 10:14:42 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int		parhenthises_closed(char *line, int *k, int *i);
t_cmd			*get_token_parenthesis_pipe(char *line);
t_cmd			*get_token_parenthesis_or(char *line);
static t_cmd	*get_token_redirection_parenthises(char *line);

static int	parhenthises_closed(char *line, int *k, int *i)
{
	int		is_closed;
	int		is_open;
	t_var	var;

	set_zero_var(&var);
	*i = -1;
	is_open = 1;
	is_closed = 0;
	while (line[++(*i)])
	{
		check_out_of_quotes(line[*i], &var);
		if (line[*i] == '(' && !var.quote && \
		!var.dquote && is_open != is_closed)
			is_open++;
		else if (line[*i] == ')' && !var.quote && \
		!var.dquote && is_open != is_closed)
		{
			is_closed++;
			*k = *i;
			continue ;
		}
		if (is_open == is_closed)
			return (1);
	}
	return (0);
}

int	close_parenthise(char *line)
{
	int	i;
	int	open;
	int	close;
	t_var	var;

	i = 0;
	set_zero_var(&var);
	open = 1;
	close = 0;
	while (line[i])
	{
		check_out_of_quotes(line[i], &var);
		if (line[i] == '(' && !var.dquote && !var.quote)
			open++;
		else if (line[i] == ')' && !var.dquote && !var.quote)
			close++;
		i++;
		if (close == open)
		{
			i++;
			break ;
		}
	}
	return (i);
}

static t_cmd	*call_and(char **line, int i)
{
	t_cmd	*operator;
	
	operator = NULL;
	if ((*line)[i] == '&' && (*line)[i + 1] == '&')
	{
		operator = get_token_parenthesis_and(remove_unused_parenthesis(ft_substr((*line), 0, i)));
		operator = and_constructor(operator,
			get_token_parenthesis_and(\
			remove_unused_parenthesis(\
			ft_substr((*line), i + 2, \
			ft_strlen((*line) + i + 2)))));
		free ((*line));
		*line = NULL;
	}
	return (operator);
}

static t_cmd	*call_or(char **line, int i)
{
	t_cmd	*operator;
	
	operator = NULL;
	if ((*line)[i] == '|' && (*line)[i + 1] == '|')
	{
		operator = get_token_parenthesis_and(remove_unused_parenthesis(ft_substr((*line), 0, i)));
		operator = or_constructor(operator,
			get_token_parenthesis_and(\
			remove_unused_parenthesis(\
			ft_substr((*line), i + 2, \
			ft_strlen((*line) + i + 2)))));
		free ((*line));
		*line = NULL;
	}
	return (operator);
}

static t_cmd	*call_pipe(char **line, int i)
{
	t_cmd	*operator;
	
	operator = NULL;
	if ((*line)[i] == '|')
	{
		operator = get_token_parenthesis_and(remove_unused_parenthesis(ft_substr((*line), 0, i)));
		operator = pipe_constructor(operator,
			get_token_parenthesis_and(\
			remove_unused_parenthesis(\
			ft_substr((*line), i + 1, \
			ft_strlen((*line) + i + 1)))));
		free ((*line));
		*line = NULL;
	}
	return (operator);
}

t_cmd	*get_token_parenthesis_and(char *line)
{
	t_cmd	*operator;
	int		i;
	int		j;
	int		k;
	t_var	var;
	
	i = 0;
	operator = NULL;
	set_zero_var(&var);
	i = skip_spaces_front(line);
	if (line[i] == ')' || line[i] == '&' || line[i] == '|')
			return (pr_custom_err(ERR_ClSD_PARNETHISE, line, line + i), NULL);
	while (line[i])
	{

		printf("still here [%c]\n", line[i]);
		check_out_of_quotes(line[i], &var);
		if (line[i] == '(' && !var.quote && !var.dquote)
			i += close_parenthise(line + i + 1);
		if (line[i] == '&' && line[i + 1] == '&'  && !var.quote && !var.dquote)
		{
			operator = call_and(&line, i);
			break ;	
		}
		i++;
	}
	if (!operator && line)
		operator = get_token_parenthesis_or(remove_unused_parenthesis(line));
	return (operator);
}

t_cmd	*get_token_parenthesis_or(char *line)
{
	t_cmd	*operator;
	int		i;
	int		j;
	int		k;
	t_var	var;
	
	i = 0;
	operator = NULL;
	set_zero_var(&var);
	i = skip_spaces_front(line);
	printf ("[%s]\n" , line);
	if (line[i] == ')' || line[i] == '&' || line[i] == '|')
			return (pr_custom_err("allo", line, line + i), NULL);
			// return (panic_recursive(ERR_ClSD_PARNETHISE, line), NULL);
	while (line[i])
	{
		check_out_of_quotes(line[i], &var);
		if (line[i] == '(' && !var.quote && !var.dquote)
			i += close_parenthise(line + i + 1);
		if (line[i] == '|' && line[i + 1] == '|'  && !var.quote && !var.dquote)
		{
			operator = call_or(&line, i);
			break ;	
		}
		else if (line[i] == '|'  && !var.quote && !var.dquote)
		{
			operator = call_pipe(&line, i);
			break ;	
		}
		i++;
	}
	if (!operator && line)
		operator = get_token_parenthesis_pipe(remove_unused_parenthesis(line));
	return (operator);
}

t_cmd	*get_token_parenthesis_pipe(char *line)
{
	t_cmd	*operator;
	int		i;
	int		j;
	int		k;
	t_var	var;
	
	i = 0;
	operator = NULL;
	set_zero_var(&var);
	i = skip_spaces_front(line);
	printf ("[%s]\n" , line);
	if (line[i] == ')' || line[i] == '&' || line[i] == '|')
			return (pr_custom_err("allo", line, line + i), NULL);
	while (line[i])
	{
		check_out_of_quotes(line[i], &var);
		if (line[i] == '(' && !var.quote && !var.dquote)
			i += close_parenthise(line + i + 1);
		else if (line[i] == '|'  && !var.quote && !var.dquote)
		{
			operator = call_pipe(&line, i);
			break ;	
		}
		i++;
	}
	if (!operator && line)
		operator = get_token_redirection_parenthises(remove_unused_parenthesis(line));
	return (operator);
}

static t_cmd	*get_token_redirection_parenthises(char *line)
{
	int	k;
	int	j;
	int	i;
	t_cmd	*operator;
	t_redir_content	red;
		t_var	var;
	set_zero_var(&var);
	i = 0;
	operator = NULL;
	while (line[i])
	{
		check_out_of_quotes(line[i], &var);
		if (line[i] == '(' && !var.quote && !var.dquote)
			i += close_parenthise(line + i + 1);
		if (line[i] == '<' && line[i + 1] == '<' && !var.quote && !var.dquote)
		{
			if (!check_for_syntax(&line, i))
				return (NULL);
			k = fill_redir_content(line, i, &red, F_HEREDOC);
			operator = get_token_parenthesis_and(
				ft_strjoin_free(remove_unused_parenthesis(ft_substr(line, 0, i)),
				ft_substr(line, + k, ft_strlen(line + k)))
				);
			operator = redir_constructor(operator, red);
			free (line);
			line = NULL;
			break ;
		}
		else if (line[i] == '<' && !var.quote && !var.dquote)
		{
			if (!check_for_syntax(&line, i))
				return (NULL);
			k = fill_redir_content(line, i, &red, F_IN_RED);
			operator = get_token_parenthesis_and(
				ft_strjoin_free(remove_unused_parenthesis(ft_substr(line, 0, i)),
				ft_substr(line, + k, ft_strlen(line + k)))
				);

			operator = redir_constructor(operator, red);
			free (line);
			line = NULL;
			break ;
		}
		else if (line[i] == '>'  && line[i + 1] == '>' && !var.quote && !var.dquote)
		{
			if (!check_for_syntax(&line, i))
				return (NULL);
			k = fill_redir_content(line, i, &red, F_APPEND);
			operator = get_token_parenthesis_and(
				ft_strjoin_free(remove_unused_parenthesis(ft_substr(line, 0, i)),
				ft_substr(line, + k, ft_strlen(line + k)))
				);

			operator = redir_constructor(operator, red);
			free (line);
			line = NULL;
			break ;
		}
		else if (line[i] == '>' && !var.quote && !var.dquote)
		{
			if (!check_for_syntax(&line, i))
				return (NULL);
			k = fill_redir_content(line, i, &red, F_OUT_RED);
			operator = get_token_parenthesis_and(
				ft_strjoin_free(remove_unused_parenthesis(ft_substr(line, 0, i)),
				ft_substr(line, + k, ft_strlen(line + k)))
				);
			operator = redir_constructor(operator, red);
			free (line);
			line = NULL;
			break ;
		}
		i++;
	}
	if (!operator && line)
		operator = get_token_redir(remove_unused_parenthesis(line));
	return (operator);
}
