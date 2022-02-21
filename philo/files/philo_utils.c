/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztune <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 17:28:26 by ztune             #+#    #+#             */
/*   Updated: 2021/10/22 17:28:29 by ztune            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//Перевод строки в число
int	ft_atoi(const char *str)
{
	int			sign;
	long int	ret;

	sign = 1;
	ret = 0;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '-')
		sign = -1;
	if (*str == '-' || *str == '+')
		str++;
	while (*str == '0')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		ret = ret * 10 + (*str - 48);
		str++;
	}
	return ((int)(ret * sign));
}

//Текущая временная метка (INT) с 3 допзнаками милисекунд
int	ft_time(void)
{
	struct timeval	time_now;

	gettimeofday(&time_now, NULL);
	return ((time_now.tv_sec - TIME_MINUS) * 1000 + time_now.tv_usec / 1000);
}

//Пауза для процесса
void	ft_usleep(int ms)
{
	long	time;

	time = ft_time();
	usleep(ms * 920);
	while (ft_time() < time + ms)
		usleep(ms * 3);
}
