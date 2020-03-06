obj-m += phonebook.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

load:
	sudo insmod phonebook.ko

unload:
	sudo rmmod phonebook

test: all load
	cc test.c -o test
	./test
	sudo dmesg | grep phonebook
	sudo rmmod phonebook
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
	rm ./test

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean