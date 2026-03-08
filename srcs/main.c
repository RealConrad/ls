#include "ft_ls.h"

static void	init_options(t_options *opts)
{
	opts->flag_l = 0;
	opts->flag_upper_r = 0;
	opts->flag_a = 0;
	opts->flag_r = 0;
	opts->flag_t = 0;
}

static void	debug_print(t_options *opts, t_args *args)
{
	int	i;

	ft_putstr_fd("Flags:  ", 1);
	if (opts->flag_l)
		ft_putstr_fd("-l ", 1);
	if (opts->flag_upper_r)
		ft_putstr_fd("-R ", 1);
	if (opts->flag_a)
		ft_putstr_fd("-a ", 1);
	if (opts->flag_r)
		ft_putstr_fd("-r ", 1);
	if (opts->flag_t)
		ft_putstr_fd("-t ", 1);
	ft_putchar_fd('\n', 1);
	ft_putstr_fd("Paths:\n", 1);
	i = 0;
	while (i < args->count)
	{
		ft_putstr_fd("  ", 1);
		ft_putstr_fd(args->paths[i], 1);
		ft_putchar_fd('\n', 1);
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_options	opts;
	t_args		args;

	init_options(&opts);
	if (args_init(&args, argc) == -1)
	{
		ft_putstr_fd("ft_ls: memory allocation failed\n", 2);
		return (1);
	}
	if (parse_args(argc, argv, &opts, &args) == -1)
	{
		args_free(&args);
		return (2);
	}
	debug_print(&opts, &args);
	args_free(&args);
	return (0);
}
