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

  // Property setters for RNCCheckboxWindows component
  REACT_METHOD(setDisabled)
  void setDisabled(bool disabled) noexcept;

  REACT_METHOD(setValue)
  void setValue(bool value) noexcept;

  REACT_METHOD(setTintColor)
  void setTintColor(const std::string& tintColor) noexcept;

  REACT_METHOD(setOnCheckColor)
  void setOnCheckColor(const std::string& onCheckColor) noexcept;

  REACT_METHOD(setOnTintColor)
  void setOnTintColor(const std::string& onTintColor) noexcept;

  REACT_METHOD(setOnFillColor)
  void setOnFillColor(const std::string& onFillColor) noexcept;

private:
  React::ReactContext m_context;

  // Event emitter for onChange event
  void emitOnChange(double target, bool value) noexcept;
};

} // namespace winrt::Checkbox