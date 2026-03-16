#include "ft_ls.h"

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

void	output_char_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	output_str_fd(const char *s, int fd)
{
	if (s)
		write(fd, s, ft_strlen(s));
}

char	*ft_strdup(const char *s)
{
	size_t	len;
	char	*dup;
	size_t	i;

	len = ft_strlen(s);
	dup = malloc(len + 1);
	if (!dup)
		return (NULL);
	i = 0;
	while (i <= len)
	{
		dup[i] = s[i];
		i++;
	}
	return (dup);
}

char	*path_join(const char *dir, const char *name)
{
	size_t	dlen;
	size_t	nlen;
	int		need_slash;
	char	*result;
	size_t	i;
	size_t	j;

	dlen = ft_strlen(dir);
	nlen = ft_strlen(name);
	need_slash = (dlen > 0 && dir[dlen - 1] != '/');
	result = malloc(dlen + need_slash + nlen + 1);
	if (!result)
		return (NULL);
	i = 0;
	while (i < dlen)
	{
		result[i] = dir[i];
		i++;
	}
	if (need_slash)
		result[i++] = '/';
	j = 0;
	while (j <= nlen)
	{
		result[i + j] = name[j];
		j++;
	}
	return (result);
}