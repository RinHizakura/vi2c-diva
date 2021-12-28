#define pr_fmt(fmt) "[i2c-diva-adap] " fmt

#include <linux/module.h>
#include <linux/i2c.h>
#include <linux/mod_devicetable.h>
#include <linux/platform_device.h>

struct diva_i2c_dev {
    struct device *dev;
    struct i2c_adapter adapter;
};

static int diva_i2c_xfer(struct i2c_adapter *adap,
                         struct i2c_msg msgs[],
                         int num)
{
    return 0;
}

static u32 diva_i2c_func(struct i2c_adapter *adap)
{
    return I2C_FUNC_I2C | I2C_FUNC_SMBUS_EMUL;
}

static struct i2c_algorithm diva_i2c_algo = {.master_xfer = diva_i2c_xfer,
                                             .functionality = diva_i2c_func};

static int diva_i2c_probe(struct platform_device *pdev)
{
    int ret;
    struct diva_i2c_dev *i2c_dev;
    struct i2c_adapter *adap;

    i2c_dev = devm_kzalloc(&pdev->dev, sizeof(struct diva_i2c_dev), GFP_KERNEL);
    if (!i2c_dev)
        return -ENOMEM;
    platform_set_drvdata(pdev, i2c_dev);
    i2c_dev->dev = &pdev->dev;

    adap = &i2c_dev->adapter;
    i2c_set_adapdata(adap, i2c_dev);
    adap->owner = THIS_MODULE;
    adap->class = I2C_CLASS_DEPRECATED;
    snprintf(adap->name, sizeof(adap->name), "%s", pdev->name);
    adap->algo = &diva_i2c_algo;
    adap->dev.parent = &pdev->dev;

    ret = i2c_add_adapter(adap);
    pr_info("Connect to diva %s\n", adap->name);
    return ret;
}

static int diva_i2c_remove(struct platform_device *pdev)
{
    return 0;
}

static const struct of_device_id diva_i2c_of_match[] = {
    {.compatible = "vi2c,diva-i2c"},
    {.compatible = "vi2c,vivy-i2c"},
    {},
};
MODULE_DEVICE_TABLE(of, diva_i2c_of_match);

struct platform_driver diva_i2c_driver = {
    .probe = diva_i2c_probe,
    .remove = diva_i2c_remove,
    .driver =
        {
            .name = "i2c-diva",
            .of_match_table = diva_i2c_of_match,
        },
};
module_platform_driver(diva_i2c_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("RinHizakura");
MODULE_DESCRIPTION("The virtual \"diva\" I2c bus adapter \"diva\"");
