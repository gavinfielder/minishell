/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_source.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfielder <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 01:58:43 by gfielder          #+#    #+#             */
/*   Updated: 2019/05/01 03:03:01 by gfielder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include "libftprintf.h"
#include "libft.h"
#include "ls.h"
#include "sh.h"
#include <stdio.h>

static void	remove_any_trailing_comment(char *line)
{
	char	*ptr;

	if ((ptr = ft_strchr(line, '#')))
		*ptr = '\0';
}

static int	is_comment(char *line)
{
	int			i;

	if (!line)
		return (-1);
	i = -1;
	while (line[++i])
	{
		if (line[i] == '#')
			return (1);
		if (line[i] != ' ' && !(line[i] >= 9 && line[i] <= 13))
			return (0);
	}
	return (1);
}

static void	getline_cleanup_remove_newline(char *line)
{
	char	*ptr;

	if ((ptr = ft_strrchr(line, '\n')))
		*ptr = '\0';
}

static int	run_source(const char *path)
{
	char		*line;
	FILE		*fp;
	size_t		size;

	size = 0;
	line = NULL;
	if ((fp = fopen(path, "r")) == NULL)
	{
		ft_dprintf(2, "%s: could not read source file\n", path);
		return (-1);
	}
	while ((getline(&line, &size, fp) > 0))
	{
		getline_cleanup_remove_newline(line);
		if (!is_comment(line))
		{
			remove_any_trailing_comment(line);
			parse_command_line(line);
		}
	}
	free(line);
	fclose(fp);
	return (0);
}

int			bi_source(int argc, char **argv, char **envp)
{
	int		i;
	int		ret;

	(void)envp;
	ret = 0;
	if (argc < 2)
		return (log_ret(-ft_dprintf(2, "usage: source file1 [file2 ...]\n")));
	i = 0;
	while (++i < argc)
		ret += run_source(argv[i]);
	return (ret);
}
