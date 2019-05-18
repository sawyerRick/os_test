#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
// #include <pthread.h>

void * create(void *arg)
{
	printf("new pthread...\n");
}

int main ()
{
	int pid = fork();
	pid_t status;

	if (pid < 0)
	{
		printf("进程创建失败...\n");
		exit(0);
	}
	else if (pid == 0)
	{
		printf("我是子进程...\n");
		exit(0);
	}
	else
	{
		pid = wait(&status);
		printf("回到父进程...\n");
		if (WIFEXITED(status))
		{
			printf("pid为%d的子进程成功退出...\n", pid);
			printf("子进程返回码:%d\n", WEXITSTATUS(status));
		}
		else
		{
			printf("pid为%d的子进程异常退出...\n", pid);
		}
	}

	return 0;
}
