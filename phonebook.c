#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

#include <linux/device.h>
#include <linux/fs.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/uaccess.h>

MODULE_LICENSE("GPL");

#define DEV_NAME "phonebook"

static int major_num = 0;
static int device_open_count = 0;

static char *msg_ptr;

static ssize_t dev_read(struct file* flip, char* buffer, size_t len, loff_t* offset)
{
    printk(KERN_INFO "phonebook: [dev_read]: _start\n");

    int bytes_read = 0;
    while (len && *msg_ptr)
    {
        put_user(*(msg_ptr++), buffer++);
        len--;
        bytes_read++;
    }

    printk(KERN_INFO "phonebook: [dev_read]: read %d bytes\n", bytes_read);

    printk(KERN_INFO "phonebook: [dev_read]: _finish");

    return bytes_read;
}

static ssize_t dev_write(struct file* flip, const char* buffer, size_t len, loff_t* offset)
{
    printk(KERN_INFO "phonebook: [dev_write]: _start\n");

    printk(KERN_INFO "phonebook: [dev_write]: _finish\n");

    return 0;
}

static int dev_open(struct inode* inode, struct file* file)
{
    printk(KERN_INFO "phonebook: [dev_open]: _start\n");

    if (device_open_count)
    {
        printk(KERN_INFO "phonebook: [dev_open]: could not open another one device\n");
        return -EBUSY;
    }

    device_open_count++;
    try_module_get(THIS_MODULE);
    printk(KERN_INFO "phonebook: [dev_open]: device was opened\n");

    printk(KERN_INFO "phonebook: [dev_open]: _finish\n");

    return 0;
}

static int dev_release(struct inode* inode, struct file* file)
{
    printk(KERN_INFO "phonebook: [dev_release]: _start\n");

    device_open_count--;
    module_put(THIS_MODULE);
    printk(KERN_INFO "phonebook: [dev_release]: device was closed\n");

    printk(KERN_INFO "phonebook: [dev_release]: _finish\n");

    return 0;
}

struct file_operations fops = {
    .owner   = THIS_MODULE,
    .read    = dev_read,
    .write   = dev_write,
    .open    = dev_open,
    .release = dev_release
};

static int __init dev_init(void)
{
    printk(KERN_INFO "phonebook: [dev_init]: _start\n");

    major_num = register_chrdev(0, DEV_NAME, &fops);
    if (major_num < 0)
    {
        printk(KERN_ALERT "phonebook: [dev_init]: could not register device: %d\n", major_num);
        return major_num;
    }

    printk(KERN_INFO "phonebook: [dev_init]: device major number %d\n", major_num);

    printk(KERN_INFO "phonebook: [dev_init]: _finish\n");

    return 0;
}

static void __exit dev_exit(void)
{
    printk(KERN_INFO "phonebook: [dev_exit]: _start\n");

    unregister_chrdev(major_num, DEV_NAME);

    printk(KERN_INFO "phonebook: [dev_exit]: _finish\n");
}

module_init(dev_init);
module_exit(dev_exit);
