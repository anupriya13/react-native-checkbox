#include "pch.h"

#ifdef RNW_NEW_ARCH

#include "CheckboxView.h"

#include <winrt/Microsoft.ReactNative.Composition.Experimental.h>

using namespace winrt;
using namespace winrt::Microsoft::ReactNative;
using namespace winrt::Microsoft::ReactNative::Composition;
using namespace winrt::Microsoft::ReactNative::Composition::Experimental;
using namespace winrt::Microsoft::ReactNative::Xaml;
using namespace winrt::Microsoft::UI::Composition;
using namespace winrt::Microsoft::UI::Xaml;
using namespace winrt::Microsoft::UI::Xaml::Controls;
using namespace winrt::Microsoft::UI::Xaml::Media;
using namespace winrt::Windows::Foundation;
namespace WF = winrt::Windows::Foundation;
namespace WUC = winrt::Windows::UI;

namespace winrt::Checkbox::implementation {

CheckboxComponentView::CheckboxComponentView() {
  // Create the XAML CheckBox control
  m_checkbox = CheckBox();
  
  // Register event handlers
  m_checkbox.Checked([weakThis = get_weak()](auto const &sender, auto const &e) {
    if (auto strongThis = weakThis.get()) {
      strongThis->OnCheckedChanged(sender, e);
    }
  });
  
  m_checkbox.Unchecked([weakThis = get_weak()](auto const &sender, auto const &e) {
    if (auto strongThis = weakThis.get()) {
      strongThis->OnCheckedChanged(sender, e);
    }
  });
}

UIElement CheckboxComponentView::GetXamlElement() {
  return m_checkbox;
}

void CheckboxComponentView::InitializeContentIsland(
    const Composition::ContentIslandComponentView &islandView) noexcept {
  // Ensure XAML application is created
  XamlApplication::EnsureCreated();

  // Create XamlIsland to host the checkbox
  m_xamlIsland = XamlIsland{};
  m_xamlIsland.Content(m_checkbox);

  // Connect the island to the content island view
  islandView.Connect(m_xamlIsland.ContentIsland());
}

void CheckboxComponentView::Initialize(const Microsoft::ReactNative::ComponentView & /*view*/) noexcept {
  // No additional initialization needed
}

void CheckboxComponentView::UpdateProps(
    const Microsoft::ReactNative::ComponentView & /*view*/,
    const winrt::com_ptr<CheckboxCodegen::CheckboxProps> &newProps,
    const winrt::com_ptr<CheckboxCodegen::CheckboxProps> &oldProps) noexcept {
  if (!newProps) {
    return;
  }

  m_updating = true;

  // Update value (IsChecked)
  if (!oldProps || newProps->value != oldProps->value) {
    m_checkbox.IsChecked(newProps->value);
  }

  // Update disabled state
  if (!oldProps || newProps->disabled != oldProps->disabled) {
    m_checkbox.IsEnabled(!newProps->disabled);
  }

  // Apply theming using Resources dictionary
  auto resources = m_checkbox.Resources();
  
  // Handle onCheckColor (checked state glyph color)
  if (newProps->onCheckColor) {
    auto color = ConvertColor(newProps->onCheckColor);
    auto colorBrush = SolidColorBrush(color);
    resources.Insert(box_value(L"CheckBoxCheckGlyphForegroundChecked"), colorBrush);
    resources.Insert(box_value(L"CheckBoxCheckGlyphForegroundCheckedPointerOver"), colorBrush);
    resources.Insert(box_value(L"CheckBoxCheckGlyphForegroundCheckedPressed"), colorBrush);
  }

  // Handle onFillColor (checked state fill)
  if (newProps->onFillColor) {
    auto color = ConvertColor(newProps->onFillColor);
    auto colorBrush = SolidColorBrush(color);
    resources.Insert(box_value(L"CheckBoxCheckBackgroundFillChecked"), colorBrush);
    resources.Insert(box_value(L"CheckBoxCheckBackgroundFillCheckedPointerOver"), colorBrush);
    resources.Insert(box_value(L"CheckBoxCheckBackgroundFillCheckedPressed"), colorBrush);
  }

  // Handle onTintColor (checked state border)
  if (newProps->onTintColor) {
    auto color = ConvertColor(newProps->onTintColor);
    auto colorBrush = SolidColorBrush(color);
    resources.Insert(box_value(L"CheckBoxCheckBackgroundStrokeChecked"), colorBrush);
    resources.Insert(box_value(L"CheckBoxCheckBackgroundStrokeCheckedPointerOver"), colorBrush);
    resources.Insert(box_value(L"CheckBoxCheckBackgroundStrokeCheckedPressed"), colorBrush);
  }

  // Handle tintColor (unchecked state border)
  if (newProps->tintColor) {
    auto color = ConvertColor(newProps->tintColor);
    auto colorBrush = SolidColorBrush(color);
    resources.Insert(box_value(L"CheckBoxCheckBackgroundStrokeUnchecked"), colorBrush);
    resources.Insert(box_value(L"CheckBoxCheckBackgroundStrokeUncheckedPointerOver"), colorBrush);
    resources.Insert(box_value(L"CheckBoxCheckBackgroundStrokeUncheckedPressed"), colorBrush);
  }

  m_updating = false;
}

void CheckboxComponentView::UpdateEventEmitter(
    const std::shared_ptr<CheckboxCodegen::CheckboxEventEmitter> &eventEmitter) noexcept {
  BaseCheckbox::UpdateEventEmitter(eventEmitter);
}

void CheckboxComponentView::OnCheckedChanged(
    IInspectable const & /*sender*/,
    RoutedEventArgs const & /*e*/) {
  // Prevent infinite loops when setting IsChecked programmatically
  if (m_updating) {
    return;
  }

  // Get the event emitter and emit the change event
  if (auto eventEmitter = EventEmitter()) {
    CheckboxCodegen::CheckboxEventEmitter::OnChange args;
    args.value = m_checkbox.IsChecked().GetBoolean();
    eventEmitter->onChange(args);
  }
}

WUC::Color CheckboxComponentView::ConvertColor(const Microsoft::ReactNative::Color &color) {
  // Color is a WinRT object with AsWindowsColor method
  return color.AsWindowsColor(nullptr);
}

void RegisterCheckboxComponentView(IReactPackageBuilder const &packageBuilder) noexcept {
  CheckboxCodegen::RegisterCheckboxNativeComponent<CheckboxComponentView>(
      packageBuilder,
      [](const Composition::IReactCompositionViewComponentBuilder &builder) {
        builder.SetContentIslandComponentViewInitializer(
            [](const Composition::ContentIslandComponentView &islandView) noexcept {
              auto userData = winrt::make_self<CheckboxComponentView>();
              userData->InitializeContentIsland(islandView);
              islandView.UserData(*userData);
            });
      });
}

} // namespace winrt::Checkbox::implementation

#endif // #ifdef RNW_NEW_ARCH
