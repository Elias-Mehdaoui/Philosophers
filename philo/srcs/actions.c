/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emehdaou <emehdaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 00:42:02 by emehdaou          #+#    #+#             */
/*   Updated: 2024/02/29 03:29:05 by emehdaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->fork_left);
		print(philo, "has taken a fork");
		pthread_mutex_lock(philo->fork_right);
		print(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->fork_right);
		print(philo, "has taken a fork");
		pthread_mutex_lock(&philo->fork_left);
		print(philo, "has taken a fork");
	}
}

void	put_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_unlock(&philo->fork_left);
		pthread_mutex_unlock(philo->fork_right);
	}
	else
	{
		pthread_mutex_unlock(philo->fork_right);
		pthread_mutex_unlock(&philo->fork_left);
	}
}

int	eat(t_philo *philo)
{
	if (ft_is_dead(philo))
		return (1);
	if (philo->data->nb_philo == 1)
		return (1);
	take_forks(philo);
	if (ft_is_dead(philo))
	{
		
		pthread_mutex_unlock(philo->fork_right);
		pthread_mutex_unlock(&philo->fork_left);
		return (1);
	}
	print(philo, "is eating");
	usleep(philo->time_to_eat * 1000);
	put_forks(philo);
	pthread_mutex_lock(&philo->meal_lock);
	philo->last_meal = get_time(philo->data->start);
	pthread_mutex_unlock(&philo->meal_lock);
	pthread_mutex_lock(&philo->eat_lock);
	philo->eat_count++;
	pthread_mutex_unlock(&philo->eat_lock);
	if (check_eat_count(philo))
		return (1);
	return (0);
}

int	check_death2(t_data *data, int i)
{
	pthread_mutex_lock(&data->philo[i].meal_lock);
	if ((get_time(data->start)
			- data->philo[i].last_meal > data->philo[i].time_to_die))
	{
		pthread_mutex_unlock(&data->philo[i].meal_lock);
		pthread_mutex_lock(&data->dead);
		data->is_dead = 1;
		pthread_mutex_unlock(&data->dead);
		pthread_mutex_lock(&data->print);
		printf("%d %d %s\n", get_time(data->philo[i].start), data->philo[i].id,
			"died");
		pthread_mutex_unlock(&data->print);
		return (1);
	}
	pthread_mutex_unlock(&data->philo[i].meal_lock);
	return (0);
}

void	check_death(t_data *data)
{
	int	i;

	while (1)
	{
		usleep(10);
		i = -1;
		if (check_all_eat(data))
			return ;
		while (++i < data->nb_philo)
		{
			if (check_eat_count(&data->philo[i]))
				break ;
			if (check_death2(data, i))
				return ;
		}
	}
}
