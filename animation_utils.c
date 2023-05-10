/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbartosi <jbartosi@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 15:30:46 by jbartosi          #+#    #+#             */
/*   Updated: 2023/03/28 12:36:10 by jbartosi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	Count_new_lines

	Returns number of \n in string
*/
int	count_new_lines(char *str)
{
	int	count;

	count = 0;
	while (*str++)
		if (*str == '\n')
			count++;
	return (count);
}

/*	Clean_terminal

	Goes up a line and deletes it n number of times
	until the printed picture is gone
*/
void	clean_terminal(int lines)
{
	int	i;

	i = 0;
	while (i++ < lines)
		printf("\e[F\e[2K");
}
