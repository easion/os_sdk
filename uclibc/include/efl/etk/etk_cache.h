/** @file etk_cache.h */
#ifndef _ETK_CACHE_H_
#define _ETK_CACHE_H_

#include <Evas.h>
#include "etk_types.h"

/**
 * @defgroup Etk_Cache Cache system of Etk
 * @brief The cache system is used by widgets that frequently need to load images, such as Etk_Tree or Etk_Iconbox
 * @{
 */


/**
 * @brief A system used to cache image objects for widgets that frequently need to load images
 * @structinfo
 */
struct Etk_Cache
{
   /* private: */
   Evas_List *cached_objects;
   int size;

   void (*free_cb)(Evas_Object *object, void *data);
   void *free_cb_data;
};


Etk_Cache   *etk_cache_new(int size);
void         etk_cache_destroy(Etk_Cache *cache);
void         etk_cache_clear(Etk_Cache *cache);

void         etk_cache_free_callback_set(Etk_Cache *cache, void (*free_cb)(Evas_Object *object, void *data), void *data);
void         etk_cache_size_set(Etk_Cache *cache, int size);
int          etk_cache_size_get(Etk_Cache *cache);
int          etk_cache_num_objects_get(Etk_Cache *cache);

void         etk_cache_add(Etk_Cache *cache, Evas_Object *object, const char *filename, const char *key);
void         etk_cache_remove(Etk_Cache *cache, Evas_Object *object);
Evas_Object *etk_cache_find(Etk_Cache *cache, const char *filename, const char *key);

/** @} */

#endif
