#include "get_next_line.h"

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

static char	*get_line(char **str)
{
	size_t	offset;
	char	*line;
	char	*temp;

	offset = 0;
	while ((*str)[offset] != '\n' && (*str)[offset] != '\0')
		offset++;
	if ((*str)[offset] == '\n')
	{
		line = ft_strsub(*str, 0, offset + 1);
		temp = ft_strdup(*str + offset + 1);
		ft_strdel(str);
		if (temp[0] != '\0')
			*str = temp;
		else
			ft_strdel(&temp);
	}
	else
	{
		line = ft_strdup(*str);
		ft_strdel(str);
	}
	return (line);
}

static int	read_line(int fd, char **buff, int *bytes)
{
	int	b;

	b = read(fd, *buff, BUFFER_SIZE);
	*bytes = b;
	return (b);
}

char	*get_next_line(int fd)
{
	static char	*line;
	char		*buff;
	char		*temp;
	int			bytes;

	if (fd < 0 || fd > 1024 || BUFFER_SIZE < 1)
		return (NULL);
	buff = (char *) malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (NULL);
	while (read_line(fd, &buff, &bytes) > 0)
	{
		buff[bytes] = '\0';
		if (!line)
			line = ft_strnew(0);
		temp = ft_strjoin(line, buff);
		ft_strdel(&line);
		line = temp;
		if (ft_strchr(buff, '\n'))
			break ;
	}
	ft_strdel(&buff);
	if (bytes < 0 || (bytes == 0 && !line))
		return (NULL);
	return (get_line(&line));
}
