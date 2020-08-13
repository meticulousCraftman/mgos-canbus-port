#include "mgos.h"
#include <SPI.h>
#include "mcp_can.h"

const int spiCSPin = 5;
const int ledPin = 2;
boolean ledON = 1;

MCP_CAN CAN(spiCSPin);

static void my_timer_cb(void *arg)
{

    unsigned char len = 0;
    unsigned char buf[8];

    if (CAN_MSGAVAIL == CAN.checkReceive())
    {
        CAN.readMsgBuf(&len, buf);

        unsigned long canId = CAN.getCanId();

        LOG(LL_INFO, ("-----------------------------"));
        LOG(LL_INFO, ("Data from ID: 0x %lu", canId));
        // LOG(LL_INFO (canId, HEX);
        LOG(LL_INFO, ("Data received: %s", buf));

        for (int i = 0; i < len; i++)
        {
            LOG(LL_INFO, ("%c ", buf[i]));
        }
    }
    else {
        LOG(LL_INFO, ("No data rxed."));
    }

    (void)arg;
}

enum mgos_app_init_result mgos_app_init(void)
{
    LOG(LL_INFO, ("Setting up CAN Bus!"));

    // CAN bus setup code
    Serial.begin(115200);

    while (CAN_OK != CAN.begin(CAN_500KBPS))
    {
        LOG(LL_INFO, ("CAN BUS Init Failed"));
        // delay(100);
        mgos_msleep(100);
    }
    LOG(LL_INFO, ("CAN BUS  Init OK!"));

    // Setup a callback timer here for checking input buffer
    mgos_set_timer(1000, MGOS_TIMER_REPEAT, my_timer_cb, NULL);

    return MGOS_APP_INIT_SUCCESS;
}
