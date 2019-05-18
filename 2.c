/*
  +----------------------------------------------------------------------+
  | My Shit                                                |
  +----------------------------------------------------------------------+
  | Author: tjz                              |
  +----------------------------------------------------------------------+
*/
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

static int data = 0;

void * create(void * arg)
{
	printf("正在运行线程...\n");
	printf("data:%d\n", data);
	printf("data = data + 1\n");
	data = data + 1;
	printf("data:%d\n", data);
	printf("在线程里休眠5s...\n");
	sleep(5);
	pthread_exit(0);
}

int main ()
{
	pthread_t tid;
	void * thread_result;
	int error;

	error = pthread_create(&tid, NULL, create, NULL);
	if (error != 0)
	{
		printf("线程创建失败...\n");
		return -1;
	}
	printf("线程成功创建...\n");
	printf("等待线程运行结束...\n");
	int res = pthread_join(tid, &thread_result);
	if (res != 0)
	{
		perror("线程回收失败...\n");
		exit(-1);
	}
	else
	{
		printf("线程成功回收...\n");
		printf("data:%d\n", data);
	}

	return 0;
}
