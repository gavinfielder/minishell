/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfielder <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 18:43:36 by gfielder          #+#    #+#             */
/*   Updated: 2019/05/06 08:48:03 by gfielder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <setjmp.h>
#include <signal.h>
#include <sys/wait.h>
#include <unistd.h>
#include "ls.h"
#include "libft.h"
#include "libftprintf.h"
#include "sh.h"

static t_file		*g_head = NULL;
static t_file		*g_last_match = NULL;
static int			g_matched_single = 0;

static pid_t		g_pid = 0;

extern int			g_signaled;
extern sigjmp_buf	g_ctrlc_buf;

t_executable		cleanup_search(void)
{
	if (g_head)
		ftls_del_tree(&g_head);
	if (g_matched_single)
		ftls_del_node(&g_last_match);
	g_matched_single = 0;
	g_pid = 0;
	g_last_match = NULL;
	return (NULL);
}

void				handle_signal(int sigval)
{
	(void)sigval;
	g_signaled = 1;
	if (g_pid)
	{
		kill(g_pid, SIGINT);
		cleanup_search();
		ft_putchar('\n');
	}
	else
		siglongjmp(g_ctrlc_buf, 1);
}

static int			run_matched(int argc, char **argv, char **envp)
{
	int		stat_loc;

	(void)argc;
	g_pid = fork();
	if (g_pid == 0 && execve(g_last_match->path, argv, envp) < 0)
		return (log_ret(-ft_dprintf(2, "Error launching executable\n")));
	else if (g_pid < 0)
		return (log_ret(-ft_dprintf(2, "Error launching executable\n")));
	waitpid(g_pid, &stat_loc, WUNTRACED);
	cleanup_search();
	if (WIFEXITED(stat_loc))
		return (log_ret(WEXITSTATUS(stat_loc)));
	else if (WIFSIGNALED(stat_loc))
		return (log_ret(WTERMSIG(stat_loc)));
	else if (WIFSTOPPED(stat_loc))
		return (log_ret(WSTOPSIG(stat_loc)));
	return (log_ret(0));
}

t_executable		find_executable(const char *key)
{
	char			**paths;
	int				i;
	t_executable	ex;

	validate_path();
	ex = NULL;
	if ((paths = ft_strsplit(sh_getenv("PATH"), ":")) == NULL)
		return (cleanup_search());
	i = -1;
	while (paths[++i] && !ex)
	{
		if (access(paths[i], X_OK | R_OK) < 0)
			continue ;
		g_head = ft_list_directory_repl(g_head, paths[i], "p");
		if ((g_last_match = ft_match_file_exact(g_head, key)))
		{
			ex = (access(g_last_match->path, X_OK) < 0) ?
				display_permission_denied : run_matched;
		}
	}
	ft_destroy_nullterm_ptrarray((void ***)(&paths));
	if (!ex)
		cleanup_search();
	return (ex ? ex : find_executable_abs_path(key));
}

t_executable		find_executable_abs_path(const char *path)
{
	if ((g_last_match = ft_get_file(path, "p")))
	{
		g_matched_single = 1;
		if (access(g_last_match->path, X_OK) < 0)
		{
			cleanup_search();
			return (display_permission_denied);
		}
		return (run_matched);
	}
	return (cleanup_search());
}
