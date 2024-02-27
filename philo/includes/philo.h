/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emehdaou <emehdaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 20:39:21 by emehdaou          #+#    #+#             */
/*   Updated: 2024/02/27 06:00:05 by emehdaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>

#ifndef PHILO_H
# define PHILO_H

typedef struct s_data	t_data;

typedef struct s_death
{
	pthread_t			thread;
	t_data				*data;
}						t_death;

typedef struct s_philo
{
	int					id;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					nb_eat;
	int					eat_count;
	pthread_mutex_t fork_left;   //
	pthread_mutex_t *fork_right; // philo->next->fork_left
    pthread_mutex_t     meal_lock;
	pthread_t			thread;
	struct timeval		start;
	long				last_meal;
	t_data				*data;
}						t_philo;

typedef struct s_data
{
	int					nb_philo;
	int					is_dead;
	pthread_mutex_t		print;
    pthread_mutex_t     dead;
    t_philo				*philo;
	struct timeval		start;
}						t_data;

int	print(t_philo *philo, char *str);
int						ft_atoi(const char *str);
void					routine(t_philo *philo);
int					eat(t_philo *philo);
int						get_time(struct timeval start);
void check_death(t_death *death);
int ft_is_dead(t_philo *philo);


#endif