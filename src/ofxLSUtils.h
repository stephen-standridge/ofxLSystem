#pragma once
#include <regex>

class ofxLSUtils{
public:
    static string grepStringInRegex(string _str, string _reg){
        smatch match;
        regex regEx(_reg);
        stringstream buffer;

        auto wordsBegin = sregex_iterator(_str.begin(), _str.end(), regEx);
        auto wordsEnd = sregex_iterator();
        for(sregex_iterator i = wordsBegin; i != wordsEnd; ++i){
            smatch m = *i;
            buffer << m.str();
        }
        return buffer.str();
    }

    static int countSubstring(const std::string& str, const std::string& sub){
        if (sub.length() == 0) return 0;
        int count = 0;
        for (size_t offset = str.find(sub); offset != std::string::npos;
             offset = str.find(sub, offset + sub.length())){
            ++count;
        }
        return count;
    }

    static vector<string> matchesInRegex(string subject, string reg){
        vector<string> results;
        try {
            smatch match;
            regex regEx(reg);
            auto wordsBegin = sregex_iterator(subject.begin(), subject.end(), regEx);
            auto wordsEnd = sregex_iterator();
            for(sregex_iterator i = wordsBegin; i != wordsEnd; ++i){
                smatch m = *i;
                results.push_back(m.str());
            }
        } catch (regex_error& e) {
            // Syntax error in the regular expression
            ofLogError("Error in regular expression");
        }
        return results;
    }
};

