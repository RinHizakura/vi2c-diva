#define pr_fmt(fmt) "[i2c-diva-adap] " fmt

#include <linux/i2c.h>
#include <linux/mod_devicetable.h>
#include <linux/module.h>
#include <linux/platform_device.h>

struct diva_i2c_dev {
    struct device *dev;
    struct i2c_adapter adapter;
    struct i2c_client *client;
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

static struct i2c_algorithm diva_i2c_algo = {
    .master_xfer = diva_i2c_xfer,
    .functionality = diva_i2c_func,
};

static struct i2c_board_info diva_i2c_board_info = {
    I2C_BOARD_INFO("vi2c,diva-i2c", 0x1),
};

static int diva_i2c_add_client(struct diva_i2c_dev *i2c_dev)
{
    i2c_dev->client =
        i2c_new_client_device(&i2c_dev->adapter, &diva_i2c_board_info);
    if (IS_ERR(i2c_dev->client))
        return -ENODEV;

    return 0;
}

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
    if (ret < 0)
        goto fail_ret;

    ret = diva_i2c_add_client(i2c_dev);
    if (ret < 0)
        goto del_adap;

    pr_info("Connect to diva adap %s\n", adap->name);
    return 0;

del_adap:
    i2c_del_adapter(adap);
fail_ret:
    return ret;
}

static int diva_i2c_remove(struct platform_device *pdev)
{
    struct diva_i2c_dev *i2c_dev = dev_get_drvdata(&pdev->dev);
    i2c_del_adapter(&i2c_dev->adapter);
    return 0;
}

struct platform_driver diva_i2c_driver = {
    .probe = diva_i2c_probe,
    .remove = diva_i2c_remove,
    .driver =
        {
            .name = "i2c-diva",
        },
};
module_platform_driver(diva_i2c_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("RinHizakura");
MODULE_DESCRIPTION("The virtual \"diva\" I2c bus adapter");
