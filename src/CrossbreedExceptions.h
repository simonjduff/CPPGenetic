//
// Created by Bastett on 20/12/2021.
//

#ifndef GENETIC_CROSSBREEDEXCEPTIONS_H
#define GENETIC_CROSSBREEDEXCEPTIONS_H

#include <exception>

namespace CrossbreedExceptions {
    struct CrossbreedException : public std::exception{
      const char * what() const override{
          return _message;
      }

    protected:
        CrossbreedException(char* message){
            _message = message;
        }
        char* _message;
    };

    struct DuplicateCutException : CrossbreedException{
    public:
        DuplicateCutException() : CrossbreedException((char*)"Cannot cut more than once in the same location"){}
    };
}


#endif //GENETIC_CROSSBREEDEXCEPTIONS_H
