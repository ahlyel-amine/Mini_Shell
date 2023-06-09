/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_parser.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 20:14:00 by aahlyel           #+#    #+#             */
/*   Updated: 2023/06/09 18:23:34 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_cmd	*redirections_parser_has_parenthesis(char *line)
{
	int	k;
	int	j;
	int	i;
	t_cmd	*operator;
	t_redir_content	red;
	t_var	var;
	
	if (!line)
		return (NULL);
	ft_memset(&var, 0, sizeof(t_var));
	i = 0;
	operator = NULL;
	while (line[i])
	{
		check_out_of_quotes(line[i], &var);
		if ((line[i] == '(') && !var.quote && !var.dquote)
		{
			k = close_parenthise(line + i + 1);
			if (k == -1)
				return (panic_recursive(ERR_UNCLSDP, &line), NULL);
			i += k; 
			continue ;
		}
		 if (line[i] == '>'  && line[i + 1] == '>' && !var.quote && !var.dquote)
		{
			if (!check_for_syntax(&line, i))
				return (NULL);
			k = fill_redir_content(line, i, &red, F_APPEND);
			operator = and_parser(
				ft_strjoin_free(remove_unused_parenthesis(ft_substr(line, 0, i)),
				ft_substr(line, k, ft_strlen(line + k)))
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
			operator = and_parser(
				ft_strjoin_free(remove_unused_parenthesis(ft_substr(line, 0, i)),
				ft_substr(line, k, ft_strlen(line + k)))
				);
			operator = redir_constructor(operator, red);
			free (line);
			line = NULL;
			break ;
		}
		else if (line[i] == '<' && line[i + 1] == '<')
		{
			k = i;
			i += 2;
			i += skip_spaces_front(line + i);
			while (isalnum(line[i]) || line[i] == '_')
				i++;
			i += skip_spaces_front(line + i);
			if (line[i] == '(')
			{
				i = k;
				k = fill_redir_content(line, k, &red, F_HEREDOC);
				operator = redir_constructor(invalid_constructor(ft_substr(line, k, ft_strlen(line + k))), red);
				free (line);
				line = NULL;
				return (operator);
			}
			break ;
		}
		else if (line[i] == '<')
		{
			i++;
			i += skip_spaces_front(line + i);
			while (isalnum(line[i]) || line[i] == '_')
				i++;
			i += skip_spaces_front(line + i);
			if (line[i] == '(')
			{
				return (
				pr_custom_err(ERR_SNTX, line, line + i),
				line = NULL, NULL);
			}
			break ;
		}
		i++;
	}
	if (!operator && line)
		operator = redirections_parser(remove_unused_parenthesis(line));
	return (operator);
}


t_cmd	*redirections_parser(char *line)
{
	t_cmd			*redirection;
	int				i;
	t_var			var;

	if (!line)
		return (NULL);
	ft_memset(&var, 0, sizeof(t_var));
	redirection = NULL;
	i = 0;
	while (line[i])
	{
		check_out_of_quotes(line[i], &var);
		if (!check_for_syntax(&line, i))
			return (NULL);
		if (!var.quote && !var.dquote)
			redirection = check_for_redirections(line, i);
		if (redirection)
		{
			free (line);
			i = -1;	
			break ;
		}
		i++;
	}
	if (i != -1)
		redirection = executable_parser(line);
	return (redirection);
}
