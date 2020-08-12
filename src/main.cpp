#include "mgos.h"
#include "tcu_sdcard.h"


extern "C" {
    enum mgos_app_init_result mgos_app_init(void)
    {
        LOG(LL_INFO, ("Setting up SD Card!"));
        setup_sdcard();
        return MGOS_APP_INIT_SUCCESS;
    }
}