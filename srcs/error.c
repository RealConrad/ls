#include "ft_ls.h"

void	print_usage_error(char invalid_flag)
{
	ft_putstr_fd("ft_ls: illegal option -- ", 2);
	ft_putchar_fd(invalid_flag, 2);
	ft_putchar_fd('\n', 2);
	ft_putstr_fd("usage: ft_ls [-lRart] [file ...]\n", 2);
}

void	print_errno_error(const char *path)
{
	ft_putstr_fd("ft_ls: cannot access '", 2);
	ft_putstr_fd(path, 2);
	ft_putstr_fd("': ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putchar_fd('\n', 2);
}
