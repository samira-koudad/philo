/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoudad <skoudad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 00:00:00 by samirakouda       #+#    #+#             */
/*   Updated: 2025/10/21 21:21:42 by skoudad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

# define PHILO_MAX 200

# define ERR_ALLOC "Allocating Error"
# define ERR_ARG "Wrong num of arguments"
# define ERR_PHILO "Invalid philo number"
# define ERR_T_DIE "Invalid time to die"
# define ERR_T_EAT "Invalid time to eat"
# define ERR_T_SLP "Invalid time to sleep"
# define ERR_NT_EAT "Invalid number of times each philosopher must eat"
# define ERR_IN_C "Invalid character input"
# define ERR_IN_V "Invalid value input"

# define ERR_TH "Failed to make threads"
# define ERR_JOIN "Failed to join threads"
# define ERR_INIT "Failed to initiate forks"

# define ERR_TIME "Failed to get current time"

# define TAKE_FORK "has taken a fork"
# define THINK "is thinking"
# define SLEEP "is sleeping"
# define EAT "is eating"
# define DIE "is died"

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	int				eating;
	int				meal_eaten;
	size_t			lst_meal;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			start_time;
	int				num_of_philos;
	int				nbt_eat;
	int				*dead;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*write_lock;
	pthread_mutex_t	*dead_lock;
	pthread_mutex_t	*meal_lock;
}	t_philo;

typedef struct s_program
{
	int				is_dead;
	pthread_mutex_t	write_lock;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	meal_lock;
	t_philo			*philos;
}	t_program;

int		is_nb(char *str);
int		valid_args(char **av);

void	init_input(t_philo *philo, char **av);
void	init_philos(t_philo *philos, t_program *program, pthread_mutex_t *forks,
			char **av);
void	init_forks(pthread_mutex_t *forks, int phili_nb);
void	init_program(t_program *program, t_philo *philos);

void	print_std(char *str, t_philo *philo, int id);
int		philo_dead(t_philo *philo, size_t time_to_die);
int		chk_dead(t_philo *philos);
int		chk_ate_all(t_philo *philo);
void	*monitor(void *ptr);

void	think(t_philo *philo);
void	dream(t_philo *philo);
void	eat(t_philo *philo);

int		dead_loop(t_philo *philo);
void	*philo_routine(void *ptr);
int		thread_make(t_program *program, pthread_mutex_t *forks);

int		print_fd(char *str, int fd);
void	destroy_all(char *s, t_program *program, pthread_mutex_t *forks);
int		ft_atoi(const char *nptr);
size_t	get_time(void);
int		ft_usleep(size_t millsec);

#endif
