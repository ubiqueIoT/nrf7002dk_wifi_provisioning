#ifndef _WIFI_H_
#define _WIFI_H

#include <zephyr/net/wifi.h>
#include <zephyr/net/wifi_mgmt.h>
#include <net/wifi_credentials.h>
#include <net/wifi_mgmt_ext.h>

void update_dev_name(uint8_t *device_name, struct net_linkaddr *mac_addr);

#endif /* _WIFI_H_*/