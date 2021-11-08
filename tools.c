/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrun <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 17:31:39 by abrun             #+#    #+#             */
/*   Updated: 2021/11/08 14:11:04 by abrun            ###   ########.fr       */
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
	printf("\n            %ld %s %s\n",
		ft_diff_time(philo->g->start, t1), philo->name, msg);
	pthread_mutex_unlock(&philo->g->print);
}

int	can_he_eats(int ph_meal, t_param *param)
{
	double	ret;

	usleep(100);
	pthread_mutex_lock(&param->var);
	ret = (double)(param->all_m) / (double)param->n_ph;
	pthread_mutex_unlock(&param->var);
	if ((double)ph_meal <= ret)
		return (1);
	return (0);
}
