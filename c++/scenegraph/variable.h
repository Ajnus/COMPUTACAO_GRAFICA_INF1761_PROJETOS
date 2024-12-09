#include <memory>
template <class T> class Variable;
template <class T> using VariablePtr = std::shared_ptr<Variable<T>>; 

#ifndef VARIABLE_H
#define VARIABLE_H

#include "appearance.h"
#include "shader.h"
#include <glm/glm.hpp>
#include <string>

template <class T>
class Variable : public Appearance {
  std::string m_name;
  T m_value; 
protected:
  Variable (const std::string& name, const T& value)
  : m_name(name), m_value(value)
  {
  }
public:
  static VariablePtr<T> Make (const std::string& name, const T& value=T())
  {
    return VariablePtr<T>(new Variable(name,value));
  }
  virtual ~Variable ()
  {
  }
  void SetValue (T value)
  {
    m_value = value;
  }
  virtual void Load (StatePtr st)
  {
    ShaderPtr shd = st->GetShader();
    shd->SetUniform(m_name,m_value);
  }
};

#endif