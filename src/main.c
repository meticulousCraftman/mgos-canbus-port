#include "mgos.h"

static void timer_cb(void *arg)
{
    // Write your code here
    (void)arg;
}

enum mgos_app_init_result mgos_app_init(void)
{
    mgos_set_timer(1000 /* ms */, MGOS_TIMER_REPEAT, timer_cb, NULL);
    return MGOS_APP_INIT_SUCCESS;
}
