/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_thread.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrun <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 17:30:06 by abrun             #+#    #+#             */
/*   Updated: 2021/11/04 13:18:10 by abrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*creation(void *ptr)
{
	t_philo			*philo;
	struct timeval	t0;
	struct timeval	t1;
	struct timeval	start;

	usleep(50000);
	philo = (t_philo *)ptr;
	gettimeofday(&start, NULL);
	philo->birth = ft_diff_time(philo->curr_t, start);
	gettimeofday(&t0, NULL);
	philo->sleep.c = 0;
	while (philo->die.c > 0)
	{
		gettimeofday(&t1, NULL);
		philo->die.c -= ft_diff_time(t0, t1);
		if (philo->eat.c > 0 && philo->die.c > 0)
			do_eat(t0, philo);
		else if (philo->sleep.c > 0 && philo->die.c > 0)
			do_sleep(t0, philo);
		if (philo->sleep.c <= 0 && !philo->eat.b
			&& !philo->think && philo->die.c > 0)
		{
			gettimeofday(&t1, NULL);
			printf("\033[0;31m");
			printf("\n%ld %s start thinking\n", ft_diff_time(philo->curr_t, t1),
				philo->name);
			philo->think = 1;
		}
		t0 = t1;
	}
	if (philo->die.c <= 0)
	{
		philo->die.c = t0.tv_sec * 1000 + t0.tv_usec / 1000
			- (start.tv_sec * 1000 + start.tv_usec / 1000);
		printf("\033[0;37m");
		printf("\n%ld %s died\n", philo->die.c, philo->name);
		philo->dead = 1;
	}
	free_params(philo);
	exit(0);
}

int	is_philo_dead(t_philo *philo)
{
	t_philo	*next;

	next = philo->next;
	while (next != philo)
	{
		if (next->dead)
			return (1);
		next = next->next;
	}
	return (0);
}
