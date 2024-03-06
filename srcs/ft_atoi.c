/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorot <mmorot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 15:07:05 by mmorot            #+#    #+#             */
/*   Updated: 2024/03/06 06:35:43 by mmorot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

static int	ft_white_space(const char *nptr, long *i)
{
	int	sign;

	sign = 1;
	while (nptr[*i] == ' ' || (nptr[*i] >= 9 && nptr[*i] <= 13))
		(*i)++;
	if (nptr[*i] == '+' || nptr[*i] == '-')
	{
		if (nptr[*i] == '-')
			sign = -1;
		(*i)++;
	}
	return (sign);
}

int	ft_atoi(const char *nptr)
{
	int		res;
	int		sign;
	long	i;

	res = 0;
	i = 0;
	sign = ft_white_space(nptr, &i);
	while (ft_isdigit(nptr[i]))
	{
		if (((res * 10) + (nptr[i] - '0')) < res)
		{
			if (sign > 0)
				return (-1);
			return (0);
		}
		res = (res * 10) + (nptr[i] - '0');
		i++;
	}
	return (res * sign);
}
