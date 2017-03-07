#ifndef CFunction_h__
#define CFunction_h__
#include "code_gen/CNode.hh"
#include "code_gen/CEnvironment.hh"
class DllExport CFunction : public CNode {
public:
  using arg_list = std::vector<std::pair<std::string, std::string>>;
  using stm_list = std::vector<std::string>;

  CFunction(const std::string& name);
  CFunction(const std::string& return_type, const std::string& name ,const arg_list& args);
  virtual void getDefinition(std::ostream&, int indentation = 0) const override;
  virtual void getDeclaration(std::ostream&, int  indentation = 0) const override;
  virtual std::unique_ptr<CNode> copy() const override;
  CFunction& addStatement(const std::string& statement_);

private:
  std::string m_return_type;
  arg_list m_args;
  stm_list m_stm;

};

#endif // CFunction_h__
