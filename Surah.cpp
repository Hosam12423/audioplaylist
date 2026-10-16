#include "Surah.h"

using namespace std;

Surah::Surah() = default;

Surah::Surah(const string& name, const string& type, const string& file)
    : name_(name), type_(type), file_(file) {}

const string& Surah::getName() const { return name_; }
const string& Surah::getType() const { return type_; }
const string& Surah::getFile() const { return file_; }
