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

static int dev_major = 0;
static int dev_cnt = 0;

static ssize_t dev_read(struct file* flip, char* buffer, size_t len, loff_t* offset)
{
    printk(KERN_INFO "phonebook: [dev_read]: _start\n");

    printk(KERN_INFO "phonebook: [dev_read]: no realisation yet\n");

    printk(KERN_INFO "phonebook: [dev_read]: _finish");

    return 0; // bytes_read
}

static ssize_t dev_write(struct file* flip, const char* buffer, size_t len, loff_t* offset)
{
    char *tmp;
    int uncopied;

    printk(KERN_INFO "phonebook: [dev_write]: _start\n");

    tmp = kmalloc(len, GFP_KERNEL);
    if (!tmp)
    {
        return -ENOMEM;
    }

    uncopied = copy_from_user(tmp, buffer, len);
    if (uncopied > 0)
    {
        kfree(tmp);

        return -EFAULT;
    }

    printk(KERN_INFO "phonebook: [dev_write]: _finish\n");

    return len;
}

static int dev_open(struct inode* inode, struct file* file)
{
    int ret;

    printk(KERN_INFO "phonebook: [dev_open]: _start\n");

    if (dev_cnt > 0)
    {
        printk(KERN_INFO "phonebook: [dev_open]: could not open another one device\n");

        ret = -EBUSY;
    }
    else
    {
        dev_cnt++;
        try_module_get(THIS_MODULE);
        printk(KERN_INFO "phonebook: [dev_open]: device was opened\n");

        ret = 0;
    }

    printk(KERN_INFO "phonebook: [dev_open]: _finish\n");

    return ret;
}

static int dev_release(struct inode* inode, struct file* file)
{
    printk(KERN_INFO "phonebook: [dev_release]: _start\n");

    dev_cnt--;
    module_put(THIS_MODULE);
    printk(KERN_INFO "phonebook: [dev_release]: device was closed\n");

    printk(KERN_INFO "phonebook: [dev_release]: _finish\n");

    return 0;
}

static struct file_operations fops = {
    .owner   = THIS_MODULE,
    .read    = dev_read,
    .write   = dev_write,
    .open    = dev_open,
    .release = dev_release
};

static int __init dev_init(void)
{
    printk(KERN_INFO "phonebook: [dev_init]: _start\n");

    dev_major = register_chrdev(0, DEV_NAME, &fops);
    if (dev_major < 0)
    {
        printk(KERN_ALERT "phonebook: [dev_init]: could not register device: %d\n", dev_major);
        return dev_major;
    }

    printk(KERN_INFO "phonebook: [dev_init]: device major number %d\n", dev_major);

    printk(KERN_INFO "phonebook: [dev_init]: _finish\n");

    return 0;
}

static void __exit dev_exit(void)
{
    printk(KERN_INFO "phonebook: [dev_exit]: _start\n");

    unregister_chrdev(dev_major, DEV_NAME);

    printk(KERN_INFO "phonebook: [dev_exit]: _finish\n");
    printk(KERN_INFO "phonebook: ==========================================\n");
}

module_init(dev_init);
module_exit(dev_exit);
