#include "pipex.h"

int	ft_main_here_doc(char **av)
{
	char	*in;
	int		fd_in;

	fd_in = open("temp", O_WRONLY | O_APPEND | O_CREAT, 0644);
	write(0, ">", 1);
	in = get_next_line(0);
	while (ft_strncmp(in, av[2], ft_strlen(av[2])) != 0)
	{
		write(0, ">", 1);
		write(fd_in, in, ft_strlen(in));
		free(in);
		in = get_next_line(0);
	}
	free(in);
	close (fd_in);
	fd_in = open("temp", O_RDONLY | O_APPEND | O_CREAT, 0644);
	return (fd_in);
}