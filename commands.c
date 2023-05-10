/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbartosi <jbartosi@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 14:07:50 by jbartosi          #+#    #+#             */
/*   Updated: 2023/04/29 14:44:18 by jbartosi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	Handle_echo

	Replicates the functionality of echo in bash
	Takes splited command line and prints stuff
	echo -> \n
	echo sd asd -> sd asd\n
	echo -n -> Nothing
	echo -n asd -> asd

*/
/*void	handle_echo(char **command, t_mshell *shell, int i)
{
	if (split_len(command) == 1)
		printf("\n");
	else if (!(ft_strncmp(command[1], "-n", 3) == 0))
	{
		i = 0;
		while (command[++i])
		{
			printf("%s", command[i]);
			if (i < split_len(command) - 1 && command[i][0] != '\0')
				printf(" ");
		}
		printf("\n");
	}
	else if (ft_strncmp(command[1], "-n", 3) == 0)
	{
		i = 1;
		while (command[++i])
		{
			printf("%s", command[i]);
			if (i < split_len(command) - 1 && command[i][0] != '\0')
				printf(" ");
		}
	}
	shell->exit_status = 0;
} */

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

	if (ft_strncmp(shell->last_line, trimed_line,
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

	handle_variables(command, shell);
	if (ft_strncmp(command[0], "exit", 5) == 0)
		return (handle_exit(command, shell), 1);
	else if (ft_strncmp(command[0], "cd", 3) == 0)
		handle_cd(command, shell);
	else if (ft_strncmp(command[0], "env", 4) == 0 && split_len(command) == 1)
		handle_env(shell);
	else if (ft_strncmp(command[0], "unset", 6) == 0 && split_len(command) == 2)
		handle_unset(command, shell);
	else if (ft_strncmp(command[0], "export", 7) == 0 && split_len(command) < 3)
		handle_export(command, shell);
	else
		handle_pipex(command, shell);
	return (tmp = ft_strtrim(line, " "), add_to_history(command, tmp, shell),
		update_prompt(shell), free(tmp), free_split(command), 0);
}

/* 	else if (ft_strncmp(command[0], "pwd", 4) == 0)
		print_pwd(shell);
	else if (ft_strncmp(command[0], "echo", 5) == 0)
		handle_echo(command, shell, i); */