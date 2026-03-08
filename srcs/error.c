#include "ft_ls.h"

void	print_usage_error(char invalid_flag)
{
	output_str_fd("ft_ls: illegal option -- ", 2);
	output_char_fd(invalid_flag, 2);
	output_char_fd('\n', 2);
	output_str_fd("usage: ft_ls [-lRart] [file ...]\n", 2);
}

void	print_errno_error(const char *path)
{
	output_str_fd("ft_ls: cannot access '", 2);
	output_str_fd(path, 2);
	output_str_fd("': ", 2);
	output_str_fd(strerror(errno), 2);
	output_char_fd('\n', 2);
}
