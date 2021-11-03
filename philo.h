/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrun <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 11:58:08 by abrun             #+#    #+#             */
/*   Updated: 2021/11/03 18:18:38 by abrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_time
{
	long int	sec;
	long int	usec;
}			t_time;

typedef struct s_task
{
	long int	t;
	long int	c;
	int			b;
}			t_task;

typedef struct s_philo
{
	pthread_t		thread;
	t_task			sleep;
	t_task			die;
	t_task			eat;
	long int		birth;
	struct timeval	curr_t;
	t_time			start;
	char			*name;
}			t_philo;

t_philo		fill_philo_parameters(char **av);

void		*creation(void *ptr);

int			ft_isdigit(int c);

int			ft_atoi(const char *str);

t_philo		fill_philo_parameters(char **av);

long int	ft_diff_time(struct timeval t0, struct timeval t1);

void		do_eat(struct timeval t0, struct timeval t1, t_philo *philo);

void		do_sleep(struct timeval t0, struct timeval t1, t_philo *philo);

void		*creation(void *ptr);

char		*ft_strjoin(char const *s1, const char *s2);

size_t		ft_strlen(const char *s);

char		*ft_itoa(int n);

int			ft_n_digit(int n);

void		ft_getnbr(char *itoa, unsigned int n, int counter);
#endif
