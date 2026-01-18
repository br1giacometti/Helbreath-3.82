#include "Version.h"
#include <cstdio>

namespace hb {
	namespace version {

		const VersionInfo& Get()
		{
			static const VersionInfo kVersion{
				HB_VERSION_MAJOR,
				HB_VERSION_MINOR,
				HB_VERSION_PATCH,
				HB_VERSION_PRERELEASE,
				HB_VERSION_BUILD
			};
			return kVersion;
		}

		const char* GetSemVer()
		{
			static char buffer[64];
			const VersionInfo& ver = Get();

			if (ver.prerelease[0] != '\0') {
				std::snprintf(buffer, sizeof(buffer), "%d.%d.%d-%s",
					ver.major, ver.minor, ver.patch, ver.prerelease);
			}
			else {
				std::snprintf(buffer, sizeof(buffer), "%d.%d.%d",
					ver.major, ver.minor, ver.patch);
			}

			return buffer;
		}

		const char* GetDisplayString()
		{
			return GetSemVer();
		}

		const char* GetFullString()
		{
			static char buffer[96];
			const VersionInfo& ver = Get();
			const char* semver = GetSemVer();

			if (ver.build[0] != '\0') {
				std::snprintf(buffer, sizeof(buffer), "%s+%s", semver, ver.build);
				return buffer;
			}

			return semver;
		}

	} // namespace version
} // namespace hb