#define _GNU_SOURCE
#include "disk_manager.hpp"
#include <fstream>
#include <unistd.h>   // pread, pwrite, close
#include <fcntl.h>    // open, O_RDWR, O_CREAT, etc.
#include <cerrno>     // errno for error handling
#include <cstring>    // strerror
#include "../common/config.hpp"

/*
    Page 0 (header):
    ┌──────────────┬─────────┬──────────────┐
    │ magic (8 B)  │ version │ num_pages    │  ← or next_page_id
    │ ...          │ (4 B)   │ (4 or 8 B)   │
    └──────────────┴─────────┴──────────────┘
*/
class UnixDiskManager : public DiskManager {
    private:
        int fd;
        int page_cntr;
    public:
        UnixDiskManager(const std::string& path) : DiskManager(path) {
            fd = open(path.c_str(), O_RDWR | O_CREAT, 0666);
            if (fd == -1) {
                throw std::runtime_error("Failed to open file: " + path);
            }
        }
        ~UnixDiskManager() {
            ssize_t flag = close(fd);
            if (flag == -1) {
                throw std::runtime_error("Failed to close file: " + std::string(strerror(errno)));
            }
        }

        void writePage(int page_id, const char* data) {
            ssize_t flag = pwrite(fd, const_cast<char*>(data), PAGE_SIZE, page_id * PAGE_SIZE);
            if (flag == -1) {
                throw std::runtime_error("Failed to write page: " + std::string(strerror(errno)));
            }
            if (flag != PAGE_SIZE) {
                throw std::runtime_error("Failed to write full page: " + std::string(strerror(errno)));
            }
        }
        void readPage(int page_id, char* data) {
            ssize_t flag= pread(fd, const_cast<char*>(data), PAGE_SIZE, page_id * PAGE_SIZE);
            if (flag == -1) {
                throw std::runtime_error("Failed to read page: " + std::string(strerror(errno)));
            }
            if (flag != PAGE_SIZE) {
                throw std::runtime_error("Failed to read full page: " + std::string(strerror(errno)));
            }
        }
        void allocatePage(int& page_id) {
            page_id = page_cntr++;
        }
};