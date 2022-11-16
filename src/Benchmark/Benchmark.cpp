#include <benchmark/benchmark.h>

#include "BufferedLogger.h"
#include "ILogLevelAccessor.h"
#include "MMFLogLevelAccessor.h"
#include "MMFLogLevelAccessor1.h"
#include "DumbLogLevelAccessor.h"
#include "DummyLogger.h"
#include "ILogger.h"

static const std::unique_ptr<ILogLevelAccessor> mmfLogLevelAccessor = std::make_unique<MMFLogLevelAccessor>();
static const std::unique_ptr<ILogLevelAccessor> mmfLogLevelAccessor1 = std::make_unique<MMFLogLevelAccessor1>();
static const std::unique_ptr<ILogLevelAccessor> dumbLogLevelAccessor = std::make_unique<DumbLogLevelAccessor>();
static const std::unique_ptr<ILogger> dummyLogger = std::make_unique<DummyLogger>();
static const std::unique_ptr<ILogger> bufferedLogger = std::make_unique<BufferedLogger>();


static void BM_MMFLogLevelAccessor_GetLogLevel(benchmark::State& state) {
	for (auto _ : state)
		mmfLogLevelAccessor->GetLogLevel();
}

BENCHMARK(BM_MMFLogLevelAccessor_GetLogLevel);

static void BM_MMFLogLevelAccessor1_GetLogLevel(benchmark::State& state) {
	for (auto _ : state)
		mmfLogLevelAccessor1->GetLogLevel();
}

BENCHMARK(BM_MMFLogLevelAccessor1_GetLogLevel);

static void BM_DumbLogLevelAccessor_GetLogLevel(benchmark::State& state) {
	for (auto _ : state)
		dumbLogLevelAccessor->GetLogLevel();
}

BENCHMARK(BM_DumbLogLevelAccessor_GetLogLevel);

static void BM_DummyLogger_WriteInfo(benchmark::State& state) {
	for (auto _ : state)
		dummyLogger->WriteInfo("testing");
}

BENCHMARK(BM_DummyLogger_WriteInfo);

static void BM_BufferedLogger_WriteInfo(benchmark::State& state) {
	for (auto _ : state)
		bufferedLogger->WriteInfo("testing");
}

BENCHMARK(BM_BufferedLogger_WriteInfo);

BENCHMARK_MAIN();
