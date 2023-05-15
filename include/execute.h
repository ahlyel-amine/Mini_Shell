#ifndef EXECUTE_H
# define EXECUTE_H

# include "minishell.h"

char		*arguments_to_str(t_arguments *args);
void		execute_line(t_cmd *cmd);
int			pipe_executer(t_cmd *cmd, int infile, int outfile, int is_pipe);
int			pipe_part_executer(t_cmd *cmd, int infile, int outfile, int is_pipe);
int			or_executer(t_cmd *cmd, int infile, int outfile, int is_pipe);
int			or_part_executer(t_cmd *cmd, int infile, int outfile, int is_pipe);
char		*get_path(char *cmd);
int			cmd_executer(t_cmd *cmd, int infile, int outfile, int is_pipe);
int			and_executer(t_cmd *cmd, int infile, int outfile, int is_pipe);
int			and_part_executer(t_cmd *cmd, int infile, int outfile, int is_pipe);
int			redirect_executer(t_cmd *cmd, int infile, int outfile, int is_pipe);
int			builtin_executer(t_cmd *cmd, int infile, int outfile, int is_pipe);
size_t		ft_double_strlen(char **str);
char		**ft_joindstrs(char **ds1, char* *ds2);

#endif