/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrun <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 18:18:47 by abrun             #+#    #+#             */
/*   Updated: 2021/11/03 18:39:59 by abrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

typedef struct s_mut
{
	pthread_mutex_t		ex;
	pthread_t		thread;
	int				n;
	struct timeval	big;
}

void	*creat(void *ptr)
{
	t_mut	*mut;

	mut = (t_mut *)ptr;
	sleep(1);
}

int main(int ac, char **av)
{
	t_mut			mut[2];
	int				c;
	struct timeval	time;

	gettimeofday(&time, NULL);
	c = 0;
	while (c < 2)
	{
		mut[c].big = time;
		mut[c].name = ft_strjoin("philo", ft_itoa(c));
		if (!mut[c].name)
			return (3);
		pthread_mutex_init(&mut[c].ex, NULL);
		if (pthread_create(&mut[c].thread, NULL, creat, (void *)&mut[c]))
			return (4);
		c++;
	}
	c = 0;
	while (c < 2)
	{
		if (pthread_join(philo[c].thread, NULL))
			return (5);
		c++;
	}
	pthread_exit (NULL);
	c = 0;
	while (c < 2)
	{
		pthread_mutex_destroy(&mut[c].ex);
		c++;
	}
	return (0);
}
