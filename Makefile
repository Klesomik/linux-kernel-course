obj-m += phonebook.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

load:
	sudo insmod phonebook.ko

nod:
	sudo mknod /dev/phonebook c $(shell awk '$$2=="phonebook" {print $$1}' /proc/devices) 0
	sudo chgrp wheel /dev/phonebook
	sudo chmod 664 /dev/phonebook

unload:
	sudo rmmod phonebook
	sudo rm -f /dev/phonebook

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean