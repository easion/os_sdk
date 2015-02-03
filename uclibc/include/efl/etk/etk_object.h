/** @file etk_object.h */
#ifndef _ETK_OBJECT_H_
#define _ETK_OBJECT_H_

#include <Evas.h>
#include <stdarg.h>
#include "etk_type.h"
#include "etk_types.h"

/* TODO/FIXME list:
 * - etk_object_type_get() and etk_object_object_type_get() are confusing: maybe we should rename them
 * - instead of having one list for all the signal-callbacks, we could maybe use one list per type of signal. It
 * would make things more optimized
 * - Dont use hash for the notification-callbacks, a hash is probably to big just for that
 */

/**
 * @defgroup Etk_Object Etk_Object
 * @brief The Etk_Object class is the base class for all the objects and widgets of Etk
 * @{
 */

#ifndef ETK_DISABLE_CAST_CHECKS
   #define ETK_OBJECT_CAST(obj, etk_type, c_type) \
      ((c_type *)etk_object_check_cast((Etk_Object *)(obj), (etk_type)))
#else
   #define ETK_OBJECT_CAST(obj, etk_type, c_type)     ((c_type *)(obj))
#endif

#define ETK_OBJECT_CHECK_TYPE(obj, etk_type) \
   (etk_type_inherits_from(((Etk_Object *)(obj))->type, (etk_type)))


/** Gets the type of an object */
#define ETK_OBJECT_TYPE       (etk_object_type_get())
/** Casts the object to an Etk_Object */
#define ETK_OBJECT(obj)       (ETK_OBJECT_CAST((obj), ETK_OBJECT_TYPE, Etk_Object))
/** Checks if the object is an Etk_Object */
#define ETK_IS_OBJECT(obj)    (ETK_OBJECT_CHECK_TYPE((obj), ETK_OBJECT_TYPE))


/**
 * @brief A callback called each time the value of the associated property is modified
 * @structinfo
 */
struct Etk_Notification_Callback
{
   /* private: */
   void (*callback)(Etk_Object *object, const char *property_name, void *data);
   void *data;
   Etk_Bool delete_me;
};

/**
 * @brief @object The base class for all the objects and widgets of Etk
 * @structinfo
 */
struct Etk_Object
{
   /* private: */
   Etk_Type *type;
   char *name;
   Etk_Bool destroy_me;

   Etk_Object *prev;
   Etk_Object *next;

   Evas_Hash *data_hash;
   Evas_List *signal_callbacks;
   Evas_List *weak_pointers;
   Evas_Hash *notification_callbacks;
   Etk_Bool should_delete_cbs;
   int notifying;
};


void        etk_object_shutdown(void);
void        etk_object_purge(void);

Etk_Type   *etk_object_type_get(void);
Etk_Object *etk_object_new(Etk_Type *object_type, const char *first_property, ...);
Etk_Object *etk_object_new_valist(Etk_Type *object_type, const char *first_property, va_list args);
void        etk_object_destroy(Etk_Object *object);

void        etk_object_name_set(Etk_Object *object, const char *name);
const char *etk_object_name_get(Etk_Object *object);
Etk_Object *etk_object_name_find(const char *name);

Etk_Object *etk_object_check_cast(Etk_Object *object, Etk_Type *type);
Etk_Type   *etk_object_object_type_get(Etk_Object *object);

void        etk_object_signal_callback_add(Etk_Object *object, Etk_Signal_Callback *signal_callback, Etk_Bool after);
void        etk_object_signal_callback_remove(Etk_Object *object, Etk_Signal_Callback *signal_callback);
void        etk_object_signal_callbacks_get(Etk_Object *object, Etk_Signal *signal, Evas_List **callbacks);

void        etk_object_weak_pointer_add(Etk_Object *object, void **pointer_location);
void        etk_object_weak_pointer_remove(Etk_Object *object, void **pointer_location);

void        etk_object_data_set(Etk_Object *object, const char *key, void *value);
void        etk_object_data_set_full(Etk_Object *object, const char *key, void *value, void (*free_cb)(void *data));
void       *etk_object_data_get(Etk_Object *object, const char *key);

void        etk_object_property_reset(Etk_Object *object, const char *property_name);
void        etk_object_properties_set(Etk_Object *object, const char *first_property, ...);
void        etk_object_properties_set_valist(Etk_Object *object, const char *first_property, va_list args);
void        etk_object_properties_get(Etk_Object *object, const char *first_property, ...);
void        etk_object_properties_get_valist(Etk_Object *object, const char *first_property, va_list args);

void        etk_object_notify(Etk_Object *object, const char *property_name);
void        etk_object_notification_callback_add(Etk_Object *object, const char *property_name, void (*callback)(Etk_Object *object, const char *property_name, void *data), void *data);
void        etk_object_notification_callback_remove(Etk_Object *object, const char *property_name, void (*callback)(Etk_Object *object, const char *property_name, void *data));

/** @} */

#endif
