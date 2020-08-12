/*
 * Connect the SD card to the following pins:
 *
 * SD Card | ESP32
 *    D2       -
 *    D3       SS
 *    CMD      MOSI
 *    VSS      GND
 *    VDD      3.3V
 *    CLK      SCK
 *    VSS      GND
 *    D0       MISO
 *    D1       -
 */
#include "mgos.h"
#include "SPI.h"
#include "FS.h"
#include "SD.h"

void writeFile(fs::FS &fs, const char *path, const char *message)
{
    LOG(LL_INFO, ("Writing file: %s\n", path));

    File file = fs.open(path, FILE_WRITE);
    if (!file)
    {
        LOG(LL_INFO, ("Failed to open file for writing"));
        return;
    }
    if (file.print(message))
    {
        LOG(LL_INFO, ("File written"));
    }
    else
    {
        LOG(LL_INFO, ("Write failed"));
    }
    file.close();
}

void appendFile(fs::FS &fs, const char *path, const char *message)
{
    LOG(LL_INFO, ("Appending to file: %s\n", path));

    File file = fs.open(path, FILE_APPEND);
    if (!file)
    {
        LOG(LL_INFO, ("Failed to open file for appending"));
        return;
    }
    if (file.print(message))
    {
        LOG(LL_INFO, ("Message appended"));
    }
    else
    {
        LOG(LL_INFO, ("Append failed"));
    }
    file.close();
}

void setup_sdcard()
{
    if (!SD.begin())
    {
        LOG(LL_INFO, ("Card Mount Failed"));
        return;
    }
    uint8_t cardType = SD.cardType();

    if (cardType == CARD_NONE)
    {
        LOG(LL_INFO, ("No SD card attached"));
        return;
    }

    LOG(LL_INFO, ("SD Card Type: "));
    if (cardType == CARD_MMC)
    {
        LOG(LL_INFO, ("MMC"));
    }
    else if (cardType == CARD_SD)
    {
        LOG(LL_INFO, ("SDSC"));
    }
    else if (cardType == CARD_SDHC)
    {
        LOG(LL_INFO, ("SDHC"));
    }
    else
    {
        LOG(LL_INFO, ("UNKNOWN"));
    }

    uint64_t cardSize = SD.cardSize() / (1024 * 1024);
    LOG(LL_INFO, ("SD Card Size: %lluMB\n", cardSize));

    writeFile(SD, "/hello.txt", "Hello ");
    appendFile(SD, "/hello.txt", "World!\n");
    LOG(LL_INFO, ("Total space: %lluMB\n", SD.totalBytes() / (1024 * 1024)));
    LOG(LL_INFO, ("Used space: %lluMB\n", SD.usedBytes() / (1024 * 1024)));
}
