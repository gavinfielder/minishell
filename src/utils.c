/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfielder <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 19:46:16 by gfielder          #+#    #+#             */
/*   Updated: 2019/05/01 01:21:53 by gfielder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <dirent.h>
#include "libftprintf.h"
#include "sh.h"

int		is_dir(char *str)
{
	DIR	*dir;

	if ((dir = opendir(str)) == NULL)
		return (0);
	if (dir != NULL)
		closedir(dir);
	return (1);
}

int		display_permission_denied(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	(void)envp;
	ft_dprintf(2, "%s: permission denied\n", argv[0]);
	return (log_ret(-1));
}
