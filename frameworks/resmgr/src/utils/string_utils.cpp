/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "utils/string_utils.h"

#include <cctype>
#include <cstdarg>
#include <cstdint>
#include <vector>

#if defined(__WINNT__)
#include <cstring>
#else
#include "securec.h"
#endif

namespace OHOS {
namespace Global {
namespace Resource {
std::string FormatString(const char *fmt, ...)
{
    std::string strResult;
    if (fmt != nullptr) {
        va_list marker;
        va_start(marker, fmt);
        strResult = FormatString(fmt, marker);
        va_end(marker);
    }
    return strResult;
}

std::string FormatString(const char *fmt, va_list args)
{
    std::string strResult;
    if (fmt != nullptr) {
        va_list tmpArgs;
        va_copy(tmpArgs, args);
        int nLength = vsnprintf(nullptr, 0, fmt, tmpArgs); // compute buffer size
        va_end(tmpArgs);
        std::vector<char> vBuffer(nLength + 1, '\0');
        int nWritten = vsnprintf_s(&vBuffer[0], nLength + 1, nLength, fmt, args);
        if (nWritten > 0) {
            strResult = &vBuffer[0];
        }
    }
    return strResult;
}
} // namespace Resource
} // namespace Global
} // namespace OHOS