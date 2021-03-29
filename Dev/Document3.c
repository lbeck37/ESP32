Starting upload
Uploading project "BeckE32_TFT_eSPI_Demo" with "ESPTOOL_PY"
Starting reset using DTR toggle process
Continuing to use "COM6"
Ending reset


Launching: C:\_Sloeber_4.3.3\arduinoPlugin\packages\esp32\tools\esptool_py\3.0.0/esptool.exe --chip esp32 --port COM6 --baud 921600 --before default_reset --after hard_reset write_flash -z --flash_mode dio --flash_freq 80m --flash_size detect 0xe000 C:\_Sloeber_4.3.3\/arduinoPlugin/packages/esp32/hardware/esp32/1.0.6/tools/partitions/boot_app0.bin 0x1000 C:\_Sloeber_4.3.3\/arduinoPlugin/packages/esp32/hardware/esp32/1.0.6/tools/sdk/bin/bootloader_qio_80m.bin 0x10000 C:\_Sloeber_4.3.3\Workspace\BeckE32_TFT_eSPI_Demo\Release/BeckE32_TFT_eSPI_Demo.bin 0x8000 C:\_Sloeber_4.3.3\Workspace\BeckE32_TFT_eSPI_Demo\Release/BeckE32_TFT_eSPI_Demo.partitions.bin 
Output:
esptool.py v3.0-dev
Serial port COM6
Connecting....
Chip is ESP32-D0WDQ6-V3 (revision 3)
Features: WiFi, BT, Dual Core, 240MHz, VRef calibration in efuse, Coding Scheme None
Crystal is 40MHz
MAC: 3c:61:05:0d:6f:b4
Uploading stub...
Running stub...
Stub running...
Changing baud rate to 921600
Changed.
Configuring flash size...
Auto-detected Flash size: 4MB
Compressed 8192 bytes to 47...
Writing at 0x0000e000... (100 %)
Wrote 8192 bytes (47 compressed) at 0x0000e000 in 0.0 seconds (effective 16383.2 kbit/s)...
Hash of data verified.
Compressed 18656 bytes to 12053...
Writing at 0x00001000... (100 %)
Wrote 18656 bytes (12053 compressed) at 0x00001000 in 0.2 seconds (effective 938.7 kbit/s)...
Hash of data verified.
Compressed 252400 bytes to 128291...
Writing at 0x00010000... (12 %)
Writing at 0x00014000... (25 %)
Writing at 0x00018000... (37 %)
Writing at 0x0001c000... (50 %)
Writing at 0x00020000... (62 %)
Writing at 0x00024000... (75 %)
Writing at 0x00028000... (87 %)
Writing at 0x0002c000... (100 %)
Wrote 252400 bytes (128291 compressed) at 0x00010000 in 2.0 seconds (effective 1008.1 kbit/s)...
Hash of data verified.
Compressed 3072 bytes to 127...
Writing at 0x00008000... (100 %)
Wrote 3072 bytes (127 compressed) at 0x00008000 in 0.0 seconds (effective 6144.1 kbit/s)...
Hash of data verified.

Leaving...
Hard resetting via RTS pin...
The execution of command "3.0.0/esptool.exe" is done.
