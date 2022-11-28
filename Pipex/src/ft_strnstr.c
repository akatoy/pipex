#include "../inc/pipex.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (needle[i] == 0)
		return ((char *)haystack);
	while (haystack[i] != '\0' && len != 0)
	{
		j = 0;
		while (haystack[i + j] == needle[j] && len > (i + j))
		{
			j++;
			if ((size_t)ft_strlen(needle) == j)
				return ((char *)haystack + i);
		}
		i++;
	}
	return (NULL);
}
/*
int main(void)
{
	char haystack[30] = "aaabcabcd";

	char *s = ft_strnstr(haystack, "c", -1);

	printf("%s", s);
}*/
