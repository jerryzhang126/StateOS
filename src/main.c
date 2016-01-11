#include <stm32f4_discovery.h>
#include <os.h>

OS_SEM(sem, 0, semNormal);

void slave()
{
	sem_wait(sem);

	LED_Tick();
}

void master()
{
	tsk_delay(1000*MSEC);

	sem_give(sem);
}

OS_WRK(sla, 0, slave,  256);
OS_WRK(mas, 0, master, 256);

int main()
{
	LED_Config();

	tsk_start(sla);
	tsk_start(mas);
	tsk_stop();
}
