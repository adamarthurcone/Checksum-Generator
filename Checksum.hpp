#ifndef CHECKSUM_HPP
#define CHECKSUM_HPP

#include <openssl/md5.h>
#include <openssl/sha.h>
#include <string>
#include <sstream>
#include <iomanip>
#include <fstream>

#define BUFFSIZE 16384

/*
 * The purpose of this class is to generate a checksum from
 * a given file.
 * 
 * Requires openssl: 
 * sudo apt-get install openssl libssl-dev
 */
class Checksum
{
  public:
    /*
    * Constructor
    */
    Checksum(std::string filename)
    {
        fname = filename;
    }
    ~Checksum();
    
    /*
    * Returns a hash of type md5.
    */
    std::string get_md5hash()
    {
        char buffer[BUFFSIZE];
        unsigned char digest[MD5_DIGEST_LENGTH];

        std::stringstream ss;
        std::string md5string;

        std::ifstream ifs(fname, std::ifstream::binary);

        MD5_CTX md5Context;

        MD5_Init(&md5Context);

        while (ifs.good())
        {

            ifs.read(buffer, BUFFSIZE);

            MD5_Update(&md5Context, buffer, ifs.gcount());
        }

        ifs.close();

        int res = MD5_Final(digest, &md5Context);

        if (res == 0)
        {              // hash failed
            return {}; // or raise an exception
        }
        // set up stringstream format
        ss << std::hex << std::uppercase << std::setfill('0');

        for (unsigned char uc : digest)
        {
            ss << std::setw(2) << (int)uc;
        }

        md5string = ss.str();

        return md5string;
    }

    /*
    * Returns a hash of type sha1
    */
    std::string get_sha1hash()
    {
        char buffer[BUFFSIZE];
        unsigned char digest[SHA_DIGEST_LENGTH];

        std::stringstream ss;
        std::string md5string;

        std::ifstream ifs(fname, std::ifstream::binary);

        SHA_CTX sha1Context;

        SHA1_Init(&sha1Context);

        while (ifs.good())
        {

            ifs.read(buffer, BUFFSIZE);

            SHA1_Update(&sha1Context, buffer, ifs.gcount());
        }

        ifs.close();

        int res = SHA1_Final(digest, &sha1Context);

        if (res == 0)
        {              // hash failed
            return {}; // or raise an exception
        }
        // set up stringstream format
        ss << std::hex << std::uppercase << std::setfill('0');

        for (unsigned char uc : digest)
        {
            ss << std::setw(2) << (int)uc;
        }

        md5string = ss.str();

        return md5string;
    }

  private:
    std::string fname;
};
#endif /* CHECKSUM_HPP */
