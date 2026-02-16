#include "BacktraceCaptureSink.h"


namespace uqm
{


BacktraceCaptureSink::BacktraceCaptureSink()
{
	//m_messages.fill(spdlog::memory_buf_t {});
}

void BacktraceCaptureSink::sink_it_(const spdlog::details::log_msg& msg)
{
	auto& target {at(m_index)};
	target.clear();
	formatter_->format(msg, target);
	++m_index;
}

void BacktraceCaptureSink::getBufferLines(uqstl::string& dest) const
{
	const size_t start = [&]() -> size_t {
		if (m_index < BacktraceSize)
		{
			return 0;
		}
		return m_index - BacktraceSize;
	}();

	const size_t unorderedStart {logicalToBufferIndex(uqstl::min(start, m_index))};
	const size_t unorderedEnd {logicalToBufferIndex(uqstl::max(start, m_index))};
	const size_t reqStrLen = uqstl::accumulate(&m_messages[unorderedStart], &m_messages[unorderedEnd], 0ull, [](const size_t sum, const spdlog::memory_buf_t& buf) -> size_t {
		return sum + buf.size() + 1;
	});

	dest.reserve(reqStrLen);

	for (size_t idx {start}; idx < m_index; ++idx)
	{
		const auto& log {at(idx)};

		dest.append(log.begin(), log.end());
	}
}

} // namespace uqm