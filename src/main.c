#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/sensor.h>
#include <zephyr/logging/log.h>
#include <zephyr/sys/printk.h>

LOG_MODULE_REGISTER(main, LOG_LEVEL_INF);

#define SCD41_NODE DT_NODELABEL(scd41)

int main(void)
{
    struct sensor_value co2, temp, humidity;
    const struct device *scd41 = DEVICE_DT_GET(SCD41_NODE);

if (!device_is_ready(scd41)) {
		printk("SCD41 not ready\n");
		return -ENODEV;
	}

printk("Sensor ready: %s\n", scd41->name);

while (1) {
		/* Fetch sensor data */
		int rc = sensor_sample_fetch(scd41);
		if (rc != 0) {
			LOG_ERR("Failed to fetch sensor data: %d\n", rc);
			k_msleep(1000);
			continue;
		}

		sensor_channel_get(scd41, SENSOR_CHAN_CO2, &co2);
		sensor_channel_get(scd41, SENSOR_CHAN_AMBIENT_TEMP, &temp);
		sensor_channel_get(scd41, SENSOR_CHAN_HUMIDITY, &humidity);
		LOG_INF("CO2: %d.%d ppm | Temp: %d.%d°C | Humidity: %d.%d%%\n",
			co2.val1, co2.val2 / 100000,
			temp.val1, temp.val2 / 100000,
			humidity.val1, humidity.val2 / 100000);

		k_msleep(5000);
	}

	return 0;
}
