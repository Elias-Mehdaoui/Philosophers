/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emehdaou <emehdaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 00:42:02 by emehdaou          #+#    #+#             */
/*   Updated: 2024/02/27 05:59:59 by emehdaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int eat(t_philo *philo)
{

    if (ft_is_dead(philo))
        return (1);
    pthread_mutex_lock(&philo->fork_left);
    print(philo, "has taken a fork");
    pthread_mutex_lock(philo->fork_right);
    print(philo, "has taken a fork");
    print(philo, "is eating");
    usleep(philo->time_to_eat * 1000);
    pthread_mutex_unlock(philo->fork_right);
    pthread_mutex_unlock(&philo->fork_left);
    pthread_mutex_lock(&philo->meal_lock);
    philo->last_meal = get_time(philo->start);
    pthread_mutex_unlock(&philo->meal_lock);
    philo->eat_count++;
    return (0);
}

void check_death(t_death *death)
{
    int i;
    while(1)
    {
        i = 0;
        while(i < death->data->nb_philo)
        {
            pthread_mutex_lock(&death->data->philo[i].meal_lock);
            if (get_time(death->data->start) - death->data->philo[i].last_meal > death->data->philo[i].time_to_die)
            {
                pthread_mutex_unlock(&death->data->philo[i].meal_lock);
                pthread_mutex_lock(&death->data->dead);
                death->data->is_dead = 1;
                pthread_mutex_unlock(&death->data->dead);
                pthread_mutex_lock(&death->data->print);
                printf("%d %d %s\n", get_time(death->data->philo[i].start), death->data->philo[i].id, "died");
                pthread_mutex_unlock(&death->data->print);
                return ;
            }
            pthread_mutex_unlock(&death->data->philo[i].meal_lock);
            i++;
        }
    }
}