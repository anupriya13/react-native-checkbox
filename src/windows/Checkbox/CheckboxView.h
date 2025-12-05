#pragma once

#include "pch.h"

#ifdef RNW_NEW_ARCH

#include "codegen/react/components/WindowsCheckBoxComponent/Checkbox.g.h"
#include <winrt/Microsoft.ReactNative.h>
#include <winrt/Microsoft.ReactNative.Composition.h>
#include <winrt/Microsoft.ReactNative.Xaml.h>
#include <winrt/Microsoft.UI.Xaml.h>
#include <winrt/Microsoft.UI.Xaml.Controls.h>

namespace winrt::Checkbox::implementation {

void RegisterCheckboxComponentView(
    winrt::Microsoft::ReactNative::IReactPackageBuilder const &packageBuilder) noexcept;

// XAML-based Checkbox component view
// Implements IXamlControl to allow being parented to XamlHost
struct CheckboxComponentView : winrt::implements<
                                    CheckboxComponentView,
                                    winrt::Microsoft::ReactNative::Xaml::IXamlControl>,
                                CheckboxCodegen::BaseCheckbox<CheckboxComponentView> {

  CheckboxComponentView();

  // IXamlControl implementation - returns the XAML CheckBox control
  winrt::Microsoft::UI::Xaml::UIElement GetXamlElement();

  // ContentIsland initialization
  void InitializeContentIsland(
      const winrt::Microsoft::ReactNative::Composition::ContentIslandComponentView &islandView) noexcept;

  // BaseCheckbox overrides
  void Initialize(const winrt::Microsoft::ReactNative::ComponentView &view) noexcept override;

  // UpdateProps - called by codegen when props change
  void UpdateProps(
      const winrt::Microsoft::ReactNative::ComponentView &view,
      const winrt::com_ptr<CheckboxCodegen::CheckboxProps> &newProps,
      const winrt::com_ptr<CheckboxCodegen::CheckboxProps> &oldProps) noexcept override;

  // UpdateEventEmitter - called by codegen to provide event emitter
  void UpdateEventEmitter(
      const std::shared_ptr<CheckboxCodegen::CheckboxEventEmitter> &eventEmitter) noexcept override;

 private:
  winrt::Microsoft::UI::Xaml::Controls::CheckBox m_checkbox{nullptr};
  winrt::Microsoft::UI::Xaml::XamlIsland m_xamlIsland{nullptr};
  bool m_updating{false};

  // Event handlers
  void OnCheckedChanged(
      winrt::Windows::Foundation::IInspectable const &sender,
      winrt::Microsoft::UI::Xaml::RoutedEventArgs const &e);

  // Helper methods
  winrt::Windows::UI::Color ConvertColor(const winrt::Microsoft::ReactNative::Color &color);
};

} // namespace winrt::Checkbox::implementation

#endif // #ifdef RNW_NEW_ARCH
