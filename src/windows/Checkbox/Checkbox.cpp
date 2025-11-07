#include "pch.h"

#include "Checkbox.h"

namespace winrt::Checkbox
{

// See https://microsoft.github.io/react-native-windows/docs/native-platform for help writing native modules

void Checkbox::Initialize(React::ReactContext const &reactContext) noexcept {
  m_context = reactContext;
}

double Checkbox::multiply(double a, double b) noexcept {
  return a * b;
}

} // namespace winrt::Checkbox