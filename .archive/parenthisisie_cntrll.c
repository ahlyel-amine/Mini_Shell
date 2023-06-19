int	has_syntax_error(char *line, int i)
{
	int	pipe;
	int	redir;

	pipe = 0;
	redir = 0;
	while (i)
	{
		if (line[i - 1] == '|')
			pipe = 1;
		else if (line[i - 1] == '<')
			redir = 1;
		i--;
	}
	return (pipe | redir);
}

char	*remove_parenthisis_syntax_checker(char *line)
{
	char	*err;
	int		i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '(' && i && !has_syntax_error(line, i))
		{
			err = ft_substr(line, 0, i);
			return (free(line), pr_custom_err(ERR_SNTX, err, err), NULL);
		}
		i++;
	}
	return (line);
}

char	*remove_unused_parenthesis(char *line)
{
	int		i;
	int		is_open;
	int		is_closed;
	t_var	var;
	char	*err;

	ft_memset(&var, 0, sizeof(t_var));
	i = 0;
	is_open = 0;
	is_closed = 0;
	while (line[i] && ft_isspace(line[i]))
		i++;
	if (line[i] && line[i] == '(')
	{
		is_open++;
		i++;
	}
	if (is_open)
		line = select_unused_parenthesis(line, i, var, is_open);
	// else
	// 	return (remove_parenthisis_syntax_checker(line));// ??? i cant remember the purpose of this function
	if (is_open && line && !line[skip_spaces_front(line)])
		return (ft_putendl_fd(ERR_CLSD_PARNETHISE, 2), NULL);
	return (line);
}
