#define pr_fmt(fmt) "[i2c-diva]" fmt

#include <linux/module.h>
#include <linux/platform_device.h>
#include "pdev_drv.h"

static void diva_i2c_dummy_release(struct device *dev) {}
static struct platform_device diva_pdev = {
    .name = DEVICE_NAME,
    .id = -1,
    .dev.release = diva_i2c_dummy_release,
};

static int __init diva_init(void)
{
    int ret = 0;

    pr_info("Ready to init diva\n");
    ret = platform_device_register(&diva_pdev);

    if (ret == 0) {
        ret = platform_driver_register(&diva_i2c_driver);
    }

    pr_info("Init diva with status %d\n", ret);
    return ret;
}
module_init(diva_init);

static void __exit diva_exit(void)
{
    platform_driver_unregister(&diva_i2c_driver);
    platform_device_unregister(&diva_pdev);
    pr_info("Exit from diva\n");
}
module_exit(diva_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("RinHizakura");
MODULE_DESCRIPTION("The virtual I2c platform device \"diva\"");
