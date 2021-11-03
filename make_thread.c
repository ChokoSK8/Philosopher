/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_thread.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrun <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 17:30:06 by abrun             #+#    #+#             */
/*   Updated: 2021/11/03 18:00:14 by abrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*creation(void *ptr)
{
	t_philo			*philo;
	struct timeval	t0;
	struct timeval	t1;
	struct timeval	start;

	philo = (t_philo *)ptr;
	gettimeofday(&start, NULL);
	philo->birth = ft_diff_time(philo->curr_t, start);
	printf("philo->birth : %ld\n", philo->birth);
	gettimeofday(&t0, NULL);
	philo->sleep.c = 0;
	while (philo->die.c > 0)
	{
		gettimeofday(&t1, NULL);
		philo->die.c -= ft_diff_time(t0, t1);
		if (philo->eat.c > 0)
			do_eat(t0, t1, philo);
		else if (philo->sleep.c > 0)
			do_sleep(t0, t1, philo);
		t0 = t1;
	}
	philo->die.c = t0.tv_sec * 1000 + t0.tv_usec / 1000
		- (start.tv_sec * 1000 + start.tv_usec / 1000);
	printf("%ld philo died\n", philo->die.c);
	return (NULL);
}

t_philo	fill_philo_parameters(char **av)
{
	t_philo	philo;

	philo.sleep.t = ft_atoi(av[4]);
	philo.sleep.c = ft_atoi(av[4]);
	philo.sleep.b = 0;
	philo.eat.t = ft_atoi(av[3]);
	philo.eat.c = ft_atoi(av[3]);
	philo.eat.b = 0;
	philo.die.t = ft_atoi(av[2]);
	philo.die.c = ft_atoi(av[2]);
	return (philo);
}
