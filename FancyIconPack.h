#pragma once

#include <JuceHeader.h>

/**
 * FancyIconPack - An advanced icon drawing utility for modern audio plugin UIs
 * Provides a comprehensive collection of scalable vector icons specifically
 * designed for audio synthesis, effects, and music production interfaces.
 *
 * All icons are drawn as resolution-independent vector graphics with:
 * - Consistent visual style and proportions
 * - Smooth curves and professional appearance
 * - Proper scaling at any size
 * - State-aware color handling
 * - Audio-specific iconography
 */
class FancyIconPack
{
public:
    FancyIconPack() = delete; // Static utility class

    // ============================================================================
    // HELPER METHODS AND UTILITIES
    // ============================================================================

    /**
     * Get consistent icon color based on component state with enhanced styling
     * @param isEnabled Whether the component is enabled
     * @param isHighlighted Whether the component is highlighted/hovered
     * @param isPressed Whether the component is currently pressed
     * @param baseColor Base color when normal
     * @param alpha Override alpha value (default: use state-based alpha)
     * @return Appropriate color for the current state
     */
    static juce::Colour getStateColor(bool isEnabled, bool isHighlighted, bool isPressed = false,
                                     juce::Colour baseColor = juce::Colour(0xff888888),
                                     float alpha = -1.0f)
    {
        if (!isEnabled)
            return baseColor.withAlpha(alpha >= 0.0f ? alpha : 0.25f);
        else if (isPressed)
            return baseColor.brighter(0.1f).withAlpha(alpha >= 0.0f ? alpha : 0.9f);
        else if (isHighlighted)
            return baseColor.brighter(0.4f).withAlpha(alpha >= 0.0f ? alpha : 1.0f);
        else
            return baseColor.withAlpha(alpha >= 0.0f ? alpha : 0.8f);
    }

    /**
     * Create a standardized stroke style for consistent icon appearance
     * @param strokeWidth Line thickness
     * @param endCapStyle End cap style (default: rounded)
     * @param joinStyle Join style (default: curved)
     * @return Configured PathStrokeType
     */
    static juce::PathStrokeType createStroke(float strokeWidth,
                                           juce::PathStrokeType::JointStyle jointStyle = juce::PathStrokeType::curved,
                                           juce::PathStrokeType::EndCapStyle endCapStyle = juce::PathStrokeType::rounded)
    {
        return juce::PathStrokeType(strokeWidth, jointStyle, endCapStyle);
    }

    /**
     * Apply consistent padding/margin to icon bounds for optical alignment
     * @param bounds Original bounds
     * @param paddingRatio Padding as ratio of smallest dimension (default: 0.1)
     * @return Reduced bounds with padding applied
     */
    static juce::Rectangle<float> applyPadding(juce::Rectangle<float> bounds, float paddingRatio = 0.1f)
    {
        auto padding = juce::jmin(bounds.getWidth(), bounds.getHeight()) * paddingRatio;
        return bounds.reduced(padding);
    }

    /**
     * Get standardized stroke width based on icon size for optimal appearance
     * @param bounds Icon bounds
     * @param baseStrokeRatio Stroke width as ratio of smallest dimension (default: 0.08)
     * @param minStroke Minimum stroke width (default: 1.0f)
     * @param maxStroke Maximum stroke width (default: 4.0f)
     * @return Optimal stroke width
     */
    static float getOptimalStrokeWidth(juce::Rectangle<float> bounds,
                                     float baseStrokeRatio = 0.08f,
                                     float minStroke = 1.0f,
                                     float maxStroke = 4.0f)
    {
        auto size = juce::jmin(bounds.getWidth(), bounds.getHeight());
		if(size <= 32.0f)
			return 1.25f;

		if(size <= 64.0f)
			return 2.25f;

		return 3.25f;
    }

    /**
     * Create a rounded rectangle path with consistent corner radius
     * @param bounds Rectangle bounds
     * @param cornerRatio Corner radius as ratio of smallest dimension (default: 0.1)
     * @return Path containing rounded rectangle
     */
    static juce::Path createRoundedRectPath(juce::Rectangle<float> bounds, float cornerRatio = 0.1f)
    {
        juce::Path path;
        auto cornerRadius = juce::jmin(bounds.getWidth(), bounds.getHeight()) * cornerRatio;
        path.addRoundedRectangle(bounds, cornerRadius);
        return path;
    }

    /**
     * Create a circular path centered in bounds
     * @param bounds Bounding rectangle
     * @param radiusRatio Radius as ratio of smallest dimension (default: 0.4)
     * @return Path containing circle
     */
    static juce::Path createCirclePath(juce::Rectangle<float> bounds, float radiusRatio = 0.4f)
    {
        juce::Path path;
        auto centre = bounds.getCentre();
        auto radius = juce::jmin(bounds.getWidth(), bounds.getHeight()) * radiusRatio;
        path.addEllipse(centre.x - radius, centre.y - radius, radius * 2, radius * 2);
        return path;
    }

    /**
     * Create standardized drop shadow effect for icons
     * @param g Graphics context
     * @param path Icon path to shadow
     * @param shadowColor Shadow color (default: semi-transparent black)
     * @param offsetX Horizontal shadow offset
     * @param offsetY Vertical shadow offset
     * @param blurRadius Shadow blur radius
     */
    static void drawDropShadow(juce::Graphics& g, const juce::Path& path,
                              juce::Colour shadowColor = juce::Colour(0x40000000),
                              float offsetX = 1.0f, float offsetY = 1.0f, float blurRadius = 2.0f)
    {
        // Simple shadow implementation - can be enhanced with actual blur later
        g.setColour(shadowColor);
        auto shadowPath = path;
        shadowPath.applyTransform(juce::AffineTransform::translation(offsetX, offsetY));
        g.fillPath(shadowPath);
    }

    /**
     * Apply gradient fill to a path for enhanced visual appeal
     * @param g Graphics context
     * @param path Path to fill
     * @param bounds Gradient bounds
     * @param topColor Top/start color
     * @param bottomColor Bottom/end color
     * @param isVertical Whether gradient is vertical (default: true)
     */
    static void fillWithGradient(juce::Graphics& g, const juce::Path& path, juce::Rectangle<float> bounds,
                                juce::Colour topColor, juce::Colour bottomColor, bool isVertical = true)
    {
        juce::ColourGradient gradient;
        if (isVertical)
            gradient = juce::ColourGradient(topColor, bounds.getTopLeft(), bottomColor, bounds.getBottomLeft(), false);
        else
            gradient = juce::ColourGradient(topColor, bounds.getTopLeft(), bottomColor, bounds.getTopRight(), false);

        g.setGradientFill(gradient);
        g.fillPath(path);
    }

    // ============================================================================
    // GENERAL UI / WORKFLOW ICONS
    // ============================================================================

    // Basic UI Operations
    static void drawCopy(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color);
    static void drawEdit(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color);
    static void drawSave(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color);
    static void drawLoad(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color);
    static void drawNewPreset(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color);
    static void drawRename(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color);
    static void drawDelete(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color);
    static void drawPaste(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color);
    static void drawDuplicate(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color);
    static void drawUndo(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color);
    static void drawRedo(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color);

    // Interface Controls
    static void drawSettings(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color);
    static void drawBurgerMenu(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color);
    static void drawDropdown(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color);
    static void drawSearch(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color);
    static void drawClose(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color);
    static void drawExpand(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color);
    static void drawCollapse(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color);
    static void drawInfo(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color);
    static void drawHelp(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color);
    static void drawWarning(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color);
    static void drawError(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color);
    static void drawCheck(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color);
    static void drawPlus(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color);
    static void drawMinus(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color);

    // Navigation Arrows
    static void drawArrowUp(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color);
    static void drawArrowDown(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color);
    static void drawArrowLeft(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color);
    static void drawArrowRight(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color);

    // Layout and View Controls
    static void drawScrollHorizontal(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color);
    static void drawScrollVertical(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color);
    static void drawGrid(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color);
    static void drawList(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color);
    static void drawLock(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color);
    static void drawUnlock(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color);
    static void drawBypass(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color);
    static void drawPower(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color);
    static void drawRefresh(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color);

    // File Operations
    static void drawDownload(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color);
    static void drawUpload(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color);
    static void drawExternalLink(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color);
    static void drawPin(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color);
    static void drawDragHandle(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color);

    // Zoom and View
    static void drawZoomIn(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color);
    static void drawZoomOut(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color);
    static void drawFullscreen(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color);
    static void drawExitFullscreen(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color);
    static void drawTab(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color);

    // Control Types
    static void drawSliderHorizontal(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color);
    static void drawSliderVertical(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color);
    static void drawKnob(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color);
    static void drawSwitch(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color);
    static void drawToggleOn(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color);
    static void drawToggleOff(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color);
    static void drawCheckbox(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color);
    static void drawRadioOn(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color);
    static void drawRadioOff(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color);
    static void drawContextMenu(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color);

    // ============================================================================
    // AUDIO-SPECIFIC ICONS
    // ============================================================================

    // Volume and Gain
    static void drawVolume(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color);
    static void drawGain(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color);
    static void drawPan(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color);
    static void drawMute(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color);
    static void drawSolo(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color);

    // Metering and Analysis
    static void drawMeter(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color);
    static void drawPeak(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color);
    static void drawClip(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color);
    static void drawWaveform(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color);
    static void drawSpectrum(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color);

    // Waveform Types
    static void drawSineWave(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color);
    static void drawSquareWave(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color);
    static void drawTriangleWave(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color);
    static void drawSawWave(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color);
    static void drawNoise(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color);

    // Phase and Signal Processing
    static void drawPhase(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color);
    static void drawInvertPhase(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color);
    static void drawFrequency(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color);
    static void drawResonance(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color);
    static void drawBandwidth(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color);

    // Filters and EQ
    static void drawEQ(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color);
    static void drawFilter(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color);
    static void drawLowpass(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color);
    static void drawHighpass(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color);
    static void drawBandpass(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color);
    static void drawNotch(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color);
    static void drawCombFilter(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color);
    static void drawFormant(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color);

    // Envelopes and Modulation
    static void drawEnvelope(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color);
    static void drawADSR(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color);
    static void drawAR(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color);
    static void drawHold(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color);
    static void drawLFO(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color);
    static void drawSync(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color);

    // Signal Flow and Routing
    static void drawInput(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color);
    static void drawOutput(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color);
    static void drawMix(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color);
    static void drawDryWet(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color);
    static void drawFeedback(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color);
    static void drawRouting(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color);
    static void drawSignalPath(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color);
    static void drawPatchCable(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color);
    static void drawCrossfade(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color);
    static void drawSidechain(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color);

    // Audio Effects
    static void drawCompressor(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color);
    static void drawLimiter(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color);
    static void drawExpander(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color);
    static void drawSaturator(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color);
    static void drawDistortion(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color);
    static void drawBitcrusher(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color);
    static void drawWaveshaper(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color);
    static void drawReverb(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color);
    static void drawDelay(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color);
    static void drawPingPongDelay(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color);
    static void drawChorus(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color);
    static void drawFlanger(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color);
    static void drawPhaser(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color);
    static void drawGranular(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color);
    static void drawFreeze(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color);

    // Stereo and Spatial
    static void drawStereo(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color);
    static void drawMono(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color);
    static void drawWidth(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color);
    static void drawBalance(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color);

    // ============================================================================
    // MIDI AND MODULATION ICONS
    // ============================================================================

    // MIDI Core
    static void drawMidi(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color);
    static void drawMidiIn(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color);
    static void drawMidiOut(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color);
    static void drawMidiChannel(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color);
    static void drawMidiCC(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color);
    static void drawMidiLearn(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color);

    // Musical Elements
    static void drawNote(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color);
    static void drawVelocity(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color);
    static void drawAftertouch(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color);
    static void drawPolyAftertouch(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color);
    static void drawModWheel(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color);
    static void drawPitchBend(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color);

    // Modulation Sources
    static void drawKeytrack(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color);
    static void drawEnvelopeFollow(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color);
    static void drawMacro(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color);
    static void drawMacroAssign(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color);

    // Modulation Matrix
    static void drawModMatrix(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color);
    static void drawModSource(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color);
    static void drawModDestination(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color);
    static void drawModDepth(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color);
    static void drawModAmount(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color);
    static void drawModCurve(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color);
    static void drawModShape(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color);
    static void drawModRouting(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color);
    static void drawModSignal(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color);

    // Automation and CV
    static void drawAutomation(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color);
    static void drawAutomationLane(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color);
    static void drawAutomationCurve(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color);
    static void drawCV(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color);
    static void drawCVIn(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color);
    static void drawCVOut(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color);

    // ============================================================================
    // SYNTH AND FX COMPONENTS
    // ============================================================================

    // Oscillators
    static void drawOsc(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color);
    static void drawOsc1(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color);
    static void drawOsc2(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color);
    static void drawOsc3(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color);
    static void drawSubOsc(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color);
    static void drawNoiseOsc(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color);
    static void drawUnison(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color);
    static void drawVoices(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color);
    static void drawPolyphony(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color);

    // Filter Components
    static void drawFilter1(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color);
    static void drawFilter2(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color);

    // Amplifier and VCA
    static void drawAmp(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color);
    static void drawVCA(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color);

    // Envelopes and LFOs
    static void drawEnv1(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color);
    static void drawEnv2(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color);
    static void drawLFO1(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color);
    static void drawLFO2(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color);
    static void drawLFO3(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color);

    // Effects Chain
    static void drawFX(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color);
    static void drawFXChain(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color);
    static void drawFXSlot(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color);

    // Specialized Effects
    static void drawTransientShaper(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color);
    static void drawPitchShifter(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color);
    static void drawLofi(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color);
    static void drawStereoImager(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color);
    static void drawUtility(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color);
    static void drawAnalyzer(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color);
    static void drawTuner(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color);

    // ============================================================================
    // ADVANCED UI / WORKFLOW FEATURES
    // ============================================================================

    // Parameter Control
    static void drawGroupParameters(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color);
    static void drawLinkControls(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color);
    static void drawAssignModulator(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color);
    static void drawLearnMode(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color);
    static void drawVisualModulation(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color);
    static void drawAnimatedKnob(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color);

    // Display Components
    static void drawSpectrumDisplay(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color);
    static void drawWaveformDisplay(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color);
    static void drawEnvelopeDisplay(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color);

    // UI Layout
    static void drawGridSnapping(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color);
    static void drawResizablePanel(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color);
    static void drawFloatingPanel(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color);
    static void drawOverlay(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color);
    static void drawTooltip(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color);
    static void drawContextPopup(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color);

    // Theme and Appearance
    static void drawThemeLight(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color);
    static void drawThemeDark(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color);
    static void drawColorPicker(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color);

    // Preset Management
    static void drawPresetBrowser(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color);
    static void drawPresetFavorite(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color);
    static void drawPresetRandom(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color);
    static void drawInitPreset(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color);
    static void drawSavePreset(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color);
    static void drawLockParameter(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color);
    static void drawParameterAutomation(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color);

    // Interaction Features
    static void drawDragToAssign(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color);
    static void drawDragToConnect(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color);
};
