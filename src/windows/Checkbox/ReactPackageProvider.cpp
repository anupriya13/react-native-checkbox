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
  AddAttributedModules(packageBuilder, true);
  // Register our Checkbox component (new architecture)
  RegisterCheckboxComponentView(packageBuilder);
}

} // namespace winrt::Checkbox::implementation