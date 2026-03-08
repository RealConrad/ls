#include "ft_ls.h"

static int	is_valid_flag(char c)
{
	return (c == 'l' || c == 'R' || c == 'a' || c == 'r' || c == 't');
}

static void	set_flag(t_options *opts, char c)
{
	if (c == 'l')
		opts->flag_l = 1;
	else if (c == 'R')
		opts->flag_upper_r = 1;
	else if (c == 'a')
		opts->flag_a = 1;
	else if (c == 'r')
		opts->flag_r = 1;
	else if (c == 't')
		opts->flag_t = 1;
}

static int	parse_flag_token(const char *token, t_options *opts)
{
	int	i;

	i = 1;
	while (token[i])
	{
		if (!is_valid_flag(token[i]))
		{
			print_usage_error(token[i]);
			return (-1);
		}
		set_flag(opts, token[i]);
		i++;
	}
	return (0);
}

/*
** Rules:
**   1.  "--"  → stop flag parsing; every subsequent arg is a path.
**   2.  "-"   → not a flag group; treat as a literal path argument.
**   3.  "-xyz" where all of x,y,z are valid flags → set them.
**   4.  "-xyz" where some char is invalid → error + exit(2).
**   5.  Anything else (or anything after "--") → path argument.
**   6.  If no path arguments were given, default to ".".
**
** Returns 0 on success, -1 on error (invalid flag).
*/
int	parse_args(int argc, char **argv, t_options *opts, t_args *args)
{
	int	i;
	int	flags_done;

	i = 1;
	flags_done = 0;
	while (i < argc)
	{
		if (!flags_done && argv[i][0] == '-' && argv[i][1] != '\0')
		{
			if (argv[i][1] == '-' && argv[i][2] == '\0')
			{
				flags_done = 1;
				i++;
				continue ;
			}
			if (parse_flag_token(argv[i], opts) == -1)
				return (-1);
		}
		else
			args_add(args, argv[i]);
		i++;
	}
	if (args->count == 0)
		args_add(args, ".");
	return (0);
}
