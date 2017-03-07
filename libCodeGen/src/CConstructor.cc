#include "code_gen/CConstructor.hh"
#include "code_gen/Internal/helpers.hh"


CConstructor::CConstructor(const arg_list& args):CAbstractFunction("","", args)
{

}

CConstructor::CConstructor(std::string, const arg_list& args) : CAbstractFunction("", "", args)
{

}



void CConstructor::mem_init(std::ostream& out) const
{
  do_first(m_mem_init, [&out](auto& e) {
    out << " : " << e;
  });
  do_rest(m_mem_init, 1, [&out](auto& e) {
    out << ", " << e;
  });
}

CConstructor& CConstructor::addStatement(const std::string& stm)
{
  m_stm.push_back(stm);
  return *this;
}

CConstructor& CConstructor::addMemberInitializers(const std::string& stm)
{
  m_mem_init.push_back(stm);
  return *this;
}

std::unique_ptr<CNode> CConstructor::copy() const
{
  return Unew CConstructor(*this);
}

void CConstructor::add_environment_internal(const CEnvironment& env_)
{
  if (name_set){
    return;
  }
  m_env.clear();
  m_env.push_back(env_);
  m_name = env_.m_name;
  name_set = true;
}

CConstructor& CConstructor::operator<<(Funct_t type_)
{
  setType(type_);
  return *this;
}



