#include "ft_ls.h"

/*
** Initialise the args list. at most argc-1 paths can exist, meaning
** plus 1 for the default ".".
** Returns 0 on success, -1 on malloc failure.
*/
int	args_init(t_args *args, int argc)
{
	args->paths = malloc(sizeof(char *) * (argc > 1 ? argc : 2));
	if (!args->paths)
		return (-1);
	args->count = 0;
	return (0);
}

void	args_add(t_args *args, char *path)
{
	args->paths[args->count] = path;
	args->count++;
}

/*
** Free the paths array.  The strings themselves belong to argv,
** so we only free the pointer array.
*/
void	args_free(t_args *args)
{
	free(args->paths);
	args->paths = NULL;
	args->count = 0;
}