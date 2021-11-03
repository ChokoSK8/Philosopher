/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrun <abrun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 11:52:02 by abrun             #+#    #+#             */
/*   Updated: 2021/11/03 17:53:21 by abrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

char	*ft_itoa(int n)
{
	int			n_digit;
	long int	n_bis;
	char		*itoa;
	int			counter;

	n_bis = n;
	n_digit = ft_n_digit(n);
	itoa = malloc(n_digit + 1);
	if (!itoa)
		return (NULL);
	counter = n_digit - 1;
	if (n_bis < 0)
	{
		itoa[0] = '-';
		n_bis = -n_bis;
	}
	ft_getnbr(itoa, n_bis, counter);
	itoa[n_digit] = '\0';
	return (itoa);
}

int	ft_n_digit(int n)
{
	int		n_digit;

	n_digit = 0;
	if (n <= 0)
		n_digit++;
	while (n != 0)
	{
		n /= 10;
		n_digit++;
	}
	if (!n_digit)
		n_digit++;
	return (n_digit);
}

void	ft_getnbr(char *itoa, unsigned int n, int counter)
{
	if (n / 10 > 0)
		ft_getnbr(itoa, n / 10, counter - 1);
	itoa[counter] = (n % 10) + '0';
}
