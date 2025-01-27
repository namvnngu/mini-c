#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

#define MAX_ENTITIES   300
#define MAX_COMPONENTS 10

typedef uint32_t ecs_entity_t;
typedef uint32_t ecs_component_t;

struct ecs_component_pool {
  void *data;
  uint32_t count;
  uint32_t unit_size;
  uint32_t *indices;
};

struct ecs_world {
  uint32_t *entities;
  uint32_t *components;
  ecs_component_pool *component_pools;
};
