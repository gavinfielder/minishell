/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfielder <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 21:22:27 by gfielder          #+#    #+#             */
/*   Updated: 2019/04/29 21:28:29 by gfielder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "libftprintf.h"
#include "sh.h"

int			handle_expansions(char **command)
{
	return (
		expand_all_env(command) |
		expand_all_home(command));
}

int			remove_escape(char **str, char *escape_sequence)
{
	char			*ptr;
	unsigned int	start;

	while ((ptr = ft_strstr(*str, escape_sequence)))
	{
		start = (unsigned int)(ptr - *str);
		if ((ft_strrepl(str, start, 1, "")) < 0)
			return (-1);
	}
	return (1);
}

int			expand_all_env(char **str)
{
	char			*ptr;
	char			*key;
	const char		*value;
	unsigned int	start;
	size_t			len;

	key = NULL;
	while ((ptr = ft_strchr(*str, '$')) && *(ptr - 1) != '\\')
	{
		start = (unsigned int)(ptr - *str);
		len = 1;
		while (ptr[len] == '_' || (ptr[len] >= 'A' && ptr[len] <= 'Z'))
			len++;
		if (len > 1)
		{
			key = ft_strsub(*str, start + 1, len - 1);
			value = sh_getenv(key);
		}
		if (!key || !value)
			ft_strrepl(str, start, 1, "");
		else
			ft_strrepl(str, start, len, value);
		ft_memdelr((void **)(&key));
	}
	return (remove_escape(str, "\\$"));
}

int			expand_all_home(char **command)
{
	char			*ptr;
	unsigned int	start;

	while ((ptr = ft_strchr(*command, '~')) && *(ptr - 1) != '\\')
	{
		start = (unsigned int)(ptr - *command);
		ft_strrepl(command, start, 1, sh_getenv("HOME"));
	}
	remove_escape(command, "\\~");
	return (1);
}
