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

