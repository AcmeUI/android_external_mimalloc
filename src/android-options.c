//
// Copyright (C) 2022 Acme
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//

#include "mimalloc.h"
#include "mimalloc/internal.h"
#include "mimalloc/atomic.h"

#if defined(__ANDROID__)
mi_decl_nodiscard inline long mi_option_get(mi_option_t option)
{
  switch (option) {
  case mi_option_reserve_huge_os_pages_at:
  return -1;
  case mi_option_eager_commit_delay:
  return 1;
  case mi_option_purge_extend_delay:
  return 1;
  case mi_option_arena_purge_mult:
  return 10;
  case mi_option_purge_delay:
  return 10;
  case mi_option_arena_eager_commit:
  return 2;
  default:
  return 0;
  }
}

mi_decl_nodiscard inline long mi_option_get_clamp(mi_option_t option, long min, long max)
{
  (void)max;
  (void)option;
  return min;
}

mi_decl_nodiscard size_t mi_option_get_size(mi_option_t option) {
  switch (option) {
    case mi_option_arena_reserve:
#if (MI_INTPTR_SIZE>4)
    return 1024L * 1024L * MI_KiB;
#else
    return  128L * 1024L * MI_KiB;
#endif
    default:
    return 0;
  }
}

mi_decl_nodiscard inline bool mi_option_is_enabled(mi_option_t option)
{
  switch (option) {
  case mi_option_eager_commit:
  case mi_option_allow_purge:
  case mi_option_purge_decommits:
  return true;
  default:
  return false;
  }
}

inline void mi_option_disable(mi_option_t option) {}
inline void _mi_options_init(void) {}
inline void _mi_warning_message(const char* fmt, ... ) {}
inline void _mi_verbose_message(const char* fmt, ... ) {}
inline void _mi_error_message(int err, const char* fmt, ...) {}
inline void _mi_fputs(mi_output_fun* out, void* arg, const char* prefix, const char* message) {}
inline void _mi_fprintf(mi_output_fun* out, void* arg, const char* fmt, ...) {}
#endif /* __ANDROID__ */
