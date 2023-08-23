#include "exec.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	if (strlen(src) + 1 < dstsize)
		memmove(dst, src, strlen(src) + 1);
	else if (dstsize != 0)
	{
		memmove(dst, src, dstsize - 1);
		dst[dstsize - 1] = '\0';
	}
	return (strlen(src));
}

static int	count_words(char *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i] && s[i] == c)
		i++;
	while (s[i])
	{
		while (s[i] && s[i] != c)
			i++;
		count++;
		while (s[i] && s[i] == c)
			i++;
	}
	return (count);
}

static char	**free_allocation(char **arr, int k)
{
	while (k >= 0)
	{
		free(arr[k]);
		k--;
	}
	free(arr);
	return (NULL);
}

static char	**ft_allocate(char *s, char c, char **arr, int words)
{
	int	i;
	int	len;
	int	k;

	len = 0;
	k = 0;
	if (!s || !arr)
		return (NULL);
	while (s[len] && k < words)
	{
		while (s[len] && s[len] == c)
			len++;
		i = len;
		while (s[i] && s[i] != c)
			i++;
		arr[k] = malloc((i - len + 1) * sizeof(char));
		if (!arr[k])
			return (free_allocation(arr, k));
		ft_strlcpy(*(arr + k), s + len, i - len + 1);
		len = i;
		k++;
	}
	arr[words] = 0;
	return (arr);
}

char	**ft_split(char *s, char c)
{
	char	**arr;
	int		words;

	if (!s)
		return (NULL);
	words = count_words(s, c);
	arr = malloc((words + 1) * sizeof(char *));
	if (!arr)
		return (NULL);
	arr = ft_allocate(s, c, arr, words);
	if (!arr)
		return (NULL);
	arr[words] = 0;
	return (arr);
}