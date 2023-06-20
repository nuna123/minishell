/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbartosi <jbartosi@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 13:56:16 by jbartosi          #+#    #+#             */
/*   Updated: 2023/05/30 15:35:22 by jbartosi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include "../pipex/pipex.h"

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/ioctl.h>
# include <errno.h>

// COLORS
# define MAGENTA	"\001\e[0;35m\002"
# define END		"\001\e[0m\002"

typedef struct s_var
{
	char	*name;
	char	*val;
}				t_var;

typedef struct s_mshell
{
	struct s_var	*vars;
	char			*user;
	char			*home;
	char			*name;
	char			*shell_prompt;
	char			*last_line;
	char			*pipex_path;
	int				exit_status;
	char			*old_path;
}				t_mshell;

//	Minishell.c
void	free_vals(t_mshell *shell);
int		ft_exit(char *line, t_mshell *shell, char **command);
int		has_char(char *str);

//	Enviroment.c
int		init_env(char **envp, t_mshell *shell);

//	Prompt.c
void	ft_get_prompt(t_mshell *shell);
void	update_prompt(t_mshell *shell);

//	Commands.c
int		handle_commands(char **command, char *line, t_mshell *shell);

//	Commands_more.c
void	handle_env(t_mshell *shell);
void	handle_unset(char **command, t_mshell *shell);
void	handle_exit(char **command, t_mshell *shell);

//	Variables.c
char	*get_hostname(void);
char	*get_arg(char *argname, t_mshell shell);

//	Export.c
void	handle_export(char **command, t_mshell *shell);

//	Export_utils.c
void	recreate(char **command, t_mshell *shell);
int		is_defined(char **command, t_mshell *shell);
char	**convert_toenvp(t_mshell *shell);

//	Export_checker.c
int		valid_identifier(char **command, t_mshell *shell);

//	Change_directory.c
void	handle_cd(char **command, t_mshell *shell);

//	Animation.c
void	ft_animate(int exit);

// SPLITTERS
// static char	*stringize(char *argv[]);
// static char	*expand_arg(char *str, int counter);
// static void	split_extand(int *is_quotes, char *str, int *counter);
char	**split_string(t_mshell shell, char **str);

#endif
