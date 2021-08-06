#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	size_t	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	i;
	size_t	j;
	char	*str;

	i = 0;
	j = 0;
	str = (char *) malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str)
		return (NULL);
	while (s1[i])
	{
		str[i + j] = s1[i];
		i++;
	}
	while (s2[j])
	{
		str[i + j] = s2[j];
		j++;
	}
	str[i + j] = '\0';
	return (str);
}

void	ft_strdel(char **ptr)
{
	if (ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
}

char	*ft_strchr(const char *s, int c)
{
	size_t	offset;
	size_t	len;

	offset = 0;
	len = ft_strlen(s);
	while (offset <= len)
	{
		if (s[offset] == c)
			return ((char *)(s + offset));
		offset++;
	}
	return (NULL);
}

char	*ft_strnew(size_t size)
{
	size_t	offset;
	char	*str;

	offset = 0;
	str = (char *) malloc(sizeof(char) * (size + 1));
	if (!str)
		return (NULL);
	while (offset < size + 1)
	{
		*(char *)(str + offset) = 0;
		offset++;
	}
	return (str);
}
