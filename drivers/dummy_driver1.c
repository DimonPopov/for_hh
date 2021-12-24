#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/cdev.h>
#include <linux/fs.h>


MODULE_LICENSE("GPL");
MODULE_AUTHOR("Popov D.S.");
MODULE_DESCRIPTION("my_dummy_device registration");
MODULE_VERSION("0.1");

#define MYDEV_NAME "my_dummy_device"

static const int count_dev = 1;         // Счетчик устройств.
static struct cdev my_dummy_cdev;       // Представление символьного устройства.
static dev_t first;                     // Старший/младший номера.



// Файловые операции.
static struct file_operations fops = {
    .owner = THIS_MODULE
};



static int __init dummy_init(void)
{
    // Регистрация пула номеров для устройств, динамическое выделение старшего номера.
    int err = alloc_chrdev_region(&first, 0, count_dev, MYDEV_NAME);
 
    if(err < 0){
        printk(KERN_ERR "my_dummy_device : alloc_chrdev_region ERROR (code: %d )\n", err);
        return -1;
    }

    // Инициализация cdev структуры.
    cdev_init(&my_dummy_cdev, &fops);

    // Добавления устройства в систему.
    err = cdev_add(&my_dummy_cdev, first, count_dev);

    if(err < 0){
        printk(KERN_ERR "my_dummy_device : cdev_add ERROR (code: %d )\n", err);
        unregister_chrdev_region(first, count_dev);
        return -1;
    }

    printk(KERN_INFO "my_dummy_device : REGISTRATION SUCCESSFUL\n");
    printk(KERN_INFO "my_dummy_device : MAJOR = %d, MINOR = %d\n", MAJOR(first), MINOR(first));
    return 0;
}



static void __exit dummy_exit(void)
{
    // Удаление устройства из системы.
    cdev_del(&my_dummy_cdev);

    // Отмена регистраций номеров устройств.
    unregister_chrdev_region(first, count_dev);
    printk(KERN_INFO "my_dummy_device : DEREGISTRATION\n");
}

module_init(dummy_init);
module_exit(dummy_exit);
