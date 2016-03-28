class ofxLSInputError : public exception{
public:
    ofxLSInputError(string m="exception!") : msg(m) {}
    ofxLSInputError() throw() {}
    const char* what() const throw() { return msg.c_str(); }

private:
    string msg;
};
