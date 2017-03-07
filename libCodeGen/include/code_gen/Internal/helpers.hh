#ifndef helpers_h__
#define helpers_h__

template <typename Container_t, typename Func_t>
void do_first(Container_t&& c, Func_t&& fun) {
  if (c.begin()== c.end()) {
    return;
  }

  fun(*c.begin());
}
template <typename Container_t, typename Func_t>
void do_rest(Container_t&& c, size_t start_element, Func_t&& fun) {
  if ( c.end() - c.begin()  < 2) {
    return;
  }

  auto mIter = c.begin();
  std::advance(mIter, start_element);
  for (; mIter != c.end(); ++mIter) {
    fun(*mIter);
  }
}

template<class It, class C>
struct range_for_t {
  It b, e;
  C c; // for lifetime
  It begin()const { return b; }
  It end()const { return e; }


};
template<class It, class C>
range_for_t<It, C> range_for(It b, It e, C&& c) {
  return{ std::move(b),std::move(e),std::forward<C>(c) };
}

template<class It>
range_for_t<It, int> range_for(It b, It e) {
  return{ std::move(b),std::move(e) };
}
template<class It>
auto reverse_it(It it) {
  return std::reverse_iterator<It>(std::move(it));
}
template<class C>
auto backwards(C&&c) {
  using std::begin; using std::end;
  auto b = begin(c), e = end(c);
  return range_for(
    reverse_it(e), reverse_it(b),
    std::forward<C>(c)
  );
}
#endif // helpers_h__
