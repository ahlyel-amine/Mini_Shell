#include "lib/libft/include/libft.h"
#include <unistd.h>


static int	word_count(char *s, char c);

char	**ft_split_char(char const *s, char c)
{
	char	**splited;
	int		wc;
	int		i;
	int		tmp_count;

	if (!s)
		return (NULL);
	i = 0;
	wc = word_count((char *)s, c);
	splited = malloc((wc + 1) * sizeof(char *));
	while (i < wc)
	{
		tmp_count = 0;
		while (*s == c)
			s++;
		while (*(s + tmp_count) != c && *(s + tmp_count))
			tmp_count++;
		if (!tmp_count)
			break ;
		splited[i] = ft_substr(s, 0, tmp_count);
		s += tmp_count;
		i++;
	}
	splited[i] = NULL;
	return (splited);
}

static int	word_count(char *s, char c)
{
	int	i;

	i = 0;
	while (*(s++))
		if (*(s - 1) != c && (*s == c || !*s))
			i++;
	return (i);
}
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
	char **paths = ft_split_char(env_path(envp), ':');
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
