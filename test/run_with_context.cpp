#include <gtest/gtest.h>

#include <coroutine.h>

static int coroutine1(coroutine_context_t **context, int arg) {
  COROUTINE_CONTEXT_BEGIN();
  int data0;
  int data1;
  COROUTINE_CONTEXT_END(context);

  ///////////////////////////////////

  int final;

  COROUTINE_BEGIN();

  coroutine_context->data0 = arg;
  COROUTINE_YIELD(3 + coroutine_context->data0);

  coroutine_context->data1 = arg;
  COROUTINE_YIELD(6 + coroutine_context->data1);

  final = 42 + arg + coroutine_context->data0 + coroutine_context->data1;

  COROUTINE_FINISH();

  return final;
}

TEST(coroutine, UseContextWithReturnTypeAndArguments) {
  coroutine_context_t *ctx = nullptr;

  int const val0 = 7;
  int val = val0;

  val += coroutine1(&ctx, val);
  int const val1 = val;
  EXPECT_EQ(val1, val0 + 3 + val0);
  EXPECT_NE(ctx, nullptr);

  val += coroutine1(&ctx, val);
  int const val2 = val;
  EXPECT_EQ(val2, val1 + 6 + val1);
  EXPECT_NE(ctx, nullptr);

  val += coroutine1(&ctx, val);
  EXPECT_EQ(val, val2 + 42 + val2 + val0 + val1);
  EXPECT_EQ(ctx, nullptr);
}

static void coroutine2(coroutine_context_t **context, int *inout) {
  COROUTINE_CONTEXT_BEGIN();
  int data0;
  int data1;
  COROUTINE_CONTEXT_END(context);

  ///////////////////////////////////

  COROUTINE_BEGIN();

  coroutine_context->data0 = *inout;
  *inout += 3 + coroutine_context->data0;
  COROUTINE_YIELD();

  coroutine_context->data1 = *inout;
  *inout += 6 + coroutine_context->data1;
  COROUTINE_YIELD();

  *inout += 42 + *inout + coroutine_context->data0 + coroutine_context->data1;
  COROUTINE_FINISH();
}

TEST(coroutine, UseContextWithoutReturnTypeButWithArguments) {
  coroutine_context_t *ctx = nullptr;

  int const val0 = 7;
  int val = val0;

  coroutine2(&ctx, &val);
  int const val1 = val;
  EXPECT_EQ(val1, val0 + 3 + val0);
  EXPECT_NE(ctx, nullptr);

  coroutine2(&ctx, &val);
  int const val2 = val;
  EXPECT_EQ(val2, val1 + 6 + val1);
  EXPECT_NE(ctx, nullptr);

  coroutine2(&ctx, &val);
  EXPECT_EQ(val, val2 + 42 + val2 + val0 + val1);
  EXPECT_EQ(ctx, nullptr);
}

static int coroutine3_val = 0;
static void coroutine3(coroutine_context_t **context) {
  COROUTINE_CONTEXT_BEGIN();
  int data0;
  int data1;
  COROUTINE_CONTEXT_END(context);

  ///////////////////////////////////

  COROUTINE_BEGIN();

  coroutine_context->data0 = coroutine3_val;
  coroutine3_val += 3 + coroutine_context->data0;
  COROUTINE_YIELD();

  coroutine_context->data1 = coroutine3_val;
  coroutine3_val += 6 + coroutine_context->data1;
  COROUTINE_YIELD();

  coroutine3_val +=
      42 + coroutine3_val + coroutine_context->data0 + coroutine_context->data1;
  COROUTINE_FINISH();
}

TEST(coroutine, UseContextWithoutReturnTypeNorArgument) {
  coroutine_context_t *ctx = nullptr;

  int const val0 = 7;
  coroutine3_val = val0;

  coroutine3(&ctx);
  int const val1 = coroutine3_val;
  EXPECT_EQ(val1, val0 + 3 + val0);
  EXPECT_NE(ctx, nullptr);

  coroutine3(&ctx);
  int const val2 = coroutine3_val;
  EXPECT_EQ(val2, val1 + 6 + val1);
  EXPECT_NE(ctx, nullptr);

  coroutine3(&ctx);
  EXPECT_EQ(coroutine3_val, val2 + 42 + val2 + val0 + val1);
  EXPECT_EQ(ctx, nullptr);
}

static int coroutine4(coroutine_context_t **context, int arg) {
  COROUTINE_CONTEXT_BEGIN();
  COROUTINE_CONTEXT_END(context);

  ///////////////////////////////////

  int final;

  COROUTINE_BEGIN();

  COROUTINE_YIELD(1 + arg);
  COROUTINE_YIELD(2 + arg);
  final = 3 + arg;

  COROUTINE_FINISH();

  return final;
}

TEST(coroutine, UseEmptyContext) {
  coroutine_context_t *ctx = nullptr;

  int const val0 = 0;

  int const val1 = coroutine4(&ctx, val0);
  EXPECT_EQ(val1, 1 + val0);
  EXPECT_NE(ctx, nullptr);

  int const val2 = coroutine4(&ctx, val1);
  EXPECT_EQ(val2, 2 + val1);
  EXPECT_NE(ctx, nullptr);

  int const val3 = coroutine4(&ctx, val2);
  EXPECT_EQ(val3, 3 + val2);
  EXPECT_EQ(ctx, nullptr);
}