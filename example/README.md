# Checkbox Example App

This example app demonstrates the usage of `@react-native-community/checkbox` on Android, iOS, and Windows platforms.

## Prerequisites

- Node.js and npm/yarn installed
- For iOS: Xcode and CocoaPods
- For Android: Android Studio and Android SDK
- For Windows: Visual Studio 2019+ with C++ desktop development and Universal Windows Platform development workloads

## Setup

1. Install dependencies:
   ```bash
   cd example
   npm install
   ```

2. For iOS, install CocoaPods dependencies:
   ```bash
   cd ios
   pod install
   cd ..
   ```

## Running the Example

### Start Metro Bundler

First, start the Metro bundler in one terminal:

```bash
npm start
```

### Run on Android

In a separate terminal:

```bash
npm run android
```

### Run on iOS

In a separate terminal:

```bash
npm run ios
```

### Run on Windows

In a separate terminal:

```bash
npm run windows
```

Or open `windows/CheckboxExample.sln` in Visual Studio and build/run from there.

## Troubleshooting

### Metro bundler not starting

If you get an error about missing dependencies, make sure you've run `npm install` in the example directory.

### Windows build issues

If you encounter build issues on Windows:
1. Make sure Visual Studio is installed with the required workloads
2. Try cleaning the build: Delete the `windows/x64` folder and rebuild
3. Ensure react-native-windows is properly installed: `npm install react-native-windows`

### Package not found

If you get errors about `@react-native-community/checkbox` not being found:
1. Make sure the parent `src` directory has been built: `cd ../src && npm run build`
2. Verify the dependency link in `package.json` points to `"@react-native-community/checkbox": "file:../src"`
