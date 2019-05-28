/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfielder <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 20:53:49 by gfielder          #+#    #+#             */
/*   Updated: 2019/05/01 00:43:18 by gfielder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/syslimits.h>
#include "libft.h"
#include "sh.h"
#include "libftprintf.h"

static int						bi_cd_errorcheck(int argc, char **argv,
									char **envp)
{
	(void)envp;
	if (argc > 2)
		return (log_ret(-ft_dprintf(2, "usage: cd [path|-]\n")));
	if (access(argv[1], F_OK) < 0)
		return (-ft_dprintf(2, "cd %s: directory does not exist\n", argv[1]));
	if (access(argv[1], R_OK) < 0)
		return (-ft_dprintf(2, "cd %s: permission denied\n", argv[1]));
	if (is_dir(argv[1]) == 0)
		return (-ft_dprintf(2, "cd %s: not a directory\n", argv[1]));
	if (access(argv[1], X_OK) < 0)
		return (-ft_dprintf(2, "cd %s: permission denied\n", argv[1]));
	return (1);
}

int								bi_cd(int argc, char **argv, char **envp)
{
	char	tmp[PATH_MAX + 1];
	int		ret;

	if (argc == 1)
		return (bi_cd(2, (char *[]){NULL, (char *)sh_getenv("HOME")}, NULL));
	if (ft_strequ(argv[1], "-"))
		return (bi_cd(2, (char *[]){NULL, (char *)sh_getenv("OLDPWD")}, NULL));
	if ((ret = bi_cd_errorcheck(argc, argv, envp)) < 0)
		return (ret);
	if (chdir(argv[1]) < 0)
		return (-ft_dprintf(2, "cd %s: Unspecified error occurred\n", argv[1]));
	else
	{
		SETENV("OLDPWD", (char *)sh_getenv("PWD"));
		getcwd(tmp, PATH_MAX);
		SETENV("PWD", tmp);
	}
	return (log_ret(0));
}
