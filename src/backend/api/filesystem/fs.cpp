#include "fs.hpp"

namespace api {


    static int copy_data(struct archive *ar, struct archive *aw) {
        int r;
        const void *buff;
        size_t size;
        std::int64_t offset;

        for (;;) {
            r = archive_read_data_block(ar, &buff, &size, &offset);
            if (r == ARCHIVE_EOF) return (ARCHIVE_OK);
            if (r < ARCHIVE_OK) return (r);
            r = archive_write_data_block(aw, buff, size, offset);
            if (r < ARCHIVE_OK) {
                fprintf(stderr, "%s\n", archive_error_string(aw));
                return (r);
            }
        }
    }

    static int extract_mem(std::uint8_t *buf, std::uint64_t *buf_len) {
        struct archive *a;
        struct archive *ext;
        struct archive_entry *entry;
        int flags;
        int r;

        flags = ARCHIVE_EXTRACT_TIME;
        flags |= ARCHIVE_EXTRACT_PERM;
        flags |= ARCHIVE_EXTRACT_ACL;
        flags |= ARCHIVE_EXTRACT_FFLAGS;

        a = archive_read_new();
        archive_read_support_format_all(a);
        ext = archive_write_disk_new();
        archive_write_disk_set_options(ext, flags);
        archive_write_disk_set_standard_lookup(ext);
        if ((r = archive_read_open_memory(a, buf, *buf_len))) return 1;
        for (;;) {
            r = archive_read_next_header(a, &entry);
            if (r == ARCHIVE_EOF) break;
            if (r < ARCHIVE_OK)
                fprintf(stderr, "%s\n", archive_error_string(a));
            if (r < ARCHIVE_WARN) return 1;
            r = archive_write_header(ext, entry);
            if (r < ARCHIVE_OK)
                fprintf(stderr, "%s\n", archive_error_string(ext));
            else if (archive_entry_size(entry) > 0) {
                r = copy_data(a, ext);
                if (r < ARCHIVE_OK)
                    fprintf(stderr, "%s\n", archive_error_string(ext));
                if (r < ARCHIVE_WARN) return 1;
            }
            r = archive_write_finish_entry(ext);
            if (r < ARCHIVE_OK)
                fprintf(stderr, "%s\n", archive_error_string(ext));
            if (r < ARCHIVE_WARN) return 1;
        }
        archive_read_close(a);
        archive_read_free(a);
        archive_write_close(ext);
        archive_write_free(ext);
        return 0;
    }

    static int extract_file(const char *filename) {
        struct archive *a;
        struct archive *ext;
        struct archive_entry *entry;
        int flags;
        int r;

        flags = ARCHIVE_EXTRACT_TIME;
        flags |= ARCHIVE_EXTRACT_PERM;
        flags |= ARCHIVE_EXTRACT_ACL;
        flags |= ARCHIVE_EXTRACT_FFLAGS;

        a = archive_read_new();
        archive_read_support_format_all(a);
        ext = archive_write_disk_new();
        archive_write_disk_set_options(ext, flags);
        archive_write_disk_set_standard_lookup(ext);
        if ((r = archive_read_open_filename(a, filename, 10240))) return 1;
        for (;;) {
            r = archive_read_next_header(a, &entry);
            if (r == ARCHIVE_EOF) break;
            if (r < ARCHIVE_OK)
                fprintf(stderr, "%s\n", archive_error_string(a));
            if (r < ARCHIVE_WARN) return 1;
            r = archive_write_header(ext, entry);
            if (r < ARCHIVE_OK)
                fprintf(stderr, "%s\n", archive_error_string(ext));
            else if (archive_entry_size(entry) > 0) {
                r = copy_data(a, ext);
                if (r < ARCHIVE_OK)
                    fprintf(stderr, "%s\n", archive_error_string(ext));
                if (r < ARCHIVE_WARN) return 1;
            }
            r = archive_write_finish_entry(ext);
            if (r < ARCHIVE_OK)
                fprintf(stderr, "%s\n", archive_error_string(ext));
            if (r < ARCHIVE_WARN) return 1;
        }
        archive_read_close(a);
        archive_read_free(a);
        archive_write_close(ext);
        archive_write_free(ext);
        return 0;
    }

    std::string MakeDir(std::string args) {

        args.erase(0, 2);
        args.erase(args.size() - 2);

        if (!std::filesystem::exists(args)) {

            return std::filesystem::create_directory(args) ? JTrue : JFalse;

        } else return JFalse;
    }

    std::string ReadFile(std::string args) {

        args.erase(0, 2);
        args.erase(args.size() - 2);

        std::ifstream f(args, std::ios_base::in);
        if (f.is_open()) {

            Document d;
            std::string buf;
            d.Clear();
            d.SetArray();
            Document::AllocatorType &allocator = d.GetAllocator();

            while (std::getline(f, buf)) {
                d.PushBack(rapidjson::Value{}.SetString(
                               buf.c_str(), buf.length(), allocator),
                           allocator);
            }
            f.close();

            StringBuffer buffer;
            Writer<StringBuffer> writer(buffer);
            d.Accept(writer);

            return buffer.GetString();

        } else return JFalse;
    }

    std::string WriteFile(std::string args) {

        Document d;
        d.Parse(args.c_str());
        std::string filename = d[0].GetString();

        std::ofstream f(filename, std::ios_base::trunc);
        if (f.is_open()) {

            f << d[1].GetString();
            f.close();

            return JTrue;

        } else return JFalse;
    }

    std::string AppendFile(std::string args) {

        Document d;
        d.Parse(args.c_str());
        std::string filename = d[0].GetString();

        std::ofstream f(filename, std::ios_base::app);
        if (f.is_open()) {

            f << d[1].GetString();
            f.close();

            return JTrue;

        } else return JFalse;
    }

    std::string RemoveFile(std::string args) {

        args.erase(0, 2);
        args.erase(args.size() - 2);

        return std::filesystem::remove(args) ? JTrue : JFalse;
    }

    std::string RemoveDir(std::string args) {

        args.erase(0, 2);
        args.erase(args.size() - 2);

        return std::filesystem::remove_all(args) ? JTrue : JFalse;
    }

    std::string ListDir(std::string args) {

        args.erase(0, 2);
        args.erase(args.size() - 2);

        Document d;
        d.SetArray();
        Document::AllocatorType &allocator = d.GetAllocator();

        for (const auto &entry : std::filesystem::directory_iterator(args))
            d.PushBack(rapidjson::Value{}.SetString(
                           entry.path().u8string().c_str(),
                           entry.path().u8string().length(), allocator),
                       allocator);
        StringBuffer buffer;
        Writer<StringBuffer> writer(buffer);
        d.Accept(writer);

        return buffer.GetString();
    }

    std::string AbsolutePath(std::string args) {

        args.erase(0, 2);
        args.erase(args.size() - 2);

        return api::Quotes(std::filesystem::absolute(args).u8string());
    }

    bool LoadResourcesFromFile(std::string filename) {

#ifdef __linux__ || (__APPLE__ && __MACH__)

        const auto temp_folder =
            std::filesystem::temp_directory_path().u8string() + "/";

#elif _WIN32

        const auto temp_folder =
            std::filesystem::temp_directory_path().u8string();

#endif


        if (!std::filesystem::exists(temp_folder + "." APP_INTERNAL_NAME)) {

            std::filesystem::create_directory(temp_folder +
                                              "." APP_INTERNAL_NAME);
        }

        if (!std::filesystem::exists("." APP_INTERNAL_NAME)) {
            std::filesystem::create_directory_symlink(
                temp_folder + "." APP_INTERNAL_NAME, "." APP_INTERNAL_NAME);
        }

        std::uint64_t i = 0;

        for (auto &p :
             std::filesystem::directory_iterator("." APP_INTERNAL_NAME)) {
            ++i;
        }

        if (i == 0) {

            chdir("." APP_INTERNAL_NAME);
            api::extract_file(("../" + filename).c_str());
            chdir("..");
        }
        return true;
    }


    bool LoadResourcesFromMemory(std::uint8_t *buf, std::uint64_t *buf_len) {

#ifdef __linux__ || (__APPLE__ && __MACH__)

        const auto temp_folder =
            std::filesystem::temp_directory_path().u8string() + "/";

#elif _WIN32

        const auto temp_folder =
            std::filesystem::temp_directory_path().u8string();

#endif


        if (!std::filesystem::exists(temp_folder + "." APP_INTERNAL_NAME)) {

            std::filesystem::create_directory(temp_folder +
                                              "." APP_INTERNAL_NAME);
        }

        if (!std::filesystem::exists("." APP_INTERNAL_NAME)) {
            std::filesystem::create_directory_symlink(
                temp_folder + "." APP_INTERNAL_NAME, "." APP_INTERNAL_NAME);
        }

        std::uint64_t i = 0;

        for (auto &p :
             std::filesystem::directory_iterator("." APP_INTERNAL_NAME)) {
            ++i;
        }

        if (i == 0) {

            chdir("." APP_INTERNAL_NAME);
            api::extract_mem(buf, buf_len);
            chdir("..");
        }
        return true;
    }


}; // namespace api