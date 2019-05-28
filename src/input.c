/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfielder <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 17:00:19 by gfielder          #+#    #+#             */
/*   Updated: 2019/05/06 09:26:50 by gfielder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <setjmp.h>
#include "libftprintf.h"
#include "libft.h"
#include <readline/readline.h>
#include <readline/history.h>

sigjmp_buf					g_ctrlc_buf;
int							g_signaled;

static const char			*g_completion_presets[] =
{
	"echo",
	"exit",
	"env",
	"setenv",
	"unsetenv",
	"emacs",
	"vim",
	"pwd",
	"norminette",
	NULL
};

char						*iterate_presets(const char *text, int state)
{
	static int	list_index;
	static int	len;
	const char	*entry;

	if (!state)
	{
		list_index = 0;
		len = strlen(text);
	}
	while ((entry = g_completion_presets[list_index++]))
	{
		if (ft_strncmp(entry, text, len) == 0)
		{
			return (ft_strdup(entry));
		}
	}
	return (NULL);
}

char						**preset_completions(const char *str,
								int start, int end)
{
	(void)start;
	(void)end;
	return (rl_completion_matches(str, iterate_presets));
}

static int					has_input(char *str)
{
	int		i;

	if (str == NULL)
		return (0);
	i = 0;
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '\t')
			return (1);
		i++;
	}
	return (0);
}

char						*sh_get_input(void)
{
	char	*ret;

	ret = NULL;
	rl_attempted_completion_function = preset_completions;
	ft_putstr("\x1B[1;33m");
	sigsetjmp(g_ctrlc_buf, 1);
	if (!g_signaled)
	{
		ret = readline("Yes, master? > ");
		if (has_input(ret))
			add_history(ret);
	}
	else
	{
		ft_putchar('\n');
		ret = ft_strdup("");
		g_signaled = 0;
	}
	ft_putstr("\x1B[0m");
	return (ret);
}
