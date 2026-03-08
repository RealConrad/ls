#include "ft_ls.h"

/*
** Simple insertion sort on an array of strings.
*/
static void	sort_names(char **names, int count)
{
	int		i;
	int		j;
	char	*tmp;

	i = 1;
	while (i < count)
	{
		tmp = names[i];
		j = i - 1;
		while (j >= 0 && ft_strcmp(names[j], tmp) > 0)
		{
			names[j + 1] = names[j];
			j--;
		}
		names[j + 1] = tmp;
		i++;
	}
}

/*
** Count how many visible entries a directory has.
*/
static int	count_entries(const char *path)
{
	DIR				*dir;
	struct dirent	*ent;
	int				count;

	dir = opendir(path);
	if (!dir)
		return (-1);
	count = 0;
	ent = readdir(dir);
	while (ent)
	{
		if (ent->d_name[0] != '.')
			count++;
		ent = readdir(dir);
	}
	closedir(dir);
	return (count);
}

/*
** Read all visible entries from a directory into a name array.
** First pass counts, second pass fills.
** Returns the count, or -1 on error.
*/
static int	read_dir(const char *path, char ***names_out)
{
	DIR				*dir;
	struct dirent	*ent;
	char			**names;
	int				count;
	int				i;

	count = count_entries(path);
	if (count == -1)
	{
		print_errno_error(path);
		return (-1);
	}
	names = malloc(sizeof(char *) * (count + 1));
	if (!names)
		return (-1);
	dir = opendir(path);
	if (!dir)
	{
		free(names);
		return (-1);
	}
	i = 0;
	ent = readdir(dir);
	while (ent)
	{
		if (ent->d_name[0] != '.')
		{
			names[i] = ft_strdup(ent->d_name);
			i++;
		}
		ent = readdir(dir);
	}
	closedir(dir);
	*names_out = names;
	return (i);
}

/*
** Free the names array.
*/
static void	free_names(char **names, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		free(names[i]);
		i++;
	}
	free(names);
}

/*
** List one directory: read, sort, print.
*/
static void	list_dir(const char *path, int print_header)
{
	char	**names;
	int		count;
	int		i;

	if (print_header)
	{
		output_str_fd(path, 1);
		output_str_fd(":\n", 1);
	}
	count = read_dir(path, &names);
	if (count == -1)
		return ;
	sort_names(names, count);
	i = 0;
	while (i < count)
	{
		output_str_fd(names[i], 1);
		output_char_fd(' ', 1);
		i++;
	}
    output_char_fd('\n', 1);
	free_names(names, count);
}

int	execute(t_options *opts, t_args *args)
{
	int	i;
	int	print_header;

	(void)opts;
	sort_names(args->paths, args->count);
	print_header = (args->count > 1);
	i = 0;
	while (i < args->count)
	{
		if (i > 0)
			output_char_fd('\n', 1);
		list_dir(args->paths[i], print_header);
		i++;
	}
	return (0);
}
