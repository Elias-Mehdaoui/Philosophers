/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emehdaou <emehdaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 19:27:30 by emehdaou          #+#    #+#             */
/*   Updated: 2024/02/28 23:51:44 by emehdaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	check_args(int argc, char **argv)
{
	int		i;
	int		j;
	long	res;

	i = 1;
	res = 0;
	while (i < argc)
	{
		j = 0;
		res = 0;
		while (argv[i][j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
				return (12);
			res = res * 10 + (argv[i][j] - '0');
			if (res > 2147483647)
				return (13);
			j++;
		}
		i++;
		if (res < 1)
			return (1);
	}
	return (0);
}

void	ft_init(t_philo *philo, t_data *data, int argc, char **argv)
{
	int	i;

	i = -1;
	pthread_mutex_init(&data->print, NULL);
	gettimeofday(&data->start, NULL);
	while (++i < data->nb_philo)
	{
		philo[i].id = i + 1;
		philo[i].time_to_die = ft_atoi(argv[2]);
		philo[i].time_to_eat = ft_atoi(argv[3]);
		philo[i].time_to_sleep = ft_atoi(argv[4]);
		philo[i].start = data->start;
		pthread_mutex_init(&philo[i].fork_left, NULL);
		pthread_mutex_init(&philo[i].meal_lock, NULL);
		pthread_mutex_init(&philo[i].eat_lock, NULL);
		if (data->nb_philo > 1)
			philo[i].fork_right = &philo[(i + 1) % data->nb_philo].fork_left;
		philo[i].data = data;
		if (argc == 6)
			philo[i].goal_eat = ft_atoi(argv[5]);
		else
			philo[i].goal_eat = -1;
		philo[i].eat_count = 0;
		philo[i].last_meal = 0;
	}
}

void	init_thread(t_death *death, t_philo *philo, t_data *data)
{
	int	i;

	i = -1;
	pthread_create(&death->thread, NULL, (void *)check_death, data);
	while (++i < data->nb_philo)
	{
		pthread_create(&philo[i].thread, NULL, (void *)routine, &philo[i]);
	}
	i = -1;
	while (++i < data->nb_philo)
		pthread_join(philo[i].thread, NULL);
	pthread_join(death->thread, NULL);
}

int	main(int argc, char **argv)
{
	t_data	data;
	t_philo	*philo;
	t_death	death;
	int		i;

	if (argc < 5 || argc > 6 || check_args(argc, argv))
		return (printf("Error \n"), 1);
	i = -1;
	memset(&data, 0, sizeof(t_data));
	if (argc != 6)
		data.all_eat = -1;
	if (data.nb_philo == 1)
		data.is_dead = 1;
	data.nb_philo = ft_atoi(argv[1]);
	philo = malloc(sizeof(t_philo) * data.nb_philo);
	if (!philo)
		return (1);
	data.philo = philo;
	pthread_mutex_init(&data.dead, NULL);
	death.data = &data;
	pthread_mutex_init(&data.all_eat_lock, NULL);
	ft_init(philo, &data, argc, argv);
	init_thread(&death, data.philo, &data);
	ft_free(&data, philo);
	return (0);
}
