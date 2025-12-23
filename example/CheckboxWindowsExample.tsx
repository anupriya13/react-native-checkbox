import * as React from 'react';
import {View, Text, Button, StyleSheet} from 'react-native';
// Use relative import for workspace linking
import {
  RNCCheckbox,
  type RNCCheckboxNativeProps,
} from '../src/specs';

// Reusable Card component for examples
function ExampleCard({children}: {children: React.ReactNode}) {
  return <View style={styles.card}>{children}</View>;
}

// Example 1: Basic Checkbox
function BasicCheckboxExample() {
  const [checked, setChecked] = React.useState(false);

  const handleChange = (event: {nativeEvent: {value: boolean}}) => {
    setChecked(event.nativeEvent.value);
  };

  return (
    <ExampleCard>
      <Text style={styles.description}>Basic checkbox with state</Text>
      <View style={styles.checkboxRow}>
        <RNCCheckbox
          value={checked}
          onChange={handleChange}
          style={styles.checkbox}
        />
        <Text style={styles.checkboxLabel}>
          {checked ? 'Checked ✓' : 'Unchecked'}
        </Text>
      </View>
    </ExampleCard>
  );
}

// Example 2: Disabled Checkbox
function DisabledCheckboxExample() {
  return (
    <ExampleCard>
      <Text style={styles.description}>
        Disabled checkboxes - user cannot interact
      </Text>
      <View style={styles.checkboxRow}>
        <RNCCheckbox
          value={true}
          disabled={true}
          style={styles.checkbox}
        />
        <Text style={styles.checkboxLabel}>Checked & Disabled</Text>
      </View>
      <View style={styles.checkboxRow}>
        <RNCCheckbox
          value={false}
          disabled={true}
          style={styles.checkbox}
        />
        <Text style={styles.checkboxLabel}>Unchecked & Disabled</Text>
      </View>
    </ExampleCard>
  );
}

// Example 3: Multiple Checkboxes
function MultipleCheckboxExample() {
  const [options, setOptions] = React.useState({
    option1: false,
    option2: true,
    option3: false,
  });

  const toggleOption = (key: keyof typeof options) => {
    setOptions(prev => ({...prev, [key]: !prev[key]}));
  };

  return (
    <ExampleCard>
      <Text style={styles.description}>Multiple checkboxes in a form</Text>
      <View style={styles.checkboxRow}>
        <RNCCheckbox
          value={options.option1}
          onChange={() => toggleOption('option1')}
          style={styles.checkbox}
        />
        <Text style={styles.checkboxLabel}>Option 1</Text>
      </View>
      <View style={styles.checkboxRow}>
        <RNCCheckbox
          value={options.option2}
          onChange={() => toggleOption('option2')}
          style={styles.checkbox}
        />
        <Text style={styles.checkboxLabel}>Option 2</Text>
      </View>
      <View style={styles.checkboxRow}>
        <RNCCheckbox
          value={options.option3}
          onChange={() => toggleOption('option3')}
          style={styles.checkbox}
        />
        <Text style={styles.checkboxLabel}>Option 3</Text>
      </View>
      <View style={styles.resultBox}>
        <Text style={styles.resultLabel}>Selected:</Text>
        <Text style={styles.resultValue}>
          {Object.entries(options)
            .filter(([_, v]) => v)
            .map(([k]) => k)
            .join(', ') || 'None'}
        </Text>
      </View>
    </ExampleCard>
  );
}

// Example 4: Controlled Toggle
function ControlledToggleExample() {
  const [checked, setChecked] = React.useState(false);

  return (
    <ExampleCard>
      <Text style={styles.description}>
        Controlled checkbox with external toggle button
      </Text>
      <View style={styles.checkboxRow}>
        <RNCCheckbox
          value={checked}
          onChange={(e: {nativeEvent: {value: boolean}}) => setChecked(e.nativeEvent.value)}
          style={styles.checkbox}
        />
        <Text style={styles.checkboxLabel}>
          Value: {checked ? 'true' : 'false'}
        </Text>
      </View>
      <View style={styles.buttonRow}>
        <Button
          title="Toggle"
          onPress={() => setChecked(prev => !prev)}
        />
        <View style={{width: 10}} />
        <Button
          title="Set True"
          onPress={() => setChecked(true)}
        />
        <View style={{width: 10}} />
        <Button
          title="Set False"
          onPress={() => setChecked(false)}
        />
      </View>
    </ExampleCard>
  );
}

// Example 5: Custom Colors
function CustomColorsExample() {
  const [checked, setChecked] = React.useState(true);

  return (
    <ExampleCard>
      <Text style={styles.description}>
        Checkbox with custom colors (tintColor, onCheckColor, onFillColor, onTintColor)
      </Text>
      <View style={styles.checkboxRow}>
        <RNCCheckbox
          value={checked}
          onChange={(e: {nativeEvent: {value: boolean}}) => setChecked(e.nativeEvent.value)}
          tintColor="#888888"
          onCheckColor="#ffffff"
          onFillColor="#0078d4"
          onTintColor="#005a9e"
          style={styles.checkbox}
        />
        <Text style={styles.checkboxLabel}>Blue theme</Text>
      </View>
      <View style={styles.checkboxRow}>
        <RNCCheckbox
          value={checked}
          onChange={(e: {nativeEvent: {value: boolean}}) => setChecked(e.nativeEvent.value)}
          tintColor="#cccccc"
          onCheckColor="#ffffff"
          onFillColor="#107c10"
          onTintColor="#0b5c0b"
          style={styles.checkbox}
        />
        <Text style={styles.checkboxLabel}>Green theme</Text>
      </View>
      <View style={styles.checkboxRow}>
        <RNCCheckbox
          value={checked}
          onChange={(e: {nativeEvent: {value: boolean}}) => setChecked(e.nativeEvent.value)}
          tintColor="#e0e0e0"
          onCheckColor="#000000"
          onFillColor="#ffb900"
          onTintColor="#d39e00"
          style={styles.checkbox}
        />
        <Text style={styles.checkboxLabel}>Yellow theme</Text>
      </View>
      <View style={styles.buttonRow}>
        <Button title="Toggle All" onPress={() => setChecked(prev => !prev)} />
      </View>
    </ExampleCard>
  );
}

const styles = StyleSheet.create({
  card: {
    backgroundColor: '#ffffff',
    borderRadius: 4,
    padding: 16,
    marginBottom: 8,
    borderWidth: 1,
    borderColor: '#d0d0d0',
  },
  description: {
    fontSize: 13,
    color: '#666',
    marginBottom: 12,
  },
  checkboxContainer: {
    justifyContent: 'center',
    alignItems: 'center',
  },
  checkbox: {
    width: 20,
    height: 20,
  },
  checkboxRow: {
    flexDirection: 'row',
    alignItems: 'center',
    marginBottom: 8,
  },
  checkboxLabel: {
    fontSize: 14,
    paddingBottom: 8,
    marginLeft: 8,
    color: '#333',
  },
  resultBox: {
    flexDirection: 'row',
    alignItems: 'center',
    backgroundColor: '#f5f5f5',
    padding: 10,
    borderRadius: 2,
    marginTop: 8,
  },
  resultLabel: {
    fontSize: 13,
    color: '#666',
    marginRight: 8,
  },
  resultValue: {
    fontSize: 13,
    fontWeight: '600',
    color: '#0078d4',
  },
  buttonRow: {
    flexDirection: 'row',
    justifyContent: 'flex-start',
    marginTop: 12,
  },
});

export const examples = [
  {
    title: 'Basic Checkbox',
    render: BasicCheckboxExample,
  },
  {
    title: 'Disabled Checkboxes',
    render: DisabledCheckboxExample,
  },
  {
    title: 'Multiple Checkboxes',
    render: MultipleCheckboxExample,
  },
  {
    title: 'Controlled Toggle',
    render: ControlledToggleExample,
  },
  {
    title: 'Custom Colors',
    render: CustomColorsExample,
  },
];
