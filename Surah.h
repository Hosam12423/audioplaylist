#ifndef SURAH_H
#define SURAH_H

#include <string>

class Surah {
public:
    Surah();
    Surah(const std::string& name, const std::string& type, const std::string& file);

    const std::string& getName() const;
    const std::string& getType() const;
    const std::string& getFile() const;

private:
    std::string name_;
    std::string type_;
    std::string file_;
};

#endif
