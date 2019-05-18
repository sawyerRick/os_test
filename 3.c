#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <ctype.h>

pthread_mutex_t counter_clock = PTHREAD_MUTEX_INITIALIZER;
int total_words = 0;

void * count_words(void * f)
{
	char * filename = (char *) f;
	FILE * fp;

	int c;
	int prevc = '\n';

	if ((fp = fopen(filename, "r")) != NULL)
	{
		while((c = getc(fp)) != EOF)
		{
			if (!isalnum(c) && isalnum(prevc))
			{
				pthread_mutex_lock(&counter_clock);
				printf("thread_tid:%u total_words++...\n", (unsigned)pthread_self());
				total_words++;
				pthread_mutex_unlock(&counter_clock);
			}
			prevc = c;
		}
	}
	else
	{
		perror(filename);
	}
	return NULL;
}

int main (int ac, char * args[])
{
	void * count_words(void *);
	if (ac != 3)
	{
		printf("用法:%s file1 file2\n", args[0]);
		return -1;
	}

	pthread_t thread_for_file1;
	pthread_t thread_for_file2;
	void * thread1_result;
	void * thread2_result;

	pthread_create(&thread_for_file1, NULL, count_words, args[1]);
	pthread_create(&thread_for_file2, NULL, count_words, args[2]);

	printf("阻塞线程1和线程2...\n");
	int res1 = pthread_join(thread_for_file1, &thread1_result);
	int res2 = pthread_join(thread_for_file2, &thread2_result);
	if (res1 == 0 && res2 == 0)
	{
		printf("成功回收线程1线程2...\n");
		printf("file1和file2的单词总数:%d\n", total_words);
	}
	else
	{
		printf("线程回收失败...\n");
	}
	pthread_mutex_destroy(&counter_clock);

	return 0;
}
