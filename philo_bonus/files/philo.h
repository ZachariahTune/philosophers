/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztune <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 17:24:13 by ztune             #+#    #+#             */
/*   Updated: 2021/10/22 17:24:22 by ztune            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <semaphore.h>
# include <pthread.h>
# include <fcntl.h>
# include <signal.h>
# define TIME_MINUS 1635000000

int	g_process_stop;
int	g_success_print;

typedef struct s_philo
{
	pid_t	*pid;
	sem_t	*create;
	sem_t	*forks;
	sem_t	*stop;
	sem_t	*print;
	int		ph_count;
	int		ph_num;
	int		time_die;
	int		time_eat;
	int		time_sleep;
	int		time_start;
	int		eat_max;
	int		eat_i;
	int		eat_last;
}	t_philo;

//philo_funcs.c
void	ph_argv_checker(int argc, char **argv, int i, int j);
t_philo	*ph_philo_init(int argc, char **argv, int time_stamp);
void	*ph_philo_control(void *ptr);
void	*ph_die_stop(void *ptr);
void	ph_wait_processes(t_philo *philo, int i);

//philo_puts.c
void	ft_puterror(int code);
void	ft_print_mes(int time, t_philo *philo, char *text);

//philo_utils.c
int		ft_atoi(const char *str);
int		ft_time(void);
void	ft_usleep(int ms);
sem_t	*ft_sem_open(char *name, int start_value);

#endif
