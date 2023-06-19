#ifndef PARSING_H
# define PARSING_H

# include "minishell.h"

char    *skip_q_hrdc_delim(char *line, char *end_line, int *q);
int     read_heredocs(char *delimiter, int q);
char    *get_filename(char *line, char *endline);

#endif