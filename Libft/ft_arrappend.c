/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nroth <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 08:56:59 by nroth             #+#    #+#             */
/*   Updated: 2022/10/14 08:57:05 by nroth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
	appends item to char * array and re allocates the space.
	original arr is freed
	NOTE: ITEM has to be freeable
*/
/* char	**ft_arrappend(char **arr, char *to_append)
{
	char	**ret;
	int		i;

	i = -1;
	ret = malloc (sizeof (char *) * (ft_arrlen((void **) arr) + 2));
	printf ("here 1\n");
	while (arr && arr[++i])
		ret[i] = arr[i];
	printf ("here 2\n");
	ret [i] = to_append;
	printf ("here 3\n");
	ret [i + 1] = NULL;
	printf ("here 4\n");
	ft_arrfree ((void **)arr);
	printf ("here 5\n");
	return (ret);
}
 */