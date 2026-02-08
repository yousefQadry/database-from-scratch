/*
    Disk Manager is only responsible for

    1 - Open/close files
    2- Read fixed-size blocks (pages)
    3- Write fixed-size blocks
    4- Allocate new pages

    Given file x and page_id Y, read Z bytes from it (4096 Bytes)

    we will use linux system calls to read and write to the disk

    It is the bridge between the database and the disk

*/

#include <string>

class DiskManager {
    public:
        DiskManager(const std::string& filename){
            
        }
        ~DiskManager();
        bool validateHeader(const char* data);
        void writePage(int page_id, const char* data);
        void readPage(int page_id, char* data);
        void allocatePage(int& page_id);
};