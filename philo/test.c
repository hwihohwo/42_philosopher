# include <string.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

void	*thread_routine(void *arg)
{
	for (int i = 1; i <= 5; i++)
	{
		usleep(1000 * 1000 * 2);
		printf("%s: ", (char *)arg);
		printf("쓰레드 함수 실행 중..%d/5\n", i);
	}
	printf("쓰레드 함수 종료\n");
	return ((void *)214748364);
}

void	mutex_test(pthread_mutex_t *lock)
{
	pthread_t		thread_1;
	pthread_t		thread_2;

	pthread_mutex_lock(lock);
	pthread_create(&thread_1, NULL, thread_routine, (void *)lock);
	pthread_create(&thread_2, NULL, thread_routine, (void *)lock);
	sleep(5);
	pthread_mutex_unlock(lock);
	pthread_join(thread_1, NULL);
	pthread_join(thread_2, NULL);
}

int	main(void)
{
	pthread_t	p_thread1;
	pthread_t	p_thread2;
	int			thr_id1;
	int			thr_id2;

	thr_id1 = pthread_create(&p_thread1, NULL, thread_routine, "thread1");
	thr_id2 = pthread_create(&p_thread2, NULL, thread_routine, "thread2");
	if (thr_id1 < 0 || thr_id2 < 0)
	{
		perror("thread create error:");
		exit(0);
	}
	pthread_detach(p_thread1);
	pthread_detach(p_thread2);
	// pthread_join(p_thread1, 0);
	// pthread_join(p_thread2, 0);

	// int	s = 0;
	// while (42)
	// {
	// 	printf("%d초 경과\n", s++);
	// 	usleep(1000 * 1000);
	// }
	printf("main()종료\n");
	return (0);
}
