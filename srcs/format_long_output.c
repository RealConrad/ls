#include "ft_ls.h"

static char	file_type_char(mode_t mode)
{
	if (S_ISDIR(mode))
		return ('d');
	if (S_ISLNK(mode))
		return ('l');
	if (S_ISCHR(mode))
		return ('c');
	if (S_ISBLK(mode))
		return ('b');
	if (S_ISFIFO(mode))
		return ('p');
	if (S_ISSOCK(mode))
		return ('s');
	return ('-');
}

static void	print_permissions(mode_t mode)
{
	output_char_fd(file_type_char(mode), 1);
	output_char_fd((mode & S_IRUSR) ? 'r' : '-', 1);
	output_char_fd((mode & S_IWUSR) ? 'w' : '-', 1);
	if (mode & S_ISUID)
		output_char_fd((mode & S_IXUSR) ? 's' : 'S', 1);
	else
		output_char_fd((mode & S_IXUSR) ? 'x' : '-', 1);
	output_char_fd((mode & S_IRGRP) ? 'r' : '-', 1);
	output_char_fd((mode & S_IWGRP) ? 'w' : '-', 1);
	if (mode & S_ISGID)
		output_char_fd((mode & S_IXGRP) ? 's' : 'S', 1);
	else
		output_char_fd((mode & S_IXGRP) ? 'x' : '-', 1);
	output_char_fd((mode & S_IROTH) ? 'r' : '-', 1);
	output_char_fd((mode & S_IWOTH) ? 'w' : '-', 1);
	// if (mode & S_ISVTX)
	// 	output_char_fd((mode & S_IXOTH) ? 't' : 'T', 1);
	// else
	output_char_fd((mode & S_IXOTH) ? 'x' : '-', 1);
}

static void	print_time(time_t mtime)
{
	char	*str;
	time_t	now;

	now = time(NULL);
	str = ctime(&mtime);
	if (!str)
		return ;
	write(1, str + 4, 7);
	if (now - mtime < SIX_MONTHS && mtime - now < SIX_MONTHS)
		write(1, str + 11, 5);
	else
	{
		write(1, " ", 1);
		write(1, str + 20, 4);
	}
}

static void	print_owner_group(t_entry *entry, t_column_data *column_data)
{
	struct passwd	*pw;
	struct group	*gr;

	pw = getpwuid(entry->stat.st_uid);
	if (pw)
		print_str_padded(pw->pw_name, column_data->owner);
	else
		print_num_padded(entry->stat.st_uid, column_data->owner);
	write(1, " ", 1);
	gr = getgrgid(entry->stat.st_gid);
	if (gr)
		print_str_padded(gr->gr_name, column_data->group);
	else
		print_num_padded(entry->stat.st_gid, column_data->group);
}

static void	print_symlink(t_entry *entry)
{
	char	buf[1024];
	int		len;

	if (S_ISLNK(entry->stat.st_mode))
	{
		output_str_fd(" -> ", 1);
		len = readlink(entry->path, buf, sizeof(buf) - 1);
		if (len >= 0)
		{
			buf[len] = '\0';
			output_str_fd(buf, 1);
		}
	}
}

static void	calc_width(t_entry *entries, int count, t_column_data *column_data)
{
	int				i;
	int				val;
	struct passwd	*pw;
	struct group	*gr;

	column_data->links = 0;
	column_data->owner = 0;
	column_data->group = 0;
	column_data->size = 0;
	i = 0;
	while (i < count)
	{
		val = num_len((long)entries[i].stat.st_nlink);
		if (val > column_data->links)
			column_data->links = val;
		pw = getpwuid(entries[i].stat.st_uid);
		if (pw)
			val = (int)ft_strlen(pw->pw_name);
		else
			val = num_len(entries[i].stat.st_uid);
		if (val > column_data->owner)
			column_data->owner = val;
		gr = getgrgid(entries[i].stat.st_gid);
		if (gr)
			val = (int)ft_strlen(gr->gr_name);
		else
			val = num_len(entries[i].stat.st_gid);
		if (val > column_data->group)
			column_data->group = val;
		val = num_len((long)entries[i].stat.st_size);
		if (val > column_data->size)
			column_data->size = val;
		i++;
	}
}

static void	print_total(t_entry *entries, int count)
{
	long	total;
	int		i;

	total = 0;
	i = 0;
	while (i < count)
	{
		total += entries[i].stat.st_blocks;
		i++;
	}
	output_str_fd("total ", 1);
	print_num_padded((total + 1) / 2, 0);
	output_char_fd('\n', 1);
}

static void	print_one_entry(t_entry *entry, t_column_data *column_data)
{
	print_permissions(entry->stat.st_mode);
	write(1, " ", 1);
	print_num_padded((long)entry->stat.st_nlink, column_data->links);
	write(1, " ", 1);
	print_owner_group(entry, column_data);
	write(1, " ", 1);
	print_num_padded((long)entry->stat.st_size, column_data->size);
	write(1, " ", 1);
	print_time(entry->stat.st_mtime);
	write(1, " ", 1);
	output_str_fd(entry->name, 1);
	print_symlink(entry);
	output_char_fd('\n', 1);
}

void	print_long_format(t_entry *entries, int count)
{
	t_column_data	column_data;
	int			i;

	print_total(entries, count);
	calc_width(entries, count, &column_data);
	i = 0;
	while (i < count)
	{
		print_one_entry(&entries[i], &column_data);
		i++;
	}
}
