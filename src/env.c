/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfielder <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 19:10:03 by gfielder          #+#    #+#             */
/*   Updated: 2019/05/06 08:17:41 by gfielder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "sh.h"
#include "libft.h"
#include "libftprintf.h"

static t_dict		*g_env;

int			sh_initenv(char **envp, int del)
{
	int		i;
	char	**split;

	if (!del)
	{
		if ((g_env = ft_dict_new(FTDICT_AUTO_STR)) == NULL)
		{
			ft_dprintf(2, "Error initializing env: not enough memory.\n");
			return (-1);
		}
		i = -1;
		while (envp[++i])
		{
			if ((split = ft_strsplit(envp[i], "=")) == NULL)
				return (-1);
			ft_dict_set(g_env, split[0], (void *)(split[1]), 0);
			ft_destroy_nullterm_ptrarray((void ***)(&split));
		}
		return (i);
	}
	return (ft_dict_del(&g_env));
}

t_dict		*copy_env(void)
{
	return (ft_dict_copy(g_env));
}

int			bi_setenv(int argc, char **argv, char **envp)
{
	(void)envp;
	if (argc == 1)
		return (log_ret(bi_env(argc, argv, envp)));
	else if (argc == 3)
	{
		if (ft_dict_set(g_env, argv[1], argv[2], 0) < 0)
			return (log_ret(-1));
		return (log_ret(0));
	}
	ft_dprintf(2, "usage: setenv MYVAR myvalue\n");
	return (log_ret(-1));
}

int			bi_unsetenv(int argc, char **argv, char **envp)
{
	int		i;
	int		ret;

	(void)envp;
	ret = 0;
	if (argc > 1)
	{
		i = 1;
		while (i < argc)
		{
			if (ft_dict_unset(g_env, argv[i]) < 0)
				ret--;
			i++;
		}
		return (log_ret(ret));
	}
	ft_dprintf(2, "usage: unsetenv MYVAR ...\n");
	return (log_ret(-1));
}

const char	*sh_getenv(char *key)
{
	return ((const char *)ft_dict_get_byref(g_env, key));
}
