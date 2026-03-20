#ifndef FT_LS_H
# define FT_LS_H

# include <stdlib.h>
# include <unistd.h>
# include <dirent.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <string.h>
# include <errno.h>

typedef struct s_options
{
	int		flag_l;
	int		flag_upper_r;
	int		flag_a;
	int		flag_r;
	int		flag_t;
}	t_options;

typedef struct s_args
{
	char	**paths;
	int		count;
}	t_args;

typedef struct s_entry
{
	char		*name;
	char		*path;
	struct stat	stat;
}	t_entry;

/* ---- parse_args.c ---- */
int		parse_args(int ac, char **av, t_options *opts, t_args *args);

/* ---- args_list.c ---- */
int		args_init(t_args *args, int argc);
void	args_add(t_args *args, char *path);
void	args_free(t_args *args);

/* ---- execute.c ---- */
int		execute(t_options *opts, t_args *args);

/* ---- utils.c ---- */
void	output_str_fd(const char *s, int fd);
void	output_char_fd(char c, int fd);
size_t	ft_strlen(const char *s);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strdup(const char *s);
char	*path_join(const char *dir, const char *name);

/* ---- error.c ---- */
void	print_usage_error(char invalid_flag);
void	print_errno_error(const char *path);

#endif