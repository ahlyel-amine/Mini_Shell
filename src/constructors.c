/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constructors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 10:33:29 by aahlyel           #+#    #+#             */
/*   Updated: 2023/04/27 10:29:49 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_cmd	*pipe_constructor(t_cmd *left, t_cmd *right)
{
	t_pipe	*pipe;

	pipe = malloc(sizeof(t_pipe));
	ft_memset(pipe, 0, sizeof(t_pipe));
	pipe->type = PIPE;
	pipe->left = left;
	pipe->right = right;
	return ((t_cmd *)pipe);
}
t_cmd	*execcmd_constructor(char **cmds)
{
	t_execcmd	*cmd;

	cmd = malloc(sizeof(t_execcmd));
	ft_memset(cmd, 0, sizeof(t_execcmd));
	cmd->type = EXEC;
	cmd->cmd = cmds;
	return ((t_cmd *)cmd);
}

t_cmd	*redir_constructor(t_cmd *cmd, t_redir_content content)
{
	t_redir	*redir;

	redir = malloc(sizeof(t_redir));
	ft_memset(redir, 0, sizeof(t_redir));
	redir->type = REDIR;
	redir->cmd = cmd;
	redir->red = content;
	return ((t_cmd *)redir);
}

t_cmd	*and_constructor(t_cmd *left, t_cmd *right)
{
	t_and	*and;

	and = malloc(sizeof(t_and));
	ft_memset(and, 0, sizeof(t_and));
	and->type = AND;
	and->left = left;
	and->right = right;
	return ((t_cmd *)and);
}

t_cmd	*or_constructor(t_cmd *left, t_cmd *right)
{
	t_or	*or;

	or = malloc(sizeof(t_or));
	ft_memset(or, 0, sizeof(t_or));
	or->type = OR;
	or->left = left;
	or->right = right;
	return ((t_cmd *)or);
}

t_cmd	*word_constructor(char *str)
{
	t_word	*word;

	word = malloc(sizeof(t_word));
	ft_memset(word, 0, sizeof(t_word));
	word->type = WORD;
	word->word = str;
	return ((t_cmd *)word);
}

t_cmd	*builtin_constructor(char *str, int has_option, char *cmd)
{
	t_builtin	*builtin;

	builtin = malloc(sizeof(t_builtin));
	ft_memset(builtin, 0, sizeof(t_builtin));
	builtin->type = BUILTIN;
	builtin->builtin = str;
	builtin->cmd = cmd;
	builtin->has_option = has_option;
	return ((t_cmd *)builtin);
}