/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emehdaou <emehdaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 00:36:55 by emehdaou          #+#    #+#             */
/*   Updated: 2024/08/29 19:03:08 by emehdaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	check_eat_count(t_philo *philo)
{
	pthread_mutex_lock(&philo->eat_lock);
	if (philo->goal_eat != -1 && philo->eat_count == philo->goal_eat)
	{
		pthread_mutex_lock(&philo->data->all_eat_lock);
		philo->data->all_eat++;
		pthread_mutex_unlock(&philo->data->all_eat_lock);
		pthread_mutex_unlock(&philo->eat_lock);
		return (1);
	}
	pthread_mutex_unlock(&philo->eat_lock);
	return (0);
}

int	check_all_eat(t_data *data)
{
	pthread_mutex_lock(&data->all_eat_lock);
	if (data->all_eat != -1 && data->all_eat == data->nb_philo)
	{
		pthread_mutex_unlock(&data->all_eat_lock);
		return (1);
	}
	pthread_mutex_unlock(&data->all_eat_lock);
	return (0);
}

void	ft_odd(t_data *data)
{
	if (data->philo[0].time_to_eat >= data->philo[0].time_to_sleep)
		usleep((data->philo[0].time_to_eat - data->philo[0].time_to_sleep)
			* 1000);
	usleep(500);
}

void	routine(t_philo *philo)
{
	// if (philo->id % 2 == 1)
	// 	usleep(100);
	while (1)
	{
		if (philo->id % 2 == 1)
			ft_odd(philo->data);
		if (eat(philo))
			return ;
		if (print(philo, "is sleeping"))
			return ;
		usleep(philo->time_to_sleep * 1000);
		if (print(philo, "is thinking"))
			return ;
	}
}
