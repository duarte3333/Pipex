#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <limits.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <fcntl.h>

typedef struct s_list
{
	char 			*file;
	char 			*cmd;
	int 			fd;
	char			*path;
	struct s_list	*next;
}				t_list;

//Checker and parsing
int		ft_atoi(const char *nptr);
int		ft_isdigit(int i);
size_t	ft_strlen(const char *str);
char	**ft_split(char const *str, char charset);
char	*ft_strjoinn(char *s1, char const *s2);


//Lists auxiliary functions
t_list	*ft_lstnew(char *file, char *cmd, int fd, char *path);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
char	*ft_get_cmd(int index, t_list *lst);
int		ft_get_index(char *cmd, t_list *lst);
int		ft_lstsize(t_list *lst);

//Path
int	ft_strncmp(const char *s1, const char *s2, size_t n);
char **ft_get_path(char **env);
char *ft_check_path(char *cmd, char **paths);

#endif