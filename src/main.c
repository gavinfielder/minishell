/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfielder <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 21:16:47 by gfielder          #+#    #+#             */
/*   Updated: 2019/05/06 08:47:47 by gfielder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <stdlib.h>
#include <signal.h>
#include "sh.h"
#include "libft.h"
#include "libftprintf.h"

int		main(int argc, char **argv, char **envp)
{
	char	*input;

	signal(SIGINT, handle_signal);
	siginterrupt(SIGINT, 1);
	(void)argc;
	(void)argv;
	(void)input;
	sh_initenv(envp, 0);
	while ((input = sh_get_input()))
	{
		parse_command_line(input);
		free(input);
	}
	sh_initenv(NULL, 1);
	return (0);
}
