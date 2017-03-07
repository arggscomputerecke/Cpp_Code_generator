#ifndef CHeaderStatement_h__
#define CHeaderStatement_h__
#include "code_gen/CNode.hh"
class DllExport CHeaderStatement :public CNode {

public:
  CHeaderStatement(const std::string& name);
  virtual void getDefinition(std::ostream&, int indentation = 0) const override;


  virtual void getDeclaration(std::ostream&, int indentation = 0) const override;


  virtual std::unique_ptr<CNode> copy() const override;

};
#endif // CHeaderStatement_h__
