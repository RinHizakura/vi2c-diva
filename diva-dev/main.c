#define pr_fmt(fmt) "[i2c-diva-dev] " fmt

#include <linux/i2c.h>
#include <linux/module.h>

#define MSG_BUF_LEN 4

static int diva_i2c_dev_probe(struct i2c_client *client,
                              const struct i2c_device_id *id)
{
    struct i2c_msg msg;
    char buf[4];

    pr_info("Connect to diva dev %s\n", client->name);

    /* Let send some message when probing and see the reponse of adapter */
    msg.addr = client->addr;
    msg.buf = buf;
    msg.len = MSG_BUF_LEN;
    /* only make sure the RD flag being zero, so we can distinguish the
     * different between read and write transfer */
    msg.flags &= ~I2C_M_RD;

    buf[0] = 'V';
    buf[1] = 'I';
    buf[2] = 'V';
    buf[3] = 'Y';

    pr_info("Transfer message: %s\n",
            i2c_transfer(client->adapter, &msg, 1) < 0 ? "FAIL" : "PASS");
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
