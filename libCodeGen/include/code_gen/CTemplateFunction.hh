#ifndef CTemplateFunction_h__
#define CTemplateFunction_h__
#include "code_gen/CFunction.hh"


class DllExport CTemplateFunction :public CAbstractFunction {
public:
  CTemplateFunction(const arg_list& template_args, const std::string& returntype, const std::string& name, const arg_list& args);
  virtual void getDefinition(std::ostream&, int indentation = 0) const override;


  virtual void getDeclaration(std::ostream&, int indentation = 0) const override;

  CTemplateFunction& addStatement(const std::string& statement__);
  virtual std::unique_ptr<CNode> copy() const override;
  arg_list m_temp_args;
};

#endif // CTemplateFunction_h__
