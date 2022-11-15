#include <benchmark/benchmark.h>

#include "ILogLevelAccessor.h"
#include "MMFLogLevelAccessor.h"
#include "MMFLogLevelAccessor1.h"
#include "DumbLogLevelAccessor.h"

static const std::unique_ptr<ILogLevelAccessor> mmfLogLevelAccessor = std::make_unique<MMFLogLevelAccessor>();
static const std::unique_ptr<ILogLevelAccessor> mmfLogLevelAccessor1 = std::make_unique<MMFLogLevelAccessor1>();
static const std::unique_ptr<ILogLevelAccessor> dumbLogLevelAccessor = std::make_unique<DumbLogLevelAccessor>();

static void BM_MMFLogLevelAccessor_GetLogLevel(benchmark::State& state) {
	for (auto _ : state)
		mmfLogLevelAccessor->GetLogLevel();
}

BENCHMARK(BM_MMFLogLevelAccessor_GetLogLevel);

static void BM_MMFLogLevelAccessor1_GetLogLevel(benchmark::State& state) {
	const std::unique_ptr<ILogLevelAccessor> logAccessor = std::make_unique<MMFLogLevelAccessor1>();
	for (auto _ : state)
		mmfLogLevelAccessor1->GetLogLevel();
}

BENCHMARK(BM_MMFLogLevelAccessor1_GetLogLevel);

static void BM_DumbLogLevelAccessor_GetLogLevel(benchmark::State& state) {
	const std::unique_ptr<ILogLevelAccessor> logAccessor = std::make_unique<DumbLogLevelAccessor>();
	for (auto _ : state)
		dumbLogLevelAccessor->GetLogLevel();
}

BENCHMARK(BM_DumbLogLevelAccessor_GetLogLevel);

BENCHMARK_MAIN();
