#ifndef CHeaderFunction_h__
#define CHeaderFunction_h__


#include "code_gen/CFunction.hh"

class DllExport CHeaderFunction : public CAbstractFunction {


public:

  CHeaderFunction(const std::string& name);
  CHeaderFunction(const std::string& return_type, const std::string& name, const arg_list& args);
  virtual void getDefinition(std::ostream&, int indentation = 0) const override;


  virtual void getDeclaration(std::ostream&, int indentation = 0) const override;


  virtual std::unique_ptr<CNode> copy() const override;
  CHeaderFunction& addStatement(const std::string& statement_);

};

#endif // CHeaderFunction_h__
