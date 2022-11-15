#include <benchmark/benchmark.h>

#include "ILogLevelAccessor.h"
#include "MMFLogLevelAccessor.h"
#include "DumbLogLevelAccessor.h"

static void BM_MMFLogLevelAccessor_GetLogLevel(benchmark::State& state) {
	const std::unique_ptr<ILogLevelAccessor> logAccessor = std::make_unique<MMFLogLevelAccessor>();
	for (auto _ : state)
		logAccessor->GetLogLevel();
}

BENCHMARK(BM_MMFLogLevelAccessor_GetLogLevel);

static void BM_DumbLogLevelAccessor_GetLogLevel(benchmark::State& state) {
	const std::unique_ptr<ILogLevelAccessor> logAccessor = std::make_unique<DumbLogLevelAccessor>();
	for (auto _ : state)
		logAccessor->GetLogLevel();
}

BENCHMARK(BM_DumbLogLevelAccessor_GetLogLevel);

BENCHMARK_MAIN();
