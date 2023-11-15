#pragma once

#include <stdlib.h>
#include <string.h>

typedef void coroutine_context_t;

#define COROUTINE_CONTEXT_BEGIN()                                              \
  struct __coroutine_data_t {                                                  \
    int __coroutine_pos

#define COROUTINE_CONTEXT_END(_arg)                                            \
  }                                                                            \
  *coroutine_context = (struct __coroutine_data_t *)*_arg;                     \
  struct __coroutine_data_t **__coroutine_ctx =                                \
      (struct __coroutine_data_t **)_arg

#define COROUTINE_BEGIN()                                                      \
  if (!coroutine_context) {                                                    \
    coroutine_context = *__coroutine_ctx =                                     \
        (struct __coroutine_data_t *)malloc(                                   \
            sizeof(struct __coroutine_data_t));                                \
    memset(coroutine_context, 0, sizeof(*coroutine_context));                  \
    coroutine_context->__coroutine_pos = 0;                                    \
  }                                                                            \
  if (coroutine_context)                                                       \
    switch (coroutine_context->__coroutine_pos) {                              \
    case 0:;

#define COROUTINE_FINISH()                                                     \
  }                                                                            \
  free(*__coroutine_ctx);                                                      \
  *__coroutine_ctx = NULL

#define COROUTINE_YIELD(...)                                                   \
  {                                                                            \
    ((struct __coroutine_data_t *)*__coroutine_ctx)->__coroutine_pos =         \
        __LINE__;                                                              \
    return __VA_ARGS__;                                                        \
  case __LINE__:;                                                              \
  }

#define COROUTINE_YIELD_AND_KEEP_LAST_ENTRYPOINT(...) return __VA_ARGS__;

#define COROUTINE_STOP(...)                                                    \
  {                                                                            \
    free(*__coroutine_ctx);                                                    \
    *__coroutine_ctx = 0;                                                      \
    return __VA_ARGS__;                                                        \
  }

#define COROUTINE_ABORT(_ctx)                                                  \
  {                                                                            \
    free(_ctx);                                                                \
    _ctx = NULL;                                                               \
  }
