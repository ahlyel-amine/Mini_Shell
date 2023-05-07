/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 12:31:37 by aahlyel           #+#    #+#             */
/*   Updated: 2023/05/07 20:05:54 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_cmd(char **path, char *cmd, int j)
{
	char	*new_cmd;
	char	*tmp_path;
	char	*tmp;
	int		i;
	
	i = 0;
	tmp = ft_substr(cmd, 0, j);
	new_cmd = skip_quotes(tmp, NULL, 0, 0);
	if (!*new_cmd)
		return (free(new_cmd), free (tmp), 0);
	if (!access(new_cmd, F_OK | X_OK))
		return (free(new_cmd), free (tmp), 1);
	tmp_path = NULL;
	while (path[i])
	{
		tmp_path = NULL;
		tmp_path = ft_strjoin(path[i], "/");
		tmp_path = ft_strjoin_free(tmp_path, ft_strdup(new_cmd));
		if (!access(tmp_path, F_OK | X_OK))
			return (free(tmp_path), free(new_cmd), free (tmp), 1);
		if (path[i + 1])
			free (tmp_path);
		i++;
	}
	return (free(tmp_path), free(new_cmd), free (tmp), 0);
}


t_cmd	*get_token_cmd(char *line, int j)
{
	t_cmd	*cmd;
	char	*cmd_line;
	char	**path;

	cmd = NULL;
	path = (char **)set__get_option_variables(0, GET | GET_PATH);
	if (!path)
		return (NULL);
	if (!check_cmd(path, line, j))
		return (free(line), NULL);
	cmd_line = skip_quotes(line, NULL, 0, 0);
	cmd = execcmd_constructor(ft_split_char(cmd_line, ' '));
	return (free(line), free(cmd_line), cmd);
}