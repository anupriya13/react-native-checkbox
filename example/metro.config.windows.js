/**
 * Metro configuration for React Native
 * https://github.com/facebook/react-native
 *
 * @format
 */
const fs = require('fs');
const path = require('path');
const {getDefaultConfig, mergeConfig} = require('@react-native/metro-config');

const rnPath = fs.realpathSync(
  path.resolve(require.resolve('react-native/package.json'), '..'),
);
const rnwPath = fs.realpathSync(
  path.resolve(require.resolve('react-native-windows/package.json'), '..'),
);

const config = getDefaultConfig(__dirname);

module.exports = mergeConfig(config, {
  resolver: {
    extraNodeModules: {
      // Redirect react-native to react-native-windows
      'react-native': rnwPath,
      'react-native-windows': rnwPath,
    },
    // Include the macos platform in addition to the defaults because the fork includes macos, but doesn't declare it
    platforms: ['ios', 'android', 'windows', 'web', 'macos'],
    // Since there are multiple copies of react-native, we need to ensure that metro only sees one of them
    blockList: [
      new RegExp(
        `${(path.resolve(rnPath) + path.sep).replace(/[/\\]/g, '/')}.*`,
      ),

      // This stops "react-native run-windows" from causing the metro server to crash if its already running
      new RegExp(
        `${path.resolve(__dirname, 'windows').replace(/[/\\]/g, '/')}.*`,
      ),
    ],
  },
  transformer: {
    getTransformOptions: async () => ({
      transform: {
        experimentalImportSupport: false,
        inlineRequires: false,
      },
    }),
  },
});
