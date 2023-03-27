/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbartosi <jbartosi@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 14:07:50 by jbartosi          #+#    #+#             */
/*   Updated: 2023/03/22 10:45:03 by jbartosi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	Print_pwd

	Takes current working directory and displays it
*/

void	print_pwd(void)
{
	char	pwd[10000];

	getcwd(pwd, 10000);
	printf("%s\n", pwd);
}

/*	Handle_cd

	Takes splited line from readline and changes
	current working directory. Depending on
	number of arguments.
	Cases:
		~ || blank
			home directory
		-
			previous directory
		relative or absolute path
*/

void	handle_cd(char **command, char **shell_prompt)
{
	static char	old_path[10000];
	char		tmp[10000];

	if (split_len(command) == 2)
	{
		if (ft_strncmp(command[1], "~", ft_strlen(command[1])) == 0)
			return (getcwd(old_path, 10000), chdir(getenv("HOME")),
				update_prompt(shell_prompt));
		else if (ft_strncmp(command[1], "-", ft_strlen(command[1])) == 0)
		{
			if (old_path[0] != '\0')
				return (getcwd(tmp, 10000), chdir(old_path),
					ft_strlcpy(old_path, tmp, ft_strlen(tmp) + 1), print_pwd(),
					update_prompt(shell_prompt));
			else
				printf("NO old path set\n");
		}
		else
			return (getcwd(old_path, 10000), chdir(command[1]),
				update_prompt(shell_prompt));
	}
	else
		return (getcwd(old_path, 10000), chdir(getenv("HOME")),
			update_prompt(shell_prompt));
}

/*	Hanle_commands

	Takes splited line from readline and launches coresponding functions
*/

void	handle_commands(char **command, char *line,
		char **shell_prompt, char *env[])
{
	char	*tmp;
	char	**cmd;
	pid_t	child;

	if (ft_strncmp(command[0], "cd", ft_strlen(command[0]) + 1) == 0)
		handle_cd(command, shell_prompt);
	else if (ft_strncmp(command[0], "pwd", ft_strlen(command[0]) + 1) == 0)
		print_pwd();
	else
	{
		cmd = ft_calloc(ft_arrlen((void **) command) + 2, sizeof (char *));
		cmd[0] = "./pipex";
		ft_cpyarr(&cmd[1], command);
		child = fork();
		if (child == 0)
			execve("./pipex/pipex", cmd, env);
		waitpid(child, NULL, 0);
		free(cmd);
	}
	return (tmp = ft_strtrim(line, " "), add_history(tmp),
		free(tmp), free_split(command));
}
