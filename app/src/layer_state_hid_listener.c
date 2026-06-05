/*
 * Copyright (c) 2024 The ZMK Contributors
 *
 * SPDX-License-Identifier: MIT
 */

#include <zmk/event_manager.h>
#include <zmk/events/layer_state_changed.h>
#include <zmk/events/endpoint_changed.h>
#include <zmk/hid.h>
#include <zmk/endpoints.h>
#include <zmk/keymap.h>

static void send_current_layer_state(void) {
    zmk_keymap_layer_index_t index = zmk_keymap_highest_layer_active();
    zmk_hid_layer_state_set(index, 0);
    zmk_endpoint_send_layer_state_report();
}

static int layer_state_hid_listener(const zmk_event_t *eh) {
    send_current_layer_state();
    return ZMK_EV_EVENT_BUBBLE;
}

ZMK_LISTENER(layer_state_hid_listener, layer_state_hid_listener);
ZMK_SUBSCRIPTION(layer_state_hid_listener, zmk_layer_state_changed);
ZMK_SUBSCRIPTION(layer_state_hid_listener, zmk_endpoint_changed);
