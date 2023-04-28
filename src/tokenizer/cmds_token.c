/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 12:31:37 by aahlyel           #+#    #+#             */
/*   Updated: 2023/04/28 09:09:56 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_cmd(char **path, char *cmd, int j)
{
	char	*new_cmd;
	char	*tmp_path;
	char	*tmp_to_free;
	int		i;

	i = 0;
	if (!path)
		return (0);
	tmp_to_free = ft_substr(cmd, 0, j);
	new_cmd = quotes(tmp_to_free, 0);
	free (tmp_to_free);
	if (!access(new_cmd, F_OK | X_OK))
		return (free(new_cmd), 1);
	tmp_path = NULL;
	while (path[i])
	{
		tmp_path = NULL;
		tmp_path = ft_strjoin(path[i], "/");
		tmp_path = ft_strjoin_free(tmp_path, ft_strdup(new_cmd));
		if (!access(tmp_path, F_OK | X_OK))
			return (free(tmp_path), free(new_cmd), 1);
		if (path[i + 1])
			free (tmp_path);
		i++;
	}
	return (free(tmp_path), free(new_cmd),0);
}


t_cmd	*get_token_cmd(char *line, int j)
{
	t_cmd	*cmd;

	cmd = NULL;
	if (!check_cmd((char **)set__get_option_variables(0, GET | GET_PATH), line, j))
		return (free(line), NULL);
	cmd = execcmd_constructor(ft_split_char(line, ' '));
	return (free(line), cmd);
}