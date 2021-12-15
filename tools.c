/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrun <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 17:31:39 by abrun             #+#    #+#             */
/*   Updated: 2021/12/15 21:32:53 by abrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long int	ft_diff_time(struct timeval t0, struct timeval t1)
{
	long int 	ret;

	ret = (t1.tv_sec * 1000 + t1.tv_usec / 1000
			- (t0.tv_sec * 1000 + t0.tv_usec / 1000));
	return (ret);
}

int	ft_timer(long int timer, struct timeval t0, t_philo *phi)
{
	struct timeval	t1;

	gettimeofday(&t1, NULL);
	while (ft_diff_time(t0, t1) < timer)
	{
		gettimeofday(&t1, NULL);
		if (ft_diff_time(phi->eat.last, t1) >= phi->die.t)
		{
			phi->die.c = 0;
			return (0);
		}
	}
	return (1);
}

void	print_msg(t_philo *philo, char *msg)
{
	struct timeval	t1;
	static int		ret = 0;

	pthread_mutex_lock(&philo->g->print);
	if (!ret)
	{
		gettimeofday(&t1, NULL);
		printf("\n            %ld %s %s\n",
			ft_diff_time(philo->g->start, t1), philo->name, msg);
		if (!ft_strncmp(msg, "died", 4))
			ret = 1;
	}
	pthread_mutex_unlock(&philo->g->print);
}

int	can_he_eats(int ph_meal, t_param *param)
{
	double	ret;

	pthread_mutex_lock(&param->var);
	ret = (double)(param->all_m) / (double)param->n_ph;
	pthread_mutex_unlock(&param->var);
	if ((double)ph_meal <= ret)
		return (1);
	return (0);
}
