#include "code_gen/CFunction.hh"
#include "code_gen/Internal/helpers.hh"

CFunction::CFunction(const std::string& name):CAbstractFunction(name)
{
 
}

CFunction::CFunction(const std::string& return_type, const std::string& name,const arg_list& args):CAbstractFunction(return_type,name,args)
{

}


void CAbstractFunction::getDefinition(std::ostream& out, int indentation /*= 0*/) const
{
  
  if (isType(inline_t))
  {
    return;
  }
  out << std::string(indentation, ' ') + m_return_type + "  ";
  do_first(backwards(m_env), [&out](auto& e) {
    out << e.m_name;
  });
  do_rest(backwards(m_env), 1, [&out](auto& e) {
    out << "::" << e.m_name;
  
  });
  out <<  "(";

  do_first(m_args, [&out](auto& e) {
    out << " " << e.first << "  " << e.second;
  });

  do_rest(m_args, 1, [&out](auto& e) {
    out << ", " << e.first << "  " << e.second;
  });

  out << ")";
  getConst(out);
  mem_init(out);
  out << " {\n";
  for (auto& e:m_stm){
    out << std::string(indentation+2, ' ')<< e << "\n";
  }
  out << std::string(indentation, ' ') << "}\n";
}

void CAbstractFunction::getDeclaration(std::ostream& out, int indentation /*= 0*/) const
{
  if (isType(inline_t))
  {
    getDeclaration_inline(out, indentation);
    return;
  }
  out << std::string(indentation, ' ') + m_return_type + "  " + m_env[0].m_name + "(";

  do_first(m_args, [&out](auto& e) {
    out << " " << e.first << "  " << e.second;
  });

  do_rest(m_args, 1, [&out](auto& e) {
    out << ", " << e.first << "  " << e.second;
  });

  out << ")";
  getConst(out);
  out << ";\n";
}

std::unique_ptr<CNode> CFunction::copy() const
{
  return Unew CFunction(*this);
}

CFunction& CFunction::addStatement(const std::string& statement_)
{
  m_stm.push_back(statement_);
  return *this;
}


CFunction& CFunction::operator<<(Funct_t f_t)
{
  setType(f_t);
  return *this;
}

void CAbstractFunction::getDeclaration_inline(std::ostream& out, int indentation /*= 0*/) const
{
  out << std::string(indentation, ' ') + m_return_type + "  " + m_env[0].m_name + "(";

  do_first(m_args, [&out](auto& e) {
    out << " " << e.first << "  " << e.second;
  });

  do_rest(m_args, 1, [&out](auto& e) {
    out << ", " << e.first << "  " << e.second;
  });

  out << ")"; 
  getConst(out);
  mem_init(out);
  out << "{\n";

  for (auto& e : m_stm) {
    out << std::string(indentation + 2, ' ') << e << "\n";
  }
  out << std::string(indentation, ' ') << "}\n";
}

void CAbstractFunction::getConst(std::ostream& out) const
{
  if (isType(const_t))
  {
    out << " const ";
  }
}

CAbstractFunction::CAbstractFunction(const std::string& name) :CAbstractFunction("void", name, {} ){
  

}
CAbstractFunction::CAbstractFunction(const std::string& return_type, const std::string& name, const arg_list& args) : CNode(name), m_return_type(return_type), m_args(args)
{
  m_env.push_back(CEnvironment(name, Funct_e));
}

void CAbstractFunction::mem_init(std::ostream& out) const
{

}

void CAbstractFunction::setType(Funct_t fun_t_)
{
  m_func_t = fun_t_;
}

bool CAbstractFunction::isType(Funct_t type_t) const
{
  return (type_t & m_func_t) == type_t;
}
