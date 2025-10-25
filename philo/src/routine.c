/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoudad <skoudad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 09:50:00 by skoudad           #+#    #+#             */
/*   Updated: 2025/10/25 04:49:38 by skoudad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	eat(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	print_std(TAKE_FORK, philo, philo->id);
	if (philo->num_of_philos == 1)
	{
		ft_usleep(philo->time_to_die);
		pthread_mutex_unlock(philo->r_fork);
		return ;
	}
	pthread_mutex_lock(philo->l_fork);
	print_std(TAKE_FORK, philo, philo->id);
	philo->eating = 1;
	print_std(EAT, philo, philo->id);
	pthread_mutex_lock(philo->meal_lock);
	philo->lst_meal = get_time();
	philo->meal_eaten++;
	pthread_mutex_unlock(philo->meal_lock);
	ft_usleep(philo->time_to_eat);
	philo->eating = 0;
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

void	think(t_philo *philo)
{
	print_std(THINK, philo, philo->id);
}

void	dream(t_philo *philo)
{
	print_std(SLEEP, philo, philo->id);
	ft_usleep(philo->time_to_sleep);
}
