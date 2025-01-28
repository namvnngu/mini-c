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
  void *data;
  uint32_t count;
  uint32_t unit_size;
  uint32_t *indices;
};

struct ecs_world {
  uint32_t *entities;
  uint32_t *components;
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
