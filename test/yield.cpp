#include <gtest/gtest.h>

#include <coroutine.h>

static int coroutine1(coroutine_context_t **context) {
  COROUTINE_CONTEXT_BEGIN();
  COROUTINE_CONTEXT_END(context);

  ///////////////////////////////////

  COROUTINE_BEGIN();
  COROUTINE_YIELD(1);
  COROUTINE_YIELD(2);
  COROUTINE_FINISH();

  return 3;
}

TEST(coroutine, YieldInRightOrder) {
  coroutine_context_t *ctx = nullptr;

  EXPECT_EQ(1, coroutine1(&ctx));
  EXPECT_NE(ctx, nullptr);

  EXPECT_EQ(2, coroutine1(&ctx));
  EXPECT_NE(ctx, nullptr);

  EXPECT_EQ(3, coroutine1(&ctx));
  EXPECT_EQ(ctx, nullptr);
}

static int coroutine2(coroutine_context_t **context) {
  COROUTINE_CONTEXT_BEGIN();
  int count;
  COROUTINE_CONTEXT_END(context);

  ///////////////////////////////////

  COROUTINE_BEGIN();
  COROUTINE_YIELD(1);
  if (coroutine_context->count < 2) {
    ++coroutine_context->count;
    COROUTINE_YIELD_AND_KEEP_LAST_ENTRYPOINT(2);
  }
  COROUTINE_YIELD(3);

  COROUTINE_FINISH();

  return 4;
}

TEST(coroutine, YieldAndKeepLastEntryPoint) {
  coroutine_context_t *ctx = nullptr;

  EXPECT_EQ(1, coroutine2(&ctx));
  EXPECT_NE(ctx, nullptr);

  EXPECT_EQ(2, coroutine2(&ctx));
  EXPECT_NE(ctx, nullptr);

  EXPECT_EQ(2, coroutine2(&ctx));
  EXPECT_NE(ctx, nullptr);

  EXPECT_EQ(3, coroutine2(&ctx));
  EXPECT_NE(ctx, nullptr);

  EXPECT_EQ(4, coroutine2(&ctx));
  EXPECT_EQ(ctx, nullptr);
}