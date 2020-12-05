#include <string.h>

#include "sdk_common.h"
#include "ble_srv_common.h"
#include "nrf_gpio.h"
#include "boards.h"
#include "nrf_log.h"

#include "ble_time_role_service.h"

#include "time_sync.h"

static uint32_t custom_value_char_add(ble_cus_t* p_cus, const ble_cus_init_t* p_cus_init)
{
    uint32_t            err_code;
    ble_gatts_char_md_t char_md;
    ble_gatts_attr_t    attr_char_value;
    ble_uuid_t          ble_uuid;
    ble_gatts_attr_md_t attr_md;

    memset(&char_md, 0, sizeof(char_md));

    char_md.char_props.read = 1;
    char_md.char_props.write = 1;
    char_md.char_props.notify = 0;
    char_md.p_char_user_desc = NULL;
    char_md.p_char_pf = NULL;
    char_md.p_user_desc_md = NULL;
    char_md.p_sccd_md = NULL;

    memset(&attr_md, 0, sizeof(attr_md));

    attr_md.read_perm = p_cus_init->custom_value_char_attr_md.read_perm;
    attr_md.write_perm = p_cus_init->custom_value_char_attr_md.write_perm;
    attr_md.vloc = BLE_GATTS_VLOC_STACK;
    attr_md.rd_auth = 0;
    attr_md.wr_auth = 0;
    attr_md.vlen = 0;

    ble_uuid.type = p_cus->uuid_type;
    ble_uuid.uuid = CUSTOM_VALUE_CHAR_UUID;

    memset(&attr_char_value, 0, sizeof(attr_char_value));

    attr_char_value.p_uuid = &ble_uuid;
    attr_char_value.p_attr_md = &attr_md;
    attr_char_value.init_len = sizeof(uint8_t);
    attr_char_value.init_offs = 0;
    attr_char_value.max_len = sizeof(uint8_t);

    err_code = sd_ble_gatts_characteristic_add(p_cus->service_handle, &char_md,
        &attr_char_value,
        &p_cus->custom_value_handles);
    if (err_code != NRF_SUCCESS)
    {
        return err_code;
    }

    return NRF_SUCCESS;
}

static void on_connect(ble_cus_t* p_cus, ble_evt_t const* p_ble_evt)
{
    p_cus->conn_handle = p_ble_evt->evt.gap_evt.conn_handle;
}

static void on_disconnect(ble_cus_t* p_cus, ble_evt_t const* p_ble_evt)
{
    UNUSED_PARAMETER(p_ble_evt);
    p_cus->conn_handle = BLE_CONN_HANDLE_INVALID;
}

static void on_write(ble_cus_t* p_cus, ble_evt_t const* p_ble_evt)
{
    ble_gatts_evt_write_t* p_evt_write = (ble_gatts_evt_write_t*)(&p_ble_evt->evt.gatts_evt.params.write);

    // Check if the handle passed with the event matches the Custom Value Characteristic handle.
    if (p_evt_write->handle == p_cus->custom_value_handles.value_handle)
    {
        if (p_evt_write->data[0] == 0x1)
        {
            ts_tx_start(1);
            bsp_board_led_on(BSP_BOARD_LED_2);
        }
        else if (p_evt_write->data[0] == 0x0)
        {
            ts_tx_stop();
            bsp_board_led_off(BSP_BOARD_LED_2);
        }
    }
}

uint32_t ble_cus_init(ble_cus_t* p_cus, const ble_cus_init_t* p_cus_init)
{
    if (p_cus == NULL || p_cus_init == NULL)
    {
        return NRF_ERROR_NULL;
    }

    uint32_t   err_code;
    ble_uuid_t ble_uuid;

    p_cus->conn_handle = BLE_CONN_HANDLE_INVALID;

    ble_uuid128_t base_uuid = { CUSTOM_SERVICE_UUID_BASE };
    err_code = sd_ble_uuid_vs_add(&base_uuid, &p_cus->uuid_type);
    VERIFY_SUCCESS(err_code);

    ble_uuid.type = p_cus->uuid_type;
    ble_uuid.uuid = CUSTOM_SERVICE_UUID;

    err_code = sd_ble_gatts_service_add(BLE_GATTS_SRVC_TYPE_PRIMARY, &ble_uuid, &p_cus->service_handle);
    if (err_code != NRF_SUCCESS)
    {
        return err_code;
    }
    return custom_value_char_add(p_cus, p_cus_init);;
}

void ble_cus_on_ble_evt(ble_evt_t const* p_ble_evt, void* p_context)
{
    ble_cus_t* p_cus = (ble_cus_t*)p_context;

    if (p_cus == NULL || p_ble_evt == NULL)
    {
        return;
    }

    switch (p_ble_evt->header.evt_id)
    {
    case BLE_GAP_EVT_CONNECTED:
        on_connect(p_cus, p_ble_evt);
        break;
    case BLE_GAP_EVT_DISCONNECTED:
        on_disconnect(p_cus, p_ble_evt);
        break;
    case BLE_GATTS_EVT_WRITE:
        on_write(p_cus, p_ble_evt);
        break;
    default:
        // No implementation needed.
        break;
    }
}