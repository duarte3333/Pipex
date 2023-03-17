/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsa-mora <dsa-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 10:05:41 by dsa-mora          #+#    #+#             */
/*   Updated: 2023/03/17 18:51:14 by dsa-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_info	*data(void)
{
	static t_info	ola;

	return (&ola);
}

t_list	*ft_set_input(char **av, int ac, char **paths)
{
	int		i;
	t_list	*input;

	input = ft_lstnew(av[2], ft_check_path(av[2], paths));
	i = 2;
	while (av[++i] && i < (ac - 1))
		ft_lstadd_back(&input, ft_lstnew(av[i], ft_check_path(av[i], paths)));
	return (input);
}

void	ft_child(t_list *input, int fd_out, char **env)
{
	if (!input->next)
	{
		dup2(fd_out, 1);
		close(fd_out);
	}
	else
	{
		dup2(input->fd[1], 1);
	}
	close(input->fd[0]);
	close(input->fd[1]);
	if (execve(input->path, input->av, env) == -1)
		perror("Command not found");
	close(data()->fd_in);
	close(0);
	close(1);
	
	//fechar pipes
	ft_free_all(data()->first, data()->paths);
	exit(1);
}

// void	free_and_close(t_list *input)
// {
// 	t_list	*temp;

// 	input = temp;
// 	while (input)
// 	{
// 		wait(NULL);
// 		input = input->next;
// 	}
// 	input = temp;
// 	close(data()->fd_in);
// 	close(data()->fd_out);
// 	if (data()->flag)
// 		unlink(".temp");
// 	ft_free_all(input, data()->paths);
// }

int main(int ac, char **av, char **env)
{
	t_list	*input;

	(data())->fd_in = open(av[1], O_RDWR);
	data()->flag = 0;
	if (data()->fd_in == -1)
	{
		data()->fd_in = open(".temp", O_RDWR | O_CREAT, 0644);
		data()->flag = 6;
		perror(av[1]);
	}
	data()->fd_out = open(av[ac - 1], O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (data()->fd_out == -1)
		perror("");
	data()->paths = ft_get_path(env);
	input = ft_set_input(av, ac, data()->paths);
	data()->first = input;
	while (input)
	{
		if (!input->prev)
			dup2(data()->fd_in, 0);
		else
		{
			dup2(input->prev->fd[0], 0);
			close(input->prev->fd[0]);
		}
		data()->pid = fork();
		if (data()->pid == 0)
			ft_child(input, data()->fd_out, env);
		// if (!input->prev)
			close(0);
		close(input->fd[1]);
		if (!input->next)
			close(input->fd[0]);
		input = input->next;
	}
	input = data()->first;
	while (input)
	{
		waitpid(-1, NULL, 0);
		input = input->next;
	}
	input = data()->first;
	if (data()->flag)
		unlink(".temp");
	close(data()->fd_in);
	close(data()->fd_out);
	ft_free_all(data()->first, data()->paths);
}

// void	ft_print_list(t_list *input)
// {
// 	while (input)
// 	{
// 		printf("cmd: %s\n", input->cmd);
// 		printf("path: %s\n", input->path);
// 		printf("av[0]: %s\n", input->av[0]);
// 		printf("av[1]: %s\n", input->av[1]);
// 		printf("fd in[1] %i and fd out[0] %i\n", input->fd[1], input->fd[0]);
// 		input = input->next;
// 	}
// }