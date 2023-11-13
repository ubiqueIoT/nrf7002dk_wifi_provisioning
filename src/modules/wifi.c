#include "wifi.h"
#include "utils.h"

void update_dev_name(uint8_t *device_name, struct net_linkaddr *mac_addr)
{
    byte_to_hex(&device_name[2], mac_addr->addr[3], 'A');
    byte_to_hex(&device_name[4], mac_addr->addr[4], 'A');
    byte_to_hex(&device_name[6], mac_addr->addr[5], 'A');
}
