#include <assert.h>
#include <rocksdb/db.h>
#include <iostream>

int main() {
    rocksdb::DB* db;
    rocksdb::Options options;
    options.create_if_missing = true;
    rocksdb::Status status =
        rocksdb::DB::Open(options, "./testdb", &db);

    if (!status.ok()) {
        std::cerr << "fail to open rocksdb ./testdb" << std::endl;
        return 0;
    }

    std::string key1 {"000001"};
    std::string value1 {"name,jack"};
    status = db->Get(rocksdb::ReadOptions(), key1, &value1);
    if (!status.ok()) {
        std::cerr << "fail to get key " << key1
            << " " << status.ToString() << std::endl;
    } else {
        std::cout << "success to get key " << key1
            << " value " << value1 << std::endl;
    }

    status = db->Put(rocksdb::WriteOptions(), key1, value1);
    if (!status.ok()) {
        std::cerr << "fail to put key " << key1
            << " " << status.ToString() << std::endl;
    }

    std::string value_returned;
    status = db->Get(rocksdb::ReadOptions(), key1, &value_returned);
    if (!status.ok()) {
        std::cerr << "fail to get key " << key1
            << " " << status.ToString() << std::endl;
    } else {
        std::cout << "key " << key1
            << " value " << value_returned << std::endl;
    }

    status = db->Delete(rocksdb::WriteOptions(), key1);
    if (!status.ok()) {
        std::cerr << status.ToString() << std::endl;
    } else {
        std::cout << "delete key " << key1 << std::endl;
    }

    delete db;
}
