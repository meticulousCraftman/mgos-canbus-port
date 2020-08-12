#include "mgos.h"


enum mgos_app_init_result mgos_app_init(void)
{
    LOG(LL_INFO, ("Hello, world!"));
    return MGOS_APP_INIT_SUCCESS;
}
