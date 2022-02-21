/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztune <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 17:25:07 by ztune             #+#    #+#             */
/*   Updated: 2021/10/22 17:25:10 by ztune            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//Прерывание процессов, удаление семафоров и очистка памяти
static void	ph_kill_delete_free(t_philo *philo, int proc_count, int error_code)
{
	int	i;

	i = -1;
	while (++i < proc_count)
		kill(philo->pid[i], SIGKILL);
	sem_close(philo->create);
	sem_close(philo->forks);
	sem_close(philo->stop);
	sem_close(philo->print);
	sem_unlink("create");
	sem_unlink("forks");
	sem_unlink("stop");
	sem_unlink("print");
	if (philo->pid != NULL)
	{
		free(philo->pid);
		philo->pid = NULL;
	}
	free(philo);
	if (error_code > 0)
		ft_puterror(error_code);
}

//Перечисление действий одного философа
static void	ph_single_actions(t_philo *philo)
{
	sem_wait(philo->forks);
	ft_print_mes(ft_time(), philo, "has taken a forks");
	philo->eat_last = ft_time();
	ft_print_mes(ft_time(), philo, "is eating");
	ft_usleep(philo->time_eat);
	sem_post(philo->forks);
	philo->eat_i++;
	ft_print_mes(ft_time(), philo, "is sleeping");
	ft_usleep(philo->time_sleep);
	ft_print_mes(ft_time(), philo, "is thinking");
	ft_usleep((double)(philo->time_die - philo->time_eat
			- philo->time_sleep) / 2);
}

//Действия философа внутри отдельного процесса
static void	ph_philo_process(t_philo *philo, int i)
{
	pthread_t	t_id;
	int			t_status;

	ft_print_mes(ft_time(), philo, "created");
	while (philo->ph_num == philo->ph_count && ++i < philo->ph_count)
		sem_post(philo->create);
	sem_wait(philo->create);
	t_status = pthread_create(&t_id, NULL, ph_philo_control, philo);
	if (t_status != 0)
	{
		sem_wait(philo->print);
		sem_post(philo->stop);
		printf("Error: Ne udalos sozdat potok dlya kontrolya filosofa\n");
		exit(1);
	}
	while (g_process_stop == 0)
		ph_single_actions(philo);
	pthread_join(t_id, NULL);
	pthread_detach(t_id);
	ph_kill_delete_free(philo, 0, 0);
	exit(1);
}

//Создание параллельных процессов для философов
static void	ph_processes_create(t_philo *philo, int i)
{
	pthread_t	t_id;
	int			t_status;

	philo->pid = (pid_t *)malloc(sizeof(pid_t) * philo->ph_count);
	if (philo->pid == NULL)
		ph_kill_delete_free(philo, 0, 7);
	while (++i < philo->ph_count)
	{
		philo->pid[i] = fork();
		if (philo->pid[i] == -1)
			ph_kill_delete_free(philo, i, 8);
		if (philo->pid[i] == 0)
		{
			philo->ph_num = i + 1;
			ph_philo_process(philo, -1);
			break ;
		}
	}
	t_status = pthread_create(&t_id, NULL, ph_die_stop, philo);
	if (t_status != 0)
		ph_kill_delete_free(philo, philo->ph_count, 9);
	ph_wait_processes(philo, -1);
	pthread_join(t_id, NULL);
	pthread_detach(t_id);
}

//Основная функция
int	main(int argc, char **argv)
{
	t_philo		*philo;

	g_process_stop = 0;
	g_success_print = 1;
	ph_argv_checker(argc, argv, 1, 0);
	philo = ph_philo_init(argc, argv, ft_time());
	philo->create = ft_sem_open("create", 0);
	philo->forks = ft_sem_open("forks", philo->ph_count / 2);
	philo->stop = ft_sem_open("stop", 0);
	philo->print = ft_sem_open("print", 1);
	ph_processes_create(philo, -1);
	ph_kill_delete_free(philo, 0, 0);
	return (0);
}
