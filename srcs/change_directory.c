/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_directory.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbartosi <jbartosi@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 13:49:18 by jbartosi          #+#    #+#             */
/*   Updated: 2023/05/29 16:31:39 by jbartosi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	Uprate_oldpwd

	Updates $OLDPWD env variable after succsesful directory change
*/
void	update_oldpwd(t_mshell *shell)
{
	int		i;
	char	tmp[10000];

	i = -1;
	getcwd(tmp, 10000);
	while (shell->vars[++i].name)
	{
		if (ft_strncmp(shell->vars[i].name, "OLDPWD", 7) == 0)
		{
			free(shell->vars[i].val);
			shell->vars[i].val = malloc(ft_strlen(shell->old_path) + 1);
			ft_strlcpy(shell->vars[i].val, shell->old_path,
				ft_strlen(shell->old_path) + 1);
		}
		else if (ft_strncmp(shell->vars[i].name, "PWD", 4) == 0)
		{
			free(shell->vars[i].val);
			shell->vars[i].val = malloc(ft_strlen(tmp) + 1);
			ft_strlcpy(shell->vars[i].val, tmp,
				ft_strlen(tmp) + 1);
		}
	}
}

/*	Go_back

	Previous directory
*/
void	go_back(t_mshell *shell)
{
	char	tmp[10000];

	getcwd(tmp, 10000);
	chdir(shell->old_path);
	free(shell->old_path);
	shell->old_path = malloc(ft_strlen(tmp) + 1);
	ft_strlcpy(shell->old_path, tmp, ft_strlen(tmp) + 1);
	update_oldpwd(shell);
	shell->exit_status = 0;
}

/*	Go_home

	Home directory
*/
void	go_home(t_mshell *shell)
{
	char	tmp[10000];

	getcwd(tmp, 10000);
	free(shell->old_path);
	shell->old_path = malloc(ft_strlen(tmp) + 1);
	ft_strlcpy(shell->old_path, tmp, ft_strlen(tmp) + 1);
	chdir(getenv("HOME"));
	update_oldpwd(shell);
	shell->exit_status = 0;
}

/*	Ft_chdir

	Relative or absolute path
*/
void	ft_chdir(char **command, t_mshell *shell)
{
	char	tmp[10000];

	getcwd(tmp, 10000);
	if (chdir(command[1]) != 0)
	{
		ft_putstr_fd("cd: No such file or directory\n", STDERR_FILENO);
		shell->exit_status = 1;
	}
	else
	{
		shell->exit_status = 0;
		free(shell->old_path);
		shell->old_path = malloc(ft_strlen(tmp) + 1);
		ft_strlcpy(shell->old_path, tmp, ft_strlen(tmp) + 1);
		update_oldpwd(shell);
	}
}

/*	Handle_cd

	Takes splited line from readline and changes
	current working directory. Depending on
	arguments.
	Cases:
		~ || blank
			home directory
		-
			previous directory
		relative or absolute path
*/
void	handle_cd(char **command, t_mshell *shell)
{
	if (ft_arrlen((void **)command) == 2)
	{
		if (ft_strncmp(command[1], "~", ft_strlen(command[1])) == 0)
			go_home(shell);
		else if (ft_strncmp(command[1], "-", ft_strlen(command[1])) == 0)
		{
			if (shell->old_path[0] != '\0')
				go_back(shell);
			else
				return (printf("NO old path set\n"), shell->exit_status = 1,
					update_prompt(shell));
		}
		else
			ft_chdir(command, shell);
	}
	else if (ft_arrlen((void **)command) > 2)
	{
		shell->exit_status = 1;
		ft_putstr_fd("cd: too many arguments\n", STDERR_FILENO);
	}
	else
		go_home(shell);
}
