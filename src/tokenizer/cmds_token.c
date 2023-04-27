/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 12:31:37 by aahlyel           #+#    #+#             */
/*   Updated: 2023/04/27 13:18:24 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"


int	check_cmd(char **path, char *cmd, int j)
{
	char	*new_cmd;
	char	*tmp_path;
	int		i;

	i = 0;
	new_cmd = quotes(ft_substr(cmd, 0, j), 0);
	if (!access(new_cmd, F_OK | X_OK))
		return (1);
	while (path[i])
	{
		tmp_path = NULL;
		tmp_path = ft_strjoin(path[i], "/");
		tmp_path = ft_strjoin_free(tmp_path, ft_strdup(new_cmd));
		if (!access(tmp_path, F_OK | X_OK))
			return (1);
		i++;
	}
	return (0);
}

t_cmd	*get_token_cmd(char *line, int j)
{
	t_cmd	*cmd;

	cmd = NULL;
	if (!check_cmd((char **)set__get_option_variables(0, GET | GET_PATH), line, j))
		return (NULL);
	cmd = execcmd_constructor(ft_split_char(line, ' '));
	return (free(line), cmd);
}