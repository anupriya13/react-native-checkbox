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

  // Property setters for RNCCheckboxWindows component
  REACT_METHOD(setDisabled)
  void setDisabled(bool disabled) noexcept;

  REACT_METHOD(setValue)
  void setValue(bool value) noexcept;

  REACT_METHOD(setTintColor)
  void setTintColor(std::string tintColor) noexcept;

  REACT_METHOD(setOnCheckColor)
  void setOnCheckColor(std::string onCheckColor) noexcept;

  REACT_METHOD(setOnTintColor)
  void setOnTintColor(std::string onTintColor) noexcept;

  REACT_METHOD(setOnFillColor)
  void setOnFillColor(std::string onFillColor) noexcept;

  // Event emitter for onChange event
  REACT_METHOD(emitOnChange)
  void emitOnChange(int target, bool value) noexcept;

private:
  React::ReactContext m_context;
};

} // namespace winrt::Checkbox