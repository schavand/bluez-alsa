/*
 * BlueALSA - dbus.h
 * Copyright (c) 2016-2021 Arkadiusz Bokowy
 *
 * This file is a part of bluez-alsa.
 *
 * This project is licensed under the terms of the MIT license.
 *
 */

#pragma once
#ifndef BLUEALSA_DBUS_H_
#define BLUEALSA_DBUS_H_

#include <stdbool.h>

#include <gio/gio.h>
#include <glib-object.h>
#include <glib.h>

#define DBUS_SERVICE "org.freedesktop.DBus"

#define DBUS_IFACE_DBUS             DBUS_SERVICE
#define DBUS_IFACE_OBJECT_MANAGER   DBUS_SERVICE ".ObjectManager"
#define DBUS_IFACE_PROPERTIES       DBUS_SERVICE ".Properties"

/* Compatibility patch for glib < 2.42. */
#ifndef G_DBUS_ERROR_UNKNOWN_OBJECT
# define G_DBUS_ERROR_UNKNOWN_OBJECT G_DBUS_ERROR_FAILED
#endif

/**
 * Definition of a D-Bus method call dispatcher. */
typedef struct _GDBusMethodCallDispatcher {
	const char *sender;
	const char *path;
	const char *interface;
	const char *method;
	void (*handler)(GDBusMethodInvocation *, void *);
	/* if true, handler will be called in a separate thread */
	bool asynchronous_call;
} GDBusMethodCallDispatcher;

typedef struct _GDBusInterfaceSkeletonVTable {
	const GDBusMethodCallDispatcher *dispatchers;
	GVariant *(*get_properties)(void *userdata);
	GVariant *(*get_property)(const char *property, GError **error, void *userdata);
	bool (*set_property)(const char *property, GVariant *value, GError **error, void *userdata);
} GDBusInterfaceSkeletonVTable;

/**
 * Definition for interface skeleton with callbacks. */
typedef struct _GDBusInterfaceSkeletonEx {
	GDBusInterfaceSkeleton parent;
	GDBusInterfaceInfo *interface_info;
	GDBusInterfaceSkeletonVTable vtable;
	/* user data passed to callback functions */
	void *userdata;
} GDBusInterfaceSkeletonEx;

bool g_dbus_dispatch_method_call(const GDBusMethodCallDispatcher *dispatchers,
		const char *sender, const char *path, const char *interface, const char *method,
		GDBusMethodInvocation *invocation, void *userdata);

GDBusInterfaceInfo *g_dbus_interface_skeleton_ex_class_get_info(
		GDBusInterfaceSkeleton *interface_skeleton);

GDBusInterfaceVTable *g_dbus_interface_skeleton_ex_class_get_vtable(
		GDBusInterfaceSkeleton *interface_skeleton);

GVariant *g_dbus_interface_skeleton_ex_class_get_properties(
		GDBusInterfaceSkeleton *interface_skeleton);

void *g_dbus_interface_skeleton_ex_new(GType interface_skeleton_type,
		GDBusInterfaceInfo *interface_info, const GDBusInterfaceSkeletonVTable *vtable,
		void *userdata, GDestroyNotify userdata_free_func);

bool g_dbus_connection_emit_properties_changed(GDBusConnection *conn,
		const char *path, const char *interface, GVariantBuilder *props,
		GError **error);

GVariantIter *g_dbus_get_managed_objects(GDBusConnection *conn,
		const char *name, const char *path, GError **error);

GVariant *g_dbus_get_property(GDBusConnection *conn, const char *service,
		const char *path, const char *interface, const char *property,
		GError **error);
bool g_dbus_set_property(GDBusConnection *conn, const char *service,
		const char *path, const char *interface, const char *property,
		const GVariant *value, GError **error);

#endif
