#pragma once

#include <typeinfo>
#include <algorithm>

// The code in this file is mostly copied from the boost libraries

class Placeholder {
        
  public:
    
    virtual ~Placeholder() {

    }

    virtual std::type_info const & type() const = 0;
    virtual Placeholder * clone() const = 0;

};

template <typename ValueType>
class Holder : public Placeholder {

  public:

    Holder(ValueType const & value) : held(value) {
    
    }

    virtual std::type_info const & type() const {
      return typeid(ValueType);
    }

    virtual Placeholder * clone() const {
      return new Holder(held);
    }

    ValueType held;

};



  class Object {

    public:

      Object() : content(0) {
      
      }

      Object(Object const & other) : content(other.content ? other.content->clone() : 0) {

      }

      template <typename ValueType>
      Object(ValueType const & value) : content(new Holder<ValueType>(value)) {

      }

      Object & operator=(Object & other) {
        other.swap(*this);
        return *this;
      }

      template <typename ValueType>
      Object & operator=(ValueType const & value) {
        Object(value).swap(*this);
        return *this;
      }

      ~Object() {
        delete content;
      }

      Object & swap(Object & other) {
        std::swap(content, other.content);
        return *this;
      }

      bool empty() const {
        return !content;
      }

      std::type_info const & type() const {
        return content ? content->type() : typeid(void);
      }

      

      Placeholder * content;

  };

  template <typename ValueType>
  ValueType obj_cast(Object const & object) {
    return static_cast<Holder<ValueType>* >(object.content)->held;
  }

