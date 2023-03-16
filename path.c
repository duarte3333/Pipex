#include "pipex.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	if (n == 0)
		return (0);
	while (*s1 && *s2 && (n - 1) && (*s1 == *s2))
	{
		s1++;
		s2++;
		n--;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

char	**ft_get_path(char **env)
{
	int		i;
	char	**paths;

	i = -1;
	paths = NULL;
	while (env[++i])
	{	
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
		{
			paths = ft_split(env[i] + 5, ':');
			return (paths);
		}
	}
	perror("PATH not found");
	i = -1;
	while (paths[++i])
		free(paths[i]);
	free(paths);
	exit(0);
}

char	*ft_check_path(char *cmd, char **paths)
{
	int		i;
	char	**first_command;
	char	*path_command;
	char	*temp;

	first_command = ft_split(cmd, ' ');

	i = 0;
	while (first_command[++i])
		free(first_command[i]);
	i = 0;
	while (paths[i])
	{
		temp = ft_strjoinn(paths[i], "/");
		path_command = ft_strjoinn(temp, first_command[0]);
		if (!access(path_command, X_OK))
		{
			free(temp);
			free(first_command[0]);
			free(first_command);
			return (path_command);
		}
		free(path_command);
		free(temp);
		i++;
	}
	free(first_command[0]);
	free(first_command);
	return (NULL);
}
