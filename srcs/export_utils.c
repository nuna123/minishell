/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbartosi <jbartosi@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 14:46:09 by jbartosi          #+#    #+#             */
/*   Updated: 2023/04/08 13:11:56 by jbartosi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	Count_vals

	Utility for counting the number of env vars
*/
static int	count_vals(t_mshell *shell)
{
	int	i;

	i = 0;
	while (shell->vars[i].name)
		i++;
	return (i);
}

/*	Is_defined

	Utility to check if env var is defined
*/
int	is_defined(char **command, t_mshell *shell)
{
	int	i;
	int	j;

	j = 0;
	while (command[1][j])
		if (command[1][j++] == '=')
			break ;
	i = -1;
	while (shell->vars[++i].name)
		if (ft_strncmp(shell->vars[i].name, command[1], j - 1) == 0)
			break ;
	if (shell->vars[i].name != NULL)
		return (1);
	else
		return (0);
}

/*	Convert_toenvp

	Takes and array of variable names and values
	and converts it into envp like array of srtings
*/
char	**convert_toenvp(t_mshell *shell)
{
	char	**exp;
	int		i;

	exp = malloc((count_vals(shell) + 1) * sizeof(char **));
	i = -1;
	while (shell->vars[++i].name)
	{
		exp[i] = malloc(ft_strlen(shell->vars[i].name)
				+ ft_strlen(shell->vars[i].val) + 2);
		ft_strlcpy(exp[i], shell->vars[i].name,
			ft_strlen(shell->vars[i].name) + 1);
		ft_strlcat(exp[i], "=", ft_strlen(exp[i]) + 2);
		ft_strlcat(exp[i], shell->vars[i].val, ft_strlen(exp[i])
			+ ft_strlen(shell->vars[i].val) + 1);
	}
	exp[i] = NULL;
	return (exp);
}

/*	Add_one

	Helper function for recreate.
	After allocating new memory and copying exitsting variables
	just adds last one
*/
void	add_one(char **command, t_var **tmp, int i, int j)
{
	while (command[1][j])
		if (command[1][j++] == '=')
			break ;
	if (!ft_strchr(command[1], '='))
		j = j + 1;
	(*tmp)[i].name = malloc((j + 1) * sizeof(char));
	ft_strlcpy((*tmp)[i].name, command[1], j);
	if (ft_strchr(command[1], '='))
	{
		(*tmp)[i].val = malloc((ft_strlen(command[1])) - j + 1);
		ft_strlcpy((*tmp)[i].val, command[1] + j,
			(ft_strlen(command[1])) - j + 1);
	}
	else
	{
		(*tmp)[i].val = malloc(2);
		ft_strlcpy((*tmp)[i].val, "\0", 2);
	}
	(*tmp)[++i].name = NULL;
	(*tmp)[i].val = NULL;
}

/*	Recreate

	Allocates memory for all env variables plus one,
	then coppies all of them in and call adding of last one.
	After that frees the previous memory and sets the new list
	to shell structure.
*/
void	recreate(char **command, t_mshell *shell)
{
	int		len;
	int		i;
	int		j;
	t_var	*tmp;

	len = count_vals(shell);
	tmp = NULL;
	tmp = malloc((len + 2) * sizeof(t_var));
	i = -1;
	while (shell->vars[++i].name)
	{
		tmp[i].name = malloc(ft_strlen(shell->vars[i].name) + 1);
		ft_strlcpy(tmp[i].name, shell->vars[i].name,
			ft_strlen(shell->vars[i].name) + 1);
		tmp[i].val = malloc(ft_strlen(shell->vars[i].val) + 1);
		ft_strlcpy(tmp[i].val, shell->vars[i].val,
			ft_strlen(shell->vars[i].val) + 1);
	}
	j = 0;
	add_one(command, &tmp, i, j);
	free_vals(shell);
	shell->vars = tmp;
}
