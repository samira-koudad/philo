/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoudad <skoudad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 15:00:08 by skoudad           #+#    #+#             */
/*   Updated: 2025/10/25 05:05:01 by skoudad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	destroy_all(char *s, t_program *program, pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	print_fd(s, 2);
	pthread_mutex_destroy(&program->write_lock);
	pthread_mutex_destroy(&program->meal_lock);
	pthread_mutex_destroy(&program->dead_lock);
	while (i < program->philos[0].num_of_philos)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
}

int	ft_atoi(const char *nptr)
{
	size_t	i;
	size_t	n;
	int		sign;

	i = 0;
	n = 0;
	sign = 1;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == 32)
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			sign = -1;
		i++;
	}
	while (nptr[i] && (nptr[i] >= '0' && nptr[i] <= '9'))
	{
		n = (n * 10) + (nptr[i] - '0');
		i++;
	}
	return (n * sign);
}

size_t	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		return (print_fd(ERR_TIME, 2), 1);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	ft_usleep(size_t millsec)
{
	size_t	start;

	start = get_time();
	while ((get_time() - start) < millsec)
		usleep(100);
	return (0);
}

int	print_fd(char *str, int fd)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
	{
		write(fd, &str[i], 1);
		i++;
	}
	write(fd, "\n", 1);
	return (1);
}
