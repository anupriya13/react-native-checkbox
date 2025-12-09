#pragma once

#include "pch.h"

// Only compile new-architecture XAML component when RNW_NEW_ARCH is defined
// and the Microsoft.UI.Xaml header is available.
#if defined(RNW_NEW_ARCH) && __has_include(<winrt/Microsoft.UI.Xaml.h>) && __has_include(<winrt/Microsoft.UI.Xaml.Controls.h>)

#include "codegen/react/components/WindowsCheckBoxComponent/Checkbox.g.h"
#include <winrt/Microsoft.ReactNative.h>
#if __has_include(<winrt/Microsoft.ReactNative.Composition.h>)
#include <winrt/Microsoft.ReactNative.Composition.h>
#endif
#include <winrt/Microsoft.UI.Xaml.h>
#include <winrt/Microsoft.UI.Xaml.Controls.h>
#include <winrt/Microsoft.UI.Xaml.Hosting.h>

namespace winrt::Checkbox::implementation {

void RegisterCheckboxComponentView(
    winrt::Microsoft::ReactNative::IReactPackageBuilder const &packageBuilder) noexcept;

// XAML-backed Checkbox implementation that does not require Microsoft.ReactNative.Xaml.h
struct CheckboxComponentViewXaml : winrt::implements<
                                    CheckboxComponentViewXaml,
                                    winrt::Windows::Foundation::IInspectable>,
                                CheckboxCodegen::BaseCheckbox<CheckboxComponentViewXaml> {

  CheckboxComponentViewXaml();

  // Returns the XAML UIElement representing the checkbox (used by XamlIsland)
  winrt::Microsoft::UI::Xaml::UIElement GetXamlElement();

  // ContentIsland initialization
  void InitializeContentIsland(
      const winrt::Microsoft::ReactNative::Composition::ContentIslandComponentView &islandView) noexcept;

  // BaseCheckbox overrides
  void Initialize(const winrt::Microsoft::ReactNative::ComponentView &view) noexcept override;

  void UpdateProps(
      const winrt::Microsoft::ReactNative::ComponentView &view,
      const winrt::com_ptr<CheckboxCodegen::CheckboxProps> &newProps,
      const winrt::com_ptr<CheckboxCodegen::CheckboxProps> &oldProps) noexcept override;

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

#elif defined(RNW_NEW_ARCH)

// Composition-only implementation (no Microsoft.ReactNative.Xaml or Microsoft.UI.Xaml dependency)
#include "codegen/react/components/WindowsCheckBoxComponent/Checkbox.g.h"
#include <winrt/Microsoft.ReactNative.h>
#if __has_include(<winrt/Microsoft.ReactNative.Composition.h>)
#include <winrt/Microsoft.ReactNative.Composition.h>
#endif
#include <winrt/Microsoft.UI.Composition.h>

namespace winrt::Checkbox::implementation {

void RegisterCheckboxComponentView(
    winrt::Microsoft::ReactNative::IReactPackageBuilder const &packageBuilder) noexcept;

// Simple composition-based checkbox view used when XAML interop header is not present.
struct CheckboxComponentViewSimple : winrt::implements<CheckboxComponentViewSimple, winrt::Windows::Foundation::IInspectable>,
                                      CheckboxCodegen::BaseCheckbox<CheckboxComponentViewSimple> {

  CheckboxComponentViewSimple();

  // BaseCheckbox overrides
  void Initialize(const winrt::Microsoft::ReactNative::ComponentView &view) noexcept override;

  void UpdateProps(
      const winrt::Microsoft::ReactNative::ComponentView &view,
      const winrt::com_ptr<CheckboxCodegen::CheckboxProps> &newProps,
      const winrt::com_ptr<CheckboxCodegen::CheckboxProps> &oldProps) noexcept override;

  void UpdateEventEmitter(
      const std::shared_ptr<CheckboxCodegen::CheckboxEventEmitter> &eventEmitter) noexcept override;

  // Create a composition visual to represent the checkbox
  winrt::Microsoft::UI::Composition::Visual CreateVisual(const winrt::Microsoft::ReactNative::ComponentView &view) noexcept override;

 private:
  bool m_updating{false};
};

} // namespace winrt::Checkbox::implementation

#endif // RNW_NEW_ARCH
