/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbartosi <jbartosi@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 11:05:33 by jbartosi          #+#    #+#             */
/*   Updated: 2023/05/30 15:23:28 by jbartosi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "animation_vars.h"

/*	count_nls

	Returns number of \n in string
*/
static int	count_nls(char *str)
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
static void	clean_terminal(int lines)
{
	int	i;

	i = 0;
	while (i++ < lines)
		printf("\e[F\e[2K");
}
/*	Logo

	Prints enlarging logo of 42 in the terminal
*/

static void	animate_logo(void)
{
	char	*logo[9];
	int		i;

	logo[0] = LOGO0;
	logo[1] = LOGO1;
	logo[2] = LOGO2;
	logo[3] = LOGO3;
	logo[4] = LOGO4;
	logo[5] = LOGO5;
	logo[6] = LOGO6;
	logo[7] = LOGO7;
	logo[8] = LOGO8;
	i = -1;
	while (++i < 9)
	{
		printf("%s\n", logo[i]);
		if (i == 0)
			usleep(350000);
		else
			usleep(180000);
		clean_terminal(count_nls(logo[i]) + 1);
	}
	sleep(1);
}

/*	Shell

	Prints shrinking shell in the terminal
*/
static void	shell(void)
{
	char	*shell[9];
	int		i;

	shell[0] = SHELL0;
	shell[1] = SHELL1;
	shell[2] = SHELL2;
	shell[3] = SHELL3;
	shell[4] = SHELL4;
	shell[5] = SHELL5;
	shell[6] = SHELL6;
	shell[7] = SHELL7;
	shell[8] = SHELL8;
	i = 9;
	while (--i > -1)
	{
		printf("%s\n", shell[i]);
		if (i == 8)
			usleep(500000);
		else
			usleep(180000);
		clean_terminal(count_nls(shell[i]) + 1);
	}
}

/*	Ft_animate

	Depending on exit int either displays enlarging 42 logo
	or shrinking seashell.
	Cleans and prepares space beforehand
*/
void	ft_animate(int exit)
{
	int		i;
	int		maxlines;

	maxlines = count_nls(SHELL8) + 1;
	i = -1;
	while (++i < maxlines)
		printf("\n");
	i = -1;
	while (++i < maxlines)
		printf("\e[F");
	if (exit == 0)
		animate_logo();
	else if (exit == 1)
		shell();
}
