/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbartosi <jbartosi@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 14:07:50 by jbartosi          #+#    #+#             */
/*   Updated: 2023/05/30 15:48:57 by jbartosi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	Handle_pipex

	Pipex by nroth
*/
void	handle_pipex(char **command, t_mshell *shell)
{
	char	**cmd;
	pid_t	child;
	int		stat;

	cmd = ft_calloc(ft_arrlen((void **) command) + 2, sizeof (char *));
	cmd[0] = "./pipex";
	ft_arrcpy(&cmd[1], command);
	child = fork();
	if (child == 0)
		execve(shell->pipex_path, cmd, convert_toenvp(shell));
	waitpid(child, &stat, 0);
	shell->exit_status = WEXITSTATUS(stat);
	free(cmd);
}

/*	Add_to_history

	Checks if the now entered line is different from the last one
	if so, then it adds it to the history.
*/
void	add_to_history(char **command, char *trimed_line, t_mshell *shell)
{
	int	i;

	if (trimed_line && ft_strncmp(shell->last_line, trimed_line,
			ft_strlen(trimed_line) + 1) != 0)
	{
		add_history(trimed_line);
		i = -1;
		while (shell->vars[++i].name)
		{
			if (ft_strncmp(shell->vars[i].name, "_", 2) == 0)
			{
				free(shell->vars[i].val);
				shell->vars[i].val = malloc(ft_strlen(command[0]) + 1);
				ft_strlcpy(shell->vars[i].val, command[0],
					ft_strlen(command[0]) + 1);
			}
		}
		free(shell->last_line);
		shell->last_line = (char *)malloc(ft_strlen(trimed_line) + 1);
		ft_strlcpy(shell->last_line, trimed_line, ft_strlen(trimed_line) + 1);
	}
}

/*	Hanle_commands

	Takes splited line from readline and launches coresponding functions
	In the end, trims the line of whitespace and adds it to the history
*/
int	handle_commands(char **command, char *line, t_mshell *shell)
{
	char		*tmp;
	size_t		cmd_len;

	if (!has_char(line))
		return (0);
	cmd_len = ft_arrlen((void **)command);
	if (ft_strncmp(command[0], "exit", 5) == 0)
		return (handle_exit(command, shell), 1);
	else if (ft_strncmp(command[0], "cd", 3) == 0)
		handle_cd(command, shell);
	else if (ft_strncmp(command[0], "env", 4) == 0 && cmd_len == 1)
		handle_env(shell);
	else if (ft_strncmp(command[0], "unset", 6) == 0 )// && cmd_len == 2
		handle_unset(command, shell);
	else if (ft_strncmp(command[0], "export", 7) == 0 && cmd_len < 3)
		handle_export(command, shell);
	else
		handle_pipex(command, shell);
	if (has_char(line))
	{
		tmp = ft_strtrim(line, " ");
		add_to_history(command, tmp, shell);
		free(tmp);
	}
	return (update_prompt(shell), ft_arrfree((void **)command), 0);
}

/* 	else if (ft_strncmp(command[0], "pwd", 4) == 0)
		print_pwd(shell);
	else if (ft_strncmp(command[0], "echo", 5) == 0)
		handle_echo(command, shell, i); */
