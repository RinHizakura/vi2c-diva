# vi2c-diva

## Introduction

The vi2c-diva project is trying to implement virtual I2C platform device "diva" and its device
driver. We'll try to understand the purpose of each component in the Linux I2C subsystem.

![](misc/linux-i2c-subsystem.png)

For traditional chinese users who want to learn more about this project, you
are welcome to check the [link](https://hackmd.io/@RinHizakura/BJDTZnUsF) for more
introduction of I2C. Welcome for any advice and discussion, thanks!

## Usage

To build and insert these module, using the following command. Note that the sequence to
insert each module is important for kerenl to match our device and driver correctly.

```
$ make subdirs
$ make -C pdev insert
$ make -C adap insert
$ make -C diva-dev insert
```

If everything goes right, it means the probe function of 'adap' and 'diva-dev' will be
callbacked by kernel, which means we match the device driver to device successfully!

```
$ dmesg
[diva-pdev] Init diva with status 0
[i2c-diva-adap] Connect to diva adap i2c-diva
[i2c-diva-dev] Connect to diva dev vi2c,diva-i2c
```

To remove the module from kernel, using the following command.

```
$ make -C diva-dev remove
$ make -C adap remove
$ make -C pdev remove
```

## Reference
* [Day 10：I2C Driver (Part 1) - 使用 Device Tree 來找 Driver](https://ithelp.ithome.com.tw/articles/10244211)
* [Implementing I2C device drivers](https://www.kernel.org/doc/html/latest/i2c/writing-clients.html)
* [How to instantiate I2C devices](https://www.kernel.org/doc/html/latest/i2c/instantiating-devices.html)
* [linux/drivers/i2c/busses/i2c-bcm2835.c](https://github.com/torvalds/linux/blob/master/drivers/i2c/busses/i2c-bcm2835.c)
