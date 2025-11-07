#include "pch.h"

#include "ReactPackageProvider.h"
#if __has_include("ReactPackageProvider.g.cpp")
#include "ReactPackageProvider.g.cpp"
#endif

#include "CheckboxView.h"

using namespace winrt::Microsoft::ReactNative;

namespace winrt::Checkbox::implementation
{

void ReactPackageProvider::CreatePackage(IReactPackageBuilder const &packageBuilder) noexcept
{
  // Register the view manager for RNCCheckboxWindows
  packageBuilder.AddViewManager(
    L"RNCCheckboxWindows",
    [](IReactContext context) {
      return winrt::make<CheckboxViewManager>(context);
    });
}

// View Manager implementation
CheckboxViewManager::CheckboxViewManager(IReactContext const& reactContext)
  : m_reactContext(reactContext) {
}

winrt::Windows::UI::Xaml::FrameworkElement CheckboxViewManager::CreateView() {
  auto view = winrt::make<CheckboxView>(m_reactContext);
  m_currentView = view;
  return view.GetView();
}

void CheckboxViewManager::UpdateProperties(
  IReactContext const& /*reactContext*/,
  FrameworkElement const& /*view*/,
  IJSValueReader const& propertyMapReader) {
  if (m_currentView) {
    m_currentView.UpdateProperties(propertyMapReader);
  }
}

} // namespace winrt::Checkbox::implementation
