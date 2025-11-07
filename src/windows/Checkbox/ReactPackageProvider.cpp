#include "pch.h"

#include "ReactPackageProvider.h"
#if __has_include("ReactPackageProvider.g.cpp")
#include "ReactPackageProvider.g.cpp"
#endif

using namespace winrt::Microsoft::ReactNative;

namespace winrt::Checkbox::implementation
{

void ReactPackageProvider::CreatePackage(IReactPackageBuilder const &packageBuilder) noexcept
{
  // TODO: Add view managers or native modules here
}

} // namespace winrt::Checkbox::implementation
