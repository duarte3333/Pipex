#include "../pipex.h"

//Esta funcao aloca memoria para n bytes com o malloc
//e depois coloca zeros em todos os bytes que alocou
void	*ft_calloc(size_t nelem, size_t elsize)
{
	char	*arr;
	size_t	i;

	i = -1;
	arr = malloc(elsize * nelem);
	if (!arr)
		return (NULL);
	if (nelem != 0)
	{
		while (++i < nelem)
			arr[i] = 0;
		return ((void *)arr);
	}
	return ((void *)arr);
}

//Esta funcao recebe duas strings e faz a concatenação de ambas
//ou seja, junta-as
char	*ft_strjoinn(char *s1, char const *s2)
{
	int		size_concat;
	char	*concat;
	int		i;
	int		j;

	i = -1;
	j = -1;
	size_concat = ft_strlen(s1) + ft_strlen(s2);
	concat = (char *)ft_calloc((size_concat + 1), sizeof(char));
	while (s1[++i])
		concat[i] = s1[i];
	while (s2[++j])
		concat[i + j] = s2[j];
	// if (s1)
	// 	free(s1);
	return (concat);
}