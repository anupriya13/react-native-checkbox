#include "pch.h"

#include "Checkbox.h"

namespace winrt::Checkbox
{

// See https://microsoft.github.io/react-native-windows/docs/native-platform for help writing native modules

void Checkbox::Initialize(React::ReactContext const &reactContext) noexcept {
  m_context = reactContext;
}

// Property setter implementations for RNCCheckboxWindows component

void Checkbox::setDisabled(bool disabled) noexcept {
  // TODO: Implement setting disabled state on the native checkbox control
}

void Checkbox::setValue(bool value) noexcept {
  // TODO: Implement setting the checked state on the native checkbox control
}

void Checkbox::setTintColor(const std::string& tintColor) noexcept {
  // TODO: Implement setting tint color on the native checkbox control
}

void Checkbox::setOnCheckColor(const std::string& onCheckColor) noexcept {
  // TODO: Implement setting on-check color on the native checkbox control
}

void Checkbox::setOnTintColor(const std::string& onTintColor) noexcept {
  // TODO: Implement setting on-tint color on the native checkbox control
}

void Checkbox::setOnFillColor(const std::string& onFillColor) noexcept {
  // TODO: Implement setting on-fill color on the native checkbox control
}

void Checkbox::emitOnChange(int target, bool value) noexcept {
  // TODO: Implement emitting onChange event back to JavaScript
  // This should fire the onChange event with the target and value
}

} // namespace winrt::Checkbox