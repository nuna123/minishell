/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbartosi <jbartosi@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 13:19:58 by jbartosi          #+#    #+#             */
/*   Updated: 2023/04/08 15:33:42 by jbartosi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	valid_identifier(char **command, t_mshell *shell)
{
	int	i;

	i = -1;
	if (command[1][0] == '-')
	{
		ft_putstr_fd("export: ", STDERR_FILENO);
		ft_putstr_fd(command[1], STDERR_FILENO);
		ft_putstr_fd(": invalid option\n", STDERR_FILENO);
		shell->exit_status = 2;
		return (0);
	}
	while (command[1][++i] != '=' && command[1][i])
	{
		if (command[1][i] == '\\')
			i++;
		if (!ft_isalpha(command[1][i]) && command[1][i] != '_')
		{
			ft_putstr_fd("export: ", STDERR_FILENO);
			ft_putstr_fd(command[1], STDERR_FILENO);
			ft_putstr_fd(": not a valid identifier\n", STDERR_FILENO);
			shell->exit_status = 1;
			return (0);
		}
	}
	return (1);
}
