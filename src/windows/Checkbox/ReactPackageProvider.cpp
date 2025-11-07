#include "pch.h"

#include "ReactPackageProvider.h"
#if __has_include("ReactPackageProvider.g.cpp")
#include "ReactPackageProvider.g.cpp"
#endif

#include "Checkbox.h"

using namespace winrt::Microsoft::ReactNative;

namespace winrt::Checkbox::implementation
{

void ReactPackageProvider::CreatePackage(IReactPackageBuilder const &packageBuilder) noexcept
{
  // Add attributed modules and view managers
  AddAttributedModules(packageBuilder, true);
}

} // namespace winrt::Checkbox::implementation
