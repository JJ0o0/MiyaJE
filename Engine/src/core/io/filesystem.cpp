#include <miya/core/io/filesystem.hpp>

#include <miya/core/logging/log.hpp>

#include <system_error>
#include <fstream>
#include <sstream>

namespace miya {
    std::filesystem::path FileSystem::s_assetRoot;

    bool FileSystem::Exists(const std::filesystem::path& path) {
        std::error_code error;
        bool exists = std::filesystem::exists(path, error);
        if (error) {
            Log::Error("Couldn't check existence of '{}': {}", path.string(), error.message());
            return false;
        }

        return exists;
    }

    bool FileSystem::IsFile(const std::filesystem::path& path) {
        std::error_code error;
        bool isFile = std::filesystem::is_regular_file(path, error);
        if (error) {
            Log::Error("Couldn't check wheter '{}' is a file: {}", path.string(), error.message());
            return false;
        }

        return isFile;
    }

    bool FileSystem::IsDirectory(const std::filesystem::path& path) {
        std::error_code error;
        bool isDirectory = std::filesystem::is_directory(path, error);
        if (error) {
            Log::Error("Couldn't check wheter '{}' is a directory: {}", path.string(), error.message());
            return false;
        }

        return isDirectory;
    }

    std::string FileSystem::ReadText(const std::filesystem::path& path) {
        std::ifstream file(path);
        if (!file.is_open()) {
            Log::Error("Couldn't read file at '{}'", path.string());
            return {};
        }

        std::stringstream buffer;
        buffer << file.rdbuf();

        return buffer.str();
    }

    std::vector<uint8_t> FileSystem::ReadBinary(const std::filesystem::path& path) {
        std::ifstream file(path, std::ios::binary | std::ios::ate);
        if (!file.is_open()) {
            Log::Error("Couldn't read binary file at '{}'", path.string());
            return {};
        }

        auto end = file.tellg();
        if (end < 0) {
            Log::Error("Couldn't determine size of binary file at '{}'", path.string());
            return {};
        }

        size_t size = static_cast<size_t>(end);
        file.seekg(0, std::ios::beg);

        std::vector<uint8_t> data(size);

        if (size > 0) {
            file.read(reinterpret_cast<char*>(data.data()), static_cast<std::streamsize>(size));
            if (!file) {
                Log::Error("Couldn't read binary file at '{}'", path.string());
                return {};
            }
        }

        return data;
    }

    bool FileSystem::WriteText(const std::filesystem::path& path, const std::string& content) {
        std::ofstream file(path);
        if (!file.is_open()) {
            Log::Error("Couldn't write on file at '{}'", path.string());
            return false;
        }

        file << content;

        if (!file) {
            Log::Error("Couldn't write on file at '{}'", path.string());
            return false;
        }

        return true;
    }

    bool FileSystem::WriteBinary(const std::filesystem::path& path, const std::vector<uint8_t>& data) {
        std::ofstream file(path, std::ios::binary);
        if (!file.is_open()) {
            Log::Error("Couldn't write on binary file at '{}'", path.string());
            return false;
        }

        if (!data.empty()) {
            file.write(reinterpret_cast<const char*>(data.data()), static_cast<std::streamsize>(data.size()));
        }

        if (!file) {
            Log::Error("Couldn't write on binary file at '{}'", path.string());
            return false;
        }

        return true;
    }

    bool FileSystem::CreateDirectory(const std::filesystem::path& path) {
        std::error_code error;
        std::filesystem::create_directory(path, error);

        if (error) {
            Log::Error("Couldn't create directory at '{}': {}", path.string(), error.message());
            return false;
        }

        return true;
    }

    bool FileSystem::CreateDirectories(const std::filesystem::path& path) {
        std::error_code error;
        std::filesystem::create_directories(path, error);
        
        if (error) {
            Log::Error("Couldn't create directories at '{}': {}", path.string(), error.message());
            return false;
        }

        return true;
    }

    std::vector<std::filesystem::path> FileSystem::ListDirectory(const std::filesystem::path& path) {
        std::vector<std::filesystem::path> entries;
        
        std::error_code error;
        std::filesystem::directory_iterator iterator(path, error);
        if (error) {
            Log::Error("Couldn't list directories at '{}': {}", path.string(), error.message());
            return {};
        }

        const std::filesystem::directory_iterator end;
        while (iterator != end) {
            entries.push_back(iterator->path());

            iterator.increment(error);
            if (error) {
                Log::Error("Couldn't list directory at '{}': {}", path.string(), error.message());
                return {};
            }
        }

        return entries;
    }

    std::filesystem::path FileSystem::NormalizePath(const std::filesystem::path& path) {
        return path.lexically_normal();
    }

    bool FileSystem::SetAssetRoot(const std::filesystem::path& path) {
        if (!Exists(path)) { 
            Log::Error("Couldn't set asset root path: '{}' doesn't exist", path.string());
            return false;
        }

        if (!IsDirectory(path)) {
            Log::Error("Couldn't set asset root path: '{}' isn't a directory", path.string());
            return false;
        }

        s_assetRoot = path;
        return true;
    }

    const std::filesystem::path& FileSystem::GetAssetRoot() { return s_assetRoot; }

    std::filesystem::path FileSystem::GetAssetPath(const std::filesystem::path& path) {
        if (path.is_absolute()) {
            Log::Error("Couldn't get asset path: '{}' is absolute", path.string());
            return {};
        }
        
        return s_assetRoot / path;
    }
}