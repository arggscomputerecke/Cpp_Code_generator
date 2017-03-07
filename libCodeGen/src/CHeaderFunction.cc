#include "code_gen/CHeaderFunction.hh"
#include "code_gen/Internal/helpers.hh"

CHeaderFunction::CHeaderFunction(const std::string& name):CAbstractFunction(name)
{

}

CHeaderFunction::CHeaderFunction(const std::string& return_type, const std::string& name, const arg_list& args) : CAbstractFunction(return_type,name,args)
{

}

void CHeaderFunction::getDefinition(std::ostream& out, int indentation /*= 0*/) const
{

}

void CHeaderFunction::getDeclaration(std::ostream& out, int indentation /*= 0*/) const
{
  out << std::string(indentation, ' ') + m_return_type + "  " + get_name() + "(";

  do_first(m_args, [&out](auto& e) {
    out << " " << e.first << "  " << e.second;
  });

  do_rest(m_args, 1, [&out](auto& e) {
    out << ", " << e.first << "  " << e.second;
  });

  out << "){\n";

  for (auto& e : m_stm) {
    out << std::string(indentation + 2, ' ') << e << "\n";
  }
  out << std::string(indentation, ' ') << "}\n";
}

std::unique_ptr<CNode> CHeaderFunction::copy() const
{
  return Unew CHeaderFunction(*this);
}

CHeaderFunction& CHeaderFunction::addStatement(const std::string& statement_)
{
  m_stm.push_back(statement_);
  return *this;
}
