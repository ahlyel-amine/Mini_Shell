#ifndef EXECUTE_H
# define EXECUTE_H

# include "minishell.h"

char		*arguments_to_str(t_arguments *args);
void		execute_line(t_cmd *cmd);
int			pipe_executer(t_cmd *cmd, int infile, int outfile);
int			pipe_part_executer(t_cmd *cmd, int infile, int outfile);
int			or_executer(t_cmd *cmd, int infile, int outfile);
int			or_part_executer(t_cmd *cmd, int infile, int outfile);
char		*get_path(char *cmd);
int			cmd_executer(t_cmd *cmd, int infile, int outfile);
int			and_executer(t_cmd *cmd, int infile, int outfile);
int			and_part_executer(t_cmd *cmd, int infile, int outfile);
int			redirect_executer(t_cmd *cmd, int infile, int outfile);
int			builtin_executer(t_cmd *cmd, int infile, int outfile);
size_t		ft_double_strlen(char **str);
char		**ft_joindstrs(char **ds1, char* *ds2);

#endif