/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_tasks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrun <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 17:31:16 by abrun             #+#    #+#             */
/*   Updated: 2021/11/03 18:04:05 by abrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	do_eat(struct timeval t0, struct timeval t1, t_philo *philo)
{
	if (!philo->eat.b)
	{
		printf("%ld %s start eating\n", ft_diff_time(philo->curr_t, t1),
				philo->name);
		philo->eat.b = 1;
	}
	philo->eat.c -= ft_diff_time(t0, t1);
	if (philo->eat.c <= 0)
	{
		philo->sleep.c = philo->sleep.t;
		philo->die.c = philo->die.t;
		philo->sleep.b = 0;
	}
}

void	do_sleep(struct timeval t0, struct timeval t1, t_philo *philo)
{
	if (!philo->sleep.b)
	{
		printf("%ld %s start sleeping\n", ft_diff_time(philo->curr_t, t1),
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
