#ifndef ATMEGASIM_SRC_INSTRN_INFO_H
#define ATMEGASIM_SRC_INSTRN_INFO_H

class ISInfo {
private:
    const char *symbol;
    const char *title;
    const char *pattern;

public:
    ISInfo() {}

    ISInfo S(const char *symbol_) { symbol = symbol_; return *this; }
    const char *S() {return symbol;}

    ISInfo T(const char *title_) { title = title_; return *this; }
    const char *T() {return title;}

    ISInfo P(const char *pattern_) { pattern = pattern_; return *this; }
    const char *P() {return pattern;}

};


#endif //ATMEGASIM_SRC_INSTRN_INFO_H
