# coroutine

The simpliest implementation of coroutine in C.
It is inspired from an article of Simon Tatham [here](https://www.chiark.greenend.org.uk/~sgtatham/coroutines.html).

This repository contains tests but all you need is the header file in the `include` directory.


Basic usage:
```C
#include <stdio.h>
#include <coroutine.h>

static int coroutine(coroutine_context_t **context, int offset) {
  ///////////////////////////////////
  /// The "persistent" data
  ///////////////////////////////////

  COROUTINE_CONTEXT_BEGIN();
  int count;
  COROUTINE_CONTEXT_END(context);

  ///////////////////////////////////

  COROUTINE_BEGIN();

  COROUTINE_YIELD(offset + 1);
  if (coroutine_context->count < 2) {
    ++coroutine_context->count;
    COROUTINE_YIELD_AND_KEEP_LAST_ENTRYPOINT(offset + 2);
  }
  COROUTINE_YIELD(offset + 3);

  COROUTINE_FINISH();

  return offset + 4;
}

int main(void) {
  coroutine_context_t *context = NULL;

  printf("=====================\n");
  int offset = 3;
  do {
  	printf("%d\n", coroutine(&context, offset));
  } while (context);
  printf("=====================\n");

  return 0;
}

```

This should output this:
```
=====================
4
5
5
6
7
=====================
````

Look at the tests to see more usages.