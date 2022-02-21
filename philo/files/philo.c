/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztune <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 17:27:48 by ztune             #+#    #+#             */
/*   Updated: 2021/10/22 17:27:50 by ztune            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//Проверка переданных параметров на корректность
static int	ph_argv_checker(int argc, char **argv, int i, int j)
{
	if (argc < 5 || argc > 6)
		return (1);
	while (i < argc)
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
				return (2);
			j++;
		}
		if (ft_atoi(argv[i]) == 0)
			return (3);
		i++;
	}
	if (ft_atoi(argv[1]) > 200)
		return (5);
	return (0);
}

//Инициализация философов
static t_philo	*ph_philos_init(int argc, char **argv, int time_stamp, int i)
{
	t_philo	*philos;

	philos = (t_philo *)malloc(sizeof(t_philo) * ft_atoi(argv[1]));
	if (philos == NULL)
		return (NULL);
	while (++i < ft_atoi(argv[1]))
	{
		pthread_mutex_init(&philos[i].fork, NULL);
		if (i > 0)
			philos[i].prev = &philos[i - 1].fork;
		philos[i].ph_count = ft_atoi(argv[1]);
		philos[i].ph_num = i + 1;
		philos[i].time_die = ft_atoi(argv[2]);
		philos[i].time_eat = ft_atoi(argv[3]);
		philos[i].time_sleep = ft_atoi(argv[4]);
		philos[i].time_start = time_stamp;
		philos[i].eat_last = time_stamp;
		philos[i].eat_max = 0;
		if (argc == 6)
			philos[i].eat_max = ft_atoi(argv[5]);
		philos[i].eat_i = 0;
	}
	philos[0].prev = &philos[philos[0].ph_count - 1].fork;
	return (philos);
}

//Закрытие параллельных потоков для философов и их контроля
static void	ph_threads_join(pthread_t *t_id, int ph_count, int j)
{
	while (g_programm_stop == 0)
		ft_usleep(10);
	while (++j <= ph_count)
	{
		pthread_join(t_id[j], NULL);
		pthread_detach(t_id[j]);
	}
	if (g_programm_stopphilo > 0)
		printf("%d %d died\n", g_programm_stoptime, g_programm_stopphilo);
	if (g_programm_stopphilo == 0)
		printf("%d Success, no philosopher died!\n", g_programm_stoptime);
}

//Создание параллельных потоков для философов и их контроля
static int	ph_threads_create(t_philo *philos, int ph_count, int i, int j)
{
	pthread_t	t_id[201];
	int			t_status;

	t_status = pthread_create(&t_id[ph_count], NULL, ph_control_thread, philos);
	if (t_status != 0)
		return (7);
	while (++i < ph_count)
	{
		t_status = pthread_create(&t_id[i], NULL, ph_single_thread, &philos[i]);
		if (t_status != 0)
		{
			while (++j < i)
			{
				pthread_join(t_id[j], NULL);
				pthread_detach(t_id[j]);
			}
			pthread_join(t_id[ph_count], NULL);
			pthread_detach(t_id[ph_count]);
			return (8);
		}
	}
	ph_threads_join(t_id, ph_count, -1);
	return (0);
}

//Основная функция
int	main(int argc, char **argv)
{
	int		error;
	t_philo	*philos;
	int		delete_i;

	g_programm_stop = 0;
	g_programm_stoptime = 0;
	g_programm_stopphilo = 0;
	error = ph_argv_checker(argc, argv, 1, 0);
	if (error > 0)
		return (ft_puterror(error));
	philos = ph_philos_init(argc, argv, ft_time(), -1);
	if (philos == NULL)
		return (ft_puterror(6));
	error = ph_threads_create(philos, philos[0].ph_count, -1, -1);
	if (error > 0)
	{
		free(philos);
		return (ft_puterror(error));
	}
	delete_i = -1;
	while (++delete_i < philos[0].ph_count)
		pthread_mutex_destroy(&philos[delete_i].fork);
	free(philos);
	return (0);
}
