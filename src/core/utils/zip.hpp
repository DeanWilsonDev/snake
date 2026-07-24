#pragma once

#include <cassert>
#include <type_traits>
#include <utility>
#include <variant>

namespace Core {

template <typename... Fs>
struct Overloaded : Fs... {
  using Fs::operator()...;
};

template <typename... Fs>
Overloaded(Fs...) -> Overloaded<Fs...>;

namespace Detail {
template <typename Variant, typename Op, std::size_t... Is>
constexpr bool IsInvocableForAllAlternatives(std::index_sequence<Is...>)
{
  return (
      std::is_invocable_v<
          Op&,
          std::variant_alternative_t<Is, Variant>&,
          std::variant_alternative_t<Is, Variant>&> &&
      ...
  );
}
}  // namespace Detail

template <typename Variant, typename Op>
auto Zip(const Variant& a, const Variant& b, Op&& op)
{
  static_assert(
      Detail::IsInvocableForAllAlternatives<Variant, Op>(
          std::make_index_sequence<std::variant_size_v<Variant>>{}
      ),
      "Zip: Op must be callable for every alternative of Variant. Add a lambda for the "
      "missing type to your Overloaded{...} set"
  );

  assert(a.index() == b.index() && "Zip: a and b hold different alternatives");

  return std::visit(
      [&](auto&& lhs) {
        using T = std::decay_t<decltype(lhs)>;
        return op(lhs, std::get<T>(b));
      },
      a
  );
}
}  // namespace Core
