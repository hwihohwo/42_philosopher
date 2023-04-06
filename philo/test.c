# include <string.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

void	*thread_routine(void *arg)
{
	// pthread_mutex_t	*lock;

	// lock = (pthread_mutex_t *)arg;
	// pthread_mutex_lock(lock);
	// pthread_mutex_unlock(lock);
	// printf("test\n");
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
	pthread_mutex_t	lock;
	pthread_t		thread;

	thread = 0;
	//memset(&lock, 0, sizeof(pthread_mutex_t));
	//pthread_mutex_init(&lock, NULL);
	//printf("%lu\n", sizeof(pthread_mutex_t));
	//mutex_test(&lock);
	printf("%lu\n", thread);
	pthread_create(&thread, NULL, thread_routine, NULL);
	printf("%lu\n", thread);
	//pthread_detach(thread);
	printf("%d\n", pthread_mutex_destroy(&lock));
}
