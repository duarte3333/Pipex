/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsa-mora <dsa-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 10:05:41 by dsa-mora          #+#    #+#             */
/*   Updated: 2023/03/18 19:14:11 by dsa-mora         ###   ########.fr       */
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

void	free_and_close_transit(t_list *input)
{	
	input = data()->first;
	close(data()->fd_in);
	close(data()->fd_out);
	ft_free_all(data()->first, data()->paths);
}

void	ft_get_in_out_fd(int ac, char **av)
{
	int		fd[2];

	(data())->fd_in = open(av[1], O_RDWR);
	data()->flag = 0;
	if (data()->fd_in == -1)
	{
		perror(av[1]);
		pipe(fd);
		(data())->fd_in = fd[0];
		close(fd[1]);
	}
	(data())->fd_out = open(av[ac - 1], O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (data()->fd_out == -1)
	{
		perror("");
		exit(av[ac - 1]);
	}
	data()->i = 1;
}

int	main(int ac, char **av, char **env)
{
	t_list	*input;

	if (ac == 5)
	{
		ft_get_in_out_fd(ac, av);
		data()->paths = ft_get_path(env);
		input = ft_set_input(av, ac, data()->paths);
		data()->first = input;
		while (input)
		{
			ft_pre_father(input);
			data()->pid = fork();
			if (data()->pid == 0)
				ft_child(input, av[data()->i], env);
			ft_pos_father(input);
			input = input->next;
		}
		input = data()->first;
		while (input)
		{
			waitpid(-1, NULL, 0);
			input = input->next;
		}
		free_and_close_transit(input);
	}
}
