/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scrumier <scrumier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 17:29:19 by scrumier          #+#    #+#             */
/*   Updated: 2024/05/15 15:17:06 by scrumier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <stdbool.h>
# include <errno.h>

# define MSG_END "\x1b[37mThe program freed all and finished the execution.\n"

# define USAGE "./philo <nbr_philo> <time_to_die> <time_to_eat> \
				<time_to_sleep> [number_of_times_each_philosopher_must_eat]\n"
# define BAD_NBR_PHILO "Philo must be bettwin 1 and 200.\n"
# define BAD_AC "The number of arguments is incorrect.\n"
# define BAD_AV "The time to do the task must be a positive integer.\n"
# define BAD_NBR_EAT "Philosophers cant that fast !\n"
# define FAIL_INIT_STRUCT "Failed to init the struct.\n"
# define FAIL_MALLOC "Failed to malloc.\n"
# define FAIL_MUTEX_INIT "Failed to init mutex.\n"
# define WRONG_MUTEX_OPCODE "Wrong mutex opcode.\n"

typedef pthread_mutex_t	t_mtx;
typedef struct s_table	t_table;

typedef enum e_timecode
{
	SECONDS,
	MILLISECONDS,
	MICROSECONDS,
}		t_timecode;

typedef struct s_fork
{
	t_mtx	fork;
	bool	taken;
	int		id;

}			t_fork;

typedef struct s_philo
{
	int			id;
	long		time_eaten;
	long		last_ate;
	bool		full;
	t_fork		*first_fork;
	t_fork		*second_fork;
	t_mtx		philo_mtx;
	pthread_t	thread_id;
	t_table		*table;
}				t_philo;

typedef struct s_table
{
	long		philo_nbr;
	long		time_to_die;
	long		time_to_eat;
	long		time_to_sleep;
	long		nb_eat;
	long		start;
	long		threads_running;
	bool		end_eat;
	bool		thread_ready;
	pthread_t	monitor;
	t_mtx		write_mtx;
	t_mtx		table_mtx;
	t_fork		*forks;
	t_philo		*philos;
}			t_table;

int		ft_check_args(int ac, char **av);
int		ft_failure(char *str);
int		ft_succes(char *str);
void	set_int(t_mtx *mtx, int *var, int value);
void	set_bool(t_mtx *mtx, bool *var, bool value);
bool	get_bool(t_mtx *mtx, bool *var);
void	set_long(t_mtx *mtx, long *var, long value);
long	get_long(t_mtx *mtx, long *var);
int		get_int(t_mtx *mtx, int *var);
void	increase_long(t_mtx *mtx, long *var, long value);
bool	eat_finished(t_table *table);
void	assign_forks(t_philo *philo, t_fork *forks, int i);
int		data_init(t_table *table);
int		ft_init_struct(t_table *table, char **av);
void	write_message(t_philo *philo, char *str);
void	*monitor_handler(void *arg);
void	*one_philo(void *arg);
void	dinner(t_table *table);
void	wait_thread(t_table *table);
bool	all_threads_running(t_mtx *philo, t_mtx *mtx, \
		long *threads, long philo_nbr);
void	de_synchro(t_philo *philo);
int		ft_strlen(char *str);
long	ft_atol(char *str);
void	ft_usleep(long time, t_table *table);
long	gettime(t_timecode timecode);
void	clean(t_table *table);
int		ft_isnbr(char *c);

#endif