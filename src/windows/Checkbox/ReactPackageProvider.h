#pragma once

#include "ReactPackageProvider.g.h"
#include "CheckboxView.h"

using namespace winrt::Microsoft::ReactNative;

namespace winrt::Checkbox::implementation
{

struct ReactPackageProvider : ReactPackageProviderT<ReactPackageProvider>
{
  ReactPackageProvider() = default;

  void CreatePackage(IReactPackageBuilder const &packageBuilder) noexcept;
};

// View Manager for the checkbox component
struct CheckboxViewManager {
  CheckboxViewManager(IReactContext const& reactContext);
  
  winrt::Windows::UI::Xaml::FrameworkElement CreateView();
  
  void UpdateProperties(
    IReactContext const& reactContext,
    winrt::Windows::UI::Xaml::FrameworkElement const& view,
    IJSValueReader const& propertyMapReader);

private:
  IReactContext m_reactContext{ nullptr };
  winrt::Checkbox::CheckboxView m_currentView{ nullptr };
};

} // namespace winrt::Checkbox::implementation

namespace winrt::Checkbox::factory_implementation
{

struct ReactPackageProvider : ReactPackageProviderT<ReactPackageProvider, implementation::ReactPackageProvider> {};

} // namespace winrt::Checkbox::factory_implementation
