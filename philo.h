/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrun <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 11:58:08 by abrun             #+#    #+#             */
/*   Updated: 2021/11/04 18:41:57 by abrun            ###   ########.fr       */
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

typedef struct s_param
{
	struct timeval	start;
	int				dead;
	pthread_mutex_t	print;
}			t_param;

typedef struct s_philo
{
	pthread_t		thread;
	t_task			sleep;
	t_task			die;
	t_task			eat;
	t_time			start;
	char			*name;
	struct s_philo	*next;
	pthread_mutex_t	fork;
	int				think;
	int				equip;
	t_param			*g;
}			t_philo;

t_philo		*init_philo(int n_ph, char **av);

t_param		*init_param(void);

t_philo		fill_philo_parameters(char **av);

void		*creation(void *ptr);

int			ft_isdigit(int c);

int			ft_atoi(const char *str);

t_philo		fill_philo_parameters(char **av);

long int	ft_diff_time(struct timeval t0, struct timeval t1);

void		print_msg(t_philo *philo, char *msg);

void		do_eat(struct timeval t0, t_philo *philo);

void		do_sleep(struct timeval t0, t_philo *philo);

void		do_think(t_philo *philo);

int			equip_fork(t_philo *philo, int ret);

void		*creation(void *ptr);

char		*ft_strjoin(char const *s1, const char *s2);

size_t		ft_strlen(const char *s);

char		*ft_itoa(int n);

int			ft_n_digit(int n);

void		ft_getnbr(char *itoa, unsigned int n, int counter);

void		free_params(t_philo *philo);
#endif
