/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbartosi <jbartosi@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 13:56:09 by jbartosi          #+#    #+#             */
/*   Updated: 2023/04/29 14:41:36 by jbartosi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	TO_DO

	X Fix error while unset path and pipex
	X Add export buildin
		X Add structure for envp in main structure
		O Add checker for valid identifier
	X Save last used command and compare it against now used
		to avoid duplicate commands in history
	X Add error number and error message handeling
	O Add support for quotes and double quotes
	O BONUS
*/

void	free_vals(t_mshell *shell)
{
	int	i;

	i = -1;
	while (shell->vars[++i].name)
		free(shell->vars[i].name);
	i = -1;
	while (shell->vars[++i].val)
		free(shell->vars[i].val);
	free(shell->vars);
}

/*	Ft_exit

	Exits and frees stuff
*/
int	ft_exit(char *line, t_mshell *shell, char **command)
{
	free(line);
	free(shell->shell_prompt);
	if (command != NULL && *command != NULL)
		free_split(command);
	free(shell->home);
	free(shell->user);
	free(shell->name);
	free(shell->pipex_path);
	free(shell->last_line);
	free(shell->old_path);
	free_vals(shell);
	ft_animate(1);
	return (shell->exit_status);
}

/*	Handle_signal

	Handles signals
	ioctl sends a fake input signal of \n
		https://man7.org/linux/man-pages/man2/ioctl_tty.2.html
	rl_replace_line replaces line in rdline buffer with 0
	rl_on_new_line begins reading a new line
*/
void	handle_signal(int sig)
{
	if (sig == SIGINT)
	{
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		rl_replace_line("", 0);
		rl_on_new_line();
	}
}

/*	Main

	Main function for the project.
	Displays prompt when waiting for input.
	Stores entered line and splits it into words.
	Handles entered commands.
	Frees prompt, line and splited line and main structure
	Buildins:
		echo <-n> MESSAGE
			Display writen message, even enviromental variables
		cd PATH
			Changind the current working directory
		pwd
			Display the current working directory
		unset NAME
			Disables variable NAME in enviroment
		env
			Display all enviromental variables
		exit
			Exits the shell

	Code for testers:
	if (argc >= 3 && !ft_strncmp(argv[1], "-c", 3))
	{
		int i = 0;
		if ((void)argv, (void)argc, signal(SIGINT, handle_signal),
			signal(SIGQUIT, SIG_IGN), init_env(envp, &shell))
		return (printf("ERROR: missing enviromental variable\n"), 1);
		//ft_animate(0);
		ft_get_prompt(&shell);
		line = argv[2];
		while (i == 0)
		{
			if (ft_strlen(line) > 0)
			{
				command = ft_split(line, ' ');
				if (ft_strncmp(command[0], "exit", 5) == 0)
					return (handle_exit(command, &shell), shell.exit_status);
				else
					handle_commands(command, line, &shell);
			}
			i++;
		}
		return (shell.exit_status);
	}
*/
int	main(int argc, char **argv, char **envp)
{
	static char		*line;
	static char		**command;
	t_mshell		shell;
	char			*temp_line;

	if ((void)argv, (void)argc, signal(SIGINT, handle_signal),
		signal(SIGQUIT, SIG_IGN), init_env(envp, &shell))
		return (printf("ERROR: missing enviromental variable\n"), 1);
	ft_animate(0);
	ft_get_prompt(&shell);
	line = readline(shell.shell_prompt);
	while (line)
	{
		if (ft_strlen(line) > 0)
		{
			temp_line = ft_strdup(line);
			command = split_string(&temp_line);
			free(temp_line);
			// printf("line: (%p, %s)\n", line, line);
			if (command[0])
				if (handle_commands(command, line, &shell) != 0)
					return (ft_exit(line, &shell, command));
		}
		free(line);
		line = readline(shell.shell_prompt);
	}
	return (command = NULL, ft_exit(line, &shell, command));
}
