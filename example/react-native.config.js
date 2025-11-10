'use strict';

const path = require('path');

const windowsSwitch = '--use-react-native-windows';

if (process.argv.includes(windowsSwitch)) {
  // Remove the flag from args so CLI doesn’t break
  process.argv = process.argv.filter((arg) => arg !== windowsSwitch);
  // Tell Metro to use Windows-specific config
  process.argv.push('--config=metro.config.windows.js');
}

module.exports = {
  // Always define reactNativePath to avoid CLI resolution issues
  reactNativePath: path.resolve(__dirname, '../node_modules/react-native'),

  // Also tell the CLI where the Windows implementation lives
  dependencies: {
    'react-native-windows': {
      root: path.resolve(__dirname, '../node_modules/react-native-windows'),
    },
  },
};
