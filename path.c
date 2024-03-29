/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsa-mora <dsa-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 09:54:15 by dsa-mora          #+#    #+#             */
/*   Updated: 2023/03/22 17:22:35 by dsa-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	if (n == 0)
		return (0);
	while ((n - 1) && (*s1 == *s2))
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
	if (paths)
	{
		while (paths[++i])
			free(paths[i]);
	}
	free(paths);
	exit(0);
}

char	*ft_empty_str(char **str)
{
	ft_free_first_command(str);
	return (NULL);
}

char	*ft_check_path(char *cmd, char **paths)
{
	int		i;
	char	**first_command;
	char	*path_command;
	char	*temp;

	first_command = ft_split(cmd, ' ');
	ft_free_rest(first_command);
	if (!first_command[0] || !first_command)
		return (ft_empty_str(first_command));
	i = -1;
	while (paths[++i])
	{
		temp = ft_strjoinn(paths[i], "/");
		path_command = ft_strjoinn(temp, first_command[0]);
		if (!access(path_command, X_OK))
		{
			free(temp);
			ft_free_first_command(first_command);
			return (path_command);
		}
		free(path_command);
		free(temp);
	}
	ft_free_first_command(first_command);
	return (NULL);
}
