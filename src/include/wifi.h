#ifndef _WIFI_H_
#define _WIFI_H

#include <zephyr/kernel.h>
#include <zephyr/sys/reboot.h>
#include <zephyr/dfu/mcuboot.h>

#include <zephyr/net/wifi.h>
#include <zephyr/net/wifi_mgmt.h>
#include <zephyr/net/conn_mgr_connectivity.h>
#include <zephyr/net/conn_mgr_monitor.h>

#include <net/wifi_credentials.h>
#include <net/wifi_mgmt_ext.h>

#include <zephyr/logging/log.h>
#include <zephyr/logging/log_ctrl.h>

#include <stdio.h>
#include <stdlib.h>
#include <modem/modem_info.h>

#define CONN_LAYER_EVENT_MASK (NET_EVENT_CONN_IF_FATAL_ERROR)
#define L4_EVENT_MASK (NET_EVENT_L4_CONNECTED | NET_EVENT_L4_DISCONNECTED)

#define CONNECTION_RETRY_TIMEOUT_SECONDS 30

/* Macro called upon a fatal error, reboots the device. */
#define FATAL_ERROR()                              \
    LOG_ERR("Fatal error! Rebooting the device."); \
    LOG_PANIC();                                   \
    IF_ENABLED(CONFIG_REBOOT, (sys_reboot(0)))

void update_dev_name(uint8_t *device_name, struct net_linkaddr *mac_addr);
struct net_linkaddr *initialize_wifi(void);

#endif /* _WIFI_H_*/