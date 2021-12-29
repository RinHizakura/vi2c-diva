#define pr_fmt(fmt) "[i2c-diva-dev] " fmt

#include <linux/i2c.h>
#include <linux/module.h>

static int diva_i2c_dev_probe(struct i2c_client *client,
                              const struct i2c_device_id *id)
{
    pr_info("Connect to diva dev %s\n", client->name);
    return 0;
}

static int diva_i2c_dev_remove(struct i2c_client *client)
{
    return 0;
}

static const struct i2c_device_id diva_i2c_dev_id[] = {
    {"vi2c,diva-i2c", 0},
    {},
};

static struct i2c_driver diva_i2c_dev_driver = {
    .probe = diva_i2c_dev_probe,
    .remove = diva_i2c_dev_remove,
    .driver =
        {
            .name = "diva-dev",
            .owner = THIS_MODULE,
        },
    .id_table = diva_i2c_dev_id,
};
module_i2c_driver(diva_i2c_dev_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("RinHizakura");
MODULE_DESCRIPTION("The virtual \"diva\" I2c device driver");
