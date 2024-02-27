/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emehdaou <emehdaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 00:36:55 by emehdaou          #+#    #+#             */
/*   Updated: 2024/02/27 06:00:39 by emehdaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void   routine(t_philo *philo)
{
    while(1)
    {
        eat(philo);
        if (philo->nb_eat != -1 && philo->eat_count == philo->nb_eat)
            return ;
        if (print(philo, "is sleeping"))
            return ;
        usleep(philo->time_to_sleep * 1000);
        if (print(philo, "is thinking"))
            return ; 
    }
}