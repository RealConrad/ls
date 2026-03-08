#ifndef FT_LS_H
# define FT_LS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <dirent.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <pwd.h>
# include <grp.h>
# include <time.h>
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

/* ---- parse_args.c ---- */
int		parse_args(int argc, char **argv, t_options *opts, t_args *args);

/* ---- args_list.c ---- */
int		args_init(t_args *args, int argc);
void	args_add(t_args *args, char *path);
void	args_free(t_args *args);

/* ---- utils.c ---- */
void	ft_putstr_fd(const char *s, int fd);
void	ft_putchar_fd(char c, int fd);
size_t	ft_strlen(const char *s);

/* ---- error.c ---- */
void	print_usage_error(char invalid_flag);
void	print_errno_error(const char *path);

#endif