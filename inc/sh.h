/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfielder <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 17:09:10 by gfielder          #+#    #+#             */
/*   Updated: 2019/05/01 02:22:08 by gfielder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_H
# define SH_H

# include "libft.h"

# define DEBUG 0

# define SETENV(x, y) bi_setenv(3, (char *[]){NULL, (x), (y)}, NULL)

char							*sh_get_input(void);

typedef int		(*t_executable)	(int argc, char **argv, char **envp);

typedef struct					s_builtin_dict_ent
{
	const char					*key;
	t_executable				f;
}								t_builtin_dict_ent;

void							handle_signal(int sigval);

t_executable					cleanup_search(void);
t_executable					find_command(char *name);
t_executable					find_builtin(const char *key);
t_executable					find_executable(const char *key);
t_executable					find_executable_abs_path(const char *path);

int								parse_command_line(char *line);
int								parse_command(char **command);
int								handle_var_set(char *command);

int								sh_initenv(char **envp, int del);
const char						*sh_getenv(char *key);
t_dict							*copy_env(void);
char							**copy_envp(void);

int								validate_path(void);

int								handle_expansions(char **command);
int								remove_escape(char **str,
									char *escape_sequence);
int								expand_all_env(char **str);
int								expand_all_home(char **command);

int								log_ret(int status);

int								bi_echo(int argc, char **argv, char **envp);
int								bi_cd(int argc, char **argv, char **envp);
int								bi_setenv(int argc, char **argv, char **envp);
int								bi_unsetenv(int argc, char **argv, char **envp);
int								bi_env(int argc, char **argv, char **envp);
int								bi_exit(int argc, char **argv, char **envp);
int								bi_source(int argc, char **argv, char **envp);

int								is_dir(char *str);
int								display_permission_denied
									(int argc, char **argv, char **envp);

#endif
