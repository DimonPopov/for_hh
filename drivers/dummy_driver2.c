#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/usb.h>


MODULE_LICENSE("GPL");
MODULE_AUTHOR("Popov D.S.");
MODULE_DESCRIPTION("my_dummy_device driver");
MODULE_VERSION("0.1");

#define MYDEV_NAME "my_dummy_device"    // Название для устройства.
#define VENDOR_ID 0x090c                // Идентификатор поставщика.
#define PRODUCT_ID 0x1000               // Идентификатор устройства.



// Таблица usb устройств.
static struct usb_device_id dummy_table[] = {
    { USB_DEVICE(VENDOR_ID, PRODUCT_ID) },
    { }
};


// При подключений устройства.
static int dummy_probe(struct usb_interface *interface, const struct usb_device_id *id)
{
    printk(KERN_INFO "my_dummy_device(%d , %d) : connected", id->idVendor, id->idProduct);
    return 0;
}


// При отключений устройства.
static void dummy_disconnect(struct usb_interface *interface)
{
    printk(KERN_INFO "my_dummy_device : disconnected");
}


// Скелет драйвера.
static struct usb_driver dummy_driver = {
    .name = MYDEV_NAME,
    .id_table = dummy_table,
    .probe = dummy_probe,
    .disconnect = dummy_disconnect,
};


// Загрузка модуля, регистрация usb.
static int __init driver_int(void)
{
    // Регистрация usb.
    int ret = usb_register(&dummy_driver);

    if(ret < 0){
        printk(KERN_ERR "my_dummy_device : REGISTRATION ERROR (code: %d )\n", ret);
        return -1;
    }else{
        printk(KERN_INFO "my_dummy_device : REGISTRATION SUCCESSFUL\n");
    }

    return 0;
}


// Выгрузка модуля, отмена регистрации usb.
static void __exit driver_exit(void)
{
    usb_deregister(&dummy_driver);
    printk(KERN_INFO "my_dummy_device : DEREGISTRATION\n");
}

module_init(driver_int);
module_exit(driver_exit);