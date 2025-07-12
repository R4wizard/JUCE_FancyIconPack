# FancyIconPack

A comprehensive, modern icon library specifically designed for professional audio plugin UIs. FancyIconPack provides scalable vector graphics with consistent styling, perfect for synthesizers, effects, and music production software.

## Overview

FancyIconPack is a static utility class that renders resolution-independent vector icons optimized for audio plugin interfaces. All icons are drawn programmatically using JUCE's graphics system, ensuring perfect scaling at any size and consistent visual appearance across different platforms.

## Key Features

- **Resolution Independent**: All icons are vector-based and scale perfectly at any size
- **Audio-Specific**: Comprehensive collection tailored for music production interfaces
- **Consistent Styling**: Unified visual language with smart stroke width scaling
- **State-Aware**: Built-in color management for enabled/disabled/highlighted states
- **Performance Optimized**: Efficient rendering with minimal memory footprint
- **Professional Appearance**: Smooth curves, proper optical alignment, and modern design

## Icon Categories

### 🎛️ General UI & Workflow (120+ icons)
Core interface elements and common workflow operations:
- **Basic Operations**: Copy, Edit, Save, Load, Delete, Undo, Redo
- **Interface Controls**: Settings, Menus, Dropdowns, Search, Close, Expand
- **Navigation**: Arrow directions, scrolling, grid/list views
- **Layout Controls**: Lock/Unlock, Bypass, Power, Refresh
- **File Operations**: Download, Upload, External links, Drag handles
- **Control Types**: Sliders, Knobs, Switches, Toggles, Checkboxes

### 🎵 Audio-Specific Icons (100+ icons)
Professional audio processing and synthesis elements:
- **Volume & Gain**: Volume, Gain, Pan, Mute, Solo controls
- **Metering**: Level meters, Peak indicators, Clipping warnings
- **Waveforms**: Sine, Square, Triangle, Saw, Noise generators
- **Signal Processing**: Phase, Frequency, Resonance, Bandwidth
- **Filters & EQ**: Various filter types, EQ curves, formant filters
- **Effects**: Compression, Distortion, Reverb, Delay, Modulation
- **Stereo & Spatial**: Stereo imaging, Width, Balance controls

### 🎹 MIDI & Modulation (60+ icons)
MIDI functionality and modulation systems:
- **MIDI Core**: MIDI I/O, Channels, CC, Learn functions
- **Musical Elements**: Notes, Velocity, Aftertouch, Pitch bend
- **Modulation Sources**: Key tracking, Envelope followers, Macros
- **Modulation Matrix**: Sources, Destinations, Routing, Curves
- **Automation**: CV, Automation lanes and curves

### 🎛️ Synthesizer Components (40+ icons)
Dedicated synthesizer building blocks:
- **Oscillators**: OSC 1-3, Sub oscillators, Noise, Unison
- **Filters**: Filter 1-2 with various response types
- **Amplifiers**: Amp, VCA components
- **Envelopes**: ENV 1-2, ADSR, AR envelopes
- **LFOs**: LFO 1-3 with sync options
- **Effects Chain**: FX slots and routing

### ⚡ Advanced Features (30+ icons)
Modern plugin workflow enhancements:
- **Parameter Control**: Grouping, Linking, Learn mode
- **Visual Elements**: Spectrum displays, Waveform viewers
- **UI Layout**: Grid snapping, Resizable panels, Overlays
- **Preset Management**: Browser, Favorites, Randomization
- **Themes**: Light/Dark mode, Color picker

## Usage Examples

### Basic Icon Drawing
```cpp
// Draw a simple volume icon
auto bounds = getLocalBounds().toFloat();
auto color = getLookAndFeel().findColour(Label::textColourId);
FancyIconPack::drawVolume(g, bounds, color);
```

### State-Aware Coloring
```cpp
// Get appropriate color based on component state
auto color = FancyIconPack::getStateColor(
    isEnabled(),           // Component enabled state
    isMouseOver(),         // Hover state
    isMouseButtonDown(),   // Press state
    Colours::lightblue     // Base color
);
FancyIconPack::drawMute(g, bounds, color);
```

### Consistent Styling
```cpp
// Apply standard padding and stroke width
auto paddedBounds = FancyIconPack::applyPadding(bounds, 0.15f);
auto strokeWidth = FancyIconPack::getOptimalStrokeWidth(bounds);

// Icons automatically use these standards internally
FancyIconPack::drawFilter(g, paddedBounds, color);
```

### Button Integration
```cpp
class IconButton : public Button
{
    void paintButton(Graphics& g, bool shouldDrawButtonAsHighlighted, 
                    bool shouldDrawButtonAsDown) override
    {
        auto color = FancyIconPack::getStateColor(
            isEnabled(), shouldDrawButtonAsHighlighted, shouldDrawButtonAsDown);
        
        FancyIconPack::drawSettings(g, getLocalBounds().toFloat(), color);
    }
};
```

## Helper Functions

The icon pack includes several utility functions for consistent styling:

### Color Management
- `getStateColor()` - Smart color selection based on component state
- Automatic alpha blending for disabled states
- Brightness adjustment for hover/press states

### Geometric Helpers
- `applyPadding()` - Consistent icon padding/margins
- `getOptimalStrokeWidth()` - Size-appropriate line thickness
- `createRoundedRectPath()` - Standardized rounded rectangles
- `createCirclePath()` - Perfect circles with proper sizing

### Visual Effects
- `drawDropShadow()` - Subtle depth enhancement
- `fillWithGradient()` - Gradient fills for visual appeal
- `createStroke()` - Consistent stroke styling

## File Organization

The implementation is split across multiple files for maintainability:

- `FancyIconPack.h` - Main header with all declarations
- `FancyIconPack_GeneralUI.cpp` - Basic UI and workflow icons
- `FancyIconPack_Audio_Part1.cpp` - Core audio processing icons
- `FancyIconPack_Audio_Part2.cpp` - Effects and signal processing
- `FancyIconPack_MIDI_Part1.cpp` - MIDI and modulation icons
- `FancyIconPack_Synth_Part1.cpp` - Synthesizer components
- `FancyIconPack_Advanced_Part1.cpp` - Advanced UI features

## Design Principles

### Visual Consistency
- Unified stroke weights that scale with icon size
- Consistent corner radii and geometric proportions
- Optical alignment through intelligent padding

### Audio-First Design
- Icons designed specifically for music production workflows
- Industry-standard symbolism and conventions
- Clear differentiation between similar concepts

### Scalability
- Vector-based rendering at all sizes
- Stroke weights optimized for small (16px) to large (128px+) sizes
- No bitmap dependencies

### Performance
- Efficient path-based rendering
- Minimal memory allocation during drawing
- Optimized for real-time UI updates

## Integration Notes

### JUCE Compatibility
- Requires JUCE 6.0 or later
- Uses standard JUCE Graphics and Path classes
- Compatible with all JUCE-supported platforms

### Color Schemes
- Works with any LookAndFeel color scheme
- Supports both light and dark themes
- Customizable through color parameters

### Accessibility
- High contrast support through state-aware coloring
- Consistent sizing for touch interfaces
- Clear visual hierarchy

## License

MIT, please see [LICENSE](LICENSE).

## Contributing

When adding new icons:
1. Follow the established naming convention
2. Use the helper functions for consistent styling
3. Test at multiple sizes (16px to 128px)
4. Ensure proper optical alignment
5. Add appropriate documentation

---

*FancyIconPack v1.0 - Professional Icons for Audio Plugin Development*
