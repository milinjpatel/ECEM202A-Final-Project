#pragma once
#include <stdint.h>
#include <stdbool.h>

#include "ble.h"
#include "ble_srv_common.h"

#define CUSTOM_SERVICE_UUID_BASE {0xE8, 0xBF, 0xF6, 0x3E, 0xBA, 0x82, 0xA8, 0xB3, \
                                  0xE2, 0x47, 0x95, 0xE4, 0x62, 0x62, 0x00, 0x84}
#define CUSTOM_SERVICE_UUID      0x2400
#define CUSTOM_VALUE_CHAR_UUID   0x2401

#define BLE_CUS_DEF(_name) static ble_cus_t _name; \
NRF_SDH_BLE_OBSERVER(_name ## _obs, \
                     BLE_HRS_BLE_OBSERVER_PRIO,                                                     \
                     ble_cus_on_ble_evt, &_name)

typedef struct
{
    uint8_t                       initial_custom_value;           /**< Initial custom value */
    ble_srv_cccd_security_mode_t  custom_value_char_attr_md;     /**< Initial security level for Custom characteristics attribute */
} ble_cus_init_t;

struct ble_cus_s
{
    uint16_t                      service_handle;                 /**< Handle of Custom Service (as provided by the BLE stack). */
    ble_gatts_char_handles_t      custom_value_handles;           /**< Handles related to the Custom Value characteristic. */
    uint16_t                      conn_handle;                    /**< Handle of the current connection (as provided by the BLE stack, is BLE_CONN_HANDLE_INVALID if not in a connection). */
    uint8_t                       uuid_type;
};

typedef struct ble_cus_s ble_cus_t;

uint32_t ble_cus_init(ble_cus_t* p_cus, const ble_cus_init_t* p_cus_init);
void ble_cus_on_ble_evt(ble_evt_t const* p_ble_evt, void* p_context);