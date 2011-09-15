#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <copperplate/init.h>
#include <copperplate/traceobj.h>
#include <vxworks/errnoLib.h>
#include <vxworks/taskLib.h>
#include <vxworks/semLib.h>

static struct traceobj trobj;

static int tseq[] = {
	8, 1, 9, 4, 10, 5, 11, 2, 6, 7,	12
};

static TASK_ID btid, ftid;

static SEM_ID sem_id;

static void backgroundTask(long a1, long a2, long a3, long a4, long a5,
			   long a6, long a7, long a8, long a9, long a10)
{
	unsigned int safety = 100000000, count = 0;
	int ret;

	traceobj_enter(&trobj);

	traceobj_mark(&trobj, 1);

	ret = semTake(sem_id, WAIT_FOREVER);
	traceobj_assert(&trobj, ret == OK);

	traceobj_mark(&trobj, 2);

	while (--safety > 0)
		count++;

	/*
	 * Force a pause so that any pending cancellation is taken
	 * regardless of whether async-cancel is enabled or not.
	 */
	pause();

	traceobj_mark(&trobj, 3);

	traceobj_exit(&trobj);
}

static void foregroundTask(long a1, long a2, long a3, long a4, long a5,
			   long a6, long a7, long a8, long a9, long a10)
{
	int ret;

	traceobj_enter(&trobj);

	traceobj_mark(&trobj, 4);

	ret = semTake(sem_id, WAIT_FOREVER);
	traceobj_assert(&trobj, ret == OK);

	traceobj_mark(&trobj, 5);

	taskDelay(3);

	traceobj_mark(&trobj, 6);

	ret = taskSuspend(btid);
	traceobj_assert(&trobj, ret == OK);

	traceobj_mark(&trobj, 7);

	traceobj_exit(&trobj);
}

int main(int argc, char *argv[])
{
	int ret;

	copperplate_init(argc, argv);

	traceobj_init(&trobj, argv[0], sizeof(tseq) / sizeof(int));

	sem_id = semCCreate(SEM_Q_PRIORITY, 0);
	traceobj_assert(&trobj, sem_id != 0);

	traceobj_mark(&trobj, 8);

	btid = taskSpawn("backgroundTask", 11, 0, 0, backgroundTask,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	traceobj_assert(&trobj, btid != ERROR);

	traceobj_mark(&trobj, 9);

	ftid = taskSpawn("foregroundTask", 10, 0, 0, foregroundTask,
			 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	traceobj_assert(&trobj, ftid != ERROR);

	traceobj_mark(&trobj, 10);

	ret = semGive(sem_id);

	traceobj_assert(&trobj, ret == OK);

	traceobj_mark(&trobj, 11);

	ret = semGive(sem_id);

	traceobj_assert(&trobj, ret == OK);

	traceobj_mark(&trobj, 12);

	ret = taskDelete(btid);
	traceobj_assert(&trobj, ret == OK);

	traceobj_join(&trobj);

	traceobj_verify(&trobj, tseq, sizeof(tseq) / sizeof(int));

	exit(0);
}