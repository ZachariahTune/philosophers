/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_puts.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztune <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 17:25:39 by ztune             #+#    #+#             */
/*   Updated: 2021/10/22 17:25:41 by ztune            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//Вывод символа
static void	ft_putchar(int c, int stdvar)
{
	write(stdvar, &c, 1);
}

//Вывод строки
static void	ft_putstr(char *str)
{
	int	i;
	int	stdvar;

	stdvar = 1;
	if (str[0] == 'E' && str[1] == 'r' && str[2] == 'r'
		&& str[3] == 'o' && str[4] == 'r' && str[5] == '\n')
		stdvar = 2;
	if (str == NULL)
		str = "(null)";
	i = 0;
	while (str[i])
	{
		ft_putchar(str[i], stdvar);
		i++;
	}
}

//Вывод ошибок
void	ft_puterror(int code)
{
	ft_putstr("Error: ");
	if (code == 1)
		ft_putstr("Programme neobhodimo peredat 4 ili 5 parametrov\n");
	if (code == 2)
		ft_putstr("Vse parametry dolzhny bit tolko chislovie\n");
	if (code == 3)
		ft_putstr("Nulevie znacheniya parametrov nedopustimy\n");
	if (code == 5)
		ft_putstr("More 200 processes for philosophers? Are you crazy???\n");
	if (code == 6)
		ft_putstr("Ne udalos videlit pamyat dlya struktury filosofa\n");
	if (code == 7)
		ft_putstr("Ne udalos videlit pamyat dlya identifikatorov processov\n");
	if (code == 8)
		ft_putstr("Ne udalos sozdat process dlya filosofa\n");
	if (code == 9)
		ft_putstr("Ne udalos sozdat potok dlya fiksirovaniya smerti\n");
	exit(1);
}

//Вывод сообщения со статусом философа
void	ft_print_mes(int time, t_philo *philo, char *text)
{
	sem_wait(philo->print);
	printf("%d %d %s\n", time - philo->time_start, philo->ph_num, text);
	sem_post(philo->print);
}
