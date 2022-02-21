/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztune <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 17:27:39 by ztune             #+#    #+#             */
/*   Updated: 2021/10/22 17:27:41 by ztune            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>
# define TIME_MINUS 1645000000

int	g_programm_stop;
int	g_programm_stoptime;
int	g_programm_stopphilo;

typedef struct s_philo
{
	pthread_mutex_t	fork;
	pthread_mutex_t	*prev;
	int				ph_count;
	int				ph_num;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				time_start;
	int				eat_max;
	int				eat_i;
	int				eat_last;
}	t_philo;

//philo_threads.c
void	*ph_control_thread(void *ptr);
void	*ph_single_thread(void *ptr);

//philo_puts.c
int		ft_puterror(int code);
void	ft_print_mes(int time, t_philo *philo, char *text);

//philo_utils.c
int		ft_atoi(const char *str);
int		ft_time(void);
void	ft_usleep(int ms);

#endif
