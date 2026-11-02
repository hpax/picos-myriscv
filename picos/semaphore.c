#include <picos/semaphore.h>

extern inline bool sem_try_down(struct semaphore *sem);
extern inline ticks_t sem_down(struct semaphore *sem);
extern inline ticks_t sem_up(struct semaphore *sem);
