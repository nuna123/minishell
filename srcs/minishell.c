/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbartosi <jbartosi@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 13:56:09 by jbartosi          #+#    #+#             */
/*   Updated: 2023/05/30 16:02:47 by jbartosi         ###   ########.fr       */
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

	++ HISTORY COMMAND?
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
		ft_arrfree((void **)command);
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


int	has_char(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (ft_isprint(str[i]) && ft_strchr("\"\' ", str[i]) == NULL)
			return (1);
	}
	return (0);
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
		// Print a newline for visual clarity
		write(STDOUT_FILENO, "\n", 1);
		
		// Redisplay the prompt
		rl_replace_line("", 0); // Clear the current input from buffer
		rl_on_new_line(); // Move the cursor to a new line
		rl_redisplay(); // Redisplay the prompt
	}
	else 
	{
		ft_printf("%d\n\n\n",sig);
	}
}
int	main(int argc, char **argv, char **envp)
{
	static char		*line;
	static char		**command;
	t_mshell		shell;
	char			*temp_line;
	
	(void) argc;
	(void) argv;
	
	signal(SIGINT, handle_signal); //handle ctrl+c
	signal(SIGQUIT, SIG_IGN);  //ignore 'ctrl+\'
	signal(EOF, handle_signal);  //handle ctrl+D
	
	if (init_env(envp, &shell))
		return (printf("ERROR: missing enviromental variable\n"), 1);
	ft_animate(0);
	ft_get_prompt(&shell);
	line = readline(shell.shell_prompt);
	while (line)
	{
		printf("[%s] \n", line);
		if (ft_strlen(line) > 0 && has_char(line))
		{
			temp_line = ft_strtrim(line, " \t");
			command = split_string(shell, &temp_line);
			free(temp_line);
			if (command && command[0] && handle_commands(command, line, &shell))
				return (ft_exit(line, &shell, command));
		}
		free(line);

		// Regenerate the prompt after each command or signal interrupt
		ft_get_prompt(&shell);  
		line = readline(shell.shell_prompt);
		printf("[%s] \n", line);
	}

	return (command = NULL, ft_exit(line, &shell, command));
}
