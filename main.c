#include "pipex.h"

void	ft_free_list(t_list **lst)
{
	t_list	*temp;
	int		i;

	while (*lst)
	{
		i = -1;
		temp = (*lst)->next;
		while ((*lst)->av[++i] != NULL)
			free((*lst)->av[i]);
		free((*lst)->av);
		free((*lst)->path);
		free(*lst);
		*lst = temp;
	}
}

void	ft_free_all(t_list *input, char **paths)
{
	int i;

	i = -1;
	while (paths[++i])
		free(paths[i]);
	free(paths);
	ft_free_list(&input);
}

void	ft_print_list(t_list *input)
{
	while (input)	
	{
		printf("cmd: %s\n", input->cmd);
		printf("path: %s\n", input->path);
		printf("av[0]: %s\n", input->av[0]);
		printf("av[1]: %s\n", input->av[1]);
		printf("fd in[1] %i and fd out[0] %i\n", input->fd[1], input->fd[0]);
		// printf("p1: %p p2: %p\n", input, input->next->prev);
		input = input->next;
	}
}

t_list	*ft_set_input(char **av, int ac, char **paths)
{
	int 	i;
	t_list  *input;

	input = ft_lstnew(av[2], ft_check_path(av[2], paths));
	i = 2;
	while (av[++i] && i < (ac - 1))
		ft_lstadd_back(&input, ft_lstnew(av[i], ft_check_path(av[i], paths)));
	return (input);
}

int main(int ac, char **av, char **env)
{
	int 	pid;
	char **paths;
	t_list *input;
	t_list *temp;
	int 	fd_in;
	int 	fd_out;

	fd_in = open(av[1], O_RDWR);
	if (fd_in == -1)
		perror(av[1]);
	fd_out = open(av[ac - 1], O_WRONLY  | O_TRUNC | O_CREAT, 0644);
	if (fd_out == -1)
		perror("");	
	printf("fd_in %i and fd_out %i\n", fd_in, fd_out);
	paths = ft_get_path(env);
	input = ft_set_input(av, ac, paths);
	temp = input;
	ft_print_list(input);
	while (input)
	{
		pid = fork();
		if (pid == 0)
		{
			if (!input->prev)
				dup2(fd_in, 0);
			else
			{
				dup2(input->prev->fd[0], 0);
				close(input->prev->fd[0]);
			}
			if (!input->next)
				dup2(fd_out, 1);
			else
			{
				//printf("eita\n");
				dup2(input->fd[1], 1);
				close(input->fd[1]);
			}
			execve(input->path, input->av, env);
		}
		input = input->next;
	}
	input = temp;
	close(fd_in);
	close(fd_out);
	ft_free_all(input, paths);
}













// int main(int ac, char **av)
// {
// 	int 	fd[2];
// 	int 	pid;
// 	char 	send[4] = "Ola";
// 	char 	received[5];

// 	fd[0] = open("in.txt",  O_RDWR | O_TRUNC | O_CREAT, 0644);
// 	fd[1] = open("out.txt", O_RDWR | O_TRUNC | O_CREAT, 0644);

// 	printf("fd before %i, %i \n", fd[0], fd[1]);
// 	if (pipe(fd) == -1)
// 		printf("Error\n");
// 	printf("fd after pipe() %i, %i \n", fd[0], fd[1]);
// 	pid = fork();
// 	if (pid == -1)
// 		printf("Error\n");
// 	if (pid == 0)
// 	{
// 		close(fd[0]);
// 		write(fd[1], send, 3);
// 		close(fd[1]);
// 		//int error = execlp("ping", "ping", "-c", "2", "google.com", NULL);
// 		if (error == -1)
// 			printf("Could not find a program to execute\n");
// 	}	
// 	else
// 	{
// 		wait(NULL);
// 		close(fd[1]);
// 		read(fd[0], &(received), 3);
// 		close(fd[0]);
// 		printf("I received: %s\n", received);
// 		//printf("Hey\n");

// 	}
// 	//if (pipe(fd) == -1)
// 	//  	return (1);
	
	
// 	return

//Esta funcao compara ate n elementos ou ate a str1 ou a str2 acabar

// void	ft_read_commands(char **paths)
// {
// 	char	*command;

// 	command = get_next_line(0);
// 	while (command)
// 	{
// 		checker_command(paths, command);
// 		free(command);
// 		command = get_next_line(0);
// 	}
// 	free(command);
// }