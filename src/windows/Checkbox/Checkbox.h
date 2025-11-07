#pragma once

#include "pch.h"
#include "resource.h"

#if __has_include("codegen/NativeCheckboxDataTypes.g.h")
  #include "codegen/NativeCheckboxDataTypes.g.h"
#endif

#include "NativeModules.h"

namespace winrt::Checkbox
{

// See https://microsoft.github.io/react-native-windows/docs/native-platform for help writing native modules

REACT_MODULE(Checkbox)
struct Checkbox
{
  REACT_INIT(Initialize)
  void Initialize(React::ReactContext const &reactContext) noexcept;

  REACT_SYNC_METHOD(multiply)
  double multiply(double a, double b) noexcept;

private:
  React::ReactContext m_context;
};

} // namespace winrt::Checkbox