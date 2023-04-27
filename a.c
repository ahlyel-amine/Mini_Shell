#include "lib/libft/include/libft.h"
#include <unistd.h>

char	*env_path(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strnstr(envp[i], "PATH=", 5))
			return (ft_substr(envp[i], 5,
						ft_strlen(envp[i] + 5)));
		i++;
	}
	return (NULL);
}

int main(int argc, char  *argv[], char **envp)
{
	char **paths = ft_split_garbg(env_path(envp), ':');
	int	i = 0;
	while (paths[i])
	{
		paths[i] = ft_strjoin(paths[i], "/");
		paths[i] = ft_strjoin(paths[i], "echo");
		int a = access(paths[i], F_OK | X_OK);
		if (!a)
			break ;
		i++;
	}
	execve(paths[i], argv, envp);
	return 0;
}
