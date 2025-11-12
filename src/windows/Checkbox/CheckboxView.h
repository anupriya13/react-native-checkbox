#pragma once

#include "pch.h"

#ifdef RNW_NEW_ARCH

#include "codegen/react/components/WindowsCheckBoxComponent/Checkbox.g.h"

#include <winrt/Microsoft.ReactNative.Composition.h>
#include <winrt/Microsoft.UI.Xaml.h>
#include <winrt/Microsoft.UI.Xaml.Controls.h>
#include <winrt/Windows.UI.Xaml.Data.h>

namespace winrt::Checkbox::implementation {

void RegisterCheckboxComponentView(
    winrt::Microsoft::ReactNative::IReactPackageBuilder const &packageBuilder) noexcept;

struct CheckboxComponentView : winrt::implements<CheckboxComponentView, winrt::IInspectable>,
                                 CheckboxCodegen::BaseCheckbox<CheckboxComponentView> {
  winrt::Microsoft::UI::Composition::Visual CreateVisual(
      const winrt::Microsoft::ReactNative::ComponentView &view) noexcept override;
  void Initialize(const winrt::Microsoft::ReactNative::ComponentView & /*view*/) noexcept override;

 private:
  winrt::Microsoft::ReactNative::ComponentView::LayoutMetricsChanged_revoker m_layoutMetricChangedRevoker;
  winrt::Microsoft::UI::Composition::SpriteVisual m_visual{nullptr};
};

} // namespace winrt::Checkbox::implementation

#endif // #ifdef RNW_NEW_ARCH
