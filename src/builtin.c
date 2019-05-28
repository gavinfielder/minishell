/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfielder <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 17:54:14 by gfielder          #+#    #+#             */
/*   Updated: 2019/05/01 03:05:51 by gfielder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sh.h"

const static t_builtin_dict_ent		g_builtins[] = {
	{"echo", bi_echo},
	{"cd", bi_cd},
	{"setenv", bi_setenv},
	{"set", bi_setenv},
	{"unsetenv", bi_unsetenv},
	{"unset", bi_unsetenv},
	{"env", bi_env},
	{"exit", bi_exit},
	{"source", bi_source},
	{"run", bi_source},
	{NULL, NULL}
};

t_executable					find_builtin(const char *key)
{
	int		i;

	i = 0;
	while (g_builtins[i].key)
	{
		if (ft_strequ(key, g_builtins[i].key))
			return (g_builtins[i].f);
		i++;
	}
	return (NULL);
}

int								bi_echo(int argc, char **argv, char **envp)
{
	int		i;

	(void)envp;
	i = 1;
	while (i < argc)
	{
		ft_putstr(argv[i]);
		if (i + 1 != argc)
			ft_putchar(' ');
		i++;
	}
	ft_putchar('\n');
	return (log_ret(0));
}
