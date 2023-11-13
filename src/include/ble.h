#ifndef _BLE_H_
#define _BLE_H_

#include <zephyr/kernel.h>
#include <zephyr/bluetooth/bluetooth.h>
#include <zephyr/bluetooth/hci.h>
#include <zephyr/bluetooth/conn.h>
#include <zephyr/bluetooth/uuid.h>
#include <zephyr/bluetooth/gatt.h>

#include <bluetooth/services/wifi_provisioning.h>

#ifdef CONFIG_WIFI_PROV_ADV_DATA_UPDATE
#define ADV_DATA_UPDATE_INTERVAL CONFIG_WIFI_PROV_ADV_DATA_UPDATE_INTERVAL
#endif /* CONFIG_WIFI_PROV_ADV_DATA_UPDATE */

#define ADV_PARAM_UPDATE_DELAY 1

#define ADV_DATA_VERSION_IDX (BT_UUID_SIZE_128 + 0)
#define ADV_DATA_FLAG_IDX (BT_UUID_SIZE_128 + 1)
#define ADV_DATA_FLAG_PROV_STATUS_BIT BIT(0)
#define ADV_DATA_FLAG_CONN_STATUS_BIT BIT(1)
#define ADV_DATA_RSSI_IDX (BT_UUID_SIZE_128 + 3)

#define PROV_BT_LE_ADV_PARAM_FAST BT_LE_ADV_PARAM(BT_LE_ADV_OPT_CONNECTABLE, \
                                                  BT_GAP_ADV_FAST_INT_MIN_2, \
                                                  BT_GAP_ADV_FAST_INT_MAX_2, NULL)

#define PROV_BT_LE_ADV_PARAM_SLOW BT_LE_ADV_PARAM(BT_LE_ADV_OPT_CONNECTABLE, \
                                                  BT_GAP_ADV_SLOW_INT_MIN,   \
                                                  BT_GAP_ADV_SLOW_INT_MAX, NULL)

#define ADV_DAEMON_STACK_SIZE 4096
#define ADV_DAEMON_PRIORITY 5

int initialize_bluetooth();
void set_bluetooth_name(uint8_t *name, uint8_t name_len);
int start_advertising();
void initialize_advertisement_state_workers();

#endif /* _BLE_H_ */
