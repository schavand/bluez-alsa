/*
 * BlueALSA - bluez-iface.c
 * Copyright (c) 2016-2021 Arkadiusz Bokowy
 *
 * This file is a part of bluez-alsa.
 *
 * This project is licensed under the terms of the MIT license.
 *
 */

#include "bluez-iface.h"

#include <stddef.h>

static const GDBusArgInfo arg_device = {
	-1, "device", "o", NULL
};

static const GDBusArgInfo arg_transport = {
	-1, "transport", "o", NULL
};

static const GDBusArgInfo arg_fd = {
	-1, "fd", "h", NULL
};

static const GDBusArgInfo arg_capabilities = {
	-1, "capabilities", "ay", NULL
};

static const GDBusArgInfo arg_properties = {
	-1, "properties", "a{sv}", NULL
};

static const GDBusArgInfo arg_fd_properties = {
	-1, "fd_properties", "a{sv}", NULL
};

static const GDBusArgInfo *in_SelectConfiguration[] = {
	&arg_capabilities,
	NULL,
};

static const GDBusArgInfo *out_SelectConfiguration[] = {
	&arg_capabilities,
	NULL,
};

static const GDBusArgInfo *in_SetConfiguration[] = {
	&arg_transport,
	&arg_properties,
	NULL,
};

static const GDBusArgInfo *in_ClearConfiguration[] = {
	&arg_transport,
	NULL,
};

static const GDBusArgInfo *in_NewConnection[] = {
	&arg_device,
	&arg_fd,
	&arg_fd_properties,
	NULL,
};

static const GDBusArgInfo *in_RequestDisconnection[] = {
	&arg_device,
	NULL,
};

static const GDBusPropertyInfo bluez_iface_battery_provider_Device = {
	-1, "Device", "o", G_DBUS_PROPERTY_INFO_FLAGS_READABLE, NULL
};

static const GDBusPropertyInfo bluez_iface_battery_provider_Percentage = {
	-1, "Percentage", "y", G_DBUS_PROPERTY_INFO_FLAGS_READABLE, NULL
};

static const GDBusPropertyInfo bluez_iface_battery_provider_Source = {
	-1, "Source", "s", G_DBUS_PROPERTY_INFO_FLAGS_READABLE, NULL
};

static const GDBusMethodInfo bluez_iface_endpoint_SelectConfiguration = {
	-1, "SelectConfiguration",
	(GDBusArgInfo **)in_SelectConfiguration,
	(GDBusArgInfo **)out_SelectConfiguration,
	NULL,
};

static const GDBusMethodInfo bluez_iface_endpoint_SetConfiguration = {
	-1, "SetConfiguration",
	(GDBusArgInfo **)in_SetConfiguration,
	NULL,
	NULL,
};

static const GDBusMethodInfo bluez_iface_endpoint_ClearConfiguration = {
	-1, "ClearConfiguration",
	(GDBusArgInfo **)in_ClearConfiguration,
	NULL,
	NULL,
};

static const GDBusMethodInfo bluez_iface_endpoint_Release = {
	-1, "Release",
	NULL,
	NULL,
	NULL,
};

static const GDBusMethodInfo bluez_iface_profile_NewConnection = {
	-1, "NewConnection",
	(GDBusArgInfo **)in_NewConnection,
	NULL,
	NULL,
};

static const GDBusMethodInfo bluez_iface_profile_RequestDisconnection = {
	-1, "RequestDisconnection",
	(GDBusArgInfo **)in_RequestDisconnection,
	NULL,
	NULL,
};

static const GDBusMethodInfo bluez_iface_profile_Release = {
	-1, "Release",
	NULL,
	NULL,
	NULL,
};

static const GDBusPropertyInfo *bluez_iface_battery_provider_properties[] = {
	&bluez_iface_battery_provider_Device,
	&bluez_iface_battery_provider_Percentage,
	&bluez_iface_battery_provider_Source,
	NULL,
};

static const GDBusMethodInfo *bluez_iface_endpoint_methods[] = {
	&bluez_iface_endpoint_SelectConfiguration,
	&bluez_iface_endpoint_SetConfiguration,
	&bluez_iface_endpoint_ClearConfiguration,
	&bluez_iface_endpoint_Release,
	NULL,
};

static const GDBusMethodInfo *bluez_iface_profile_methods[] = {
	&bluez_iface_profile_NewConnection,
	&bluez_iface_profile_RequestDisconnection,
	&bluez_iface_profile_Release,
	NULL,
};

const GDBusInterfaceInfo bluez_iface_battery_provider = {
	-1, BLUEZ_IFACE_BATTERY_PROVIDER,
	NULL,
	NULL,
	(GDBusPropertyInfo **)bluez_iface_battery_provider_properties,
	NULL,
};

const GDBusInterfaceInfo bluez_iface_media_endpoint = {
	-1, BLUEZ_IFACE_MEDIA_ENDPOINT,
	(GDBusMethodInfo **)bluez_iface_endpoint_methods,
	NULL,
	NULL,
	NULL,
};

const GDBusInterfaceInfo bluez_iface_profile = {
	-1, BLUEZ_IFACE_PROFILE,
	(GDBusMethodInfo **)bluez_iface_profile_methods,
	NULL,
	NULL,
	NULL,
};
