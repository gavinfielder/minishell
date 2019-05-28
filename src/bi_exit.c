/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfielder <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 17:54:14 by gfielder          #+#    #+#             */
/*   Updated: 2019/05/01 01:25:51 by gfielder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "sh.h"
#include "libftprintf.h"

static int	g_status = 0;

int			log_ret(int status)
{
	g_status = status;
	return (status);
}

int			bi_exit(int argc, char **argv, char **envp)
{
	int			status;

	(void)envp;
	if (argc > 2)
		return (log_ret((-ft_dprintf(2, "exit: too many arguments\n"))));
	status = (argc == 2 ? ft_atoi(argv[1]) : g_status);
	cleanup_search();
	sh_initenv(NULL, 1);
	ft_printf("%{bright red}Goodbye cruel world!%{}\n");
	exit(status);
	return (log_ret(0));
}
