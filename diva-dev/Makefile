MODULENAME := diva-dev
obj-m += $(MODULENAME).o
$(MODULENAME)-y += main.o

KERNELDIR ?= /lib/modules/`uname -r`/build
PWD       := $(shell pwd)

all:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules

clean:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) clean

insert: all
	sudo insmod $(MODULENAME).ko

remove:
	sudo rmmod $(MODULENAME).ko
