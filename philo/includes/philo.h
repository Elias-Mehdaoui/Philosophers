/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emehdaou <emehdaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 20:39:21 by emehdaou          #+#    #+#             */
/*   Updated: 2024/02/25 21:52:27 by emehdaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

#ifndef PHILO_H
# define PHILO_H


typedef struct s_philo
{
    int				id;
    int				time_to_die;
    int				time_to_eat;
    int				time_to_sleep;
    int				nb_eat;
    int				*eat_count;
    pthread_mutex_t	*fork_left;
    pthread_mutex_t	*fork_right;
    struct timeval	start;
    struct timeval	last_meal;
}				t_philo;

typedef struct s_data
{
    int				nb_philo;
    
    struct timeval	start;
}				t_data;

#endif