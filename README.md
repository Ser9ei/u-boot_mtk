                  Ralink/MediaTek U-Boot for MIPS SoC
        RT3052/RT3352/RT3883/RT5350/MT7620/MT7621/MT7628/MT7688
                     Based on MediaTek SDK 5.0.1.0

*This is a Fork from* https://gitlab.com/db260179/u-boot-mt7621/-/tree/master/

**New features:**
- New profiles:
Xiaomi mi router 4a gigabit v2 (r4av2/rb02) - mt7621 chip
Xiaomi mi mini - mt7620 chip
- Links to the uboot/factory/firmware mode of the httpd failsafe repair for quickly switch between html pages (see screenshots below)

#### Preparing Toolchain

For MT7621 U-Boot:
- extract 'toolchain/mips-2012.03.tar.bz2' to /opt (tar -xvf toolchain/mips-2012.03.tar.xz -C /opt/)

For RT3XXX/MT7620/MT7628/MT7688 U-Boot:
- extract 'toolchain/buildroot-gcc342.tar.bz2' to /opt

Both toolchains require x86 (32-bit) Linux environment. If you are on x64 (64-bit)
environment you need to do the following:
Ubuntu 18.04 or Debian 9,10
```
dpkg --add-architecture i386

apt install libc6:i386 libncurses5:i386 libstdc++6:i386
```

#### Build Instructions

- Copy appropriate '.config' file (e.g. profiles/XIAOMI/MI-R4AV2.config)
  to 'uboot-5.x.x.x' dir.
- Goto 'uboot-5.x.x.x' dir.
- Run 'make menuconfig', choose [Exit] and confirm [Save]. This is important step!
- Run 'make'.
- Use image file uboot.bin (ROM mode) for NOR and SPI-flash boards.
- Use image file uboot.img (RAM mode) for NAND-flash boards.

To clean U-Boot tree:
- Run 'make clean'.
- Run 'make unconfig'.

#### Build for new Boards

- Goto 'uboot-5.x.x.x' dir.
- Run 'make menuconfig'.
- Select SoC, Ram, Flash type for your board. See some .config from profiles, you will get the general idea.
- Choose [Exit] and confirm [Save] then run 'make'.

NOTE:
1. Before building for a new board, know the GPIO number for reset, leds and configure them
   properly during 'make menuconfig'. Extra careful with the reset button (GPIO_BTN_RESET).
2. It's better to configure UART baud rate same as your stock firmware 115200 or 57600.
3. All profiles has disabled option "Enable all Ethernet PHY" to prevent LAN-WAN
   spoofing (EPHY will be enabled later in FW logic). To force enable EPHY (e.g. for
   use OpenWRT/PandoraBox), select option "Enable all Ethernet PHY".
4. See if your board's spi or nand flash chip is listed on here 'uboot-5.x.x.x/drivers/spi_flash.c' (281 line)
   or 'uboot-5.x.x.x/drivers/nand/nand_device_list.h'. Don't risk it if your flash chip is not on the list.

#### Flash Instructions

Take a backup of the current u-boot partition (`mtd0`).

Get info about mtd partitions structure:
  ```
  cat /proc/mtd
  ```
Make backup of original u-boot (mtd0 - partition device name in the sample with uboot):
  ```
  cat /dev/mtd0 > /tmp/uboot_orig.bin
  ```
Transfer the backup off the device and to a safe place:
  ```
 scp root@192.168.1.1:/tmp/uboot_orig.bin .
  ```
  
Transfer the new uboot to the router:
  ```
  scp uboot_new.bin root@192.168.1.1:/tmp/
  ```
  And flash:
  ```
  mtd -e /dev/mtd0 write /tmp/uboot_new.bin /dev/mtd0
  ```
  

**Danger**: *This is the point of no return, if you have any errors or problems, please revert the original image at any time using:*

  ```
  mtd -e /dev/mtd0 write /tmp/uboot_orig.bin /dev/mtd0
  ```
Double check the boot partition name 'Bootloader' by 'cat /proc/mtd', usually it's on /dev/mtd0 or sometimes mtd1.
- Reboot router.

                             WARNING

- Do not remove power supply during flash U-Boot!!!
- Device may be bricked due to your incorrect actions!!!

#### Main Features

1. Press and hold the RESET button on Power-On for 2~3 sec, this will switch to Recovery mode. Set your Ethernet
   ipv4 to 192.168.1.2, subnet mask 255.255.255.0 and gateway 192.168.1.1.
2. Go to 192.168.1.1 from any browser and upload or upgrade your firmware. You can also upgrade your factory and u-boot
   partition from 192.168.1.1/factory.html and 192.168.1.1/uboot.html respectively.
   For Xiaomi routers http server maybe reached by the 192.168.31.1 ip, it depend on envoriment from the Config/BootEnv partition values.
![firmware](https://user-images.githubusercontent.com/61657001/231694117-161912d1-38ab-465a-b424-1948591c48ed.jpg)

![uboot](https://user-images.githubusercontent.com/61657001/231694190-ee70e38d-673c-4eec-9328-42dc966e81b1.jpg)

![factory](https://user-images.githubusercontent.com/61657001/231694218-3a3a6bd5-16ab-4556-803e-012cc8546efa.jpg)

3. Also you can use TFTP client or ASUS Firmware Restoration (device IP-address is 192.168.1.1). Some devices with usb
   port can also support Recovery from USB storage.

NOTE:
- Usually, Xiaomi router has 192.168.31.1 address, so please remeber about it and find you router in the failsafe repair mode by this address or modify u-boot enviriments for ip address to the 192.168.1.1
- U-Boot will perform switch to Recovery mode on flash content integrity fail.
- Alert LED(s) is blinking in Recovery mode and on erasing/flashing.
- To Recovery from USB storage, place FW image with a filename 'root_uImage' to first
  FAT16/FAT32 partition, plug-in USB2 pen and switch to Recovery mode (see 3).

