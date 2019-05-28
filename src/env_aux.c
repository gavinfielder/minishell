/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_aux.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfielder <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 20:32:35 by gfielder          #+#    #+#             */
/*   Updated: 2019/04/30 23:13:36 by gfielder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "sh.h"
#include "libft.h"
#include "libftprintf.h"

int			validate_path(void)
{
	const char	*path;

	path = sh_getenv("PATH");
	if (path == NULL || ft_strcmp(path, "") == 0)
	{
		bi_setenv(3, (char *[]){NULL, "PATH",
			"/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/opt/X11/bin:."},
			NULL);
		return (1);
	}
	return (0);
}

char		**copy_envp(void)
{
	t_dict	*dict;
	char	**arr;

	if (!(dict = copy_env()))
		return (NULL);
	arr = ft_dict_to_ntarr(dict);
	ft_dict_del(&dict);
	return (arr);
}
