#define pr_fmt(fmt) "[diva-pdev] " fmt

#include <linux/module.h>
#include <linux/platform_device.h>

static void diva_i2c_dummy_release(struct device *dev) {}
static struct platform_device diva_pdev = {
    .name = "i2c-diva",
    .id = -1,
    .dev.release = diva_i2c_dummy_release,
};

static int __init diva_init(void)
{
    int ret = 0;

    ret = platform_device_register(&diva_pdev);
    pr_info("Init diva with status %d\n", ret);
    return ret;
}
module_init(diva_init);

static void __exit diva_exit(void)
{
    platform_device_unregister(&diva_pdev);
    pr_info("Exit from diva\n");
}
module_exit(diva_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("RinHizakura");
MODULE_DESCRIPTION("The virtual I2c platform device \"diva\"");
