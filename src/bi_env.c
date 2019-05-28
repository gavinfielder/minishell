/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfielder <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 17:54:14 by gfielder          #+#    #+#             */
/*   Updated: 2019/05/01 01:25:27 by gfielder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"
#include "sh.h"
#include "libftprintf.h"

static void						print_env(char **envp)
{
	int		i;

	i = 0;
	while (envp[i])
	{
		ft_printf("%s\n", envp[i]);
		i++;
	}
}

static int						run_env(int argc,
									char **argv, char **envp)
{
	int				ret;
	t_executable	ex;

	ret = 0;
	if ((ex = find_command(argv[0])))
		ret = ex(argc, argv, envp);
	else
		ret = -ft_dprintf(2, "command not found: %s\n", argv[0]);
	return (log_ret(ret));
}

static t_dict					*bi_env_init(int *argc, char ***argv,
									char ***envp, t_clopt *clargs)
{
	t_dict			*dict;

	*clargs = ft_optget(*argc, *argv);
	if (ft_issel(clargs, 'i'))
		*envp = (char *[]){NULL};
	if (!(*envp))
		return (NULL);
	dict = ft_ntarr_to_dict(*envp);
	return (dict);
}

int								bi_env(int argc, char **argv, char **envp)
{
	int				i;
	t_clopt			clargs;
	t_dict			*dict;
	int				ret;

	ret = 0;
	if (!(dict = bi_env_init(&argc, &argv, &envp, &clargs)))
		return (log_ret(-1));
	i = -1;
	while (++i < clargs.args.argc)
	{
		if (ft_dict_set_parse(dict, clargs.args.argv[i]) < 0)
			break ;
	}
	envp = ft_dict_to_ntarr(dict);
	if (i < clargs.args.argc)
		ret = run_env(clargs.args.argc - i, clargs.args.argv + i, envp);
	else
		print_env(envp);
	ft_destroy_nullterm_ptrarray((void ***)(&envp));
	ft_dict_del(&dict);
	return (log_ret(ret));
}
