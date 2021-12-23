//
// Created by Simon Duff on 20/12/2021.
//

#ifndef GENETIC_CROSSBREEDEXCEPTIONS_H
#define GENETIC_CROSSBREEDEXCEPTIONS_H

#include <exception>
#include <string>

namespace CrossbreedExceptions {
    struct CrossbreedException : public std::exception{
      const char * what() const override{
          return _message.c_str();
      }

    protected:
        CrossbreedException(std::string message){
            _message = message;
        }
        std::string _message;
    };

    struct DuplicateCutException : CrossbreedException{
    public:
        DuplicateCutException() : CrossbreedException("Cannot cut more than once in the same location"){}
    };

    struct CutOutOfBoundsException : CrossbreedException{
    public:
        CutOutOfBoundsException(int maxIndex) : CrossbreedException("Cut " + std::to_string(maxIndex) + " is outside the bounds of the genome"){}
    };
}


#endif //GENETIC_CROSSBREEDEXCEPTIONS_H
