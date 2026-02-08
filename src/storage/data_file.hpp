/*
    Manage pages that stores records
    Insert records
    Scan 
    Delete

    It doesnt care how they are stored
    Record and pages
*/

#include "../common/config.hpp"
#include <string>


struct Page {
    int page_id;
    char data[PAGE_SIZE];
};

// Pointer to a tuple unique page_id and slot number 
struct Record {
    int page_id;
    int slot_id;
};

class DataFile {
    public:
        DataFile(const std::string& filename);
        ~DataFile();
};