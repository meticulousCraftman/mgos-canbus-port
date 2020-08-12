# Running SD.h library from Arduino on ESP32 running Mongoose OS

This mongoose os app does not use the arduino-compat library provided by Mongoose OS. Instead, the source files, header files and static library files have been added from esp32-arduino project directly.

This application was written for the primary reason of making SD Cards to work reliably on Mongoose OS. nvliu/sdlib was unable to mount the SD Card, after several futile attempts. I tested the ESP32 module using Arduino SD library and everything worked!

So for that reason, I ported the entire Arduino core that is required to run SD.h and FS.h files.

## Build command

```console
foo@bar:~$ mos build --platform esp32 --local --verbose --no-libs-update --binary-libs-dir "binary_libs"
Local build starts...
Internet connection to fetch new packages
```

## Flash

```console
foo@bar:~$ mos flash esp32 --port /dev/ttyUSB0 build/fw.zip
```

## Running
Watch the application write data to a file named **hello.txt**.
```console
foo@bar:~$ mos console --port /dev/ttyUSB0
```

![Console screen on output](images/output.png)


## Output
Remove the SD Card from your ESP32 board/SDCard module. Plug it into your computer to see a file named **hello.txt** with the contents `Hello World!` in it.
