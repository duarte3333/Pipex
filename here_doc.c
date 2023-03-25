/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsa-mora <dsa-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 10:58:47 by dsa-mora          #+#    #+#             */
/*   Updated: 2023/03/25 11:32:55 by dsa-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	while (s1 && s2 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

int	ft_main_here_doc(char **av)
{
	char	*in;
	int		fd_in;

	fd_in = open(".temp", O_WRONLY | O_CREAT, 0644);
	if (fd_in == -1)
	{
		perror("");
		exit(0);
	}
	write(0, ">", 1);
	in = get_next_line(0);
	while (1)
	{
		if ((ft_strncmp(in, av[2], ft_strlen(av[2])) == 0) && \
			(ft_strlen(in) - 1 == ft_strlen(av[2])))
			break ;
		write(0, ">", 1);
		write(fd_in, in, ft_strlen(in));
		free(in);
		in = get_next_line(0);
	}
	free(in);
	close (fd_in);
	fd_in = open(".temp", O_RDONLY | O_CREAT, 0644);
	return (fd_in);
}

void	ft_fd_here_doc(int ac, char **av)
{
	(data())->fd_in = ft_main_here_doc(av);
	(data())->fd_out = open(av[ac - 1], O_WRONLY \
		|O_APPEND | O_CREAT, 0644);
	if (data()->fd_out == -1)
	{
		perror("");
		exit(0);
	}
	data()->flag = 6;
}
