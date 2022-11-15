#include "fs.hpp"

namespace api {


    std::string MakeDir(std::string args) {

        Document d;
        d.Parse(args.c_str());
        std::string path = d[0].GetString();

        if (!std::filesystem::exists(path)) {

            return std::filesystem::create_directory(path) ? JTrue : JFalse;

        } else return JFalse;
    }

    std::string ReadFile(std::string args) {

        Document d;
        d.Parse(args.c_str());
        std::string filename = d[0].GetString();
        std::string buf;
        d.Clear();
        d.SetArray();
        Document::AllocatorType& allocator = d.GetAllocator();

        std::ifstream f(filename, std::ios_base::in);
        if (f.is_open()) {

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

        Document d;
        d.Parse(args.c_str());
        std::string filename = d[0].GetString();

        return std::filesystem::remove(filename) ? JTrue : JFalse;
    }

    std::string RemoveDir(std::string args) {

        Document d;
        d.Parse(args.c_str());
        std::string dirname = d[0].GetString();

        return std::filesystem::remove_all(dirname) ? JTrue : JFalse;
    }

    std::string ListDir(std::string args) {

        Document d;
        d.Parse(args.c_str());
        std::string dirname = d[0].GetString();
        d.Clear();
        d.SetArray();
        Document::AllocatorType& allocator = d.GetAllocator();

        for (const auto& entry : std::filesystem::directory_iterator(dirname))
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

        Document d;
        d.Parse(args.c_str());
        std::string path = d[0].GetString();

        return api::Quotes(std::filesystem::absolute(path).u8string());
    }


}; // namespace api