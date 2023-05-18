/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbartosi <jbartosi@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 13:13:34 by jbartosi          #+#    #+#             */
/*   Updated: 2023/04/08 13:12:44 by jbartosi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	Get_hostname

	Reads /etc/hostname file and returns shorten version for the prompt
*/
char	*get_hostname(void)
{
	int		fd;
	char	*hostname;
	int		i;

	fd = open ("/etc/hostname", O_RDONLY);
	if (fd == -1)
		return (NULL);
	hostname = get_next_line(fd);
	close(fd);
	i = 0;
	while (!ft_strchr("\n.", hostname[i]))
		i++;
	hostname[i] = 0;
	return (hostname);
}

/*	Home_tilda

	Checks for tilda in command line and replaces it with home path
*/
void	home_tilda(char **command, t_mshell *s, int len, int i)
{
	char	*tmp;

	if (command[i][0] == '~' && len == 1)
	{
		free(command[i]);
		command[i] = malloc(ft_strlen(s->home) + 1);
		ft_strlcpy(command[i], s->home, ft_strlen(s->home) + 1);
	}
	else if (command[i][0] == '~' && command[i][1] == '/')
	{
		tmp = malloc(ft_strlen(command[i]) + 1);
		ft_strlcpy(tmp, command[i], ft_strlen(command[i]) + 1);
		free(command[i]);
		command[i] = malloc(ft_strlen(s->home) + ft_strlen(tmp) + 1);
		ft_strlcpy(command[i], s->home, ft_strlen(s->home) + 1);
		ft_strlcat(command[i], "/", ft_strlen(command[i]) + 2);
		ft_strlcat(command[i], tmp + 2, ft_strlen(command[i])
			+ ft_strlen(tmp) + 1);
		free(tmp);
	}
}

/*	Exit_status

	Checks for $? in echo command and fill it with the exit number
	And if $something doesnt exist, null terminates result
*/
void	exit_status(char **command, t_mshell *s, int len, int i)
{
	char	*exit_num;
	char	*tmp;

	if (command[i][0] == '$' && command[i][1] == '?')
	{
		tmp = malloc(ft_strlen(command[i]) + 1);
		ft_strlcpy(tmp, command[i], ft_strlen(command[i]) + 1);
		free(command[i]);
		exit_num = ft_itoa(s->exit_status);
		command[i] = malloc(ft_strlen(exit_num) + ft_strlen(tmp) + 1);
		ft_strlcpy(command[i], exit_num, ft_strlen(exit_num) + 1);
		ft_strlcat(command[i], tmp + 2, ft_strlen(command[i])
			+ ft_strlen(tmp) + 1);
		s->exit_status = 0;
		return (free(exit_num), free(tmp));
	}
	else if (command[i][0] == '$' && len > 1)
		command[i][0] = '\0';
}

/*	get_arg

	Loops through the vars array in the t_mshell struct to search for argname
	returns non-freeable string VAL or NULL
*/
char	*get_arg(char *argname, t_mshell shell)
{
	int	i;

	i = -1;
	if (!ft_strncmp(argname, "?", 2))
		return (ft_itoa(shell.exit_status));
	while (shell.vars[++i].name)
	{
		if (!ft_strncmp(argname, shell.vars[i].name, ft_strlen(argname)))
			return (shell.vars[i].val);
	}
	return (NULL);
}
