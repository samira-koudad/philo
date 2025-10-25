/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoudad <skoudad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 19:40:04 by skoudad           #+#    #+#             */
/*   Updated: 2025/10/25 05:04:48 by skoudad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	*monitor(void *ptr)
{
	t_philo	*philos;

	philos = (t_philo *)ptr;
	while (1)
		if (chk_dead(philos) == 1 || chk_ate_all(philos) == 1)
			break ;
	return (ptr);
}

int	chk_dead(t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philos[0].num_of_philos)
	{
		if (philo_dead(&philos[i], philos[i].time_to_die))
		{
			print_std(DIE, &philos[i], philos[i].id);
			pthread_mutex_lock(philos->dead_lock);
			*philos->dead = 1;
			pthread_mutex_unlock(philos->dead_lock);
			return (1);
		}
		i++;
	}
	return (0);
}

int	philo_dead(t_philo *philo, size_t time_to_die)
{
	pthread_mutex_lock(philo->meal_lock);
	if (get_time() - philo->lst_meal >= time_to_die && philo->eating == 0)
		return (pthread_mutex_unlock(philo->meal_lock), 1);
	pthread_mutex_unlock(philo->meal_lock);
	return (0);
}

void	print_std(char *str, t_philo *philo, int id)
{
	size_t	time;

	pthread_mutex_lock(philo->write_lock);
	time = get_time() - philo->start_time;
	if (!dead_loop(philo))
		printf("%zu %d %s\n", time, id, str);
	pthread_mutex_unlock(philo->write_lock);
}

int	chk_ate_all(t_philo *philos)
{
	int	i;
	int	ate;

	i = 0;
	ate = 0;
	if (philos[0].nbt_eat == -1)
		return (0);
	while (i < philos[0].num_of_philos)
	{
		pthread_mutex_lock(philos[i].meal_lock);
		if (philos[i].meal_eaten >= philos[i].nbt_eat)
			ate++;
		pthread_mutex_unlock(philos[i].meal_lock);
		i++;
	}
	if (ate == philos[0].num_of_philos)
	{
		pthread_mutex_lock(philos->dead_lock);
		*philos->dead = 1;
		pthread_mutex_unlock(philos->dead_lock);
		return (1);
	}
	return (0);
}
