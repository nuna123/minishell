/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitters.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nroth <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 10:55:22 by nroth             #+#    #+#             */
/*   Updated: 2023/05/10 10:55:24 by nroth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*expand_arg(char *str, int counter, t_mshell shell)
{
	char	*argname;
	char	*arg;
	int		argname_len;
	char	*newstr;

	argname_len = 0;
	while (!ft_strchr("\'\" ", str[counter + argname_len + 1]))
		argname_len++;
	argname = ft_substr (str, counter + 1, argname_len);
	arg = get_arg(argname, shell);
	newstr = ft_calloc((ft_strlen(str) - argname_len - 1)
			+ ft_strlen(arg) + 1, sizeof(char));
	ft_strlcpy(newstr, str, counter + 1);
	if (arg)
		ft_strlcpy(ft_strchr(newstr, 0), arg, ft_strlen(arg) + 1);
	else
		counter++;
	ft_strlcpy(ft_strchr(newstr, 0),
		&str[counter + argname_len + 1],
		ft_strlen(&str[counter + argname_len + 1]) + 1);
	free(argname);
	free(str);
	return (newstr);
}

char	*expand_args(char **str_ptr, t_mshell shell)
{
	int		i;
	int		is_quotes;
	char	*str;

	str = *str_ptr;
	i = -1;
	is_quotes = 0;
	while (str[++i])
	{
		if (str[i] == '\'' && (i <= 0 || str[i - 1] != '\\'))
			is_quotes = !is_quotes;
		else if (str[i] == '$' && !is_quotes)
			str = expand_arg (str, i--, shell);
	}
	*str_ptr = str;
	return (str);
}

static void	split_extand(int *is_quotes, char *str, int *counter)
{
	if ((str[*counter] == '\"' || str[*counter] == '\'')
		&& !*is_quotes)
	{
		if (!str[*counter - 1] || str[*counter - 1] != '\\')
		{
			*is_quotes = 2;
			if (str[*counter] == '\'')
				*is_quotes = 1;
			ft_memmove(&str[*counter],
				&str[*counter + 1], ft_strlen(&(str[*counter])));
			*counter -= 1;
		}
		else
			ft_memmove(&str[*counter - 1],
				&str[*counter], ft_strlen(&(str[*counter])) + 1);
	}
	else if (((str[*counter] == '\"' && *is_quotes == 2)
			|| (str[*counter] == '\'' && *is_quotes == 1)))
	{
		ft_memmove(&str[*counter], &str[*counter + 1],
			ft_strlen(&(str[*counter + 1])) + 1);
		*is_quotes = 0;
		*counter -= 1;
	}
}

void	extand2(char **str, int *counter, int *is_quotes, char ***ret)
{
	char	*temp;

	if ((*str)[*counter] == ' ' && !*is_quotes)
	{
		temp = ft_substr(*str, 0, *counter);
		*ret = ft_arrappend(*ret, temp);
		*str = &((*str)[*counter]) + 1;
		*counter = -1;
		*is_quotes = 0;
	}
	else
		split_extand(is_quotes, *str, counter);
}

//IS_QUOTES: 0 == NO, 1 == SINGLE QUOTES, 2 == DOUBLE
char	**split_string(t_mshell shell, char **str_ptr)
{
	char	**ret;
	int		counter;
	int		is_quotes;
	char	*temp;
	char	*str;

	str = expand_args(str_ptr, shell);
	is_quotes = 0;
	ret = NULL;
	counter = -1;
	while (str[++counter])
		extand2(&str, &counter, &is_quotes, &ret);
	if (*str)
	{
		temp = malloc(sizeof(char) * ft_strlen(str) + 1);
		ft_strlcpy(temp, str, ft_strlen(str) + 1);
		ret = ft_arrappend(ret, temp);
	}
	return (ret);
}

/* 
int	main(void)
{
	char *str = ft_strdup("echo $ARG");
	printf("STR: %s\n", str);

	char **arr	 = split_string(&str);

	printf ("\n\n\nRET:\n" );
	for (int i = 0; arr[i]; i++)
	{
		printf("\t{%s}\n", arr[i]);
	}

	free (str);
	ft_arrfree((void **)arr);
} */