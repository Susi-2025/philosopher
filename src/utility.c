/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinguyen <vinguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 15:41:48 by vinguyen          #+#    #+#             */
/*   Updated: 2025/11/16 11:32:19 by vinguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static	int	find_value(char *s, int *i);

int	ft_valid_num(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (1);
	while (s[i] == ' ' || (s[i] >= 9 && s[i] <= 13))
		i++;
	if (s[i] == '-' || s[i] == '0' || s[i] == '\0')
		return (1);
	if (find_value(s, &i) == 1)
		return (1);
	while (s[i] == ' ' || (s[i] >= 9 && s[i] <= 13))
		i++;
	if (s[i] == '\0')
		return (0);
	else
		return (1);
}

static	int	find_value(char *s, int *i)
{
	int	res;
	int	digit;

	res = 0;
	while (s[*i] >= '0' && s[*i] <= '9')
	{
		digit = s[*i] - '0';
		if (res > INT_MAX / 10 || (res == INT_MAX / 10 && digit > (INT_MAX
					% 10)))
			return (1);
		res = res * 10 + (s[*i] - '0');
		(*i)++;
	}
	return (0);
}

int	ft_atoi(char *s)
{
	int				i;
	unsigned int	res;

	i = 0;
	res = 0;
	while (s[i] == ' ' || (s[i] >= 9 && s[i] <= 13))
		i++;
	if (s[i] == '+')
		i++;
	while (s[i] >= '0' && s[i] <= '9')
	{
		if (res > (UINT_MAX - (s[i] - '0')) / 10)
			return (-1);
		res = res * 10 + s[i] - '0';
		i++;
	}
	return (res);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	if (!s1 && !s2)
		return (0);
	if (!s1)
		return (-1);
	if (!s2)
		return (1);
	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

void	ft_bzero(void *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((unsigned char *)s)[i] = '\0';
		i++;
	}
}
