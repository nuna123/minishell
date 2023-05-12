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

char	**ft_arrappend(char **arr, char *to_append)
{
	char	**ret;
	int		i;

	i = 0;
	ret = malloc (sizeof (char *) * (ft_arrlen((void **) arr) + 2));
	while (arr && arr[i])
	{
		ret [i] = ft_strdup(arr[i]);
		i++;
	}
		
	ret [i] = to_append;
	ret [i + 1] = NULL;
	if (arr)
		ft_arrfree ((void **)arr);
	return (ret);
}

static char	*expand_arg(char *str, int counter)
{
	char	*argname;
	char	*arg;
	int		argname_len;
	char	*newstr;

	argname_len = 0;
	while (!ft_strchr("\'\" ", str[counter + argname_len + 1]))
		argname_len++;
	argname = ft_substr (str, counter + 1, argname_len);
	arg = getenv(argname);
	printf("ARG: {%s}\n", arg);
	newstr = ft_calloc((ft_strlen(str) - argname_len - 1)
			+ ft_strlen(arg) + 1, sizeof(char));
	ft_strlcpy(newstr, str, counter + 1);
	if (arg)
		ft_strlcpy(ft_strchr(newstr, 0), arg, ft_strlen(arg) + 1);
	else
		counter++;
	ft_strlcpy(ft_strchr(newstr, 0),
		&str[counter + argname_len + 1], ft_strlen(&str[counter + argname_len + 1]) + 1);
	free(argname);
	free(str);
	
	return (newstr);
}

//ADDING ALL ARGV TO ONE INPUT LINE

/* static char	*stringize(char *argv[])
{
	char	*cmds;
	int		i;
	int		is_quotes;

	i = -1;
	cmds = ft_strdup("");
	while (argv[++i])
	{
		cmds = ft_new_strjoin(cmds, argv[i]);
		if (argv[i + 1])
			cmds = ft_new_strjoin(cmds, " ");
	}
	i = -1;
	is_quotes = 0;
	while (cmds[++i])
	{
		if (cmds[i] == '\'' && (i <= 0 || cmds[i - 1] != '\\'))
			is_quotes = !is_quotes;
		else if (cmds[i] == '$' && !is_quotes)
			cmds = expand_arg (cmds, i);
	}
	return (cmds);
} */

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

//IS_QUOTES: 0 == NO, 1 == SINGLE QUOTES, 2 == DOUBLE
char	**split_string(char **str_ptr)
{
	char	**ret;
	int		counter;
	int		is_quotes;
	char	*temp;
	char	*str = *str_ptr;

	int i = -1;
	is_quotes = 0;
	// printf("STR: {%s}\n", str);
	while (str[++i])
	{
		if (str[i] == '\'' && (i <= 0 || str[i - 1] != '\\'))
			is_quotes = !is_quotes;
		else if (str[i] == '$' && !is_quotes)
			str = expand_arg (str, i);
		*str_ptr = str;
	}

	// printf("AFTER STR: {%s}\n", str);

	ret = NULL;
	counter = -1;
	while (str[++counter])
	{
		if (str[counter] == ' ' && !is_quotes)
		{
			temp = ft_substr(str, 0, counter);
			// printf("newstr: {%s}\n", temp);
			ret = ft_arrappend(ret, temp);
			str = &(str[counter]) + 1;
			counter = -1;
			is_quotes = 0;
		}
		else
			split_extand(&is_quotes, str, &counter);
	}

	if (*str)
	{
		// printf("newstr: {%s}\n", str);
		temp = malloc(sizeof(char) * ft_strlen(str) + 1);
		ft_strlcpy(temp, str, ft_strlen(str) + 1);
		ret = ft_arrappend(ret, temp);
	}
	return (ret);
}
/* 
char	**resplit_argv(int argc, char *argv[])
{
	char	*str;
	char	**ret;

	if (argc < 2)
		return (argv);
	str = stringize (argv);
	printf ("STR: {%s}\n", str);
	ret = split_string (str);
	free (str);
	return (ret);
} */
	// printf ("STR:  {%s}\n", str);



int	main(void)
{
	char *str = ft_strdup("echo \"$ARG 'hi'\"");
	printf("STR: %s\n", str);

	char **arr	 = split_string(&str);

	printf ("\n\n\nRET:\n" );
	for (int i = 0; arr[i]; i++)
	{
		printf("\t{%s}\n", arr[i]);
	}

	free (str);
	ft_arrfree((void **)arr);
}