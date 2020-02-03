#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/device.h>
#include <linux/fs.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/uaccess.h>

MODULE_LICENSE("GPL");

static int major_num = 0;
static int device_open_count = 0;

static char *msg_ptr;

static ssize_t device_read(struct file* flip, char* buffer, size_t len, loff_t* offset)
{
	int bytes_read = 0;
	if (*msg_ptr == 0)
	{
		return 0;
	}
	while (len && *msg_ptr)
	{
		put_user(*(msg_ptr++), buffer++);
		len--;
		bytes_read++;
	}
	return bytes_read;
}

static ssize_t device_write(struct file* flip, const char* buffer, size_t len, loff_t* offset)
{
        printk(KERN_INFO "phonebook: write not realized\n");
}

static int device_open(struct inode* inode, struct file* file)
{
	if (device_open_count)
	{
		return -EBUSY;
	}
	device_open_count++;
	try_module_get(THIS_MODULE);
        printk(KERN_INFO "phonebook: device was opened\n");
	return 0;
}

static int device_release(struct inode* inode, struct file* file)
{
	device_open_count--;
	module_put(THIS_MODULE);
        printk(KERN_INFO "phonebook: device was closed\n");
	return 0;
}

struct file_operations fops = {
        .read    = device_read,
        .write   = device_write,
        .open    = device_open,
        .release = device_release
};

static int __init dev_init(void)
{
	major_num = register_chrdev(0, "phonebook", &fops);
	if (major_num < 0)
	{
		printk(KERN_ALERT "phonebook: Could not register device: %d\n", major_num);
		return major_num;
	}
	else
	{
		printk(KERN_INFO "phonebook: device major number %d\n", major_num);
		return 0;
	}
}

static void __exit dev_exit(void)
{
	printk(KERN_INFO "phonebook: exit\n");

	unregister_chrdev(major_num, "phonebook");
}

module_init(dev_init);
module_exit(dev_exit);
