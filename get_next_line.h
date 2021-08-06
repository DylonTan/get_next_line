#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

#include <stdlib.h>
#include <unistd.h>

size_t	ft_strlen(const char *str);

char	*ft_strjoin(char *s1, char *s2);

void	ft_strdel(char **ptr);

char	*ft_strchr(const char *s, int c);

char	*ft_strnew(size_t size);

char	*get_next_line(int fd);

#endif
