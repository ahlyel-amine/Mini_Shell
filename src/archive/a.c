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