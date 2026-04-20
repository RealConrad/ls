#include "ft_ls.h"

static void	list_dir(const char *path, t_options *opts, int print_header);

static int	cmp_entries(t_entry *a, t_entry *b, t_options *opts)
{
	int	result;

	if (opts->flag_t)
	{
		if (a->stat.st_mtime > b->stat.st_mtime)
			result = -1;
		else if (a->stat.st_mtime < b->stat.st_mtime)
			result = 1;
		else
			result = ft_strcmp(a->name, b->name);
	}
	else
		result = ft_strcmp(a->name, b->name);
	if (opts->flag_r)
		return (-result);
	return (result);
}

static void	sort_entries(t_entry *entries, int count, t_options *opts)
{
	int		i;
	int		swapped;
	t_entry	tmp;

	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		i = 0;
		while (i < count - 1)
		{
			if (cmp_entries(&entries[i], &entries[i + 1], opts) > 0)
			{
				tmp = entries[i];
				entries[i] = entries[i + 1];
				entries[i + 1] = tmp;
				swapped = 1;
			}
			i++;
		}
	}
}

static int	count_entries(const char *path, t_options *opts)
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
		if (ent->d_name[0] != '.' || opts->flag_a)
			count++;
		ent = readdir(dir);
	}
	closedir(dir);
	return (count);
}

static int	read_dir(const char *path, t_options *opts, t_entry **out)
{
	DIR				*dir;
	struct dirent	*ent;
	t_entry			*entries;
	int				count;
	int				i;

	count = count_entries(path, opts);
	if (count == -1)
	{
		print_errno_error(path);
		return (-1);
	}
	entries = malloc(sizeof(t_entry) * (count + 1));
	if (!entries)
		return (-1);
	dir = opendir(path);
	if (!dir)
	{
		free(entries);
		return (-1);
	}
	i = 0;
	ent = readdir(dir);
	while (ent)
	{
		if (ent->d_name[0] != '.' || opts->flag_a)
		{
			entries[i].name = ft_strdup(ent->d_name);
			entries[i].path = path_join(path, ent->d_name);
			lstat(entries[i].path, &entries[i].stat);
			i++;
		}
		ent = readdir(dir);
	}
	closedir(dir);
	*out = entries;
	return (i);
}

static void	free_entries(t_entry *entries, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		free(entries[i].name);
		free(entries[i].path);
		i++;
	}
	free(entries);
}

static void	recurse_dirs(t_entry *entries, int count, t_options *opts)
{
	int	i;

	i = 0;
	while (i < count)
	{
		if (ft_strcmp(entries[i].name, ".") != 0
			&& ft_strcmp(entries[i].name, "..") != 0
			&& S_ISDIR(entries[i].stat.st_mode))
		{
			output_char_fd('\n', 1);
			list_dir(entries[i].path, opts, 1);
		}
		i++;
	}
}

static void	print_entries(t_entry *entries, int count, t_options *opts)
{
	int	i;

	if (opts->flag_l)
		print_long_format(entries, count);
	else
	{
		i = 0;
		while (i < count)
		{
			output_str_fd(entries[i].name, 1);
			output_char_fd('\n', 1);
			i++;
		}
	}
}

static void	list_dir(const char *path, t_options *opts, int print_header)
{
	t_entry	*entries;
	int		count;

	if (print_header)
	{
		output_str_fd(path, 1);
		output_str_fd(":\n", 1);
	}
	count = read_dir(path, opts, &entries);
	if (count == -1)
		return ;
	sort_entries(entries, count, opts);
	print_entries(entries, count, opts);
	if (opts->flag_upper_r)
		recurse_dirs(entries, count, opts);
	free_entries(entries, count);
}

int	execute(t_options *opts, t_args *args)
{
	t_entry	*entries;
	int		i;
	int		print_header;

	entries = malloc(sizeof(t_entry) * args->count);
	if (!entries)
		return (1);
	i = 0;
	while (i < args->count)
	{
		entries[i].name = ft_strdup(args->paths[i]);
		entries[i].path = ft_strdup(args->paths[i]);
		lstat(args->paths[i], &entries[i].stat);
		i++;
	}
	sort_entries(entries, args->count, opts);
	print_header = (args->count > 1) || opts->flag_upper_r;
	i = 0;
	while (i < args->count)
	{
		if (i > 0)
			output_char_fd('\n', 1);
		list_dir(entries[i].path, opts, print_header);
		i++;
	}
	free_entries(entries, args->count);
	return (0);
}