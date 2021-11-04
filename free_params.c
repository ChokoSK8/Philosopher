/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_params.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrun <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 13:13:39 by abrun             #+#    #+#             */
/*   Updated: 2021/11/04 13:17:24 by abrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_params(t_philo *philo)
{
	t_philo		*next;

	next = philo->next;
	while (next != philo)
	{
		free(next->name);
		next = next->next;
	}
	free(next->name);
}
