#include "../../my_cache.h"
#include "../../../../include/data_struct/lru_list.h"

#define DATAFROMLN(ln) (((coarse_cache*)((ln)->data))->data)
#define ETRFROMLN(ln) (((coarse_cache*)((ln)->data))->etr)

#define GETOFFSET(lba) TRANSOFFSET(lba)

typedef struct coarse_cache{
	char *data;
	GTD_entry *etr;
}coarse_cache;

typedef struct coarse_cache_monitor{
	uint32_t max_caching_page;
	uint32_t now_caching_page;
	LRU *lru;
}coarse_cache_monitor;

uint32_t coarse_init(struct my_cache *, uint32_t total_caching_physical_pages);
uint32_t coarse_free(struct my_cache *);
bool coarse_is_needed_eviction(struct my_cache *, uint32_t lba);
uint32_t coarse_update_entry(struct my_cache *, GTD_entry *, uint32_t lba, uint32_t ppa);
uint32_t coarse_update_entry_gc(struct my_cache *, GTD_entry *, uint32_t lba, uint32_t ppa);
uint32_t coarse_insert_entry_from_translation(struct my_cache *, GTD_entry *, uint32_t lba, char *data);
uint32_t coarse_update_from_translation_gc(struct my_cache *, char *data, uint32_t lba, uint32_t ppa);
uint32_t coarse_get_mapping(struct my_cache *, uint32_t lba);
struct GTD_entry *coarse_get_eviction_GTD_entry(struct my_cache *);//if return value is NULL, it is clean eviction.
bool coarse_update_eviction_target_translation(struct my_cache* , GTD_entry *etr, mapping_entry * map, char *data);
bool coarse_exist(struct my_cache *, uint32_t lba);
