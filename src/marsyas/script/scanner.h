// Generated by Flexc++ V1.05.00 on Mon, 18 Nov 2013 23:14:02 -0800

#ifndef Scanner_H_INCLUDED_
#define Scanner_H_INCLUDED_

// $insert baseclass_h
#include "scannerbase.h"
#include "parserbase.h"

// $insert namespace-open
namespace Marsyas
{

// $insert classHead
class Scanner: public ScannerBase
{
    public:
        explicit Scanner(std::istream &in = std::cin,
                                std::ostream &out = std::cout);

        Scanner(std::string const &infile, std::string const &outfile);
        
        // $insert lexFunctionDecl
        int lex();

        enum token_type {
          BOOL = Parser::BOOL,
          INT = Parser::INT,
          REAL = Parser::REAL,
          STRING = Parser::STRING,
          ID = Parser::ID,
          ARROW = Parser::ARROW
        };

        long int_value()
        {
          return std::stol(matched());
        }

        double real_value()
        {
          return std::stod(matched());
        }

        bool bool_value()
        {
          static const std::string true_string("true");
          return (matched() == true_string);
        }

        std::string string_value()
        {
          const std::string & text = matched();
          return text.substr(1,text.length()-2);
        }

    private:
        int lex__();
        int executeAction__(size_t ruleNr);

        void print();
        void preCode();     // re-implement this function for code that must 
                            // be exec'ed before the patternmatching starts
};

// $insert scannerConstructors
inline Scanner::Scanner(std::istream &in, std::ostream &out)
:
    ScannerBase(in, out)
{}

inline Scanner::Scanner(std::string const &infile, std::string const &outfile)
:
    ScannerBase(infile, outfile)
{}

// $insert inlineLexFunction
inline int Scanner::lex()
{
    return lex__();
}

inline void Scanner::preCode() 
{
    // optionally replace by your own code
}

inline void Scanner::print() 
{
    print__();
}

// $insert namespace-close
}

#endif // Scanner_H_INCLUDED_

