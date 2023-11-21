
#include <zephyr/types.h>
#include <stddef.h>
#include <string.h>
#include <errno.h>
#include <zephyr/sys/printk.h>
#include <zephyr/kernel.h>

#include "ble.h"
#include "wifi.h"

static uint8_t device_name[] = {'P', 'V', '0', '0', '0', '0', '0', '0'};

int main(void)
{
	// struct net_if *iface = net_if_get_default();
	// struct net_linkaddr *mac_addr = net_if_get_link_addr(iface);
	struct net_linkaddr *mac_addr = initialize_wifi();

	k_sleep(K_SECONDS(1));

	initialize_bluetooth();

	if (mac_addr)
	{
		update_dev_name(device_name, mac_addr);
	}

	set_bluetooth_name(device_name, sizeof(device_name));
	start_advertising();
	initialize_advertisement_state_workers();

	// net_mgmt(NET_REQUEST_WIFI_CONNECT_STORED, iface, NULL, 0);

	return 0;
}
