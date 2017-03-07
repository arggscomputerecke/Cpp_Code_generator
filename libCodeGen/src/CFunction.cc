#include "code_gen/CFunction.hh"
#include "code_gen/Internal/helpers.hh"

CFunction::CFunction(const std::string& name):CAbstractFunction(name)
{
 
}

CFunction::CFunction(const std::string& return_type, const std::string& name,const arg_list& args):CAbstractFunction(return_type,name,args)
{

}


void CFunction::getDefinition(std::ostream& out, int indentation /*= 0*/) const
{
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

  out << ") {\n";
  for (auto& e:m_stm){
    out << std::string(indentation+2, ' ')<< e << "\n";
  }
  out << std::string(indentation, ' ') << "}\n";
}

void CFunction::getDeclaration(std::ostream& out, int indentation /*= 0*/) const
{
  out << std::string(indentation, ' ') + m_return_type + "  " + get_name() + "(";

  do_first(m_args, [&out](auto& e) {
    out << " " << e.first << "  " << e.second;
  });

  do_rest(m_args, 1, [&out](auto& e) {
    out << ", " << e.first << "  " << e.second;
  });

  out << ");\n";
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


CAbstractFunction::CAbstractFunction(const std::string& name) :CAbstractFunction("void", name, {} ){
  

}
CAbstractFunction::CAbstractFunction(const std::string& return_type, const std::string& name, const arg_list& args) : CNode(name), m_return_type(return_type), m_args(args)
{
  m_env.push_back(CEnvironment(name, Funct_t));
}
