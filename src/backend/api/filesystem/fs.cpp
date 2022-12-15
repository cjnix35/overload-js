#include "fs.hpp"

namespace api {

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

}; // namespace api