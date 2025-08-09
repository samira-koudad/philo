/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoudad <skoudad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 00:00:00 by skoudad           #+#    #+#             */
/*   Updated: 2025/08/09 21:14:14 by skoudad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_int(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= 9))
			return (0);
		i++;
	}
	return (1);
}

int init_params(int ac, char **av, t_data *data)
{
	int	i;

	i = 1;
	while (av[i])
	{
		if (is_int(av[i++]))
			return (0);
	}

	data->philo_nbr = ft_atoi(av[1]);
	data->time_die = ft_atoi(av[2]);
	data->time_eat = ft_atoi(av[3]);
	data->time_sleep = ft_atoi(av[4]);
	data->eating_times = (int)2147483647;
	if (ac == 6)
		data->eating_times = ft_atoi(av[5]);
	if (data->philo_nbr < 1 || data->time_die <= 0 || data->time_eat <= 0
		|| data->time_sleep <= 0 || (ac == 6 && data->eating_times <= 0))
		return (0);
	return (1);
}

t_philo	*init_philo(t_data *data)
{
	t_philo	*philo;
	int		i;

	philo = malloc(sizeof(t_philo) * data->philo_nbr);
	if (!philo)
		return (NULL);
	pthread_mutex_init(&data->print, NULL);
	i = 0;
	while (i < data->philo_nbr)
	{
		philo[i].id = i;
		philo[i].nbr_eat = 0;
		gettimeofday(&philo[i].last_eat_time, NULL);
		pthread_mutex_init(&philo[i].fork, NULL);
		philo[i].data = data;
		philo[i].right_philo = &philo[(i + 1) % data->philo_nbr];
		i++;
	}
	return (philo);
}

void	ft_message(t_philo *philo, char *msg)
{
	pthread_mutex_lock(&(philo->data->print));

	printf("%d %s\n", philo->id, msg);
	pthread_mutex_unlock(&(philo->data->print));
}

int	get_time(struct timeval *begin)
{
	struct timeval diff_time;

	gettimeofday(&diff_time, NULL);
	return ((1e3 * ((&diff_time)->tv_sec - begin->tv_sec))
		+ (1e-3 * ((&diff_time)->tv_usec - begin->tv_usec)));
}

void	custom_pause(int pause_time)
{
	struct timeval	begin;

	gettimeofday(&begin, NULL);
	while (get_time(&begin) < pause_time)
	{
		usleep(200);
	}
}

void	eat(t_philo *philo)
{
	if (philo->id % 2) // si pair
		pthread_mutex_lock(&philo->fork); // prend fork face
	else
		pthread_mutex_lock(&philo->right_philo->fork); // prend fork droite
	ft_message(philo, "has taken a fork");
	if (philo->id % 2) // si pair
		pthread_mutex_lock(&philo->right_philo->fork); // prend fork droite
	else
		pthread_mutex_lock(&philo->fork); // prend fork face
	ft_message(philo, "has taken a fork");

	ft_message(philo, "is eating");
	gettimeofday(&philo->last_eat_time, NULL);
	custom_pause(philo->data->time_eat);

	pthread_mutex_unlock(&philo->fork);
	pthread_mutex_unlock(&philo->right_philo->fork);

	philo->nbr_eat++;

}

void	*routine(void *ptr)
{
	t_philo	*philo = ptr;

	// if (philo->id % 2)
	// 	custom_pause(philo->data->time_die / 2);
	while(1)
	{
		ft_message(philo, "message");
		// eat(philo);
		// ft_message(philo, "is sleeping");
		// ft_message(philo, "is thinking");
	}
	return (NULL);
}


void	print_data_philo(t_philo *philo)
{
	t_data *data = philo->data;

	printf("Data:\n");
	printf("  philo_nbr: %d\n", data->philo_nbr);
	printf("  time_die: %d\n", data->time_die);
	printf("  time_eat: %d\n", data->time_eat);
	printf("  time_sleep: %d\n", data->time_sleep);
	printf("  eating_times: %d\n", data->eating_times);

	printf("Philo:\n");
	printf("  id: %d\n", philo->id);
	printf("  nbr_eat: %d\n", philo->nbr_eat);
	printf("  last_eat_time: %ld.%06ld\n", philo->last_eat_time.tv_sec, (long)philo->last_eat_time.tv_usec);
	printf("  right_philo id: %d\n", philo->right_philo->id);
}


void	thread_launch(t_philo *philo, t_data *data)
{
	int	count;

	count = 0;
	gettimeofday(&data->routine_start, NULL);
	while (count < data->philo_nbr)
	{
		// printf("%d id\n", count);
		// print_data_philo(&philo[count]);
		if (pthread_create(&philo[count].thread, NULL, &routine, &philo[count]))
			return;
		// sleep(1);
		count++;
	}
	count = 0;
	while (count < data->philo_nbr)
	{
		pthread_join(philo[count].thread, NULL);
		count++;
	}

}

int main(int ac, char **av)
{
	t_data	data;
	t_philo	*philo;

	if (ac < 5 || ac > 6)
		return (1);
	if (!init_params(ac, av, &data))
		return (write(2, "Error\n", 6), 1);
	philo = init_philo(&data);
	if (!philo)
		return (1);
	thread_launch(philo, &data);
	return (0);

}
