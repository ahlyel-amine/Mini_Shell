#include "../../lib/libft/include/libft.h"
#include <unistd.h>


// static int	word_count(char *s, char c);

// char	**ft_split_char(char const *s, char c)
// {
// 	char	**splited;
// 	int		wc;
// 	int		i;
// 	int		tmp_count;

// 	if (!s)
// 		return (NULL);
// 	i = 0;
// 	wc = word_count((char *)s, c);
// 	splited = malloc((wc + 1) * sizeof(char *));
// 	while (i < wc)
// 	{
// 		tmp_count = 0;
// 		while (*s == c)
// 			s++;
// 		while (*(s + tmp_count) != c && *(s + tmp_count))
// 			tmp_count++;
// 		if (!tmp_count)
// 			break ;
// 		splited[i] = ft_substr(s, 0, tmp_count);
// 		s += tmp_count;
// 		i++;
// 	}
// 	splited[i] = NULL;
// 	return (splited);
// }

// static int	word_count(char *s, char c)
// {
// 	int	i;

// 	i = 0;
// 	while (*(s++))
// 		if (*(s - 1) != c && (*s == c || !*s))
// 			i++;
// 	return (i);
// }
// char	*env_path(char **envp)
// {
// 	int	i;

// 	i = 0;
// 	while (envp[i])
// 	{
// 		if (ft_strnstr(envp[i], "PATH=", 5))
// 			return (ft_substr(envp[i], 5,
// 						ft_strlen(envp[i] + 5)));
// 		i++;
// 	}
// 	return (NULL);
// }

// int main(void)
// {
//     pid_t p = fork();
// 	char **a;
// 	a = malloc(sizeof (char *) * 2);
// 	a[0] = malloc(3);
// 	a[0][0] = 'l';
// 	a[0][1] = 's';
// 	a[0][2] = 0;
// 	a[1] = NULL;
//     if ( p == -1 ) {
//         perror("fork failed");
//         return EXIT_FAILURE;
//     }
//     else if ( p == 0 ) {
//         execve("/bin/ls", a, NULL);
//         return EXIT_FAILURE;
//     }

//     int status;
//     if ( waitpid(p, &status, 0) == -1 ) {
//         perror("waitpid failed");
//         return EXIT_FAILURE;
//     }

//     if ( WIFEXITED(status) ) {
//         const int es = WEXITSTATUS(status);
//         printf("exit status was %d\n", status);
//     }
//     return EXIT_SUCCESS;
// }
int compare_matches(char *realfile, char *myfile);

int skip_unkown(char *realfile, char *myfile)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
    while (realfile[i] == '*')
        i++;
    while (realfile[i] && myfile[j] && myfile[j] != realfile[i])
        j++;
    if (myfile[j] == realfile[i])
       return compare_matches(realfile + i, myfile + j);
    else if (!realfile[i] && !myfile[j])
        return (1);
    else
        return (0);
}

int compare_matches(char *realfile, char *myfile)
{
	int	i;
	int	j;
	i = 0;
	j = 0;
    while (realfile[i] && myfile[j] && realfile[i] == myfile[j])
    {
        i++;
        j++;
    }
    if (realfile[i] == '*')
        return skip_unkown(realfile + i, myfile + j);
    else if (!realfile[i] && !myfile[j])
        return (1);
    else
        return (0);
}

int main (int ac, char **av)
{
    if (ac == 3)
        printf("%d\n", compare_matches(av[1], av[2]));
}

t_arguments	*skip_spaces_back(t_arguments *args)
{
	t_arguments	*head;
	int	i;
	int	j;
	char	*tmp;

	tmp = NULL;
	head = args;
	i = 0;
	while (head->next)
		head = head->next;
	while (head->str[i])
	{
		j = 0;
		while (!head->str[i + j] || ft_isspace(head->str[i + j]))
		{
			if (!head->str[i + j])
				tmp = ft_substr(head->str, 0, i);
			j++;
		}
		i += ++j;
	}
	if (tmp)
	{
		free(head->str);
		head->str = tmp;
	}
	return (args);
}


// void	get_dollars(t_arguments	**arguments, char *line, int *i, int *j)
// {
// 	int	k;

// 	k = 1;
// 	*i += *j;
// 	*j = 0;
// 	if (ft_isdigit(line[*i + 1]))
// 		*i += 2;
// 	// else if (line[*i] == '$'  && line[*i + k] == '\"')
// 	// 	(*i)++;
// 	else if (line[*i] == '$'  && !(ft_isalnum(line[*i + k]) || line[*i + k] == '_'))
// 		(*j)++;
// 	else if (line[*i] == '$' && line[*i + 1] == '$')
// 		(*j)++;
// 	else if (line[*i] == '$' && (ft_isalnum(line[*i + k]) || line[*i + k] == '_'))
// 	{
// 		while (ft_isalnum(line[*i + k]) || line[*i + k] == '_')
// 			k++;
// 		*arguments = arguments_constructor(*arguments, ft_substr(line, *i, k), IS_VARIABLE);
// 		*i += k;
// 	}
// }

// t_arguments	*get_arguments(char *line, int *i, int is_word)
// {
// 	t_arguments	*arguments;
// 	t_var		var;
// 	int			j;

// 	ft_memset(&var, 0, sizeof(t_var));
// 	arguments = NULL;
// 	j = 0;
// 	while (line[*i + j])
// 	{
// 		check_out_of_quotes(line[*i + j], &var);
// 		if ((var.dquote && line[*i + j] == '\"') || (var.quote && line[*i + j] == '\''))
// 		{
// 			if (j)
// 				arguments = arguments_constructor(arguments, ft_substr(line, *i, j), IS_STR );
// 			*i += j + 1;
// 			j = 0;
// 			continue ;
// 		}
// 		if (!var.quote && !var.dquote && ft_isspace(line[*i + j]))
// 		{
// 			if (is_word)
// 				break;
// 			if (j)
// 				arguments = arguments_constructor(arguments, ft_substr(line, *i, j), IS_STR);
// 			*i += j + 1;
// 			j = 0;
// 			continue ;
// 		}
// 		else if ((line[*i + j] == '\"' && var.quote) || (line[*i + j] == '\'' && var.dquote))
// 			j++;
// 		else if (!var.dquote && !var.quote && (line[*i + j] == '\'' || line[*i + j] == '\"'))
// 		{
// 			if (j)
// 				arguments = arguments_constructor(arguments, ft_substr(line, *i, j), IS_STR | DONT_EXPAND_WILD_CARDS);
// 			*i += j + 1;
// 			j = 0;
// 			continue ;
// 		}
// 		else if (line[*i + j] == '$' && (var.dquote || (!var.dquote && !var.quote)))
// 		{
// 			if (j)
// 				arguments = arguments_constructor(arguments, ft_substr(line, *i, j), IS_STR);
// 			get_dollars(&arguments, line, i, &j);
// 			continue ;
// 		}
// 		else if (line[*i + j] && line[*i + j] != '\'' && line[*i + j] != '\"')
// 			j++;
// 	}
// 	if (j)
// 	{
// 		arguments = arguments_constructor(arguments, ft_substr(line, *i, j), IS_STR);
// 		*i += j;
// 	}
	
// 	return (arguments);
// }




// t_arguments	*split_merged(t_arguments *arguments)
// {
// 	char	**str;
// 	int		len;
// 	int		i;
// 	t_arguments	*head;
// 	t_arguments	*new = NULL;
// 	t_arguments	*tmp;

// 	i = 0;
// 	head = arguments;
// 	if (head->type == 1)
// 	{
// 		str = ft_split(head->str, ' ');
// 		len = ft_double_strlen(str);
// 		tmp = head->next;
// 		free(head->str);
// 		free (head);
// 		while (i < len)
// 				new = arguments_constructor(new, str[i++], IS_STR | MERGED);
// 		free (str);
// 		head = new;
// 		while (new->next)
// 			new = new->next;
// 		new->next = tmp;
// 		arguments = head;
// 	}
// 	while (head->next)
// 	{
// 		new = NULL;
// 		i = 0;
// 		if (head->next->type == 1)
// 		{

// 			str = ft_split(head->next->str, ' ');
// 			len = ft_double_strlen(str);
// 			if (len == 1)
// 			{
// 				free (str[i]);
// 				free (str);
// 				head = head->next;
// 				continue ;
// 			}
// 			while (i < len)
// 				new = arguments_constructor(new, str[i++], IS_STR | MERGED);
// 			free (str);
// 			tmp = (head->next)->next;
// 			free(head->next->str);
// 			free (head->next);
// 			head->next = new;
// 			while (new->next)
// 				new = new->next;
// 			new->next = tmp;
// 		}
// 		head = head->next;
// 	}
// 	return (arguments);
// }

// t_arguments	*merge_arguments(t_arguments *arguments)
// {
// 	t_arguments	*head;
// 	t_arguments	*tmp;

// 	if (!arguments)
// 		return (NULL);
// 	head = arguments;
// 	while (head->next)
// 	{
// 		if (head->type == head->next->type && head->type != 0)
// 		{
// 			tmp = head->next;
// 			head->str = ft_strjoin_free(head->str, ft_strdup(" "));
// 			head->str = ft_strjoin_free(head->str, (head->next)->str);
// 			head->next = (head->next)->next;
// 			free (tmp);
// 		}
// 		else
// 			head = head->next;
// 	}
// 	return (split_merged(arguments));
// }


// t_arguments *tokenize_variables(t_arguments *arguments, int type)
// {
// 	int		i;
// 	int		j;
// 	int		is_var;
// 	char	*tmp;
	
// 	i = 0;
// 	j = 0;
// 	is_var = 0;
// 	if (!arguments || !arguments->str)
// 		return (NULL);
// 	tmp = arguments->str;
// 	while (tmp[i + j] && !(type & QUOTE))
// 	{
// 		if (tmp[i + j] == '$' && !ft_isdigit(tmp[i + j + 1]) && ft_isvariable(tmp[i + j + 1]))
// 		{
// 			is_var++;
// 			if (is_var == 1)
// 			{
// 				free(arguments);
// 				arguments = NULL;
// 			}
// 			if (j)
// 				arguments = arguments_constructor(arguments, ft_substr(tmp, i, j), IS_STR);
// 			i += j + 1;
// 			j = 0;
// 			while (ft_isvariable(tmp[i + j]))
// 				j++;
// 			arguments = arguments_constructor(arguments, ft_substr(tmp, i, j), IS_VARIABLE);
// 			i += j;
// 			j = -1;
// 		}
// 		else if (tmp[i + j] == '$' && ft_isdigit(tmp[i + j + 1]))
// 		{
// 			is_var++;
// 			if (is_var == 1)
// 			{
// 				free(arguments);
// 				arguments = NULL;
// 			}
// 			if (j)
// 				arguments = arguments_constructor(arguments, ft_substr(tmp, i, j), IS_STR);
// 			i += j + 2;
// 			j = -1;
// 		}
// 		j++;
// 	}
// 	if (j && is_var)
// 		arguments = arguments_constructor(arguments, ft_substr(tmp, i, j), IS_STR);
// 	if (is_var)
// 		free(tmp);

// 	return (arguments);
// }

// char	*skip_quotes(char *line, int *i, int j, int is_word)
// {
// 	char		*tmp;
// 	int			a;
// 	t_arguments	*arguments;

// 	a = count_dollars(line, i, j);
// 	if (is_word)
// 		tmp = ft_calloc(1, ft_strlen(line + *i) + a + 1);
// 	else
// 		tmp = ft_calloc(1, ft_strlen(line + j) + a + 1);
// 	if (!tmp)
// 		return (NULL);
// 	if (is_word)
// 		*i = delete_quotes(line, &tmp, *i, is_word);
// 	else
// 		delete_quotes(line, &tmp, j, is_word);
// 	return (tmp);
// }


// int	delete_quotes(char *line, char **tmp, int i, int is_word)
// {
// 	t_var	var;
// 	int		k;

// 	k = 0;
// 	ft_memset(&var, 0, sizeof(t_var));
// 	while (line[i])
// 	{
// 		check_out_of_quotes(line[i], &var);
// 		if (!var.quote && !var.dquote && ft_isspace(line[i]))
// 		{
// 			if (is_word)
// 				break ;
// 			(*tmp)[k++] = line[i];
// 		}
// 		else if ((line[i] == '\"' && var.quote) || (line[i] == '\'' && var.dquote))
// 			(*tmp)[k++] = line[i];
// 		else if (line[i] == '$' && (var.dquote || (!var.dquote && !var.quote)))
// 		{
// 			transform_dollar(line, &i, &k, tmp);
// 			continue ;
// 		}
// 		else if (line[i] != '\'' && line[i] != '\"')
// 			(*tmp)[k++] = line[i];
// 		i++;
// 	}
// 	return (i);
// }

// char	**arguments_list_to_dstr(t_arguments *args)
// {
// 	t_arguments	*tmp;
// 	char		**dstr;
// 	int			len;

// 	len = 0;
// 	tmp = args;
// 	while (tmp)
// 	{
// 		len++;
// 		tmp = tmp->next;
// 	}
// 	dstr = malloc(sizeof(char *) * (len + 1));
// 	if (!dstr)
// 		return (NULL);
// 	len = 0;
// 	while (args)
// 	{
// 		dstr[len++] = args->str;
// 		args = args->next;
// 	}
// 	dstr[len] = NULL;
// 	return (dstr);
// }

// char	**str_to_double(char *str)
// {
// 	char	**dstr;

// 	dstr = malloc(sizeof(char *) * 2);
// 	if (!dstr)
// 		return (NULL);
// 	dstr[0] = str;
// 	dstr[1] = NULL;
// 	return (dstr);
// }

// void	remove_arg(t_arguments **arguments, t_arguments **to_remove)
// {
// 	t_arguments	*tmp;
// 	t_arguments	*rem;

// 	tmp = *arguments;
// 	while (tmp)
// 	{
// 		if (!tmp->next && tmp == *to_remove)
// 		{
// 			tmp = NULL;
// 			break ;
// 		}
// 		else if (tmp->next == *to_remove)
// 		{
// 			tmp = tmp->next->next;
// 			break ;
// 		}
// 	}
// 	free ((*to_remove)->str);
// 	free (*to_remove);
// 	*to_remove = tmp;
// }


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

void	print_cmd(t_cmd *cmd)
{
	t_execcmd	*cmds;

	cmds = (t_execcmd *)cmd;
	printf("---------cmd----------\n");
	if (!cmds)
		return ;
	if (cmds->cmd)
		print_arguments(cmds->cmd, "cmd");
	printf("--------------------------\n");
	printf("---------options----------\n");
	if (cmds->options)
		print_arguments(cmds->options, "option");
	printf("--------------------------\n");
}