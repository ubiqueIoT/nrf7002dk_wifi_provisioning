#include "wifi.h"
#include "utils.h"

LOG_MODULE_REGISTER(aws_iot_logging, LOG_LEVEL_DBG);

static struct net_mgmt_event_callback l4_cb;
static struct net_mgmt_event_callback conn_cb;

static void connect_work_fn(struct k_work *work);
static K_WORK_DELAYABLE_DEFINE(connect_work, connect_work_fn);

void update_dev_name(uint8_t *device_name, struct net_linkaddr *mac_addr)
{
    byte_to_hex(&device_name[2], mac_addr->addr[3], 'A');
    byte_to_hex(&device_name[4], mac_addr->addr[4], 'A');
    byte_to_hex(&device_name[6], mac_addr->addr[5], 'A');
}

static void connect_work_fn(struct k_work *work)
{
    // TODO!!!!!!!!!!!!!!!!!
    int err;
    // const struct aws_iot_config config = {
    //     .client_id = hw_id,
    // };

    LOG_INF("Connecting to AWS IoT");

    // err = aws_iot_connect(&config);
    if (err == -EAGAIN)
    {
        LOG_INF("Connection attempt timed out, "
                "Next connection retry in %d seconds",
                CONNECTION_RETRY_TIMEOUT_SECONDS);

        (void)k_work_reschedule(&connect_work, K_SECONDS(CONNECTION_RETRY_TIMEOUT_SECONDS));
    }
    else if (err)
    {
        LOG_ERR("aws_iot_connect, error: %d", err);
        FATAL_ERROR();
    }
}

static void l4_event_handler(struct net_mgmt_event_callback *cb,
                             uint32_t event,
                             struct net_if *iface)
{
    switch (event)
    {
    case NET_EVENT_L4_CONNECTED:
        LOG_INF("Network connectivity established");
        // on_net_event_l4_connected(); TODO!!!!!!!!!!!!!!!!!!!!
        break;
    case NET_EVENT_L4_DISCONNECTED:
        LOG_INF("Network connectivity lost");
        // on_net_event_l4_disconnected(); TODO!!!!!!!!!!!!!!!!!!!!
        break;
    default:
        /* Don't care */
        return;
    }
}

static void connectivity_event_handler(struct net_mgmt_event_callback *cb,
                                       uint32_t event,
                                       struct net_if *iface)
{
    if (event == NET_EVENT_CONN_IF_FATAL_ERROR)
    {
        LOG_ERR("NET_EVENT_CONN_IF_FATAL_ERROR");
        FATAL_ERROR();
        return;
    }
}

struct net_linkaddr *initialize_wifi()
{
    struct net_if *iface = net_if_get_default();
    struct net_linkaddr *mac_addr = net_if_get_link_addr(iface);

    net_mgmt(NET_REQUEST_WIFI_CONNECT_STORED, iface, NULL, 0);

    /* Setup handler for Zephyr NET Connection Manager events. */
    net_mgmt_init_event_callback(&l4_cb, l4_event_handler, L4_EVENT_MASK);
    net_mgmt_add_event_callback(&l4_cb);

    /* Setup handler for Zephyr NET Connection Manager Connectivity layer. */
    net_mgmt_init_event_callback(&conn_cb, connectivity_event_handler, CONN_LAYER_EVENT_MASK);
    net_mgmt_add_event_callback(&conn_cb);

    return mac_addr;
}