#define pr_fmt(fmt) "[i2c-diva]" fmt

#include <linux/mod_devicetable.h>
#include <linux/module.h>
#include <linux/platform_device.h>

#define DEVICE_NAME "diva-i2c"

static void diva_i2c_dummy_release(struct device *dev) {}

static struct platform_device diva_pdev = {
    .name = DEVICE_NAME,
    .id = -1,
    .dev.release = diva_i2c_dummy_release,
};

static int diva_i2c_probe(struct platform_device *pdev)
{
    printk("Connect");
    return 0;
}

static int diva_i2c_remove(struct platform_device *pdev)
{
    return 0;
}

static struct platform_device_id diva_idtbl[] = {
    {"diva"},
    {"vivy"},
    {},
};

static struct platform_driver diva_i2c = {
    .probe = diva_i2c_probe,
    .remove = diva_i2c_remove,
    .driver =
        {
            .name = DEVICE_NAME,
        },
    .id_table = diva_idtbl,
};

static int __init diva_init(void)
{
    int ret = 0;

    ret = platform_device_register(&diva_pdev);

    if (ret == 0) {
        ret = platform_driver_register(&diva_i2c);
    }

    printk("Open");
    return ret;
}
module_init(diva_init);

static void __exit diva_exit(void)
{
    platform_driver_unregister(&diva_i2c);
    platform_device_unregister(&diva_pdev);
    printk("Shutdown");
}
module_exit(diva_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("RinHizakura");
MODULE_DESCRIPTION("The virtual I2c platform device \"diva\"");
