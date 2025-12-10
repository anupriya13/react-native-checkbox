#include "pch.h"

// XAML-backed implementation when Microsoft.UI.Xaml is available
#if defined(RNW_NEW_ARCH) && __has_include(<winrt/Microsoft.UI.Xaml.h>) && __has_include(<winrt/Microsoft.UI.Xaml.Controls.h>)

#include "CheckboxView.h"

#if __has_include(<winrt/Microsoft.ReactNative.Composition.Experimental.h>)
#include <winrt/Microsoft.ReactNative.Composition.Experimental.h>
#endif

using namespace winrt;
using namespace winrt::Microsoft::ReactNative;
using namespace winrt::Microsoft::ReactNative::Composition;
using namespace winrt::Microsoft::ReactNative::Composition::Experimental;
using namespace winrt::Microsoft::UI::Composition;
using namespace winrt::Microsoft::UI::Xaml;
using namespace winrt::Microsoft::UI::Xaml::Controls;
using namespace winrt::Microsoft::UI::Xaml::Media;
using namespace winrt::Windows::Foundation;
namespace WUC = winrt::Windows::UI;

namespace winrt::Checkbox::implementation {

CheckboxComponentViewXaml::CheckboxComponentViewXaml() {
  m_checkbox = CheckBox();
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

UIElement CheckboxComponentViewXaml::GetXamlElement() {
  return m_checkbox;
}

void CheckboxComponentViewXaml::InitializeContentIsland(
    const Composition::ContentIslandComponentView &islandView) noexcept {
  // Ensure XAML application is created. If RNW's XamlApplication helper is
  // available use it, otherwise skip - the host should initialize XAML.
#if __has_include(<winrt/Microsoft.ReactNative.Xaml.h>)
  XamlApplication::EnsureCreated();
#endif
  m_xamlIsland = XamlIsland{};
  m_xamlIsland.Content(m_checkbox);
  islandView.Connect(m_xamlIsland.ContentIsland());
}

void CheckboxComponentViewXaml::Initialize(const Microsoft::ReactNative::ComponentView & /*view*/) noexcept {}

void CheckboxComponentViewXaml::UpdateProps(
    const Microsoft::ReactNative::ComponentView & /*view*/,
    const winrt::com_ptr<CheckboxCodegen::CheckboxProps> &newProps,
    const winrt::com_ptr<CheckboxCodegen::CheckboxProps> &oldProps) noexcept {
  if (!newProps) return;
  m_updating = true;
  if (!oldProps || newProps->value != oldProps->value) {
    m_checkbox.IsChecked(newProps->value);
  }
  if (!oldProps || newProps->disabled != oldProps->disabled) {
    m_checkbox.IsEnabled(!newProps->disabled);
  }
  m_updating = false;
}

void CheckboxComponentViewXaml::UpdateEventEmitter(
    const std::shared_ptr<CheckboxCodegen::CheckboxEventEmitter> &eventEmitter) noexcept {
  BaseCheckbox::UpdateEventEmitter(eventEmitter);
}

void CheckboxComponentViewXaml::OnCheckedChanged(IInspectable const & /*sender*/, RoutedEventArgs const & /*e*/) {
  if (m_updating) return;
  if (auto eventEmitter = EventEmitter()) {
    CheckboxCodegen::CheckboxEventEmitter::OnChange args;
    args.value = m_checkbox.IsChecked().GetBoolean();
    eventEmitter->onChange(args);
  }
}

WUC::Color CheckboxComponentViewXaml::ConvertColor(const Microsoft::ReactNative::Color &color) {
  return color.AsWindowsColor(nullptr);
}

void RegisterCheckboxComponentView(IReactPackageBuilder const &packageBuilder) noexcept {
  // Register the XAML-backed view when composition builder is available
#if __has_include(<winrt/Microsoft.ReactNative.Composition.h>)
  CheckboxCodegen::RegisterCheckboxNativeComponent<CheckboxComponentViewXaml>(
      packageBuilder,
      [](const Composition::IReactCompositionViewComponentBuilder &builder) {
        builder.SetContentIslandComponentViewInitializer(
            [](const Composition::ContentIslandComponentView &islandView) noexcept {
              auto userData = winrt::make_self<CheckboxComponentViewXaml>();
              userData->InitializeContentIsland(islandView);
              islandView.UserData(*userData);
            });
      });
#endif
}

} // namespace winrt::Checkbox::implementation

#elif defined(RNW_NEW_ARCH) && __has_include(<winrt/Microsoft.ReactNative.Composition.h>)

// Composition-only fallback implementation
#include "CheckboxView.h"

using namespace winrt;
using namespace winrt::Microsoft::ReactNative;
using namespace winrt::Microsoft::ReactNative::Composition;
using namespace winrt::Microsoft::UI::Composition;

namespace winrt::Checkbox::implementation {

CheckboxComponentViewSimple::CheckboxComponentViewSimple() {}

void CheckboxComponentViewSimple::Initialize(const Microsoft::ReactNative::ComponentView & /*view*/) noexcept {}

void CheckboxComponentViewSimple::UpdateProps(
    const Microsoft::ReactNative::ComponentView & /*view*/,
    const winrt::com_ptr<CheckboxCodegen::CheckboxProps> &newProps,
    const winrt::com_ptr<CheckboxCodegen::CheckboxProps> & /*oldProps*/) noexcept {
  if (!newProps) return;
  m_updating = true;
  m_updating = false;
}

void CheckboxComponentViewSimple::UpdateEventEmitter(const std::shared_ptr<CheckboxCodegen::CheckboxEventEmitter> &eventEmitter) noexcept {
  BaseCheckbox::UpdateEventEmitter(eventEmitter);
}

Visual CheckboxComponentViewSimple::CreateVisual(const Microsoft::ReactNative::ComponentView &view) noexcept {
  auto compView = view.as<winrt::Microsoft::ReactNative::Composition::ComponentView>();
  auto compositor = compView.Compositor();
  auto visual = compositor.CreateContainerVisual();
  auto sprite = compositor.CreateSpriteVisual();
  sprite.Size({20.0f, 20.0f});
  auto brush = compositor.CreateColorBrush({0.8f, 0.8f, 0.8f, 1.0f});
  sprite.Brush(brush);
  visual.Children().InsertAtTop(sprite);
  return visual;
}

void RegisterCheckboxComponentView(IReactPackageBuilder const &packageBuilder) noexcept {
  packageBuilder.as<winrt::Microsoft::ReactNative::IReactPackageBuilderFabric>().AddViewComponent(
      L"Checkbox", [](winrt::Microsoft::ReactNative::IReactViewComponentBuilder const &builder) noexcept {
        auto compBuilder = builder.as<winrt::Microsoft::ReactNative::Composition::IReactCompositionViewComponentBuilder>();

        builder.SetCreateProps([](winrt::Microsoft::ReactNative::ViewProps props,
                              const winrt::Microsoft::ReactNative::IComponentProps& cloneFrom) noexcept {
            return winrt::make<CheckboxCodegen::CheckboxProps>(props, cloneFrom); 
        });

        compBuilder.SetViewComponentViewInitializer([](const winrt::Microsoft::ReactNative::ComponentView &view) noexcept {
          auto userData = winrt::make_self<CheckboxComponentViewSimple>();
          if CONSTEXPR_SUPPORTED_ON_VIRTUAL_FN_ADDRESS (&CheckboxComponentViewSimple::Initialize != &CheckboxCodegen::BaseCheckbox<CheckboxComponentViewSimple>::Initialize) {
            userData->Initialize(view);
          }
          view.UserData(*userData);
        });
      });
}

} // namespace winrt::Checkbox::implementation

#else

// RNW new-arch not available or no compatible headers; provide a no-op
#include "CheckboxView.h"
namespace winrt::Checkbox::implementation {
inline void RegisterCheckboxComponentView(IReactPackageBuilder const & /*packageBuilder*/) noexcept {}
}

#endif
