#include <iostream>
#include <string>
#include <fstream>
#include <limits>

#define RAND_START_SIZE_FOR_STRING 33
#define RAND_MAX_SIZE_FOR_STRING 127

 void Encrypt( const std::string& origin_string, std::string& key_string, std::fstream& str_out_file, const std::string& str_out_filepath, std::fstream& key_out_file, const std::string& key_out_filepath);
 std::string&  Decrypt(std::fstream& str_in_file,const std::string& str_in_filepath, std::fstream& key_in_file, const std::string& key_in_filepath) ;

int main(int argc, char* argv[]) {

    std::string origin_str;
    std::string key_str;

    std::string filepath {"file.txt"};
    std::fstream ioput_file;

    std::string encfile {"encfile.txt"};
    std::fstream encript_file;


    std::string tumbler;
    std::cout << "Enter \" encrypt \" to encrypt string by key or enter \" decrypt \" to decrypt string in file by key" << std::endl;
    std::cin >> tumbler;


    if(  ( tumbler.size() !=0) && ( tumbler == "encrypt" )  ) {

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        std::cout << "Enter origin string : " ;
        std::getline(std::cin, origin_str);

        std::cout << "Enter key string : ";
        std::getline(std::cin, key_str);

        Encrypt(origin_str, key_str, ioput_file, filepath, encript_file, encfile);

      }else if (  ( tumbler.size() !=0) && ( tumbler == "decrypt" )  ) {

        std::cout << "We use a standart filename - \" file.txt\" to encrypt string and \"ecnfile.txt\" for key file " << std::endl;

         Decrypt(ioput_file, filepath, encript_file, encfile);

      } else {

        std::cout << "Invalid controll word" << std::endl;
      }

    return 0;
}



void Encrypt( const std::string& origin_string, std::string& key_string, std::fstream& str_out_file, const std::string& str_out_filepath, std::fstream& key_out_file, const std::string& key_out_filepath) {
    std::string res;
        srand( time( 0 ) );

        char encrypt_value = RAND_START_SIZE_FOR_STRING + rand() % RAND_MAX_SIZE_FOR_STRING;

        for (unsigned int ch = key_string.size() ; ch < origin_string.size(); ++ch ) {
               encrypt_value = RAND_START_SIZE_FOR_STRING + rand() % RAND_MAX_SIZE_FOR_STRING;

                key_string += encrypt_value;
        }

        if (key_string.size() == origin_string.size()) {

            for (unsigned int ch = 0; ch < origin_string.size(); ++ch ) {
                res += origin_string[ch] ^ key_string[ch];

            }
        }

 key_out_file.open(key_out_filepath, std::ios_base::out);
    if (key_out_file.is_open()){

        key_out_file << key_string << std::endl;
        key_out_file.close();

    } else {

     std::cout<< "Sorry, cant open the out string file" << std::endl;

    }


str_out_file.open(str_out_filepath, std::ios_base::out);

    if (str_out_file.is_open()) {
        str_out_file <<res << std::endl;
        str_out_file.close();

    } else {

          std::cout<< "Sorry, cant open the out key file" << std::endl;
    }


std::cout << " Ecrypt done " <<std::endl;
}



std::string&  Decrypt(std::fstream& str_in_file,const std::string& str_in_filepath, std::fstream& key_in_file, const std::string& key_in_filepath) {
    std::string res;
    char dot { '.' };
    std::string str_to_decrypt;
    std::string key_to_use;

    str_in_file.open(str_in_filepath, std::ios_base::in);

        if (str_in_file.is_open()) {

            std::getline(str_in_file, str_to_decrypt);

            std::cout<< "String to decrypt : " << str_to_decrypt << std::endl;

        } else {

            std::cout<< "Sorry, cant open the in string file" << std::endl;
        }

    key_in_file.open(key_in_filepath, std::ios_base::in);

        if (key_in_file.is_open()) {

                std::getline(key_in_file, key_to_use);
                std::cout<<"Key string :  "<< key_to_use << std::endl;

        } else {

                    std::cout<< "Sorry, cant open the in key file" << std::endl;
               }

        std::cout <<"We start ";

        for (unsigned int ch = 0; ch < str_to_decrypt.size() ; ++ch) {

                std::cout<< dot;
                res += str_to_decrypt[ch] ^ key_to_use[ch];
        }

        std::cout<< "Done" << std::endl;
        std::cout<< "original string: " << res << std::endl;

    return res;

}
