#ifndef _SCL_H_
#define _SCL_H_

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>

typedef uint64_t u64;
typedef int64_t i64;
typedef uint32_t u32;
typedef int32_t i32;
typedef uint16_t u16;
typedef int16_t i16;
typedef uint8_t u8;
typedef int8_t i8;
typedef u8 byte;

#ifndef MIN
#define MIN(A, B)                                                                                  \
  __extension__({                                                                                  \
    typeof(A) _a = (A);                                                                            \
    typeof(B) _b = (B);                                                                            \
    (_b) < (_a) ? (_b) : (_a);                                                                     \
  })
#endif

#ifndef MAX
#define MAX(A, B)                                                                                  \
  __extension__({                                                                                  \
    typeof(A) _a = (A);                                                                            \
    typeof(B) _b = (B);                                                                            \
    (_b) > (_a) ? (_b) : (_a);                                                                     \
  })
#endif

#define COUNT_POW(X) (31 - __builtin_clz((u32)(X)))
#define NEXT_POW(X) (((X) > 8) ? (1 << (32 - __builtin_clz((u32)(X)-1))) : 8)

#define repeat(N) for (int _L = (N), i = 0; i < _L; ++i)

#define in ,
#define foreach_in(T, A)                                                                           \
  for (u64 it_index = 0; it_index == 0; ++it_index)                                                \
    for (T *_ITER_END = arr_end(A), *it = arr_begin(A); it != _ITER_END; ++it, ++it_index)
#define foreach(...) foreach_in(__VA_ARGS__)

////////////////////
// PRINT BEGIN
////////////////////

#define _GET_NTH_ARG(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, N, ...) N
#define COUNT_VARARGS(...) _GET_NTH_ARG("ignored", ##__VA_ARGS__, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0)

#define _fe_0(_call, ...)
#define _fe_1(_call, x) _call(x)
#define _fe_2(_call, x, ...) _call(x) _fe_1(_call, __VA_ARGS__)
#define _fe_3(_call, x, ...) _call(x) _fe_2(_call, __VA_ARGS__)
#define _fe_4(_call, x, ...) _call(x) _fe_3(_call, __VA_ARGS__)
#define _fe_5(_call, x, ...) _call(x) _fe_4(_call, __VA_ARGS__)
#define _fe_6(_call, x, ...) _call(x) _fe_5(_call, __VA_ARGS__)
#define _fe_7(_call, x, ...) _call(x) _fe_6(_call, __VA_ARGS__)
#define _fe_8(_call, x, ...) _call(x) _fe_7(_call, __VA_ARGS__)
#define _fe_9(_call, x, ...) _call(x) _fe_8(_call, __VA_ARGS__)
#define _fe_10(_call, x, ...) _call(x) _fe_9(_call, __VA_ARGS__)

#define CALL_MACRO_X_FOR_EACH(x, ...)                                                              \
  _GET_NTH_ARG("ignored", ##__VA_ARGS__, _fe_10, _fe_9, _fe_8, _fe_7, _fe_6, _fe_5, _fe_4, _fe_3,  \
               _fe_2, _fe_1, _fe_0)                                                                \
  (x, ##__VA_ARGS__)

#define _FMT(x)                                                                                    \
  _Generic((x), char * : " %s", char : " %c", unsigned int : " %u", int : " %d", unsigned long: " %lu", long : " %l", float : " %f", double : " %f", default : " 0x%x")

#define print_var(x) printf(_FMT(x), (x));

// Print up to 10 things
#define print(...)                                                                                 \
  { CALL_MACRO_X_FOR_EACH(print_var, ##__VA_ARGS__) }

// Print up to 10 things and a newline
#define println(...)                                                                               \
  do {                                                                                             \
    print(__VA_ARGS__);                                                                            \
    print("\n");                                                                                   \
  } while (0)

////////////////////
// ARRAY BEGIN
////////////////////

#define ARR_STRUCT_STACK(T, N)                                                                     \
  struct {                                                                                         \
    T data[N];                                                                                     \
    byte remaining;                                                                                \
  }

#define ARR_STRUCT_HEAP(T, N)                                                                      \
  struct {                                                                                         \
    T *data;                                                                                       \
    u32 len;                                                                                       \
    byte cap, remaining;                                                                           \
  }

#define Array(T, N)                                                                                \
  struct {                                                                                         \
    _Static_assert(sizeof(T) * N >= 15,                                                            \
                   "Array stack size is too small. Must be at least 15 bytes.");                   \
    union {                                                                                        \
      ARR_STRUCT_STACK(T, N) stack;                                                                \
      ARR_STRUCT_HEAP(T, N) heap;                                                                  \
    };                                                                                             \
  }

#define arr_onstack(A) (!arr_onheap(A))
#define arr_onheap(A) ((A).stack.remaining == 0xFF)
#define arr_stacklen(A) (arr_stackcap(A) - (A).stack.remaining)
#define arr_setstacklen(A, N) ((A).stack.remaining = arr_stackcap(A) - (N))
#define arr_len(A) (arr_onheap(A) ? (A).heap.len : arr_stacklen(A))
#define arr_setlen(A, N) (arr_onheap(A) ? ((A).heap.len = (N)) : arr_setstacklen(A, N))
#define arr_inc(A) (arr_onheap(A) ? (++(A).heap.len) : (--(A).stack.remaining))
#define arr_dec(A) (arr_onheap(A) ? (--(A).heap.len) : (++(A).stack.remaining))
#define arr_stride(A) (sizeof((A).stack.data[0]))
#define arr_stackcap(A) (sizeof((A).stack.data) / arr_stride(A))
#define arr_cap(A) (arr_onheap(A) ? (1U << (A).heap.cap) : arr_stackcap(A))
#define arr_data(A) (arr_onheap(A) ? (A).heap.data : (A).stack.data)
#define arr_get(A, I) (arr_data(A)[I])
#define arr_set(A, I, V) (arr_get(A, I) = (V))
#define arr_last_value(A) arr_get(A, arr_len(A) - 1)
#define arr_begin(A) &arr_data(A)[0]
#define arr_end(A) (arr_begin(A) + arr_len(A))

#define arr_init(A, N)                                                                             \
  do {                                                                                             \
    arr_setstacklen(A, 0);                                                                         \
    arr_resize(A, N);                                                                              \
  } while (0)

#define str_init(A, S)                                                                             \
  do {                                                                                             \
    int L = strlen(S);                                                                             \
    arr_init((A), L);                                                                              \
    memcpy(arr_data(A), (S), L);                                                                   \
  } while (0)

#define arr_putstack(A)                                                                            \
  do {                                                                                             \
    void *_PTR = (A).heap.data;                                                                    \
    memcpy((A).stack.data, _PTR, sizeof((A).stack.data));                                          \
    u64 _LEN = arr_len(A);                                                                         \
    (A).stack.remaining = 0;                                                                       \
    arr_setstacklen(A, _LEN);                                                                      \
    free(_PTR);                                                                                    \
  } while (0)

#define arr_putheap(A)                                                                             \
  do {                                                                                             \
    u64 _N = NEXT_POW(arr_stackcap(A));                                                            \
    void *_PTR = malloc(_N * arr_stride(A));                                                       \
    memcpy(_PTR, (A).stack.data, sizeof((A).stack.data));                                          \
    (A).heap.data = _PTR;                                                                          \
    u64 _LEN = arr_len(A);                                                                         \
    (A).stack.remaining = 0xFF;                                                                    \
    (A).heap.cap = COUNT_POW(_N);                                                                  \
    arr_setlen(A, _LEN);                                                                           \
  } while (0)

#define arr_resize(A, N)                                                                           \
  __extension__({                                                                                  \
    u64 _N = (N);                                                                                  \
    if (_N > arr_cap(A)) {                                                                         \
      if (arr_onheap(A)) {                                                                         \
        (A).heap.cap <<= 1;                                                                        \
        (A).heap.data = realloc((A).heap.data, arr_stride(A) * arr_cap(A));                        \
      } else if (_N > arr_stackcap(A)) {                                                           \
        u64 _L = NEXT_POW(_N);                                                                     \
        void *_PTR = malloc(_L * arr_stride(A));                                                   \
        memcpy(_PTR, (A).stack.data, sizeof((A).stack.data));                                      \
        (A).heap.data = _PTR;                                                                      \
        (A).heap.cap = COUNT_POW(_L);                                                              \
        (A).stack.remaining = 0xFF;                                                                \
      }                                                                                            \
    }                                                                                              \
    arr_setlen(A, _N);                                                                             \
  })

#define arr_push(A, V) (arr_resize((A), arr_len(A) + 1), arr_set((A), arr_len(A) - 1, (V)))

#define arr_pop(A) (arr_setlen((A), arr_len(A) - 1), arr_get((A), arr_len(A)))

#define arr_free(A)                                                                                \
  do {                                                                                             \
    if (arr_onheap(A))                                                                             \
      free((A).heap.data);                                                                         \
  } while (0)

// TODO: Find closest power of two that is less than N.
// Duplicate the array sqrt(N) times.
// Copy remaining duplicates one by one
#define arr_repeat(A, N)                                                                           \
  do {                                                                                             \
    int _STRIDE = arr_len(A) * arr_stride(A);                                                      \
    arr_resize((A), arr_len(A) * (N));                                                             \
    byte *_PTR = (void *)arr_data(A);                                                              \
    for (int _L = (N), i = 1; i < _L; ++i) {                                                       \
      memcpy(_PTR + i * _STRIDE, _PTR, _STRIDE);                                                   \
    }                                                                                              \
  } while (0)

#define arr_concat(A, B)                                                                           \
  do {                                                                                             \
    int LA = arr_len(A);                                                                           \
    int LB = arr_len(B);                                                                           \
    arr_resize((A), LA + LB);                                                                      \
    byte *PTR = (void *)arr_data(A);                                                               \
    memcpy(PTR + LA * arr_stride(A), arr_data(B), LB * arr_stride(B));                             \
  } while (0)

#define arr_insert(A, I, V)                                                                        \
  do {                                                                                             \
    int _I = (I);                                                                                  \
    int _L = arr_len(A);                                                                           \
    int STRIDE = arr_stride(A);                                                                    \
    arr_resize((A), _L + 1);                                                                       \
    byte *PTR = (void *)arr_data(A);                                                               \
    memmove(PTR + STRIDE * (_I + 1), PTR + STRIDE * _I, STRIDE * (_L - _I));                       \
    arr_set((A), _I, (V));                                                                         \
  } while (0)

#define arr_nullterminated(A)                                                                      \
  (arr_onstack(A) ? (arr_set(A, arr_len(A), 0), arr_data(A))                                       \
                  : (arr_push((A), 0), arr_dec(A), arr_data(A)))

#define arr_cstr(A) arr_nullterminated(A)

////////////////////
// ARRAY END
////////////////////

#ifndef NO_DEFAULT_STRING
typedef Array(char, 15) string;
#endif

#endif /* _SCL_H_ */
