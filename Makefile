obj-m += afsk.o
PWD := $(shell pwd)
all:
	make -C /lib/modules/4.1.21+/build M=$(PWD) modules

clean:
	make -C /lib/modules/4.1.21+/build M=$(PWD) clean
