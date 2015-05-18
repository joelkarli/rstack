#ifndef _ENVIRONMENT_H_
#define _ENVIRONMENT_H_

#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>

#include "object.h"
#include "word.h"
#include "rstr.h"

class Environment {

  public:

    Environment() {
      // Initialize default words.
      vocabulary["pick"] = new PickWord();
      vocabulary["roll"] = new RollWord();
      vocabulary["drop"] = new DropWord();
      vocabulary["+"] = new PlusWord();
      vocabulary["-"] = new MinusWord();
      vocabulary["*"] = new MultiplyWord();
      vocabulary["/"] = new DivideWord();
      vocabulary["."] = new PrintWord();
      vocabulary["cr"] = new CarriageReturnWord();
      vocabulary["="] = new EqualWord();
      vocabulary[">"] = new GreaterWord();
      vocabulary["<"] = new LessWord();
      vocabulary["%"] = new ModuloWord();
      vocabulary["bye"] = new ByeWord();
    }

    ~Environment() {
      // Call words destructors.
      vocabulary.clear();
    }

    void load(std::string const & filepath) {
      std::ifstream ifs(filepath.c_str());
      std::string text;
      std::map<std::string, Word*>::iterator found;
      TimesWord * tmp_times_word;
      IfWord * tmp_if_word;
      WhileWord * tmp_while_word;
      if (ifs.is_open()) {
        while (ifs.good()) {
          ifs >> text;
          if (ifs.eof()) {
            break;
          }
          found = vocabulary.find(text);
          if (found != vocabulary.end()) {
            found->second->execute(vector);
          }
          else {
            if (text == "def") {
              add_new_word(ifs);
            }
            if (rstr::start_with(text, "\"")) {
              vector.push_back(construct_string_object(ifs, text));
            }
            else if (text == "times") {
              tmp_times_word = construct_times_word(ifs);
              tmp_times_word->execute(vector);
              delete tmp_times_word;
            }
            else if (text == "if") {
              tmp_if_word = construct_if_word(ifs);
              tmp_if_word->execute(vector);
              delete tmp_if_word;
            }
            else if (text == "while") {
              tmp_while_word = construct_while_word(ifs);
              tmp_while_word->execute(vector);
              delete tmp_while_word;
            }
            else {
              vector.push_back(Object(to_int(text)));
            }
          }
        }
        ifs.close();
      }
    }


  private:

    /**
     * \brief Adds a new word to the vocabulary.
     */
    void add_new_word(std::ifstream & ifs) {
      std::string text;
      std::string word_name;
      Word * word = new Word();
      std::map<std::string, Word*>::iterator found;
      if (ifs.good()) {
        ifs >> word_name;
      }
      while (ifs.good() && text != "end") {
        ifs >> text;
        if (ifs.eof()) {
          break;
        }
        found = vocabulary.find(text);
        if (found != vocabulary.end()) {
          word->add_word(found->second);
        }
        else if (text == "times") {
          word->add_word(construct_times_word(ifs, word_name, word));
        }
        else if (text == "if") {
          word->add_word(construct_if_word(ifs, word_name, word));
        }
        else if (rstr::start_with(text, "\"")) {
          word->add_word(new PushWord(construct_string_object(ifs, text)));
        }
        else if (text == "while") {
          word->add_word(construct_while_word(ifs, word_name, word));
        }
        else if (text == word_name) {
          word->add_word(word);
        }
        else if (text != "end") {
          word->add_word(new PushWord(Object(to_int(text))));
        }
      }
      vocabulary[word_name] = word;
    }

    TimesWord * construct_times_word(std::ifstream & ifs) {
      std::string text;
      TimesWord * times_word = new TimesWord();
      std::map<std::string, Word*>::iterator found;
      while (ifs.good() && text != "end") {
        ifs >> text;
        if (ifs.eof()) {
          break;
        }
        found = vocabulary.find(text);
        if (found != vocabulary.end()) {
          times_word->add_word(found->second);
        }
        else if (text == "times") {
          times_word->add_word(construct_times_word(ifs));
        }
        else if (text == "if") {
          times_word->add_word(construct_if_word(ifs));
        }
        else if (rstr::start_with(text, "\"")) {
          times_word->add_word(new PushWord(construct_string_object(ifs, text)));
        }
        else if (text == "while") {
          times_word->add_word(construct_while_word(ifs));
        }
        else if (text != "end") {
          times_word->add_word(new PushWord(Object(to_int(text))));
        }
      }
      return times_word;
    }

    TimesWord * construct_times_word(std::ifstream & ifs, std::string const & parent_name, Word * parent) {
      std::string text;
      TimesWord * times_word = new TimesWord();
      std::map<std::string, Word*>::iterator found;
      while (ifs.good() && text != "end") {
        ifs >> text;
        if (ifs.eof()) {
          break;
        }
        found = vocabulary.find(text);
        if (found != vocabulary.end()) {
          times_word->add_word(found->second);
        }
        else if (text == "times") {
          times_word->add_word(construct_times_word(ifs, parent_name, parent));
        }
        else if (text == "if") {
          times_word->add_word(construct_if_word(ifs, parent_name, parent));
        }
        else if (rstr::start_with(text, "\"")) {
          times_word->add_word(new PushWord(construct_string_object(ifs, text)));
        }
        else if (text == "while") {
          times_word->add_word(construct_while_word(ifs, parent_name, parent));
        }
        else if (text == parent_name) {
          times_word->add_word(parent);
        }
        else if (text != "end") {
          times_word->add_word(new PushWord(Object(to_int(text))));
        }
      }
      return times_word;
    }

    WhileWord * construct_while_word(std::ifstream & ifs) {
      std::string text;
      WhileWord * while_word = new WhileWord();
      std::map<std::string, Word*>::iterator found;
      while (ifs.good() && text != "end") {
        ifs >> text;
        if (ifs.eof()) {
          break;
        }
        found = vocabulary.find(text);
        if (found != vocabulary.end()) {
          while_word->add_word(found->second);
        }
        else if (text == "times") {
          while_word->add_word(construct_times_word(ifs));
        }
        else if (text == "if") {
          while_word->add_word(construct_if_word(ifs));
        }
        else if (rstr::start_with(text, "\"")) {
          while_word->add_word(new PushWord(construct_string_object(ifs, text)));
        }
        else if (text == "while") {
          while_word->add_word(construct_while_word(ifs));
        }
        else if (text != "end") {
          while_word->add_word(new PushWord(Object(to_int(text))));
        }
      }
      return while_word;
    }

    WhileWord * construct_while_word(std::ifstream & ifs, std::string const & parent_name, Word * parent) {
      std::string text;
      WhileWord * while_word = new WhileWord();
      std::map<std::string, Word*>::iterator found;
      while (ifs.good() && text != "end") {
        ifs >> text;
        if (ifs.eof()) {
          break;
        }
        found = vocabulary.find(text);
        if (found != vocabulary.end()) {
          while_word->add_word(found->second);
        }
        else if (text == "times") {
          while_word->add_word(construct_times_word(ifs, parent_name, parent));
        }
        else if (text == "if") {
          while_word->add_word(construct_if_word(ifs, parent_name, parent));
        }
        else if (rstr::start_with(text, "\"")) {
          while_word->add_word(new PushWord(construct_string_object(ifs, text)));
        }
        else if (text == "while") {
          while_word->add_word(construct_while_word(ifs, parent_name, parent));
        }
        else if (text == parent_name) {
          while_word->add_word(parent);
        }
        else if (text != "end") {
          while_word->add_word(new PushWord(Object(to_int(text))));
        }
      }
      return while_word;
    }

    IfWord * construct_if_word(std::ifstream & ifs) {
      std::string text;
      IfWord * if_word = new IfWord();
      std::map<std::string, Word*>::iterator found;
      bool add_to_if_branch = true;
      bool add_word = true;
      Word * word_to_add;
      while (ifs.good() && text != "end") {
        ifs >> text;
        if (ifs.eof()) {
          break;
        }
        add_word = true;
        found = vocabulary.find(text);
        if (found != vocabulary.end()) {
          word_to_add = found->second;
        }
        else if (text == "times") {
          word_to_add = construct_times_word(ifs);
        }
        else if (text == "if") {
          word_to_add = construct_if_word(ifs);
        }
        else if (rstr::start_with(text, "\"")) {
          word_to_add = new PushWord(construct_string_object(ifs, text));
        }
        else if (text == "else") {
          add_to_if_branch = false;
          add_word = false;
        }
        else if (text == "end") {
          add_word = false;
        }
        else if (text == "while") {
          word_to_add = construct_while_word(ifs);
        }
        else {
          word_to_add = new PushWord(Object(to_int(text)));
        }
        if (add_word) {
          if (add_to_if_branch) {
            if_word->add_word(word_to_add);
          }
          else {
            if_word->add_else_word(word_to_add);
          }
        }
      }
      return if_word;
    }

    IfWord * construct_if_word(std::ifstream & ifs, std::string const & parent_name, Word * parent) {
      std::string text;
      IfWord * if_word = new IfWord();
      std::map<std::string, Word*>::iterator found;
      bool add_to_if_branch = true;
      bool add_word = true;
      Word * word_to_add;
      while (ifs.good() && text != "end") {
        ifs >> text;
        if (ifs.eof()) {
          break;
        }
        add_word = true;
        found = vocabulary.find(text);
        if (found != vocabulary.end()) {
          word_to_add = found->second;
        }
        else if (text == "times") {
          word_to_add = construct_times_word(ifs, parent_name, parent);
        }
        else if (text == "if") {
          word_to_add = construct_if_word(ifs, parent_name, parent);
        }
        else if (rstr::start_with(text, "\"")) {
          word_to_add = new PushWord(construct_string_object(ifs, text));
        }
        else if (text == "else") {
          add_to_if_branch = false;
          add_word = false;
        }
        else if (text == parent_name) {
          word_to_add = parent;
        }
        else if (text == "end") {
          add_word = false;
        }
        else if (text == "while") {
          word_to_add = construct_while_word(ifs, parent_name, parent);
        }
        else {
          word_to_add = new PushWord(Object(to_int(text)));
        }
        if (add_word) {
          if (add_to_if_branch) {
            if_word->add_word(word_to_add);
          }
          else {
            if_word->add_else_word(word_to_add);
          }
        }
      }
      return if_word;
    }

    Object construct_string_object(std::ifstream & ifs, std::string const & already_read) {
      std::string push_str = already_read;
      if (! rstr::end_with(push_str, "\"")) {
        std::filebuf * pbuf = ifs.rdbuf();
        char current;
        while (ifs.good() && current != '"') {
          current = pbuf->sbumpc();
          push_str.push_back(current);
        }
      }
      push_str.erase(0, 1);
      push_str.erase(push_str.size() - 1, 1);
      return Object(push_str);
    }

    int to_int(std::string const & str) {
    std::stringstream ss;
    ss << str;
    int ret;
    ss >> ret;
    return ret;
  }

    std::map<std::string, Word*> vocabulary;
    std::vector<Object> vector;

};

#endif
