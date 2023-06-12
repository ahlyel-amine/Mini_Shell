// unsigned short	check_wild_cards(char *str, unsigned short type)
// {
// 	int	i;

// 	i = 0;
// 	while (str[i])
// 	{
// 		if (str[i] == '*')
// 		{
// 			i = -1;
// 			break ;
// 		}
// 		i++;
// 	}
// 	if (type == 3 && i != -1)
// 		type = 1;
// 	return (type);
// }

// void	something_wrong(char *error, void *to_free)
// {
// 	free(to_free);
// 	ft_putstr_fd(error, 2);
// 	set__get_option_variables(0, FREE);
// 	exit(1);
// }

// static int	parhenthises_closed(char *line, int *k, int *i)
// {
// 	int		is_closed;
// 	int		is_open;
// 	t_var	var;

// 	ft_memset(&var, 0, sizeof(t_var));
// 	*i = -1;
// 	is_open = 1;
// 	is_closed = 0;
// 	while (line[++(*i)])
// 	{
// 		check_out_of_quotes(line[*i], &var);
// 		if (line[*i] == '(' && !var.quote && \
// 		!var.dquote && is_open != is_closed)
// 			is_open++;
// 		else if (line[*i] == ')' && !var.quote && \
// 		!var.dquote && is_open != is_closed)
// 		{
// 			is_closed++;
// 			*k = *i;
// 			continue ;
// 		}
// 		if (is_open == is_closed)
// 			return (1);
// 	}
// 	return (0);
// }

// int	check_after_parenthesis(char *line, int i, int open, int close)
// {
// 	int	j;

// 	j = 0;
// 	if (open != close)
// 		return (0);
// 	i += skip_spaces_front(line + i);
// 	if (line[i] == '(' || line[i] == ')')
// 		return (0);
// 	return (1);
// }

// void	transform_dollar(char *line, int *i, int *k, char **tmp)
// {
// 	if (ft_isdigit(line[*i + 1]))
// 		*i += 2;
// 	else if (line[*i] == '$' && (!line[*i + 1] || ft_isspace(line[*i + 1])))
// 		(*tmp)[(*k)++] = line[(*i)++];
// 	else if (line[*i] == '$' && line[*i + 1] == '$')
// 		(*tmp)[(*k)++] = line[(*i)++];
// 	else if (line[*i] == '$')
// 	{
// 		(*i)++;
// 		(*tmp)[(*k)++] = '\"';
// 		while (ft_isalnum(line[*i]) || line[*i] == '_')
// 			(*tmp)[(*k)++] = line[(*i)++];
// 		(*tmp)[(*k)++] = '\"';
// 	}
// }

// int	count_dollars(char *line, int *i, int j)
// {
// 	int	begin;
// 	int	dollars;

// 	if (i)
// 		begin = *i;
// 	else
// 		begin = j;
// 	dollars = 0;
// 	while (line[begin])
// 	{
// 		if (line[begin] == '$')
// 			dollars++;
// 		begin++;
// 	}
// 	return (begin);
// }