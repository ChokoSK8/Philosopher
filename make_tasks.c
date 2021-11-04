/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_tasks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrun <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 17:31:16 by abrun             #+#    #+#             */
/*   Updated: 2021/11/04 13:13:02 by abrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	do_eat(struct timeval t0, t_philo *philo)
{
	struct timeval	t1;

	gettimeofday(&t1, NULL);
	if (!philo->eat.b)
	{
		pthread_mutex_lock(&philo->mex);
		pthread_mutex_lock(&philo->next->mex);
		philo->think = 0;
		printf("\033[0;32m");
		printf("\n%ld %s start eating\n", ft_diff_time(philo->curr_t, t1),
			philo->name);
		philo->eat.b = 1;
	}
	philo->eat.c -= ft_diff_time(t0, t1);
	if (philo->eat.c <= 0)
	{
		philo->sleep.c = philo->sleep.t;
		philo->die.c = philo->die.t;
		philo->sleep.b = 0;
		pthread_mutex_unlock(&philo->mex);
		pthread_mutex_unlock(&philo->next->mex);
	}
}

void	do_sleep(struct timeval t0, t_philo *philo)
{
	struct timeval	t1;

	gettimeofday(&t1, NULL);
	if (!philo->sleep.b)
	{
		printf("\033[0;33m");
		printf("\n%ld %s start sleeping\n", ft_diff_time(philo->curr_t, t1),
			philo->name);
		philo->sleep.b = 1;
	}
	philo->sleep.c -= ft_diff_time(t0, t1);
	if (philo->sleep.c <= 0)
	{
		philo->eat.c = philo->eat.t;
		philo->eat.b = 0;
	}
}
