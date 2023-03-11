#include "pipex.h"

void	ft_free_list(t_list **lst)
{
	t_list	*temp;

	while (*lst)
	{
		temp = (*lst)->next;
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
		printf("cmd: %s and file: %s\n", input->cmd, input->file);
		printf("path: %s\n", input->path);
		printf("av: %s\n", input->av[0]);
		input = input->next;
	}
}

t_list	*ft_set_input(char **av, int ac, char **paths)
{
	int 	i;
	int 	fd_in;
	int 	fd_out;
	t_list  *input;

	fd_in = open(av[1], O_RDWR);
	if (fd_in == -1)
		perror(av[1]);
	fd_out = open("out.txt", O_RDWR | O_TRUNC | O_CREAT, 0644);
	if (fd_out == -1)
		perror("");	
	input = ft_lstnew(av[1], av[2], ft_check_path(av[2], paths));
	i = 2;
	while (av[++i] && i < (ac - 1))
	{
		if (i == (ac - 2))
			ft_lstadd_back(&input, ft_lstnew(av[i + 1], av[i], \
				ft_check_path(av[i], paths)));
		else
			ft_lstadd_back(&input, ft_lstnew(NULL, av[i], \
				ft_check_path(av[i], paths)));
	}
	close(fd_in);
	close(fd_out);
	return (input);
}

int main(int ac, char **av, char **env)
{
	int 	pid;
	char **paths;
	t_list *input;

	paths = ft_get_path(env);
	input = ft_set_input(av, ac, paths);
	ft_print_list(input);
	while (input)
	{
		pid = fork();
		if (!input->prev)
			dup2(open(av[1], O_RDWR), 0); //fd[0] passa a ser stdin
		else
			dup2(input->prev->fd[0], 0); //fd[0] passa a ser stdin
		if (!input->next)
			dup2(open("out.txt", O_RDWR | O_TRUNC | O_CREAT, 0644), 1); //fd[0] passa a ser stdin
		else
			dup2(input->fd[1], 1); //fd[1] passa a ser stdout
		if (pid == 0)
			execve(input->path, input->av, env);
		input = input->next;
	}
	printf("oi\n");
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