#include "code_gen/CTemplateFunction.hh"
#include "code_gen/Internal/helpers.hh"

CTemplateFunction::CTemplateFunction(const arg_list& template_args, const std::string& returntype, const std::string& name, const arg_list& args):CAbstractFunction(returntype,name,args),m_temp_args(template_args)
{
  
}

void CTemplateFunction::getDefinition(std::ostream& out, int indentation /*= 0*/) const
{
  
}

void CTemplateFunction::getDeclaration(std::ostream& out, int indentation /*= 0*/) const
{
  out << std::string(indentation, ' ') << "template <";
  do_first(m_temp_args, [&out](auto& e) {
    out << e.first << "  " << e.second;
  });

  do_rest(m_temp_args, 1, [&out](auto& e) {
    out << ", " << e.first << "  " << e.second;
  });
  out << ">\n";

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

CTemplateFunction& CTemplateFunction::addStatement(const std::string& statement__)
{
  m_stm.push_back(statement__);
  return *this;
}

std::unique_ptr<CNode> CTemplateFunction::copy() const
{
  return Unew CTemplateFunction(*this);
}

