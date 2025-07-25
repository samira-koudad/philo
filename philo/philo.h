/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoudad <skoudad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 19:58:02 by skoudad           #+#    #+#             */
/*   Updated: 2025/07/25 20:17:22 by skoudad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

#include "libft/libft.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <pthread.h>
#include <sys/time.h>

typedef struct s_data
{
	int philo_nbr;
	int time_die;
	int time_eat;
	int time_sleep;
	int eating_times;
	struct timeval	routine_start;
	pthread_mutex_t	print;
} t_data ;

typedef struct s_philo
{
	t_data	*data;
	int	id;
	int	nbr_eat;
	struct timeval	last_eat_time;
	pthread_mutex_t	fork;
	struct s_philo	*right_philo;
	pthread_t thread;
} t_philo ;
void	thread_launch(t_philo *philo, t_data *data);

#endif
