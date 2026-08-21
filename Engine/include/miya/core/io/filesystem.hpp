#pragma once

#include <filesystem>
#include <cstdint>
#include <string>
#include <vector>

namespace miya {
    class FileSystem {
        public:
            static bool Exists(const std::filesystem::path& path);

            static bool IsFile(const std::filesystem::path& path);
            static bool IsDirectory(const std::filesystem::path& path);

            static std::string ReadText(const std::filesystem::path& path);
            static std::vector<uint8_t> ReadBinary(const std::filesystem::path& path);

            static bool WriteText(const std::filesystem::path& path, const std::string& content);
            static bool WriteBinary(const std::filesystem::path& path, const std::vector<uint8_t>& data);

            static bool CreateDirectory(const std::filesystem::path& path);
            static bool CreateDirectories(const std::filesystem::path& path);

            static std::vector<std::filesystem::path> ListDirectory(const std::filesystem::path& path);

            static std::filesystem::path NormalizePath(const std::filesystem::path& path);

            static bool SetAssetRoot(const std::filesystem::path& path);
            static const std::filesystem::path& GetAssetRoot();
            static std::filesystem::path GetAssetPath(const std::filesystem::path& path);
        private:
            static std::filesystem::path s_assetRoot;
    };
}