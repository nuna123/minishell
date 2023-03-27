/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbartosi <jbartosi@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 14:45:08 by jbartosi          #+#    #+#             */
/*   Updated: 2023/03/13 12:16:25 by jbartosi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	Free_split

	Frees memory from spliting a line
*/

void	free_split(char	**arr)
{
	int	i;

	i = -1;
	while (arr[++i])
		free(arr[i]);
	free(arr);
}

/*	Split_len

	Counts the number of splited words
*/

int	split_len(char **str)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (str[i++])
		len++;
	return (len);
}
