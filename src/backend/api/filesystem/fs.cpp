#include "fs.hpp"

namespace api {


    std::string MakeDirectory(std::string args) {

        json arr = json::parse(args);
        std::string path = arr[0].get<std::string>();

        if (!std::filesystem::exists(path)) {

            return std::filesystem::create_directory(path) ? "\"true\"" :
                                                             "\"false\"";

        } else return "\"false\"";
    }

    std::string ReadFile(std::string args) {

        json arr = json::parse(args);
        json ret;
        std::string filename = arr[0].get<std::string>();
        std::string buf;

        std::ifstream f(filename, std::ios_base::in);
        if (f.is_open()) {

            while (std::getline(f, buf)) { ret.push_back(buf); }
            f.close();

            return ret.dump();

        } else return "\"false\"";
    }

    std::string WriteFile(std::string args) {

        json arr = json::parse(args);
        std::string filename = arr[0].get<std::string>();

        std::ofstream f(filename, std::ios_base::trunc);
        if (f.is_open()) {

            f << arr[1].get<std::string>();
            f.close();

            return "\"true\"";

        } else return "\"false\"";
    }

    std::string AppendFile(std::string args) {

        json arr = json::parse(args);
        std::string filename = arr[0].get<std::string>();

        std::ofstream f(filename, std::ios_base::app);
        if (f.is_open()) {

            f << arr[1].get<std::string>();
            f.close();

            return "\"true\"";

        } else return "\"false\"";
    }

    std::string RemoveFile(std::string args) {

        json arr = json::parse(args);
        std::string filename = arr[0].get<std::string>();

        return std::filesystem::remove(filename) ? "\"true\"" : "\"false\"";
    }

    std::string RemoveDirectory(std::string args) {

        json arr = json::parse(args);
        std::string dirname = arr[0].get<std::string>();

        return std::filesystem::remove_all(dirname) ? "\"true\"" : "\"false\"";
    }

    std::string ListDirectory(std::string args) {

        json arr = json::parse(args);
        json ret;
        std::string dirname = arr[0].get<std::string>();

        for (const auto& entry : std::filesystem::directory_iterator(dirname))
            ret.push_back(entry.path());

        return ret.dump();
    }

    std::string AbsolutePath(std::string args) {

        json arr = json::parse(args);
        std::string path = arr[0].get<std::string>();

        return "\"" + std::filesystem::absolute(path).u8string() + "\"";
    }


}; // namespace api