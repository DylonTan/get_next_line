#include "get_next_line_bonus.h"
#include <stdio.h>

static char	*ft_strsub(const char *str, size_t start, size_t len)
{
	size_t	i;
	char	*substr;

	if (!str)
		return (NULL);
	substr = (char *) malloc(sizeof(char) * (len + 1));
	if (!substr)
		return (NULL);
	i = 0;
	while (len)
	{
		substr[i] = str[start];
		start++;
		i++;
		len--;
	}
	substr[i] = '\0';
	return (substr);
}

static char	*ft_strdup(const char *s1)
{
	size_t	i;
	char	*s2;

	i = 0;
	s2 = (char *) malloc(sizeof(char) * (ft_strlen(s1) + 1));
	if (!s2)
		return (NULL);
	while (s1[i])
	{
		s2[i] = s1[i];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}

static char	*get_line(int fd, char **threads)
{
	size_t	offset;
	char	*line;
	char	*temp;

	offset = 0;
	while (threads[fd][offset] != '\n' && threads[fd][offset] != '\0')
		offset++;
	if (threads[fd][offset] == '\n')
	{
		line = ft_strsub(threads[fd], 0, offset + 1);
		temp = ft_strdup(threads[fd] + offset + 1);
		ft_strdel(&threads[fd]);
		if (temp[0] != '\0')
			threads[fd] = temp;
		else
			ft_strdel(&temp);
	}
	else
	{
		line = ft_strdup(threads[fd]);
		ft_strdel(&threads[fd]);
	}
	return (line);
}

int	read_line(int fd, char **buff, int *bytes)
{
	int	b;

	b = read(fd, *buff, BUFFER_SIZE);
	*bytes = b;
	return (b);
}

char	*get_next_line(int fd)
{
	static char	*threads[1024];
	char		*buff;
	char		*temp;
	int			bytes;

	if (fd < 0 || fd >= 1024 || BUFFER_SIZE < 1)
		return (NULL);
	buff = (char *) malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (NULL);
	while (read_line(fd, &buff, &bytes) > 0)
	{
		buff[bytes] = '\0';
		if (!threads[fd])
			threads[fd] = ft_strnew(0);
		temp = ft_strjoin(threads[fd], buff);
		ft_strdel(&threads[fd]);
		threads[fd] = temp;
		if (ft_strchr(buff, '\n'))
			break ;
	}
	ft_strdel(&buff);
	if (bytes < 0 || (bytes == 0 && !threads[fd]))
		return (NULL);
	return (get_line(fd, threads));
}
