/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_token_archive.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbrahm <aelbrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 19:10:04 by aahlyel           #+#    #+#             */
/*   Updated: 2023/06/24 18:32:20 by aelbrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


int	fill_redir_content_herdoc(char *line, int i, t_redir_content *red)
{
	int	quote;
	int	dquote;
	int	k;

	i += 2;
	k = 0;
	quote = 0;
	dquote = 0;
	while (ft_isspace(line[i]))
		i++;
	if (!line[i])
		something_wrong("Asyntax error near unexpected token `newline'", line);
	check_out_of_quotes(line[i], &quote, &dquote);
	if (quote || dquote)
		k++;
	red->fd =i + k;
	while (line[i + k] && ((ft_isalnum(line[i + k]) || line[i + k] == '_') || (quote || dquote)))
		check_out_of_quotes(line[++i + k], &quote, &dquote);
	red->file_name = ft_substr(line, red->fd, i + k);
	red->efile_name  = NULL;
	if (red->file_name == red->efile_name)
		something_wrong("Bsyntax error near unexpected token `newline'", line);
	red->fd = 0;
	red->mode = 0;
	red->type = HEREDOC;
	return (i + k);
}

int	fill_redir_content_inredir(char *line, int i, t_redir_content *red)
{
	int	quote;
	int	dquote;
	int	k;

	i += 1;
	k = 0;
	quote = 0;
	dquote = 0;
	while (ft_isspace(line[i]))
		i++;
	if (!line[i])
		something_wrong("Asyntax error near unexpected token `newline'", line);
	check_out_of_quotes(line[i], &quote, &dquote);
	if (quote || dquote)
		k++;
	red->file_name = ft_strdup(line + i + k);
	while ((!ft_isspace(line[i + k]) && !ft_strchr("|&$<>", line[i + k])) || quote || dquote)
		check_out_of_quotes(line[++i + k], &quote, &dquote);
	red->efile_name = line + i + k;
	if (red->file_name == red->efile_name)
		something_wrong("Bsyntax error near unexpected token `newline'", line);
	red->fd = 0;
	red->mode = O_RDONLY;
	red->type = IN_REDIR;
	return (i + k);
}

int	fill_redir_content_append(char *line, int i, t_redir_content *red)
{
	int	j;

	j = 0;
	line = skip_quotes(line, i + 2);
	while (ft_isspace(line[j]))
		j++;
	if (!line[j])
		something_wrong("Esyntax error near unexpected token `newline'", line);
	red->file_name = ft_strdup(line + j);
	while (!ft_isspace(line[j]) && !ft_strchr("|&$<>", line[j]))
		j++;
	red->efile_name = line + i;
	if (red->file_name == red->efile_name)
		something_wrong("Fsyntax error near unexpected token `newline'", line);
	red->fd = 1;
	red->mode = O_APPEND | O_WRONLY | O_CREAT;
	red->type = APPEND;
	return (free(line), i + j + 2);
}

int	fill_redir_content_outredir(char *line, int i, t_redir_content *red)
{
	int	j;

	j = 0;
	line = skip_quotes(line, i + 1);
	while (ft_isspace(line[j]))
		j++;
	if (!line[j])
		something_wrong("Esyntax error near unexpected token `newline'", line);
	red->file_name = ft_strdup(line + j);
	while (!ft_isspace(line[j]) && !ft_strchr("|&$<>", line[j]))
		j++;
	red->efile_name = line + j;
	if (red->file_name == red->efile_name)
		something_wrong("Esyntax error near unexpected token `newline'", line);
	red->fd = 1;
	red->mode = O_TRUNC | O_WRONLY | O_CREAT;
	red->type = OUT_REDIR;
	return (free(line), i + j + 1);
}