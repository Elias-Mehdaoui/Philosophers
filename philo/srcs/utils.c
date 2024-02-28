/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emehdaou <emehdaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 00:21:48 by emehdaou          #+#    #+#             */
/*   Updated: 2024/02/28 04:45:06 by emehdaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	get_time(struct timeval start)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	return ((now.tv_sec * 1000 + now.tv_usec / 1000) - (start.tv_sec * 1000
			+ start.tv_usec / 1000));
}

int	print(t_philo *philo, char *str)
{
	if (ft_is_dead(philo))
		return (1);
	pthread_mutex_lock(&(philo->data->print));
	printf("%d %d %s\n", get_time(philo->start), philo->id, str);
	pthread_mutex_unlock(&(philo->data->print));
	return (0);
}

int	ft_is_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->dead);
	if (philo->data->is_dead)
	{
		pthread_mutex_unlock(&philo->data->dead);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->dead);
	return (0);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	neg;
	int	result;

	i = 0;
	neg = 1;
	result = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			neg = -1;
		i++;
	}
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
		result = result * 10 + (str[i++] - '0');
	return (result * neg);
}

void	ft_free(t_data *data, t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < data->nb_philo)
	{
		pthread_mutex_destroy(&philo[i].fork_left);
		pthread_mutex_destroy(&philo[i].meal_lock);
		pthread_mutex_destroy(&philo[i].eat_lock);
	}
	pthread_mutex_destroy(&data->print);
	pthread_mutex_destroy(&data->dead);
	pthread_mutex_destroy(&data->all_eat_lock);
	free(data->philo);
}
