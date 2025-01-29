#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_ENTITIES   300
#define MAX_COMPONENTS 10

typedef uint32_t ecs_entity_t;
typedef uint32_t ecs_component_t;

struct ecs_entity_stack {
  uint32_t data[MAX_ENTITIES];
  int16_t top;
};

struct ecs_component_pool {
  /* The array of component data. */
  void *data;

  /* The fixed number of components. */
  uint32_t count;

  /* The size of a single component. */
  uint32_t unit_size;

  /* The stack of indices pointing to unused component data in `data`. */
  uint32_t *indices;
};

struct ecs_world {
  /* The stack of unused entity IDs. */
  uint32_t *entities;

  /* The array of indices pointing to data in the component pool's data. */
  uint32_t *components;

  /* The array of component pools where indices represents component type. */
  struct ecs_component_pool *component_pools;
};

static struct ecs_entity_stack ecs__entity_stack_new() {
  struct ecs_entity_stack s;
  for (size_t i = 0; i < MAX_ENTITIES; i++) {
    s.data[i] = MAX_ENTITIES - i - 1;
  }
  s.top = MAX_ENTITIES - 1;
  return s;
}

static uint32_t ecs__entity_stack_pop(struct ecs_entity_stack *s) {
  if (s->top == -1) {
    return MAX_ENTITIES;
  }
  return s->data[s->top--];
}

static void ecs__entity_stack_push(struct ecs_entity_stack *s, uint32_t e) {
  if (s->top == MAX_ENTITIES - 1) {
    return;
  }
  s->data[++s->top] = e;
}
