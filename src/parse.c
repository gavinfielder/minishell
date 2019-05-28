/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfielder <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 17:40:19 by gfielder          #+#    #+#             */
/*   Updated: 2019/05/06 08:19:53 by gfielder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "libft.h"
#include "libftprintf.h"

int				parse_command_line(char *line)
{
	char	**commands;
	int		i;
	int		ret;

	if ((commands = ft_strsplit(line, ";")) == NULL)
		return (log_ret(-1));
	i = -1;
	while (commands[++i])
	{
		if ((ret = parse_command(&(commands[i]))) < 0)
			;
	}
	ft_destroy_nullterm_ptrarray((void ***)(&commands));
	return (log_ret(ret));
}

int				parse_command(char **command)
{
	t_argsarr		*args;
	t_executable	ex;
	int				ret;
	char			**envp;

	ret = 0;
	envp = copy_envp();
	handle_expansions(command);
	if ((args = ft_strsplit_args(*command, " \t", "\"\"")) == NULL)
		return (log_ret(-1));
	if (args->argc == 0)
		ret = -1;
	else if (handle_var_set(*command))
		ret = 0;
	else if ((ex = find_command(args->argv[0])))
		ret = ex(args->argc, args->argv, envp);
	else
		ret = -ft_dprintf(2, "command not found: %s\n", args->argv[0]);
	ft_argsarr_del(&args);
	ft_destroy_nullterm_ptrarray((void ***)(&envp));
	return (log_ret(ret));
}

t_executable	find_command(char *name)
{
	t_executable	ex;

	if ((ex = find_builtin(name)))
		return (ex);
	else if ((ex = find_executable(name)))
		return (ex);
	return (NULL);
}

int				handle_var_set(char *command)
{
	char	**split;
	char	*eq;
	int		i;

	if ((eq = ft_strchr(command, '=')) && (*(eq - 1) != '\\')
		&& (eq != command))
	{
		i = 0;
		while (command + i != eq)
		{
			if (!(command[i] == '_'
					|| (command[i] >= 'A' && command[i] <= 'Z')))
				return (0);
			i++;
		}
		if (command[i + 1] && !ft_strchr(command + i + 1, '='))
		{
			split = ft_strsplit_grouping(command, "=", "\"\"");
			bi_setenv(3, (char *[]){NULL, split[0], split[1]}, NULL);
			ft_destroy_nullterm_ptrarray((void ***)(&split));
			return (1);
		}
	}
	return (0);
}
