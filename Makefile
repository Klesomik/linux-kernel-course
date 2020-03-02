obj-m += phonebook.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

load:
	sudo insmod phonebook.ko

unload:
	sudo rmmod phonebook

test: all load

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean