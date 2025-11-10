/**
 * @format
 */
import {AppRegistry} from 'react-native';
import App from './App';
// You could use the function component as well
// import App from './AppFunction';
import {name as appName} from './app.json';
console.log('**************************************************************');
console.log('App Name:', appName);
console.log('**************************************************************');

AppRegistry.registerComponent(appName, () => App);
