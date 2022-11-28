#include "../inc/pipex.h"

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*tmp;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (NULL);
	tmp = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!tmp)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i] != '\0')
	{
		tmp[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		tmp[i] = s2[j];
		j++;
		i++;
	}
	tmp[i] = '\0';
	return (tmp);
}
