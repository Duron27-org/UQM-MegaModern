#pragma once

#ifndef UQM_CORE_LOG_LOG_H_
#define UQM_CORE_LOG_LOG_H_

#include "core/log/logger.h"

//namespace uqmlog = spdlog;
namespace uqm
{
namespace log = ::spdlog;
}

namespace error
{
template <typename... Args>
void saveError(uqm::log::format_string_t<Args...> fmt, Args&&... args)
{
	uqm::log::error(fmt, std::forward<Args>(args)...);
}
} // namespace error

#endif /* UQM_CORE_LOG_LOG_H_ */