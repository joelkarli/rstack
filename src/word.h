#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <typeinfo>
#include <string>

#include "object.h"

class Word {

  public:

    virtual ~Word() {
      // Calls words destructors.
      words.clear();
    }

    virtual void execute(std::vector<Object> & vector) {
      std::for_each(words.begin(), words.end(), [&vector](Word * word) {
        word->execute(vector);
      });
    }

    void add_word(Word * word) {
      words.push_back(word);
    }

    std::vector<Word*> words;

};

class PlusWord : public Word {

  public:

    void execute(std::vector<Object> & vector) {
      auto fst = obj_cast<int>(vector.back());
      vector.pop_back();
      auto snd = obj_cast<int>(vector.back());
      vector.pop_back();
      vector.push_back(Object(fst + snd));
    }

};


class MinusWord : public Word {

  public:

    void execute(std::vector<Object> & vector) {
      auto fst = obj_cast<int>(vector.back());
      vector.pop_back();
      auto snd = obj_cast<int>(vector.back());
      vector.pop_back();
      vector.push_back(Object(snd - fst));
    }

};



class MultiplyWord : public Word {

  public:

    void execute(std::vector<Object> & vector) {
      auto fst = obj_cast<int>(vector.back());
      vector.pop_back();
      auto snd = obj_cast<int>(vector.back());
      vector.pop_back();
      vector.push_back(Object(fst * snd));
    }

};


class DivideWord : public Word {

  public:

    void execute(std::vector<Object> & vector) {
      auto fst = obj_cast<int>(vector.back());
      vector.pop_back();
      auto snd = obj_cast<int>(vector.back());
      vector.pop_back();
      vector.push_back(Object(snd / fst));
    }

};

class DropWord : public Word {

  public:

    void execute(std::vector<Object> & vector) {
      vector.pop_back();
    }

};

class PrintWord : public Word {

  public:

    void execute(std::vector<Object> & vector) {
      auto fst = vector.back();
      if (fst.type() == typeid(std::string)) {
        auto casted = obj_cast<std::string>(fst);
        std::cout << casted;
      }
      else {
        auto casted = obj_cast<int>(fst);
        std::cout << casted;
      }
      vector.pop_back();
    }

};

class ByeWord : public Word {

  public:

    void execute(std::vector<Object> & vector) {
      std::exit(EXIT_SUCCESS);
    }

};

class CarriageReturnWord : public Word {

  public:

    void execute(std::vector<Object> & vector) {
      std::cout << std::endl;
    }

};

/**
 * Used by the interpreter to push an object on the vector.
 *
 */
class PushWord : public Word {

  public:

    PushWord(Object const & to_push) : object_to_push(to_push) {

    }

    void execute(std::vector<Object> & vector) {
      vector.push_back(object_to_push);
    }

  private:

    Object object_to_push;

};

class TimesWord : public Word {

  public:

    void execute(std::vector<Object> & vector) {
      auto times = obj_cast<int>(vector.back());
      vector.pop_back();
      for (int i = 0; i < times; ++i) {
        std::for_each(words.begin(), words.end(), [&vector](Word * word) {
          word->execute(vector);
        });
      }
    }

};

class ModuloWord : public Word {

  public:

    void execute(std::vector<Object> & vector) {
      auto fst = obj_cast<int>(vector.back());
      vector.pop_back();
      auto snd = obj_cast<int>(vector.back());
      vector.pop_back();
      vector.push_back(Object(snd % fst));
    }

};

class EqualWord : public Word {

  public:

    void execute(std::vector<Object> & vector) {
      auto fst = obj_cast<int>(vector.back());
      vector.pop_back();
      auto snd = obj_cast<int>(vector.back());
      vector.pop_back();
      vector.push_back(fst == snd ? Object(1) : Object(0));
    }

};

class GreaterWord : public Word {

  public:

    void execute(std::vector<Object> & vector) {
      auto fst = obj_cast<int>(vector.back());
      vector.pop_back();
      auto snd = obj_cast<int>(vector.back());
      vector.pop_back();
      vector.push_back(snd > fst ? Object(1) : Object(0));
    }

};

class LessWord : public Word {

  public:

    void execute(std::vector<Object> & vector) {
      auto fst = obj_cast<int>(vector.back());
      vector.pop_back();
      auto snd = obj_cast<int>(vector.back());
      vector.pop_back();
      vector.push_back(snd < fst ? Object(1) : Object(0));
    }

};

class IfWord : public Word {

  public:

    void execute(std::vector<Object> & vector) {
      auto fst = obj_cast<int>(vector.back());
      vector.pop_back();
      if (fst != 0) {
        std::for_each(words.begin(), words.end(), [&vector](Word * word) {
          word->execute(vector);
        });
      }
      else {
        std::for_each(else_words.begin(), else_words.end(), [&vector](Word * word) {
          word->execute(vector);
        });
      }
    }

    void add_else_word(Word * word) {
      else_words.push_back(word);
    }

    std::vector<Word*> else_words;

};

class WhileWord : public Word {

  public:

    void execute(std::vector<Object> & vector) {
      auto fst = obj_cast<int>(vector.back());
      while (fst != 0) {
        std::for_each(words.begin(), words.end(), [&vector, &fst](Word * word) {
          word->execute(vector);
          fst = obj_cast<int>(vector.back());
        });
      }
    }

};

class PickWord : public Word {

   public:

    void execute(std::vector<Object> & vector) {
      auto depth = obj_cast<int>(vector.back());
      vector.pop_back();
      vector.push_back(vector[vector.size() - 1 - depth]);
    }

};

class RollWord : public Word {

  public:

    void execute(std::vector<Object> & vector) {
      auto depth = obj_cast<int>(vector.back());
      vector.pop_back();
      std::rotate(vector.end() - (depth + 1), vector.end() - depth, vector.end());
    }

};
