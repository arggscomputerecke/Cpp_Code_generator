#ifndef CFunction_h__
#define CFunction_h__
#include "code_gen/CNode.hh"
#include "code_gen/CEnvironment.hh"

enum Funct_t
{
  normal_t = 0,
  const_t = 1,
  inline_t = 2
};
class DllExport CAbstractFunction : public CNode {
public:
  using arg_list = std::vector<std::pair<std::string, std::string>>;
  using stm_list = std::vector<std::string>;

  CAbstractFunction(const std::string& name);
  CAbstractFunction(const std::string& return_type, const std::string& name ,const arg_list& args);
  virtual void getDefinition(std::ostream&, int indentation = 0) const override;
  virtual void getDeclaration(std::ostream&, int  indentation = 0) const override;
  virtual void mem_init(std::ostream& out) const;
  void setType(Funct_t fun_t_);
protected:
  std::string m_return_type;
  arg_list m_args;
  stm_list m_stm;
  Funct_t m_func_t = normal_t;
  bool isType(Funct_t type_t) const;
private:
  void getDeclaration_inline(std::ostream& out, int  indentation = 0) const;
  void getConst(std::ostream& out) const;
};


class DllExport CFunction :public CAbstractFunction {
public:
  CFunction(const std::string& name);
  CFunction(const std::string& return_type, const std::string& name, const arg_list& args);

  virtual std::unique_ptr<CNode> copy() const override;
  CFunction& addStatement(const std::string& statement_);
  CFunction& operator<<(Funct_t f_t);
  


};
#endif // CFunction_h__
