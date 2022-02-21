/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_funcs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztune <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 17:25:26 by ztune             #+#    #+#             */
/*   Updated: 2021/10/22 17:25:28 by ztune            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//Проверка переданных параметров на корректность
void	ph_argv_checker(int argc, char **argv, int i, int j)
{
	if (argc < 5 || argc > 6)
		ft_puterror(1);
	while (i < argc)
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
				ft_puterror(2);
			j++;
		}
		if (ft_atoi(argv[i]) == 0)
			ft_puterror(3);
		i++;
	}
	if (ft_atoi(argv[1]) > 200)
		ft_puterror(5);
}

//Инициализация стартового философа
t_philo	*ph_philo_init(int argc, char **argv, int time_stamp)
{
	t_philo	*philo;

	philo = (t_philo *)malloc(sizeof(t_philo));
	if (philo == NULL)
		ft_puterror(6);
	philo->ph_count = ft_atoi(argv[1]);
	philo->time_die = ft_atoi(argv[2]);
	philo->time_eat = ft_atoi(argv[3]);
	philo->time_sleep = ft_atoi(argv[4]);
	philo->time_start = time_stamp;
	philo->eat_last = time_stamp;
	philo->eat_max = 0;
	if (argc == 6)
		philo->eat_max = ft_atoi(argv[5]);
	philo->eat_i = 0;
	return (philo);
}

//Параллельный поток внутри процесса для ожидания смерти или наетости
void	*ph_philo_control(void *ptr)
{
	t_philo	*philo;
	int		printf_time;

	philo = (t_philo *)ptr;
	while (1 == 1)
	{
		if (ft_time() - philo->eat_last >= philo->time_die)
		{
			sem_wait(philo->print);
			printf_time = ft_time() - philo->time_start;
			printf("%d %d died\n", printf_time, philo->ph_num);
			sem_post(philo->stop);
		}
		if (philo->eat_max > 0 && philo->eat_i == philo->eat_max)
		{
			g_process_stop = 1;
			break ;
		}
		ft_usleep(9);
	}
	return (NULL);
}

//Параллельный поток для остановки процессов в случае чьей-то смерти
void	*ph_die_stop(void *ptr)
{
	t_philo	*philo;
	int		i;

	philo = (t_philo *)ptr;
	sem_wait(philo->stop);
	g_success_print = 0;
	i = -1;
	while (++i < philo->ph_count)
		kill(philo->pid[i], SIGKILL);
	return (NULL);
}

//Ожидание завершения всех процессов в случае успеха
void	ph_wait_processes(t_philo *philo, int i)
{
	int		printf_time;

	while (++i < philo->ph_count)
		waitpid(-1, NULL, 0);
	if (g_success_print == 1)
	{
		printf_time = ft_time() - philo->time_start;
		printf("%d Success, no philosopher died!\n", printf_time);
	}
	sem_post(philo->stop);
}
