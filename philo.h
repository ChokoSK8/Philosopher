/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrun <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 11:58:08 by abrun             #+#    #+#             */
/*   Updated: 2021/12/15 21:50:06 by abrun            ###   ########.fr       */
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

typedef struct s_task
{
	long int	t;
	long int	c;
	int			b;
	struct timeval	last;
}			t_task;

typedef struct s_param
{
	struct timeval	start;
	int				dead;
	int				meal;
	int				n_meal;
	int				all_m;
	int				n_ph;
	pthread_mutex_t	print;
	pthread_mutex_t	var;
	pthread_mutex_t	think;
	pthread_mutex_t	end;
}			t_param;

typedef struct s_philo
{
	pthread_t		thread;
	t_task			sleep;
	t_task			die;
	t_task			eat;
	char			*name;
	struct s_philo	*next;
	struct s_philo	*prev;
	pthread_mutex_t	fork;
	int				think;
	int				equip;
	int				meal;
	int				id;
	t_param			*g;
}			t_philo;

t_philo		*init_philo(int n_ph, int ac, char **av);

t_param		*init_param(int ac, char **av, int n_ph);

t_philo		fill_philo_parameters(char **av, int c, t_param *param);

t_philo		*assign_prev_next(t_philo *philo, int c, int n_ph);

void		*creation(void *ptr);

void		*exit_thread(t_philo *philo);

int			ft_isdigit(int c);

int			ft_atoi(const char *str);

long int	ft_diff_time(struct timeval t0, struct timeval t1);

void		print_msg(t_philo *philo, char *msg);

int			can_he_eats(int ph_meal, t_param *param);

void		do_eat(t_philo *philo);

void		do_sleep(t_philo *philo);

void		do_think(t_philo *philo);

int			do_death(t_philo *philo);

void		set_after_eat(t_philo *philo);

void		take_fork(t_philo *philo);

void		*creation(void *ptr);

char		*ft_strjoin(char const *s1, const char *s2);

size_t		ft_strlen(const char *s);

char		*ft_itoa(int n);

int			ft_n_digit(int n);

void		ft_getnbr(char *itoa, unsigned int n, int counter);

void		free_params(t_philo *philo);

void		free_init(t_philo *philo, int c);

int			ft_strncmp(const char *s1, const char *s2, size_t n);

int		ft_timer(long int timer, struct timeval t0, t_philo *philo);
#endif
