/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nroth <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 16:16:24 by nroth             #+#    #+#             */
/*   Updated: 2023/01/11 16:16:25 by nroth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_cpyarr(char **dest, char **src)
{
	while (*src)
	{
		*dest = *src;
		dest++;
		src++;
	}
	*dest = NULL;
}
