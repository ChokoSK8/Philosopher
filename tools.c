/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrun <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 17:31:39 by abrun             #+#    #+#             */
/*   Updated: 2021/11/04 18:41:59 by abrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long int	ft_diff_time(struct timeval t0, struct timeval t1)
{
	long int	ret;

	ret = (t1.tv_sec * 1000 + t1.tv_usec / 1000
			- (t0.tv_sec * 1000 + t0.tv_usec / 1000));
	return (ret);
}

void	print_msg(t_philo *philo, char *msg)
{
	struct timeval	t1;

	pthread_mutex_lock(&philo->g->print);
	gettimeofday(&t1, NULL);
//	printf("\033[0;31m");
	printf("\n%ld %s %s\n",
		ft_diff_time(philo->g->start, t1), philo->name, msg);
	pthread_mutex_unlock(&philo->g->print);
}
