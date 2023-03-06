#pragma once
#include <Windows.h>
#include <string>
#include <sstream>
#include <array>
#include <exception>
#include <codecvt>
#include <memory>
#include <algorithm>
class ShortName
{
private:
    inline static const BYTE ILLEGAL_CHARS[] = {
        0x22, 0x2A, 0x2B, 0x2C, 0x2E, 0x2F, 0x3A, 0x3B,
        0x3C, 0x3D, 0x3E, 0x3F, 0x5B, 0x5C, 0x5D, 0x7C
    };

    static const BYTE ASCII_SPACE =0x20;
public:
    ShortName(std::string nameExt) {
        if (nameExt.length() > 12) throw ("name too long");
        
        int i = nameExt.find_first_of('.');
        std::string nameString, extString;
        
        if (i < 0) {
            std::transform(nameString.begin(), nameString.end(), nameString.begin(), [](unsigned char c){ return std::toupper(c); });
            extString = "";
        } else {
            std::transform(nameString.begin(), nameString.begin() + i, nameString.begin(), [](unsigned char c){ return std::toupper(c); });
            std::transform(nameString.begin() + i + 1, nameString.end(), extString.begin(), [](unsigned char c){ return std::toupper(c); });
        }
        
        this->nameBytes = toCharArray(nameString, extString);
        checkValidChars(nameBytes, nameExt.length());
    }
public:
    // static ShortName* DOT(){
    //     return new ShortName(".", "");
    // }
    // static ShortName* DOT_DOT(){
    //     return new ShortName("..", "");
    // }
    ShortName(std::string name, std::string ext)
    {
        this->nameBytes = toCharArray(name, ext);
    }
    ~ShortName()
    {
        delete [] nameBytes;
    }
private:
    BYTE* nameBytes;
    static BYTE* toCharArray(std::string name, std::string ext)
    {
        checkValidName(name);
        checkValidExt(ext);
        
        BYTE* result = new BYTE[11]{ASCII_SPACE};
        memcpy(result, name.data(),name.length());
        memcpy(result + 8, ext.data(),ext.length());

        return result;
    }
    static void checkValidName(std::string name) {
        checkString(name, "name", 1, 8);
    }

    static void checkValidExt(std::string ext) {
        checkString(ext, "extension", 0, 3);
    }

    static void checkString(std::string str, std::string strType,
            int minLength, int maxLength) {
        std::stringstream err;

        err.clear();
        err << strType <<
                    " must have at least " << minLength << 
                    " characters: " << str;
        if (str.length() < minLength)
            throw err.str();

        err.clear();
        err << strType <<
                    " has more than " << maxLength <<
                    " characters: " << str;
        if (str.length() > maxLength)
            throw err.str();
    }
public:
    static std::shared_ptr<ShortName> parse(BYTE* data){
        char nameArr[8];
        nameArr[7] = '\0';
        for (int i = 0; i < 8; i++) {
            memcpy(nameArr + i, data + i, 1);
        }

        BYTE result = 0;
        memcpy(&result, data, 1);
        if (result == 0x05) {
            nameArr[0] = (char) 0xe5;
        }
        
        char extArr[4];
        extArr[3] = '\0';
        for (int i = 0; i < 3; i++) {
            memcpy(extArr + i, data + 0x08 + i, 1);
        }
        std::string str_name = std::string(nameArr);
        std::string str_ext = std::string(extArr);
        str_name.erase(str_name.find_last_not_of(" \n\r\t")+1);;
        str_ext.erase(str_ext.find_last_not_of(" \n\r\t")+1);;
        return std::make_shared<ShortName>(str_name,str_ext);
    }

    static std::shared_ptr<ShortName> get(std::string name)
    {
        return std::make_shared<ShortName>(name);
    }

    static void checkValidChars(BYTE* chars, int length) {
            
        if (chars[0] == 0x20) throw(
                "0x20 can not be the first character");

        for (int i=0; i < length; i++) {
            if ((chars[i] & 0xff) != chars[i]) throw ("multi-byte character at %d", i);

            BYTE toTest = (BYTE) (chars[i] & 0xff);
            
            if (toTest < 0x20 && toTest != 0x05) throw ("caracter < 0x20 at %d", i);

            for (int j=0; j < 16; j++) {
                if (toTest == ILLEGAL_CHARS[j]) throw ("illegal character %d at %d", ILLEGAL_CHARS[j], i);
            }
        }
    }

    static bool canConvert(std::string nameExt)
    {
        /* TODO: do this without exceptions */
        try {
            ShortName::get(nameExt);
            return true;
        } catch (std::exception ex) {
            return false;
        }
    }
    BYTE checkSum()
    {
        BYTE dest[11];
        for (int i = 0; i < 11; i++)
            dest[i] = (BYTE) nameBytes[i];

        int sum = dest[0];
        for (int i = 1; i < 11; i++) {
            sum = dest[i] + (((sum & 1) << 7) + ((sum & 0xfe) >> 1));
        }
        
        return (BYTE) (sum & 0xff);
        
    }
    std::string asSimpleString()
    {
        char bname[8]{0};
        char bext[4]{0};
        memcpy(bname, this->nameBytes, 8);
        memcpy(bext, this->nameBytes + 8, 3);
        std::string name(bname);
        std::string ext(bext);
        name.erase(name.find_last_not_of(" \n\r\t")+1);
        ext.erase(ext.find_last_not_of(" \n\r\t")+1);
        
        return ext.empty() ? name : (name + "." + ext);
    }
};