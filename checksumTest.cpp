#include "Checksum.hpp"
#include <string>

int main(int argc, char *argv[])
{

    Checksum *hash_test = new Checksum("CatalogChecksum.cpp");

    printf("md5 hash for Checksum.cpp: %s\n", hash_test->get_md5hash().c_str());
    printf("sha1 hash for Checksum.cpp: %s\n", hash_test->get_sha1hash().c_str());

    return (0);
}
