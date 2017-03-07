#ifndef CConstructor_h__
#define CConstructor_h__
#include "code_gen/CFunction.hh"

class DllExport CConstructor :public CAbstractFunction {
public:
  CConstructor(const arg_list& args);
  CConstructor(std::string, const arg_list& args);
  virtual void mem_init(std::ostream& out) const override;
  CConstructor& addStatement(const std::string& stm);
  CConstructor& addMemberInitializers(const std::string& stm);
  virtual std::unique_ptr<CNode> copy() const override;
  virtual void add_environment_internal(const CEnvironment& env_);
  CConstructor& operator<<(Funct_t type_);
private: 
  std::vector<std::string> m_mem_init;
  
  mutable bool name_set =false;

};
#endif // CConstructor_h__
