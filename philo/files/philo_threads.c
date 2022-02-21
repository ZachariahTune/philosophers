/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_threads.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztune <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 17:28:01 by ztune             #+#    #+#             */
/*   Updated: 2021/10/22 17:28:03 by ztune            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//Контроль питания и смертей философов
static void	ph_philos_control(t_philo *philos, int i, int eat_stop, int t_start)
{
	while (g_programm_stop == 0)
	{
		i = -1;
		eat_stop = 0;
		while (++i < philos[0].ph_count)
		{
			if (ft_time() - philos[i].eat_last >= philos[i].time_die)
			{
				g_programm_stop = 1;
				g_programm_stoptime = ft_time() - t_start;
				g_programm_stopphilo = philos[i].ph_num;
				break ;
			}
			if (philos[i].eat_max > 0 && philos[i].eat_i >= philos[i].eat_max)
				eat_stop++;
		}
		if (eat_stop == philos[0].ph_count)
		{
			g_programm_stop = 1;
			g_programm_stoptime = ft_time() - t_start;
			break ;
		}
		ft_usleep(9);
	}
}

//Создание параллельного потока для контроля философов
void	*ph_control_thread(void *ptr)
{
	t_philo	*philos;

	philos = (t_philo *)ptr;
	ph_philos_control(philos, -1, 0, philos[0].time_start);
	return (NULL);
}

//Перечисление действий одного философа
static void	ph_single_actions(t_philo *philo)
{
	if (philo->ph_num % 2 == 0)
	{
		pthread_mutex_lock(&philo->fork);
		ft_print_mes(ft_time(), philo, "has taken a fork (r)");
	}
	pthread_mutex_lock(philo->prev);
	ft_print_mes(ft_time(), philo, "has taken a fork (l)");
	if (philo->ph_num % 2 == 1)
	{
		pthread_mutex_lock(&philo->fork);
		ft_print_mes(ft_time(), philo, "has taken a fork (r)");
	}
	philo->eat_last = ft_time();
	ft_print_mes(ft_time(), philo, "is eating");
	ft_usleep(philo->time_eat);
	pthread_mutex_unlock(&philo->fork);
	pthread_mutex_unlock(philo->prev);
	philo->eat_i++;
	ft_print_mes(ft_time(), philo, "is sleeping");
	ft_usleep(philo->time_sleep);
	ft_print_mes(ft_time(), philo, "is thinking");
}

//Запуск действий отдельно взятого философа
void	*ph_single_thread(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	if (philo->ph_num % 2 == 1)
		ft_usleep((double)philo->time_eat * 0.9);
	while (g_programm_stop == 0 && philo->ph_count > 1)
	{
		ph_single_actions(philo);
		ft_usleep((double)(philo->time_die
				- philo->time_eat - philo->time_sleep) / 2);
	}
	return (NULL);
}
