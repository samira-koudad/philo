/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoudad <skoudad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 20:05:08 by skoudad           #+#    #+#             */
/*   Updated: 2025/10/25 04:49:31 by skoudad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	is_nb(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (1);
		i++;
	}
	return (0);
}

int	valid_args(char **av)
{
	if (ft_atoi(av[1]) > PHILO_MAX || ft_atoi(av[1]) <= 0 || is_nb(av[1]) == 1)
		return (print_fd(ERR_PHILO, 2), 1);
	if (ft_atoi(av[2]) <= 0 || is_nb(av[2]) == 1)
		return (print_fd(ERR_T_DIE, 2), 1);
	if (ft_atoi(av[3]) <= 0 || is_nb(av[3]) == 1)
		return (print_fd(ERR_T_EAT, 2), 1);
	if (ft_atoi(av[4]) <= 0 || is_nb(av[4]) == 1)
		return (print_fd(ERR_T_SLP, 2), 1);
	if (av[5] && (ft_atoi(av[5]) < 0 || is_nb(av[5]) == 1))
		return (print_fd(ERR_NT_EAT, 2), 1);
	return (0);
}

int	main(int ac, char **av)
{
	t_program		program;
	t_philo			philos[PHILO_MAX];
	pthread_mutex_t	forks[PHILO_MAX];

	if (ac != 5 && ac != 6)
		return (print_fd(ERR_ARG, 2), 1);
	if (valid_args(av) == 1)
		return (1);
	init_program(&program, philos);
	init_forks(forks, ft_atoi(av[1]));
	init_philos(philos, &program, forks, av);
	thread_make(&program, forks);
	destroy_all(NULL, &program, forks);
	return (0);
}
