#include "FancyIconPack.h"

// ============================================================================
// AUDIO-SPECIFIC ICONS IMPLEMENTATION - PART 2
// ============================================================================

// Filters and EQ (Part 2)
// ============================================================================

void FancyIconPack::drawNotch(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color)
{
    auto iconBounds = bounds;
    auto stroke = getOptimalStrokeWidth(iconBounds);

    // Frequency response curve with deep notch
    juce::Path responseCurve;
    auto curveY = iconBounds.getCentreY();

    responseCurve.startNewSubPath(iconBounds.getX(), curveY);

    auto notchX = iconBounds.getCentreX();
    auto notchDepth = iconBounds.getHeight() * 0.35f;

    // Create curve with sharp notch in center
    for (int i = 0; i <= 40; ++i)
    {
        auto x = iconBounds.getX() + (i / 40.0f) * iconBounds.getWidth();
        auto distFromNotch = std::abs(x - notchX) / (iconBounds.getWidth() * 0.1f);
        auto y = curveY;

        // Sharp dip at notch frequency
        if (distFromNotch < 1.0f)
        {
            auto notchFactor = 1.0f - (1.0f - distFromNotch * distFromNotch);
            y += notchDepth * notchFactor;
        }

        responseCurve.lineTo(x, y);
    }

    g.setColour(color);
    g.strokePath(responseCurve, createStroke(stroke * 1.2f));

    // Frequency axis
    g.setColour(color.withAlpha(0.5f));
    g.drawLine(iconBounds.getX(), iconBounds.getBottom() - stroke,
               iconBounds.getRight(), iconBounds.getBottom() - stroke, stroke * 0.7f);

    // Notch indicator arrow
    juce::Path notchArrow;
    notchArrow.startNewSubPath(notchX, iconBounds.getY() + stroke);
    notchArrow.lineTo(notchX, curveY - stroke);
    notchArrow.lineTo(notchX - stroke * 1.5f, curveY - stroke * 3.0f);
    notchArrow.lineTo(notchX + stroke * 1.5f, curveY - stroke * 3.0f);
    notchArrow.closeSubPath();

    g.setColour(color.withAlpha(0.7f));
    g.fillPath(notchArrow);
}

void FancyIconPack::drawCombFilter(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color)
{
    auto iconBounds = bounds;
    auto stroke = getOptimalStrokeWidth(iconBounds);

    // Comb filter frequency response (multiple peaks and nulls)
    juce::Path combResponse;
    auto baseY = iconBounds.getCentreY();
    auto amplitude = iconBounds.getHeight() * 0.3f;

    combResponse.startNewSubPath(iconBounds.getX(), baseY);

    // Create comb pattern with multiple peaks
    auto numTeeth = 6;
    for (int i = 0; i <= 60; ++i)
    {
        auto x = iconBounds.getX() + (i / 60.0f) * iconBounds.getWidth();
        auto phase = (i / 60.0f) * numTeeth * 2.0f * juce::MathConstants<float>::pi;
        auto y = baseY + std::cos(phase) * amplitude * 0.8f;
        combResponse.lineTo(x, y);
    }

    g.setColour(color);
    g.strokePath(combResponse, createStroke(stroke));

    // Delay line representation
    auto delayRect = juce::Rectangle<float>(iconBounds.getX() + iconBounds.getWidth() * 0.1f,
                                          iconBounds.getY() + iconBounds.getHeight() * 0.7f,
                                          iconBounds.getWidth() * 0.8f,
                                          iconBounds.getHeight() * 0.15f);

    g.setColour(color.withAlpha(0.3f));
    g.fillRoundedRectangle(delayRect, stroke);
    g.setColour(color);
    g.drawRoundedRectangle(delayRect, stroke, stroke * 0.7f);

    // Delay taps
    for (int i = 1; i < 4; ++i)
    {
        auto tapX = delayRect.getX() + (i / 4.0f) * delayRect.getWidth();
        g.setColour(color.withAlpha(0.6f));
        g.drawLine(tapX, delayRect.getY(), tapX, delayRect.getBottom(), stroke * 0.7f);

        // Small circles at tap points
        auto tapSize = stroke * 1.5f;
        g.fillEllipse(tapX - tapSize * 0.5f, delayRect.getCentreY() - tapSize * 0.5f,
                      tapSize, tapSize);
    }

    // "COMB" label
    g.setColour(color.withAlpha(0.7f));
    g.setFont(juce::Font(iconBounds.getHeight() * 0.1f, juce::Font::bold));
    g.drawText("COMB", delayRect, juce::Justification::centred);
}

void FancyIconPack::drawFormant(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color)
{
    auto iconBounds = bounds;
    auto stroke = getOptimalStrokeWidth(iconBounds);

    // Vocal tract representation
    juce::Path vocalTract;
    auto tractWidth = iconBounds.getWidth() * 0.6f;
    auto tractHeight = iconBounds.getHeight() * 0.4f;
    auto tractX = iconBounds.getX() + (iconBounds.getWidth() - tractWidth) * 0.5f;
    auto tractY = iconBounds.getY() + iconBounds.getHeight() * 0.1f;

    // Create vocal tract shape (mouth cavity)
    vocalTract.startNewSubPath(tractX, tractY + tractHeight);
    vocalTract.quadraticTo(tractX + tractWidth * 0.3f, tractY,
                          tractX + tractWidth, tractY + tractHeight * 0.3f);
    vocalTract.quadraticTo(tractX + tractWidth * 0.7f, tractY + tractHeight,
                          tractX, tractY + tractHeight);

    g.setColour(color.withAlpha(0.3f));
    g.fillPath(vocalTract);
    g.setColour(color);
    g.strokePath(vocalTract, createStroke(stroke));

    // Formant frequency response peaks
    juce::Path formantResponse;
    auto responseY = iconBounds.getY() + iconBounds.getHeight() * 0.6f;
    auto responseHeight = iconBounds.getHeight() * 0.3f;

    formantResponse.startNewSubPath(iconBounds.getX(), responseY + responseHeight * 0.5f);

    // Create multiple formant peaks (F1, F2, F3)
    float formantFreqs[] = {0.2f, 0.5f, 0.8f}; // Relative positions
    float formantAmps[] = {0.8f, 0.6f, 0.4f};  // Relative amplitudes

    for (int i = 0; i <= 80; ++i)
    {
        auto x = iconBounds.getX() + (i / 80.0f) * iconBounds.getWidth();
        auto freq = i / 80.0f;
        auto amplitude = 0.1f; // Base level

        // Add formant peaks
        for (int f = 0; f < 3; ++f)
        {
            auto dist = std::abs(freq - formantFreqs[f]);
            auto peak = formantAmps[f] * std::exp(-dist * dist * 50.0f);
            amplitude += peak;
        }

        auto y = responseY + responseHeight * (1.0f - amplitude);
        formantResponse.lineTo(x, y);
    }

    g.setColour(color);
    g.strokePath(formantResponse, createStroke(stroke));

    // Formant labels
    g.setColour(color.withAlpha(0.7f));
    g.setFont(juce::Font(iconBounds.getHeight() * 0.08f, juce::Font::bold));

    for (int f = 0; f < 3; ++f)
    {
        auto labelX = iconBounds.getX() + formantFreqs[f] * iconBounds.getWidth();
        auto labelY = responseY + responseHeight * (1.0f - formantAmps[f]) - stroke * 2.0f;
        auto labelText = juce::String("F") + juce::String(f + 1);

        g.drawText(labelText,
                  juce::Rectangle<float>(labelX - stroke * 3.0f, labelY - stroke * 2.0f,
                                       stroke * 6.0f, stroke * 4.0f),
                  juce::Justification::centred);
    }
}

// Envelopes and Modulation
// ============================================================================

void FancyIconPack::drawEnvelope(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color)
{
    auto iconBounds = bounds;
    auto stroke = getOptimalStrokeWidth(iconBounds);

    // Generic envelope shape
    juce::Path envelope;
    auto baseY = iconBounds.getBottom() - iconBounds.getHeight() * 0.1f;
    auto startX = iconBounds.getX();
    auto width = iconBounds.getWidth();
    auto height = iconBounds.getHeight() * 0.8f;

    envelope.startNewSubPath(startX, baseY);

    // Attack
    envelope.lineTo(startX + width * 0.2f, baseY - height * 0.9f);
    // Decay
    envelope.lineTo(startX + width * 0.4f, baseY - height * 0.6f);
    // Sustain
    envelope.lineTo(startX + width * 0.7f, baseY - height * 0.6f);
    // Release
    envelope.lineTo(startX + width, baseY);

    g.setColour(color);
    g.strokePath(envelope, createStroke(stroke));

    // Base line
    g.setColour(color.withAlpha(0.4f));
    g.drawLine(startX, baseY, startX + width, baseY, stroke * 0.6f);
}

void FancyIconPack::drawADSR(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color)
{
    auto iconBounds = bounds;
    auto stroke = getOptimalStrokeWidth(iconBounds);

    // ADSR envelope with labeled segments
    juce::Path envelope;
    auto baseY = iconBounds.getBottom() - iconBounds.getHeight() * 0.15f;
    auto startX = iconBounds.getX();
    auto width = iconBounds.getWidth();
    auto height = iconBounds.getHeight() * 0.7f;

    envelope.startNewSubPath(startX, baseY);

    // Attack
    auto attackX = startX + width * 0.25f;
    envelope.lineTo(attackX, baseY - height);

    // Decay
    auto decayX = startX + width * 0.45f;
    auto sustainLevel = height * 0.65f;
    envelope.lineTo(decayX, baseY - sustainLevel);

    // Sustain
    auto sustainX = startX + width * 0.7f;
    envelope.lineTo(sustainX, baseY - sustainLevel);

    // Release
    envelope.lineTo(startX + width, baseY);

    g.setColour(color);
    g.strokePath(envelope, createStroke(stroke));

    // Base line
    g.setColour(color.withAlpha(0.4f));
    g.drawLine(startX, baseY, startX + width, baseY, stroke * 0.6f);

    // Stage labels (small dots at segment boundaries)
    g.setColour(color.withAlpha(0.8f));
    auto dotRadius = stroke * 0.8f;

    g.fillEllipse(attackX - dotRadius, baseY - height - dotRadius, dotRadius * 2, dotRadius * 2);
    g.fillEllipse(decayX - dotRadius, baseY - sustainLevel - dotRadius, dotRadius * 2, dotRadius * 2);
    g.fillEllipse(sustainX - dotRadius, baseY - sustainLevel - dotRadius, dotRadius * 2, dotRadius * 2);
}

void FancyIconPack::drawAR(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color)
{
    auto iconBounds = bounds;
    auto stroke = getOptimalStrokeWidth(iconBounds);

    // AR envelope curve (Attack-Release, no Decay/Sustain)
    juce::Path envelope;
    auto baseY = iconBounds.getBottom() - stroke;
    auto startX = iconBounds.getX();
    auto attackX = iconBounds.getX() + iconBounds.getWidth() * 0.3f;
    auto endX = iconBounds.getRight();
    auto peakY = iconBounds.getY() + iconBounds.getHeight() * 0.2f;

    // Start at zero
    envelope.startNewSubPath(startX, baseY);

    // Attack phase (linear rise)
    envelope.lineTo(attackX, peakY);

    // Release phase (exponential decay)
    auto releasePoints = 8;
    for (int i = 1; i <= releasePoints; ++i)
    {
        auto ratio = i / static_cast<float>(releasePoints);
        auto x = attackX + (endX - attackX) * ratio;
        auto decay = std::exp(-ratio * 3.0f); // Exponential decay
        auto y = peakY + (baseY - peakY) * (1.0f - decay);
        envelope.lineTo(x, y);
    }

    g.setColour(color);
    g.strokePath(envelope, createStroke(stroke));

    // Phase markers
    auto dotRadius = stroke * 1.5f;
    g.fillEllipse(startX - dotRadius, baseY - dotRadius, dotRadius * 2, dotRadius * 2);
    g.fillEllipse(attackX - dotRadius, peakY - dotRadius, dotRadius * 2, dotRadius * 2);

    // Labels
    g.setFont(juce::Font(iconBounds.getHeight() * 0.12f));
    g.drawText("A", juce::Rectangle<float>(startX, baseY + stroke * 2, attackX - startX, iconBounds.getHeight() * 0.15f),
               juce::Justification::centred);
    g.drawText("R", juce::Rectangle<float>(attackX, baseY + stroke * 2, endX - attackX, iconBounds.getHeight() * 0.15f),
               juce::Justification::centred);
}

void FancyIconPack::drawHold(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color)
{
    auto iconBounds = bounds;
    auto stroke = getOptimalStrokeWidth(iconBounds);

    // Hold/Pause symbol - two vertical bars
    auto barWidth = iconBounds.getWidth() * 0.15f;
    auto barHeight = iconBounds.getHeight() * 0.6f;
    auto spacing = iconBounds.getWidth() * 0.2f;
    auto centerX = iconBounds.getCentreX();
    auto centerY = iconBounds.getCentreY();

    // Left bar
    auto leftBar = juce::Rectangle<float>(centerX - spacing * 0.5f - barWidth,
                                         centerY - barHeight * 0.5f,
                                         barWidth, barHeight);

    // Right bar
    auto rightBar = juce::Rectangle<float>(centerX + spacing * 0.5f,
                                          centerY - barHeight * 0.5f,
                                          barWidth, barHeight);

    g.setColour(color);
    g.fillRoundedRectangle(leftBar, 2.0f);
    g.fillRoundedRectangle(rightBar, 2.0f);

    // Optional: Small "HOLD" label below
    auto labelArea = juce::Rectangle<float>(iconBounds.getX(), iconBounds.getBottom() - iconBounds.getHeight() * 0.2f,
                                          iconBounds.getWidth(), iconBounds.getHeight() * 0.15f);
    g.setFont(juce::Font(labelArea.getHeight() * 0.8f, juce::Font::bold));
    g.drawText("HOLD", labelArea, juce::Justification::centred);
}

void FancyIconPack::drawLFO(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color)
{
    auto iconBounds = bounds;
    auto stroke = getOptimalStrokeWidth(iconBounds);

    // LFO - slow sine wave with rate indication
    juce::Path lfoWave;
    auto waveY = iconBounds.getCentreY();
    auto amplitude = iconBounds.getHeight() * 0.3f;
    auto points = 20;

    lfoWave.startNewSubPath(iconBounds.getX(), waveY);

    for (int i = 1; i <= points; ++i)
    {
        auto x = iconBounds.getX() + (i / static_cast<float>(points)) * iconBounds.getWidth();
        auto phase = (i / static_cast<float>(points)) * juce::MathConstants<float>::twoPi * 1.0f; // One full cycle
        auto amp = std::sin(phase) * amplitude;
        lfoWave.lineTo(x, waveY + amp);
    }

    g.setColour(color);
    g.strokePath(lfoWave, createStroke(stroke));

    // Center line
    g.setColour(color.withAlpha(0.3f));
    g.drawLine(iconBounds.getX(), waveY, iconBounds.getRight(), waveY, stroke * 0.5f);

    // Rate indication (arrows showing slow modulation)
    auto arrowY = iconBounds.getY() + iconBounds.getHeight() * 0.8f;
    auto arrowSpacing = iconBounds.getWidth() * 0.3f;

    g.setColour(color.withAlpha(0.7f));
    for (int i = 0; i < 3; ++i)
    {
        auto arrowX = iconBounds.getX() + arrowSpacing * (i + 0.5f);
        auto arrowSize = iconBounds.getWidth() * 0.05f;

        // Right-pointing arrow
        juce::Path arrow;
        arrow.startNewSubPath(arrowX, arrowY);
        arrow.lineTo(arrowX + arrowSize, arrowY - arrowSize * 0.5f);
        arrow.lineTo(arrowX + arrowSize, arrowY + arrowSize * 0.5f);
        arrow.closeSubPath();

        g.fillPath(arrow);
    }
}

void FancyIconPack::drawSync(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color)
{
    auto iconBounds = bounds;
    auto stroke = getOptimalStrokeWidth(iconBounds);

    // Synchronization symbol - two interlocked timing wheels
    auto centerY = iconBounds.getCentreY();
    auto wheelRadius = iconBounds.getHeight() * 0.25f;
    auto wheel1X = iconBounds.getX() + iconBounds.getWidth() * 0.35f;
    auto wheel2X = iconBounds.getX() + iconBounds.getWidth() * 0.65f;

    // Draw two overlapping timing wheels
    g.setColour(color.withAlpha(0.3f));
    g.fillEllipse(wheel1X - wheelRadius, centerY - wheelRadius, wheelRadius * 2.0f, wheelRadius * 2.0f);
    g.fillEllipse(wheel2X - wheelRadius, centerY - wheelRadius, wheelRadius * 2.0f, wheelRadius * 2.0f);

    g.setColour(color);
    g.drawEllipse(wheel1X - wheelRadius, centerY - wheelRadius, wheelRadius * 2.0f, wheelRadius * 2.0f, stroke);
    g.drawEllipse(wheel2X - wheelRadius, centerY - wheelRadius, wheelRadius * 2.0f, wheelRadius * 2.0f, stroke);

    // Timing marks around wheels
    for (int i = 0; i < 8; ++i)
    {
        auto angle = (i / 8.0f) * 2.0f * juce::MathConstants<float>::pi;
        auto cosA = std::cos(angle);
        auto sinA = std::sin(angle);

        // Wheel 1 marks
        auto markRadius = wheelRadius * 0.8f;
        auto x1 = wheel1X + cosA * markRadius;
        auto y1 = centerY + sinA * markRadius;
        auto x2 = wheel1X + cosA * wheelRadius;
        auto y2 = centerY + sinA * wheelRadius;

        g.setColour(color.withAlpha(0.7f));
        g.drawLine(x1, y1, x2, y2, stroke * 0.8f);

        // Wheel 2 marks (offset phase for sync indication)
        angle += juce::MathConstants<float>::pi * 0.125f; // Slight offset
        cosA = std::cos(angle);
        sinA = std::sin(angle);

        x1 = wheel2X + cosA * markRadius;
        y1 = centerY + sinA * markRadius;
        x2 = wheel2X + cosA * wheelRadius;
        y2 = centerY + sinA * wheelRadius;

        g.drawLine(x1, y1, x2, y2, stroke * 0.8f);
    }

    // Sync connection line
    g.setColour(color);
    g.drawLine(wheel1X + wheelRadius * 0.5f, centerY, wheel2X - wheelRadius * 0.5f, centerY, stroke);

    // "SYNC" label
    g.setColour(color.withAlpha(0.8f));
    g.setFont(juce::Font(iconBounds.getHeight() * 0.12f, juce::Font::bold));
    g.drawText("SYNC", juce::Rectangle<float>(iconBounds.getX(), iconBounds.getBottom() - iconBounds.getHeight() * 0.2f,
                                            iconBounds.getWidth(), iconBounds.getHeight() * 0.15f),
               juce::Justification::centred);
}

// Signal Flow and Routing
// ============================================================================

void FancyIconPack::drawInput(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color)
{
    auto iconBounds = bounds;
    auto stroke = getOptimalStrokeWidth(iconBounds);

    // Input jack/connector
    auto jackRect = juce::Rectangle<float>(iconBounds.getX() + iconBounds.getWidth() * 0.3f,
                                         iconBounds.getY() + iconBounds.getHeight() * 0.2f,
                                         iconBounds.getWidth() * 0.4f,
                                         iconBounds.getHeight() * 0.6f);

    // Outer jack housing
    g.setColour(color.withAlpha(0.3f));
    g.fillRoundedRectangle(jackRect, stroke);
    g.setColour(color);
    g.drawRoundedRectangle(jackRect, stroke, stroke);

    // Inner connector
    auto innerRect = jackRect.reduced(stroke * 2.0f);
    g.setColour(color.withAlpha(0.6f));
    g.fillRoundedRectangle(innerRect, stroke * 0.5f);

    // Signal arrow pointing inward
    auto arrowCenterX = iconBounds.getX() + iconBounds.getWidth() * 0.15f;
    auto arrowY = iconBounds.getCentreY();
    auto arrowSize = iconBounds.getWidth() * 0.08f;

    juce::Path arrow;
    arrow.startNewSubPath(arrowCenterX - arrowSize, arrowY);
    arrow.lineTo(arrowCenterX + arrowSize, arrowY);
    arrow.lineTo(arrowCenterX + arrowSize * 0.5f, arrowY - arrowSize * 0.6f);
    arrow.startNewSubPath(arrowCenterX + arrowSize, arrowY);
    arrow.lineTo(arrowCenterX + arrowSize * 0.5f, arrowY + arrowSize * 0.6f);

    g.setColour(color);
    g.strokePath(arrow, createStroke(stroke));

    // Connection line from arrow to jack
    g.drawLine(arrowCenterX + arrowSize, arrowY, jackRect.getX(), jackRect.getCentreY(), stroke * 0.8f);

    // "IN" label
    g.setColour(color.withAlpha(0.8f));
    g.setFont(juce::Font(iconBounds.getHeight() * 0.15f, juce::Font::bold));
    g.drawText("IN", juce::Rectangle<float>(iconBounds.getX(), iconBounds.getBottom() - iconBounds.getHeight() * 0.15f,
                                          iconBounds.getWidth(), iconBounds.getHeight() * 0.12f),
               juce::Justification::centred);
}

void FancyIconPack::drawOutput(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color)
{
    auto iconBounds = bounds;
    auto stroke = getOptimalStrokeWidth(iconBounds);

    // Output jack/connector
    auto jackRect = juce::Rectangle<float>(iconBounds.getX() + iconBounds.getWidth() * 0.3f,
                                         iconBounds.getY() + iconBounds.getHeight() * 0.2f,
                                         iconBounds.getWidth() * 0.4f,
                                         iconBounds.getHeight() * 0.6f);

    // Outer jack housing
    g.setColour(color.withAlpha(0.3f));
    g.fillRoundedRectangle(jackRect, stroke);
    g.setColour(color);
    g.drawRoundedRectangle(jackRect, stroke, stroke);

    // Inner connector
    auto innerRect = jackRect.reduced(stroke * 2.0f);
    g.setColour(color.withAlpha(0.6f));
    g.fillRoundedRectangle(innerRect, stroke * 0.5f);

    // Signal arrow pointing outward
    auto arrowCenterX = iconBounds.getX() + iconBounds.getWidth() * 0.85f;
    auto arrowY = iconBounds.getCentreY();
    auto arrowSize = iconBounds.getWidth() * 0.08f;

    juce::Path arrow;
    arrow.startNewSubPath(arrowCenterX - arrowSize, arrowY);
    arrow.lineTo(arrowCenterX + arrowSize, arrowY);
    arrow.lineTo(arrowCenterX + arrowSize * 0.5f, arrowY - arrowSize * 0.6f);
    arrow.startNewSubPath(arrowCenterX + arrowSize, arrowY);
    arrow.lineTo(arrowCenterX + arrowSize * 0.5f, arrowY + arrowSize * 0.6f);

    g.setColour(color);
    g.strokePath(arrow, createStroke(stroke));

    // Connection line from jack to arrow
    g.drawLine(jackRect.getRight(), jackRect.getCentreY(), arrowCenterX - arrowSize, arrowY, stroke * 0.8f);

    // "OUT" label
    g.setColour(color.withAlpha(0.8f));
    g.setFont(juce::Font(iconBounds.getHeight() * 0.15f, juce::Font::bold));
    g.drawText("OUT", juce::Rectangle<float>(iconBounds.getX(), iconBounds.getBottom() - iconBounds.getHeight() * 0.15f,
                                           iconBounds.getWidth(), iconBounds.getHeight() * 0.12f),
               juce::Justification::centred);
}

void FancyIconPack::drawMix(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color)
{
    auto iconBounds = bounds;
    auto stroke = getOptimalStrokeWidth(iconBounds);

    // Mixer symbol - multiple inputs converging to one output
    auto centerX = iconBounds.getCentreX();
    auto centerY = iconBounds.getCentreY();

    // Three input lines from left
    auto inputSpacing = iconBounds.getHeight() * 0.25f;
    auto inputLength = iconBounds.getWidth() * 0.3f;
    auto inputStartX = iconBounds.getX() + stroke;

    g.setColour(color.withAlpha(0.7f));

    for (int i = 0; i < 3; ++i)
    {
        auto inputY = centerY + (i - 1) * inputSpacing;
        g.drawLine(inputStartX, inputY, inputStartX + inputLength, inputY, stroke);

        // Small input indicators
        auto inputDotSize = stroke * 1.5f;
        g.fillEllipse(inputStartX - inputDotSize * 0.5f, inputY - inputDotSize * 0.5f,
                      inputDotSize, inputDotSize);
    }

    // Mixing junction (triangle pointing right)
    auto mixerSize = iconBounds.getHeight() * 0.2f;
    auto mixerX = inputStartX + inputLength;

    juce::Path mixer;
    mixer.startNewSubPath(mixerX, centerY - mixerSize);
    mixer.lineTo(mixerX + mixerSize * 1.5f, centerY);
    mixer.lineTo(mixerX, centerY + mixerSize);
    mixer.closeSubPath();

    g.setColour(color.withAlpha(0.3f));
    g.fillPath(mixer);
    g.setColour(color);
    g.strokePath(mixer, createStroke(stroke));

    // Output line
    auto outputStartX = mixerX + mixerSize * 1.5f;
    auto outputEndX = iconBounds.getRight() - stroke;

    g.setColour(color);
    g.drawLine(outputStartX, centerY, outputEndX, centerY, stroke * 1.2f);

    // Output indicator
    auto outputDotSize = stroke * 1.8f;
    g.fillEllipse(outputEndX - outputDotSize * 0.5f, centerY - outputDotSize * 0.5f,
                  outputDotSize, outputDotSize);

    // Mix level indicator
    g.setColour(color.withAlpha(0.6f));
    g.setFont(juce::Font(iconBounds.getHeight() * 0.1f, juce::Font::bold));
    g.drawText("MIX", juce::Rectangle<float>(mixerX, centerY + mixerSize + stroke,
                                           mixerSize * 1.5f, iconBounds.getHeight() * 0.15f),
               juce::Justification::centred);
}

void FancyIconPack::drawDryWet(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color)
{
    auto iconBounds = bounds;
    auto stroke = getOptimalStrokeWidth(iconBounds);

    // Split view showing dry vs wet signal
    auto splitX = iconBounds.getCentreX();

    // Dry side (left) - clean waveform
    auto dryBounds = iconBounds.removeFromLeft(iconBounds.getWidth() * 0.5f);
    juce::Path dryWave;
    auto dryY = dryBounds.getCentreY();
    auto dryAmplitude = dryBounds.getHeight() * 0.25f;
    auto points = 8;

    dryWave.startNewSubPath(dryBounds.getX(), dryY);
    for (int i = 1; i <= points; ++i)
    {
        auto x = dryBounds.getX() + (i / static_cast<float>(points)) * dryBounds.getWidth();
        auto phase = (i / static_cast<float>(points)) * juce::MathConstants<float>::twoPi * 1.5f;
        auto amp = std::sin(phase) * dryAmplitude;
        dryWave.lineTo(x, dryY + amp);
    }

    g.setColour(color.withAlpha(0.6f));
    g.strokePath(dryWave, createStroke(stroke));

    // Wet side (right) - processed waveform
    auto wetBounds = iconBounds.removeFromRight(iconBounds.getWidth());
    juce::Path wetWave;
    auto wetY = wetBounds.getCentreY();
    auto wetAmplitude = wetBounds.getHeight() * 0.25f;

    wetWave.startNewSubPath(wetBounds.getX(), wetY);
    for (int i = 1; i <= points; ++i)
    {
        auto x = wetBounds.getX() + (i / static_cast<float>(points)) * wetBounds.getWidth();
        auto phase = (i / static_cast<float>(points)) * juce::MathConstants<float>::twoPi * 1.5f;
        // Add some harmonics for "wet" effect
        auto amp = (std::sin(phase) + std::sin(phase * 2.0f) * 0.3f) * wetAmplitude;
        wetWave.lineTo(x, wetY + amp);
    }

    g.setColour(color);
    g.strokePath(wetWave, createStroke(stroke));

    // Dividing line
    g.setColour(color.withAlpha(0.3f));
    g.drawLine(splitX, iconBounds.getY(), splitX, iconBounds.getBottom(), stroke * 0.6f);

    // Labels
    g.setColour(color.withAlpha(0.8f));
    g.setFont(juce::Font(iconBounds.getHeight() * 0.15f, juce::Font::bold));

    auto dryLabel = juce::Rectangle<float>(dryBounds.getX(), iconBounds.getBottom() - iconBounds.getHeight() * 0.2f,
                                         dryBounds.getWidth(), iconBounds.getHeight() * 0.15f);
    g.drawText("DRY", dryLabel, juce::Justification::centred);

    auto wetLabel = juce::Rectangle<float>(wetBounds.getX(), iconBounds.getBottom() - iconBounds.getHeight() * 0.2f,
                                         wetBounds.getWidth(), iconBounds.getHeight() * 0.15f);
    g.drawText("WET", wetLabel, juce::Justification::centred);
}

void FancyIconPack::drawFeedback(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color)
{
    auto iconBounds = bounds;
    auto stroke = getOptimalStrokeWidth(iconBounds);

    // Feedback loop as circular arrow
    auto centre = iconBounds.getCentre();
    auto radius = juce::jmin(iconBounds.getWidth(), iconBounds.getHeight()) * 0.3f;

    // Main circular path
    juce::Path feedbackLoop;
    feedbackLoop.addCentredArc(centre.x, centre.y, radius, radius, 0.0f,
                              juce::MathConstants<float>::pi * 0.3f,
                              juce::MathConstants<float>::pi * 2.2f, true);

    g.setColour(color);
    g.strokePath(feedbackLoop, createStroke(stroke));

    // Arrow head
    auto arrowAngle = juce::MathConstants<float>::pi * 2.2f;
    auto arrowTip = centre + juce::Point<float>(std::cos(arrowAngle) * radius, std::sin(arrowAngle) * radius);
    auto arrowSize = radius * 0.3f;

    juce::Path arrowHead;
    arrowHead.startNewSubPath(arrowTip);
    arrowHead.lineTo(arrowTip.x - arrowSize * 0.8f, arrowTip.y - arrowSize * 0.4f);
    arrowHead.lineTo(arrowTip.x - arrowSize * 0.4f, arrowTip.y);
    arrowHead.lineTo(arrowTip.x - arrowSize * 0.8f, arrowTip.y + arrowSize * 0.4f);
    arrowHead.closeSubPath();

    g.fillPath(arrowHead);

    // Signal flow points
    auto inputPoint = centre + juce::Point<float>(-radius * 1.2f, 0);
    auto outputPoint = centre + juce::Point<float>(radius * 1.2f, 0);

    g.setColour(color.withAlpha(0.7f));
    auto dotRadius = stroke * 1.2f;
    g.fillEllipse(inputPoint.x - dotRadius, inputPoint.y - dotRadius, dotRadius * 2, dotRadius * 2);
    g.fillEllipse(outputPoint.x - dotRadius, outputPoint.y - dotRadius, dotRadius * 2, dotRadius * 2);
}

void FancyIconPack::drawRouting(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color)
{
    auto iconBounds = bounds;
    auto stroke = getOptimalStrokeWidth(iconBounds);

    // Signal routing matrix diagram
    auto nodeRadius = iconBounds.getWidth() * 0.06f;
    auto dotRadius = stroke * 1.2f;

    // Input nodes (left side)
    juce::Point<float> input1(iconBounds.getX() + nodeRadius, iconBounds.getY() + iconBounds.getHeight() * 0.25f);
    juce::Point<float> input2(iconBounds.getX() + nodeRadius, iconBounds.getY() + iconBounds.getHeight() * 0.75f);

    // Output nodes (right side)
    juce::Point<float> output1(iconBounds.getRight() - nodeRadius, iconBounds.getY() + iconBounds.getHeight() * 0.25f);
    juce::Point<float> output2(iconBounds.getRight() - nodeRadius, iconBounds.getY() + iconBounds.getHeight() * 0.75f);

    // Center routing matrix
    auto matrixCenter = iconBounds.getCentre();
    auto matrixSize = juce::jmin(iconBounds.getWidth(), iconBounds.getHeight()) * 0.3f;

    g.setColour(color);

    // Draw input nodes
    g.fillEllipse(input1.x - nodeRadius, input1.y - nodeRadius, nodeRadius * 2, nodeRadius * 2);
    g.fillEllipse(input2.x - nodeRadius, input2.y - nodeRadius, nodeRadius * 2, nodeRadius * 2);

    // Draw output nodes
    g.fillEllipse(output1.x - nodeRadius, output1.y - nodeRadius, nodeRadius * 2, nodeRadius * 2);
    g.fillEllipse(output2.x - nodeRadius, output2.y - nodeRadius, nodeRadius * 2, nodeRadius * 2);

    // Draw routing matrix (diamond shape)
    juce::Path matrix;
    matrix.startNewSubPath(matrixCenter.x, matrixCenter.y - matrixSize);
    matrix.lineTo(matrixCenter.x + matrixSize * 0.7f, matrixCenter.y);
    matrix.lineTo(matrixCenter.x, matrixCenter.y + matrixSize);
    matrix.lineTo(matrixCenter.x - matrixSize * 0.7f, matrixCenter.y);
    matrix.closeSubPath();

    g.strokePath(matrix, createStroke(stroke));

    // Connection lines
    g.drawLine(input1.x, input1.y, matrixCenter.x - matrixSize * 0.7f, matrixCenter.y - matrixSize * 0.3f, stroke);
    g.drawLine(input2.x, input2.y, matrixCenter.x - matrixSize * 0.7f, matrixCenter.y + matrixSize * 0.3f, stroke);
    g.drawLine(matrixCenter.x + matrixSize * 0.7f, matrixCenter.y - matrixSize * 0.3f, output1.x, output1.y, stroke);
    g.drawLine(matrixCenter.x + matrixSize * 0.7f, matrixCenter.y + matrixSize * 0.3f, output2.x, output2.y, stroke);

    // Routing dots
    g.fillEllipse(matrixCenter.x - dotRadius, matrixCenter.y - matrixSize * 0.3f - dotRadius, dotRadius * 2, dotRadius * 2);
    g.fillEllipse(matrixCenter.x - dotRadius, matrixCenter.y + matrixSize * 0.3f - dotRadius, dotRadius * 2, dotRadius * 2);
}

void FancyIconPack::drawSignalPath(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color)
{
    auto iconBounds = bounds;
    auto stroke = getOptimalStrokeWidth(iconBounds);

    // Signal flow line with processing blocks
    auto flowY = iconBounds.getCentreY();
    auto blockSize = iconBounds.getHeight() * 0.25f;
    auto blockSpacing = iconBounds.getWidth() * 0.3f;

    g.setColour(color);

    // Main signal flow line
    g.drawLine(iconBounds.getX(), flowY, iconBounds.getRight(), flowY, stroke);

    // Processing blocks along the signal path
    for (int i = 0; i < 3; ++i)
    {
        auto blockX = iconBounds.getX() + blockSpacing * (i + 0.5f) - blockSize * 0.5f;
        auto blockY = flowY - blockSize * 0.5f;

        // Draw processing block
        g.fillRoundedRectangle(blockX, blockY, blockSize, blockSize, 2.0f);

        // Signal flow arrows
        if (i < 2)
        {
            auto arrowX = blockX + blockSize + blockSpacing * 0.3f;
            auto arrowSize = stroke * 2;

            // Arrow head
            juce::Path arrow;
            arrow.startNewSubPath(arrowX - arrowSize, flowY - arrowSize);
            arrow.lineTo(arrowX, flowY);
            arrow.lineTo(arrowX - arrowSize, flowY + arrowSize);

            g.strokePath(arrow, createStroke(stroke, juce::PathStrokeType::mitered, juce::PathStrokeType::butt));
        }
    }

    // Input/Output indicators
    auto ioRadius = stroke * 1.5f;
    g.setColour(color.brighter(0.2f));
    g.fillEllipse(iconBounds.getX() - ioRadius, flowY - ioRadius, ioRadius * 2, ioRadius * 2);
    g.fillEllipse(iconBounds.getRight() - ioRadius, flowY - ioRadius, ioRadius * 2, ioRadius * 2);
}

void FancyIconPack::drawPatchCable(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color)
{
    auto iconBounds = bounds;
    auto stroke = getOptimalStrokeWidth(iconBounds);

    // Modular synthesizer patch cable
    auto jackRadius = iconBounds.getWidth() * 0.12f;
    auto cableThickness = stroke * 2.0f;

    // Left jack (input)
    auto leftJack = juce::Point<float>(iconBounds.getX() + jackRadius, iconBounds.getCentreY());
    // Right jack (output)
    auto rightJack = juce::Point<float>(iconBounds.getRight() - jackRadius, iconBounds.getCentreY());

    g.setColour(color);

    // Draw jacks (3.5mm style)
    // Outer ring
    g.drawEllipse(leftJack.x - jackRadius, leftJack.y - jackRadius, jackRadius * 2, jackRadius * 2, stroke);
    g.drawEllipse(rightJack.x - jackRadius, rightJack.y - jackRadius, jackRadius * 2, jackRadius * 2, stroke);

    // Inner connector
    auto innerRadius = jackRadius * 0.4f;
    g.fillEllipse(leftJack.x - innerRadius, leftJack.y - innerRadius, innerRadius * 2, innerRadius * 2);
    g.fillEllipse(rightJack.x - innerRadius, rightJack.y - innerRadius, innerRadius * 2, innerRadius * 2);

    // Patch cable with slight curve
    juce::Path cable;
    cable.startNewSubPath(leftJack.x + jackRadius * 0.8f, leftJack.y);

    auto controlPoint1 = leftJack + juce::Point<float>(iconBounds.getWidth() * 0.25f, -iconBounds.getHeight() * 0.15f);
    auto controlPoint2 = rightJack + juce::Point<float>(-iconBounds.getWidth() * 0.25f, iconBounds.getHeight() * 0.15f);

    cable.cubicTo(controlPoint1, controlPoint2, rightJack + juce::Point<float>(-jackRadius * 0.8f, 0));

    g.strokePath(cable, createStroke(cableThickness, juce::PathStrokeType::curved, juce::PathStrokeType::rounded));

    // Cable strain relief
    g.setColour(color.darker(0.3f));
    auto reliefSize = jackRadius * 0.6f;
    g.fillRoundedRectangle(leftJack.x + jackRadius * 0.3f, leftJack.y - reliefSize * 0.3f, reliefSize, reliefSize * 0.6f, 2.0f);
    g.fillRoundedRectangle(rightJack.x - jackRadius * 0.9f, rightJack.y - reliefSize * 0.3f, reliefSize, reliefSize * 0.6f, 2.0f);
}

void FancyIconPack::drawCrossfade(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color)
{
    auto iconBounds = bounds;
    auto stroke = getOptimalStrokeWidth(iconBounds);

    // Crossfade symbol - two curves intersecting
    auto crossArea = iconBounds.reduced(iconBounds.getWidth() * 0.1f, iconBounds.getHeight() * 0.2f);

    // Curve A (fading out)
    juce::Path curveA;
    curveA.startNewSubPath(crossArea.getX(), crossArea.getY());
    curveA.quadraticTo(crossArea.getCentreX(), crossArea.getCentreY() - crossArea.getHeight() * 0.2f,
                      crossArea.getRight(), crossArea.getBottom());

    // Curve B (fading in)
    juce::Path curveB;
    curveB.startNewSubPath(crossArea.getX(), crossArea.getBottom());
    curveB.quadraticTo(crossArea.getCentreX(), crossArea.getCentreY() + crossArea.getHeight() * 0.2f,
                      crossArea.getRight(), crossArea.getY());

    g.setColour(color);
    g.strokePath(curveA, createStroke(stroke * 1.5f));

    g.setColour(color.withAlpha(0.7f));
    g.strokePath(curveB, createStroke(stroke * 1.5f));

    // Intersection point highlight
    g.setColour(color.brighter(0.3f));
    auto dotRadius = stroke * 2;
    g.fillEllipse(crossArea.getCentreX() - dotRadius, crossArea.getCentreY() - dotRadius, dotRadius * 2, dotRadius * 2);

    // Source labels
    g.setColour(color.withAlpha(0.8f));
    g.setFont(juce::Font(iconBounds.getHeight() * 0.12f, juce::Font::bold));

    auto labelHeight = iconBounds.getHeight() * 0.15f;
    g.drawText("A", juce::Rectangle<float>(crossArea.getX(), crossArea.getY() - labelHeight,
                                         crossArea.getWidth() * 0.3f, labelHeight), juce::Justification::centred);
    g.drawText("B", juce::Rectangle<float>(crossArea.getX(), crossArea.getBottom(),
                                         crossArea.getWidth() * 0.3f, labelHeight), juce::Justification::centred);
}

void FancyIconPack::drawSidechain(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color)
{
    auto iconBounds = bounds;
    auto stroke = getOptimalStrokeWidth(iconBounds);

    // Main signal flow (horizontal)
    auto mainY = iconBounds.getCentreY();
    g.setColour(color);
    g.drawLine(iconBounds.getX(), mainY, iconBounds.getRight(), mainY, stroke * 1.5f);

    // Sidechain input (vertical from top)
    auto sideChainX = iconBounds.getCentreX();
    auto sideChainTop = iconBounds.getY();
    auto sideChainBottom = mainY - iconBounds.getHeight() * 0.1f;

    g.drawLine(sideChainX, sideChainTop, sideChainX, sideChainBottom, stroke);

    // Processing block at junction
    auto blockSize = iconBounds.getHeight() * 0.3f;
    auto blockX = sideChainX - blockSize * 0.5f;
    auto blockY = mainY - blockSize * 0.5f;

    g.fillRoundedRectangle(blockX, blockY, blockSize, blockSize, 3.0f);

    // Sidechain indicator - small waveform above
    juce::Path sideWave;
    auto waveArea = juce::Rectangle<float>(sideChainX - iconBounds.getWidth() * 0.15f,
                                         sideChainTop,
                                         iconBounds.getWidth() * 0.3f,
                                         iconBounds.getHeight() * 0.2f);

    auto waveY = waveArea.getCentreY();
    auto amplitude = waveArea.getHeight() * 0.4f;
    auto points = 8;

    sideWave.startNewSubPath(waveArea.getX(), waveY);
    for (int i = 1; i <= points; ++i)
    {
        auto x = waveArea.getX() + (i / static_cast<float>(points)) * waveArea.getWidth();
        auto phase = (i / static_cast<float>(points)) * juce::MathConstants<float>::twoPi * 2.0f;
        auto amp = std::sin(phase) * amplitude;
        sideWave.lineTo(x, waveY + amp);
    }

    g.setColour(color.withAlpha(0.7f));
    g.strokePath(sideWave, createStroke(stroke * 0.8f));

    // Arrow showing sidechain direction
    auto arrowSize = stroke * 2;
    juce::Path arrow;
    arrow.startNewSubPath(sideChainX - arrowSize, sideChainBottom + arrowSize);
    arrow.lineTo(sideChainX, sideChainBottom);
    arrow.lineTo(sideChainX + arrowSize, sideChainBottom + arrowSize);

    g.setColour(color);
    g.strokePath(arrow, createStroke(stroke, juce::PathStrokeType::mitered, juce::PathStrokeType::butt));

    // Label
    g.setFont(juce::Font(iconBounds.getHeight() * 0.1f, juce::Font::bold));
    g.drawText("SC", juce::Rectangle<float>(blockX, blockY + blockSize + stroke, blockSize, iconBounds.getHeight() * 0.12f),
               juce::Justification::centred);
}

// Audio Effects
// ============================================================================

void FancyIconPack::drawCompressor(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color)
{
    auto iconBounds = bounds;
    auto stroke = getOptimalStrokeWidth(iconBounds);

    // Compression curve showing input/output relationship
    juce::Path compressionCurve;
    auto baseY = iconBounds.getBottom() - iconBounds.getHeight() * 0.1f;
    auto baseX = iconBounds.getX() + iconBounds.getWidth() * 0.1f;
    auto points = 15;

    compressionCurve.startNewSubPath(baseX, baseY);

    for (int i = 1; i <= points; ++i)
    {
        auto inputRatio = i / static_cast<float>(points);
        auto x = baseX + inputRatio * iconBounds.getWidth() * 0.8f;

        // Compression curve: linear up to threshold, then compressed
        auto outputRatio = inputRatio;
        if (inputRatio > 0.6f) // Threshold at 60%
        {
            auto overThreshold = inputRatio - 0.6f;
            outputRatio = 0.6f + overThreshold * 0.3f; // 3:1 compression ratio
        }

        auto y = baseY - outputRatio * iconBounds.getHeight() * 0.8f;
        compressionCurve.lineTo(x, y);
    }

    g.setColour(color);
    g.strokePath(compressionCurve, createStroke(stroke));

    // Reference line (1:1 ratio)
    g.setColour(color.withAlpha(0.3f));
    g.drawLine(baseX, baseY, baseX + iconBounds.getWidth() * 0.8f, baseY - iconBounds.getHeight() * 0.8f, stroke * 0.6f);

    // Threshold marker
    auto thresholdX = baseX + iconBounds.getWidth() * 0.8f * 0.6f;
    auto thresholdY = baseY - iconBounds.getHeight() * 0.8f * 0.6f;
    g.setColour(color.withAlpha(0.7f));
    g.drawLine(thresholdX, baseY, thresholdX, thresholdY, stroke * 0.8f);
}

void FancyIconPack::drawLimiter(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color)
{
    auto iconBounds = bounds;
    auto stroke = getOptimalStrokeWidth(iconBounds);

    // Limiting curve with hard ceiling
    juce::Path limitingCurve;
    auto baseY = iconBounds.getBottom() - iconBounds.getHeight() * 0.1f;
    auto ceilingY = iconBounds.getY() + iconBounds.getHeight() * 0.3f;
    auto limitThreshold = iconBounds.getX() + iconBounds.getWidth() * 0.6f;

    limitingCurve.startNewSubPath(iconBounds.getX(), baseY);

    // Linear response up to threshold
    limitingCurve.lineTo(limitThreshold, ceilingY);

    // Hard limiting (flat ceiling)
    limitingCurve.lineTo(iconBounds.getRight(), ceilingY);

    g.setColour(color);
    g.strokePath(limitingCurve, createStroke(stroke * 1.2f));

    // Ceiling line
    g.setColour(color.withAlpha(0.6f));
    g.drawLine(iconBounds.getX(), ceilingY, iconBounds.getRight(), ceilingY, stroke * 0.8f);

    // Threshold indicator
    g.setColour(color.withAlpha(0.5f));
    g.drawLine(limitThreshold, baseY, limitThreshold, ceilingY, stroke * 0.7f);

    // "LIMIT" label
    g.setColour(color.withAlpha(0.8f));
    g.setFont(juce::Font(iconBounds.getHeight() * 0.1f, juce::Font::bold));
    g.drawText("LIMIT", juce::Rectangle<float>(iconBounds.getX(), ceilingY - iconBounds.getHeight() * 0.15f,
                                             iconBounds.getWidth(), iconBounds.getHeight() * 0.12f),
               juce::Justification::centred);
}

void FancyIconPack::drawExpander(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color)
{
    auto iconBounds = bounds;
    auto stroke = getOptimalStrokeWidth(iconBounds);

    // Expansion curve - opposite of compression
    juce::Path expansionCurve;
    auto baseY = iconBounds.getBottom() - iconBounds.getHeight() * 0.1f;
    auto points = 20;

    expansionCurve.startNewSubPath(iconBounds.getX(), baseY);

    for (int i = 1; i <= points; ++i)
    {
        auto x = iconBounds.getX() + (i / static_cast<float>(points)) * iconBounds.getWidth();
        auto inputRatio = i / static_cast<float>(points);

        // Expansion curve: quiet signals get quieter, loud signals get louder
        auto outputRatio = std::pow(inputRatio, 1.5f); // Expansion
        auto y = baseY - outputRatio * iconBounds.getHeight() * 0.8f;

        expansionCurve.lineTo(x, y);
    }

    g.setColour(color);
    g.strokePath(expansionCurve, createStroke(stroke * 1.2f));

    // Reference line (1:1 ratio)
    g.setColour(color.withAlpha(0.4f));
    g.drawLine(iconBounds.getX(), baseY,
               iconBounds.getRight(), iconBounds.getY() + iconBounds.getHeight() * 0.1f,
               stroke * 0.7f);

    // Expansion ratio indicators
    g.setColour(color.withAlpha(0.6f));
    auto midX = iconBounds.getCentreX();
    auto expandedY = baseY - 0.75f * iconBounds.getHeight() * 0.8f;
    auto referenceY = baseY - 0.5f * iconBounds.getHeight() * 0.8f;

    // Arrow showing expansion effect
    juce::Path arrow;
    arrow.startNewSubPath(midX, referenceY);
    arrow.lineTo(midX, expandedY);
    arrow.lineTo(midX - stroke * 1.5f, expandedY + stroke * 2.0f);
    arrow.lineTo(midX + stroke * 1.5f, expandedY + stroke * 2.0f);
    arrow.closeSubPath();

    g.fillPath(arrow);

    // "EXP" label
    g.setColour(color.withAlpha(0.8f));
    g.setFont(juce::Font(iconBounds.getHeight() * 0.12f, juce::Font::bold));
    g.drawText("EXP", juce::Rectangle<float>(iconBounds.getX(), iconBounds.getY(),
                                           iconBounds.getWidth(), iconBounds.getHeight() * 0.15f),
               juce::Justification::centred);
}

void FancyIconPack::drawSaturator(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color)
{
    auto iconBounds = bounds;
    auto stroke = getOptimalStrokeWidth(iconBounds);

    // Saturation curve showing soft clipping/saturation
    juce::Path saturationCurve;
    auto centerX = iconBounds.getCentreX();
    auto centerY = iconBounds.getCentreY();
    auto amplitude = iconBounds.getHeight() * 0.35f;
    auto points = 40;

    saturationCurve.startNewSubPath(iconBounds.getX(), centerY);

    for (int i = 1; i <= points; ++i)
    {
        auto x = iconBounds.getX() + (i / static_cast<float>(points)) * iconBounds.getWidth();
        auto inputRatio = (i / static_cast<float>(points) - 0.5f) * 2.0f; // -1 to +1

        // Saturation function (tanh-like curve)
        auto saturated = std::tanh(inputRatio * 3.0f) * 0.8f; // Soft saturation
        auto y = centerY - saturated * amplitude;

        saturationCurve.lineTo(x, y);
    }

    g.setColour(color);
    g.strokePath(saturationCurve, createStroke(stroke * 1.2f));

    // Input signal reference (linear)
    juce::Path linearRef;
    linearRef.startNewSubPath(iconBounds.getX(), centerY + amplitude * 0.6f);
    linearRef.lineTo(iconBounds.getRight(), centerY - amplitude * 0.6f);

    g.setColour(color.withAlpha(0.4f));
    g.strokePath(linearRef, createStroke(stroke * 0.7f));

    // Saturation regions indicators
    g.setColour(color.withAlpha(0.6f));
    auto topSatY = centerY - amplitude * 0.8f;
    auto bottomSatY = centerY + amplitude * 0.8f;

    // Top saturation line
    g.drawLine(iconBounds.getX() + iconBounds.getWidth() * 0.3f, topSatY,
               iconBounds.getRight(), topSatY, stroke * 0.6f);

    // Bottom saturation line
    g.drawLine(iconBounds.getX(), bottomSatY,
               iconBounds.getX() + iconBounds.getWidth() * 0.7f, bottomSatY, stroke * 0.6f);

    // "SAT" label
    g.setColour(color.withAlpha(0.8f));
    g.setFont(juce::Font(iconBounds.getHeight() * 0.12f, juce::Font::bold));
    g.drawText("SAT", juce::Rectangle<float>(iconBounds.getX(), iconBounds.getBottom() - iconBounds.getHeight() * 0.15f,
                                           iconBounds.getWidth(), iconBounds.getHeight() * 0.12f),
               juce::Justification::centred);
}

void FancyIconPack::drawDistortion(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color)
{
    auto iconBounds = bounds;
    auto stroke = getOptimalStrokeWidth(iconBounds);

    // Distorted sine wave showing clipping and harmonics
    juce::Path distortedWave;
    auto waveY = iconBounds.getCentreY();
    auto points = 20;
    auto amplitude = iconBounds.getHeight() * 0.3f;

    distortedWave.startNewSubPath(iconBounds.getX(), waveY);

    for (int i = 1; i <= points; ++i)
    {
        auto x = iconBounds.getX() + (i / static_cast<float>(points)) * iconBounds.getWidth();
        auto phase = (i / static_cast<float>(points)) * juce::MathConstants<float>::twoPi * 2.0f;

        // Sine wave with hard clipping and some overdrive characteristics
        auto cleanSignal = std::sin(phase) * 1.5f; // Overdrive
        auto distortedSignal = juce::jlimit(-1.0f, 1.0f, cleanSignal); // Hard clip

        // Add some odd harmonics for more realistic distortion
        distortedSignal += std::sin(phase * 3.0f) * 0.1f;

        auto y = waveY + distortedSignal * amplitude;
        distortedWave.lineTo(x, y);
    }

    g.setColour(color);
    g.strokePath(distortedWave, createStroke(stroke));

    // Center line
    g.setColour(color.withAlpha(0.3f));
    g.drawLine(iconBounds.getX(), waveY, iconBounds.getRight(), waveY, stroke * 0.5f);

    // Clipping indicators (horizontal lines showing limits)
    auto clipLevel = amplitude * 0.8f;
    g.setColour(color.withHue(0.0f).withAlpha(0.6f)); // Red tint
    g.drawLine(iconBounds.getX(), waveY - clipLevel, iconBounds.getRight(), waveY - clipLevel, stroke * 0.6f);
    g.drawLine(iconBounds.getX(), waveY + clipLevel, iconBounds.getRight(), waveY + clipLevel, stroke * 0.6f);
}

void FancyIconPack::drawBitcrusher(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color)
{
    auto iconBounds = bounds;
    auto stroke = getOptimalStrokeWidth(iconBounds);

    // Pixelated/crushed waveform showing quantization
    juce::Path crushedWave;
    auto waveY = iconBounds.getCentreY();
    auto amplitude = iconBounds.getHeight() * 0.3f;
    auto steps = 8; // Low bit depth for crushing effect

    crushedWave.startNewSubPath(iconBounds.getX(), waveY);

    for (int i = 0; i <= steps; ++i)
    {
        auto x = iconBounds.getX() + (i / static_cast<float>(steps)) * iconBounds.getWidth();

        // Create stepped/quantized sine wave
        auto phase = (i / static_cast<float>(steps)) * juce::MathConstants<float>::twoPi * 1.5f;
        auto smoothValue = std::sin(phase);

        // Quantize to fewer bits (4-bit = 16 levels)
        auto quantizedValue = std::round(smoothValue * 7.0f) / 7.0f;
        auto y = waveY + quantizedValue * amplitude;

        if (i == 0)
        {
            crushedWave.startNewSubPath(x, y);
        }
        else
        {
            // Create stepped pattern
            auto prevX = iconBounds.getX() + ((i-1) / static_cast<float>(steps)) * iconBounds.getWidth();
            auto prevPhase = ((i-1) / static_cast<float>(steps)) * juce::MathConstants<float>::twoPi * 1.5f;
            auto prevQuantized = std::round(std::sin(prevPhase) * 7.0f) / 7.0f;
            auto prevY = waveY + prevQuantized * amplitude;

            crushedWave.lineTo(prevX, prevY); // Hold previous value
            crushedWave.lineTo(x, prevY);     // Step to new x
            crushedWave.lineTo(x, y);         // Step to new y
        }
    }

    g.setColour(color);
    g.strokePath(crushedWave, createStroke(stroke * 1.2f, juce::PathStrokeType::mitered, juce::PathStrokeType::butt));

    // Original smooth wave for comparison (faded)
    juce::Path smoothWave;
    smoothWave.startNewSubPath(iconBounds.getX(), waveY);

    for (int i = 1; i <= 20; ++i)
    {
        auto x = iconBounds.getX() + (i / 20.0f) * iconBounds.getWidth();
        auto phase = (i / 20.0f) * juce::MathConstants<float>::twoPi * 1.5f;
        auto y = waveY + std::sin(phase) * amplitude;
        smoothWave.lineTo(x, y);
    }

    g.setColour(color.withAlpha(0.3f));
    g.strokePath(smoothWave, createStroke(stroke * 0.8f));

    // "CRUSH" label
    g.setColour(color.withAlpha(0.8f));
    g.setFont(juce::Font(iconBounds.getHeight() * 0.1f, juce::Font::bold));
    g.drawText("CRUSH", juce::Rectangle<float>(iconBounds.getX(), iconBounds.getBottom() - iconBounds.getHeight() * 0.15f,
                                             iconBounds.getWidth(), iconBounds.getHeight() * 0.12f),
               juce::Justification::centred);
}

void FancyIconPack::drawWaveshaper(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color)
{
    auto iconBounds = bounds;
    auto stroke = getOptimalStrokeWidth(iconBounds);

    // Waveshaping transfer function curve
    juce::Path transferCurve;
    auto centerX = iconBounds.getCentreX();
    auto centerY = iconBounds.getCentreY();
    auto amplitude = iconBounds.getHeight() * 0.35f;
    auto points = 30;

    transferCurve.startNewSubPath(iconBounds.getX(), centerY + amplitude);

    for (int i = 1; i <= points; ++i)
    {
        auto x = iconBounds.getX() + (i / static_cast<float>(points)) * iconBounds.getWidth();
        auto inputRatio = (i / static_cast<float>(points) - 0.5f) * 2.0f; // -1 to +1

        // Waveshaping function - S-curve with some distortion character
        auto shaped = inputRatio + 0.3f * std::sin(inputRatio * juce::MathConstants<float>::pi * 2.0f);
        shaped = juce::jlimit(-1.0f, 1.0f, shaped); // Clamp to prevent overflow

        auto y = centerY - shaped * amplitude;
        transferCurve.lineTo(x, y);
    }

    g.setColour(color);
    g.strokePath(transferCurve, createStroke(stroke * 1.2f));

    // Reference diagonal line (linear transfer)
    g.setColour(color.withAlpha(0.4f));
    g.drawLine(iconBounds.getX(), centerY + amplitude,
               iconBounds.getRight(), centerY - amplitude, stroke * 0.7f);

    // Grid lines for reference
    g.setColour(color.withAlpha(0.2f));
    g.drawLine(centerX, iconBounds.getY(), centerX, iconBounds.getBottom(), stroke * 0.5f); // Vertical center
    g.drawLine(iconBounds.getX(), centerY, iconBounds.getRight(), centerY, stroke * 0.5f);  // Horizontal center

    // Input/Output labels
    g.setColour(color.withAlpha(0.6f));
    g.setFont(juce::Font(iconBounds.getHeight() * 0.08f, juce::Font::bold));

    // Input arrow (bottom)
    g.drawText("IN", juce::Rectangle<float>(centerX - iconBounds.getWidth() * 0.1f,
                                          iconBounds.getBottom() - iconBounds.getHeight() * 0.1f,
                                          iconBounds.getWidth() * 0.2f, iconBounds.getHeight() * 0.08f),
               juce::Justification::centred);

    // Output arrow (left side)
    g.drawText("OUT", juce::Rectangle<float>(iconBounds.getX(), centerY - iconBounds.getHeight() * 0.04f,
                                           iconBounds.getWidth() * 0.15f, iconBounds.getHeight() * 0.08f),
               juce::Justification::centred);
}

void FancyIconPack::drawReverb(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color)
{
    auto iconBounds = bounds;
    auto stroke = getOptimalStrokeWidth(iconBounds);

    // Reverb visualization as decay envelope with reflections
    auto centre = iconBounds.getCentre();

    // Main impulse
    g.setColour(color);
    g.fillEllipse(centre.x - stroke * 2, centre.y - stroke * 2, stroke * 4, stroke * 4);

    // Concentric circles representing reflections
    for (int i = 1; i <= 4; ++i)
    {
        auto radius = iconBounds.getWidth() * 0.1f * i;
        auto alpha = 1.0f - (i - 1) * 0.2f; // Fade out
        auto ringStroke = stroke * (1.0f - (i - 1) * 0.15f); // Get thinner

        g.setColour(color.withAlpha(alpha));
        g.drawEllipse(centre.x - radius, centre.y - radius, radius * 2, radius * 2, ringStroke);
    }

    // Decay envelope overlay
    juce::Path decayEnvelope;
    auto envelopeY = iconBounds.getBottom() - iconBounds.getHeight() * 0.2f;
    auto envelopeWidth = iconBounds.getWidth() * 0.7f;
    auto envelopeStart = iconBounds.getX() + (iconBounds.getWidth() - envelopeWidth) * 0.5f;

    decayEnvelope.startNewSubPath(envelopeStart, envelopeY);

    // Exponential decay
    for (int i = 1; i <= 10; ++i)
    {
        auto ratio = i / 10.0f;
        auto x = envelopeStart + ratio * envelopeWidth;
        auto decay = std::exp(-ratio * 3.0f); // Exponential decay
        auto y = envelopeY - decay * iconBounds.getHeight() * 0.15f;
        decayEnvelope.lineTo(x, y);
    }

    g.setColour(color.withAlpha(0.6f));
    g.strokePath(decayEnvelope, createStroke(stroke * 0.8f));
}

void FancyIconPack::drawDelay(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color)
{
    auto iconBounds = bounds;
    auto stroke = getOptimalStrokeWidth(iconBounds);

    // Delay line representation with multiple taps
    auto lineY = iconBounds.getCentreY();
    auto lineLength = iconBounds.getWidth() * 0.8f;
    auto lineStart = iconBounds.getX() + (iconBounds.getWidth() - lineLength) * 0.5f;

    // Main delay line
    g.setColour(color);
    g.drawLine(lineStart, lineY, lineStart + lineLength, lineY, stroke * 1.5f);

    // Input pulse
    auto inputX = lineStart;
    auto pulseHeight = iconBounds.getHeight() * 0.3f;
    g.fillRoundedRectangle(inputX - stroke, lineY - pulseHeight * 0.5f, stroke * 2, pulseHeight, stroke);

    // Delay taps with decreasing amplitude
    auto tapPositions = {0.3f, 0.6f, 0.9f};
    auto tapAlphas = {0.8f, 0.6f, 0.4f};
    auto tapHeights = {0.8f, 0.6f, 0.4f};

    auto tapIt = tapPositions.begin();
    auto alphaIt = tapAlphas.begin();
    auto heightIt = tapHeights.begin();

    while (tapIt != tapPositions.end())
    {
        auto tapX = lineStart + *tapIt * lineLength;
        auto tapHeight = pulseHeight * *heightIt;
        auto alpha = *alphaIt;

        g.setColour(color.withAlpha(alpha));
        g.fillRoundedRectangle(tapX - stroke * 0.8f, lineY - tapHeight * 0.5f, stroke * 1.6f, tapHeight, stroke * 0.8f);

        // Tap output line
        g.drawLine(tapX, lineY + tapHeight * 0.5f, tapX, lineY + iconBounds.getHeight() * 0.25f, stroke);

        ++tapIt;
        ++alphaIt;
        ++heightIt;
    }

    // Time arrow
    auto arrowY = iconBounds.getY() + iconBounds.getHeight() * 0.8f;
    g.setColour(color.withAlpha(0.7f));
    g.drawLine(lineStart, arrowY, lineStart + lineLength * 0.7f, arrowY, stroke);

    // Arrow head
    auto arrowHeadX = lineStart + lineLength * 0.7f;
    auto arrowSize = stroke * 2;
    g.drawLine(arrowHeadX, arrowY, arrowHeadX - arrowSize, arrowY - arrowSize * 0.5f, stroke);
    g.drawLine(arrowHeadX, arrowY, arrowHeadX - arrowSize, arrowY + arrowSize * 0.5f, stroke);
}

void FancyIconPack::drawPingPongDelay(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color)
{
    auto iconBounds = bounds;
    auto stroke = getOptimalStrokeWidth(iconBounds);

    // Ping pong delay - stereo bouncing pattern
    auto centerY = iconBounds.getCentreY();
    auto leftChannel = iconBounds.removeFromLeft(iconBounds.getWidth() * 0.45f);
    auto rightChannel = iconBounds.removeFromRight(iconBounds.getWidth() / 0.55f * 0.45f);
    auto centerGap = iconBounds; // remaining center area

    // Input signal (center)
    auto inputX = centerGap.getCentreX();
    auto inputRadius = stroke * 1.5f;
    g.setColour(color);
    g.fillEllipse(inputX - inputRadius, centerY - inputRadius, inputRadius * 2, inputRadius * 2);

    // Ping pong bounces with decreasing amplitude
    auto bounceCount = 4;
    auto bounceSpacing = iconBounds.getHeight() * 0.15f;

    for (int i = 0; i < bounceCount; ++i)
    {
        auto bounceY = centerY + (i + 1) * bounceSpacing;
        auto alpha = 1.0f - (i * 0.2f); // Decreasing volume
        auto bounceRadius = inputRadius * alpha;

        g.setColour(color.withAlpha(alpha));

        if (i % 2 == 0)
        {
            // Left channel bounce
            auto leftX = leftChannel.getCentreX();
            g.fillEllipse(leftX - bounceRadius, bounceY - bounceRadius, bounceRadius * 2, bounceRadius * 2);

            // Connection line from previous bounce
            if (i == 0)
            {
                // From input
                g.drawLine(inputX, centerY + inputRadius, leftX, bounceY - bounceRadius, stroke * alpha);
            }
            else
            {
                // From right channel
                auto prevBounceY = centerY + i * bounceSpacing;
                auto rightX = rightChannel.getCentreX();

                // Curved connection showing ping pong
                juce::Path bouncePath;
                bouncePath.startNewSubPath(rightX, prevBounceY);
                bouncePath.quadraticTo(inputX, prevBounceY + bounceSpacing * 0.5f, leftX, bounceY);
                g.strokePath(bouncePath, createStroke(stroke * alpha * 0.8f));
            }
        }
        else
        {
            // Right channel bounce
            auto rightX = rightChannel.getCentreX();
            g.fillEllipse(rightX - bounceRadius, bounceY - bounceRadius, bounceRadius * 2, bounceRadius * 2);

            // Connection from left channel
            auto prevBounceY = centerY + i * bounceSpacing;
            auto leftX = leftChannel.getCentreX();

            // Curved connection showing ping pong
            juce::Path bouncePath;
            bouncePath.startNewSubPath(leftX, prevBounceY);
            bouncePath.quadraticTo(inputX, prevBounceY + bounceSpacing * 0.5f, rightX, bounceY);
            g.strokePath(bouncePath, createStroke(stroke * alpha * 0.8f));
        }
    }

    // L/R channel indicators
    g.setColour(color);
    g.setFont(juce::Font(iconBounds.getHeight() * 0.12f, juce::Font::bold));

    auto labelY = iconBounds.getY() + iconBounds.getHeight() * 0.1f;
    g.drawText("L", juce::Rectangle<float>(leftChannel.getX(), labelY, leftChannel.getWidth(), iconBounds.getHeight() * 0.12f),
               juce::Justification::centred);
    g.drawText("R", juce::Rectangle<float>(rightChannel.getX(), labelY, rightChannel.getWidth(), iconBounds.getHeight() * 0.12f),
               juce::Justification::centred);

    // Delay time indicators
    g.setColour(color.withAlpha(0.6f));
    g.setFont(juce::Font(iconBounds.getHeight() * 0.08f));

    for (int i = 0; i < bounceCount && i < 3; ++i)
    {
        auto bounceY = centerY + (i + 1) * bounceSpacing;
        auto alpha = 1.0f - (i * 0.2f); // Same calculation as above
        auto bounceRadius = inputRadius * alpha; // Recalculate bounceRadius for this scope
        auto delayTime = juce::String((i + 1) * 125) + "ms"; // Example delay times

        auto timeArea = juce::Rectangle<int>(static_cast<int>(centerGap.getX()),
                                           static_cast<int>(bounceY + bounceRadius + stroke),
                                           static_cast<int>(centerGap.getWidth()),
                                           static_cast<int>(iconBounds.getHeight() * 0.08f));
        g.drawText(delayTime, timeArea, juce::Justification::centred);
    }

    // Movement arrows showing ping pong motion
    g.setColour(color.withAlpha(0.5f));
    auto arrowSize = stroke * 1.2f;

    for (int i = 0; i < 2; ++i)
    {
        auto arrowY = centerY + (i + 1.5f) * bounceSpacing;

        // Left-to-right arrow
        if (i % 2 == 0)
        {
            auto arrowStartX = leftChannel.getRight();
            auto arrowEndX = rightChannel.getX();
            auto arrowMidX = (arrowStartX + arrowEndX) * 0.5f;

            g.drawLine(arrowStartX, arrowY, arrowEndX, arrowY, stroke * 0.6f);

            // Arrow head
            juce::Path arrowHead;
            arrowHead.startNewSubPath(arrowEndX - arrowSize, arrowY - arrowSize * 0.5f);
            arrowHead.lineTo(arrowEndX, arrowY);
            arrowHead.lineTo(arrowEndX - arrowSize, arrowY + arrowSize * 0.5f);

            g.strokePath(arrowHead, createStroke(stroke * 0.6f, juce::PathStrokeType::mitered, juce::PathStrokeType::butt));
        }
        else
        {
            // Right-to-left arrow
            auto arrowStartX = rightChannel.getX();
            auto arrowEndX = leftChannel.getRight();

            g.drawLine(arrowStartX, arrowY, arrowEndX, arrowY, stroke * 0.6f);

            // Arrow head
            juce::Path arrowHead;
            arrowHead.startNewSubPath(arrowEndX + arrowSize, arrowY - arrowSize * 0.5f);
            arrowHead.lineTo(arrowEndX, arrowY);
            arrowHead.lineTo(arrowEndX + arrowSize, arrowY + arrowSize * 0.5f);

            g.strokePath(arrowHead, createStroke(stroke * 0.6f, juce::PathStrokeType::mitered, juce::PathStrokeType::butt));
        }
    }
}

void FancyIconPack::drawChorus(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color)
{
    auto iconBounds = bounds;
    auto stroke = getOptimalStrokeWidth(iconBounds);

    // Multiple modulated sine waves to show chorus effect
    auto waveY = iconBounds.getCentreY();
    auto amplitude = iconBounds.getHeight() * 0.2f;
    auto points = 24;

    // Draw 3 chorus voices with slight modulation differences
    for (int voice = 0; voice < 3; ++voice)
    {
        juce::Path chorusWave;
        auto voiceOffset = (voice - 1) * amplitude * 0.2f;
        auto phaseOffset = voice * 0.15f;
        auto modulationRate = 0.3f + voice * 0.1f; // Different modulation rates
        auto alpha = 1.0f - voice * 0.25f;

        chorusWave.startNewSubPath(iconBounds.getX(), waveY + voiceOffset);

        for (int i = 1; i <= points; ++i)
        {
            auto x = iconBounds.getX() + (i / static_cast<float>(points)) * iconBounds.getWidth();
            auto phase = (i / static_cast<float>(points)) * juce::MathConstants<float>::twoPi * 1.2f + phaseOffset;

            // Add chorus modulation (pitch/timing variation)
            auto modulation = std::sin((i / static_cast<float>(points)) * juce::MathConstants<float>::twoPi * modulationRate) * 0.1f;
            auto modulatedPhase = phase + modulation;

            auto y = waveY + voiceOffset + std::sin(modulatedPhase) * amplitude;
            chorusWave.lineTo(x, y);
        }

        g.setColour(color.withAlpha(alpha));
        g.strokePath(chorusWave, createStroke(stroke * (1.0f - voice * 0.15f)));
    }

    // Modulation indicator (LFO-like wave at bottom)
    juce::Path modWave;
    auto modY = iconBounds.getBottom() - iconBounds.getHeight() * 0.2f;
    auto modAmplitude = iconBounds.getHeight() * 0.08f;

    modWave.startNewSubPath(iconBounds.getX(), modY);

    for (int i = 1; i <= 12; ++i)
    {
        auto x = iconBounds.getX() + (i / 12.0f) * iconBounds.getWidth();
        auto phase = (i / 12.0f) * juce::MathConstants<float>::twoPi * 0.5f;
        auto y = modY + std::sin(phase) * modAmplitude;
        modWave.lineTo(x, y);
    }

    g.setColour(color.withAlpha(0.6f));
    g.strokePath(modWave, createStroke(stroke * 0.8f));

    // "CHORUS" label
    g.setColour(color.withAlpha(0.8f));
    g.setFont(juce::Font(iconBounds.getHeight() * 0.1f, juce::Font::bold));
    g.drawText("CHORUS", juce::Rectangle<float>(iconBounds.getX(), iconBounds.getY(),
                                              iconBounds.getWidth(), iconBounds.getHeight() * 0.12f),
               juce::Justification::centred);
}

void FancyIconPack::drawFlanger(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color)
{
    auto iconBounds = bounds;
    auto stroke = getOptimalStrokeWidth(iconBounds);

    // Flanging sweep pattern - comb filtering visualization
    auto centerY = iconBounds.getCentreY();
    auto sweepHeight = iconBounds.getHeight() * 0.6f;

    // Main signal path
    g.setColour(color);
    g.drawLine(iconBounds.getX(), centerY, iconBounds.getRight(), centerY, stroke);

    // Delayed signal path with comb filtering pattern
    juce::Path combPattern;
    auto delayedY = centerY + iconBounds.getHeight() * 0.15f;
    combPattern.startNewSubPath(iconBounds.getX(), delayedY);

    // Create comb filter response (series of peaks and nulls)
    auto points = 16;
    for (int i = 1; i <= points; ++i)
    {
        auto x = iconBounds.getX() + (i / static_cast<float>(points)) * iconBounds.getWidth();
        auto freq = i / static_cast<float>(points);

        // Comb filter response - alternating peaks and nulls
        auto combResponse = std::abs(std::sin(freq * juce::MathConstants<float>::pi * 4.0f));
        auto y = delayedY - combResponse * iconBounds.getHeight() * 0.25f;

        combPattern.lineTo(x, y);
    }

    g.setColour(color.withAlpha(0.7f));
    g.strokePath(combPattern, createStroke(stroke * 0.9f));

    // Sweep indicator (moving delay time)
    auto sweepX = iconBounds.getX() + iconBounds.getWidth() * 0.6f; // Current sweep position

    // Sweep line
    g.setColour(color.withAlpha(0.8f));
    g.drawLine(sweepX, iconBounds.getY() + iconBounds.getHeight() * 0.2f,
               sweepX, iconBounds.getBottom() - iconBounds.getHeight() * 0.2f, stroke * 1.2f);

    // Sweep direction arrows
    juce::Path sweepArrow;
    sweepArrow.startNewSubPath(sweepX, iconBounds.getY() + iconBounds.getHeight() * 0.15f);
    sweepArrow.lineTo(sweepX - stroke * 1.5f, iconBounds.getY() + iconBounds.getHeight() * 0.25f);
    sweepArrow.lineTo(sweepX + stroke * 1.5f, iconBounds.getY() + iconBounds.getHeight() * 0.25f);
    sweepArrow.closeSubPath();

    g.fillPath(sweepArrow);

    // Feedback path (curved arrow)
    juce::Path feedbackPath;
    auto feedbackStart = iconBounds.getRight() - iconBounds.getWidth() * 0.2f;
    auto feedbackMid = iconBounds.getX() + iconBounds.getWidth() * 0.3f;

    feedbackPath.startNewSubPath(feedbackStart, centerY);
    feedbackPath.quadraticTo(feedbackStart + iconBounds.getWidth() * 0.1f, centerY - iconBounds.getHeight() * 0.2f,
                            feedbackMid, centerY - iconBounds.getHeight() * 0.15f);
    feedbackPath.quadraticTo(feedbackMid - iconBounds.getWidth() * 0.1f, centerY,
                            feedbackMid, centerY);

    g.setColour(color.withAlpha(0.6f));
    g.strokePath(feedbackPath, createStroke(stroke * 0.8f));

    // "FLANGE" label
    g.setColour(color.withAlpha(0.8f));
    g.setFont(juce::Font(iconBounds.getHeight() * 0.1f, juce::Font::bold));
    g.drawText("FLANGE", juce::Rectangle<float>(iconBounds.getX(), iconBounds.getBottom() - iconBounds.getHeight() * 0.15f,
                                              iconBounds.getWidth(), iconBounds.getHeight() * 0.12f),
               juce::Justification::centred);
}

void FancyIconPack::drawPhaser(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color)
{
    auto iconBounds = bounds;
    auto stroke = getOptimalStrokeWidth(iconBounds);

    // Phase shifting visualization - multiple all-pass stages
    auto centerY = iconBounds.getCentreY();
    auto stageWidth = iconBounds.getWidth() / 4.0f;

    // Draw 4 all-pass filter stages
    for (int stage = 0; stage < 4; ++stage)
    {
        auto stageX = iconBounds.getX() + stage * stageWidth;
        auto stageCenterX = stageX + stageWidth * 0.5f;

        // All-pass filter symbol (circle with cross)
        auto radius = stageWidth * 0.15f;

        g.setColour(color.withAlpha(0.3f));
        g.fillEllipse(stageCenterX - radius, centerY - radius, radius * 2.0f, radius * 2.0f);

        g.setColour(color);
        g.drawEllipse(stageCenterX - radius, centerY - radius, radius * 2.0f, radius * 2.0f, stroke * 0.8f);

        // Cross inside circle (all-pass symbol)
        g.drawLine(stageCenterX - radius * 0.6f, centerY - radius * 0.6f,
                   stageCenterX + radius * 0.6f, centerY + radius * 0.6f, stroke * 0.7f);
        g.drawLine(stageCenterX - radius * 0.6f, centerY + radius * 0.6f,
                   stageCenterX + radius * 0.6f, centerY - radius * 0.6f, stroke * 0.7f);

        // Connection lines between stages
        if (stage < 3)
        {
            g.setColour(color.withAlpha(0.7f));
            g.drawLine(stageCenterX + radius, centerY,
                       stageX + stageWidth + stageWidth * 0.5f - radius, centerY, stroke * 0.8f);
        }

        // Phase shift indicators (curved arrows showing phase change)
        if (stage > 0)
        {
            juce::Path phaseShift;
            auto arrowY = centerY - iconBounds.getHeight() * 0.25f;
            auto arrowRadius = juce::jmax(stageWidth * 0.2f, stroke * 2.0f); // Ensure minimum radius

            // Only draw if we have reasonable dimensions
            if (arrowRadius > stroke && iconBounds.getHeight() > stroke * 4.0f)
            {
                phaseShift.addCentredArc(stageCenterX, arrowY, arrowRadius, arrowRadius,
                                       0.0f, -juce::MathConstants<float>::pi * 0.5f, juce::MathConstants<float>::pi * 0.5f, true);

                g.setColour(color.withAlpha(0.6f));
                g.strokePath(phaseShift, createStroke(stroke * 0.7f));

                // Arrow head with bounds checking
                auto arrowEndX = stageCenterX + arrowRadius * 0.7f;
                auto arrowEndY = arrowY + arrowRadius * 0.7f;

                // Ensure arrow head coordinates are finite and reasonable
                if (std::isfinite(arrowEndX) && std::isfinite(arrowEndY) &&
                    arrowEndX > iconBounds.getX() && arrowEndX < iconBounds.getRight() &&
                    arrowEndY > iconBounds.getY() && arrowEndY < iconBounds.getBottom())
                {
                    juce::Path arrowHead;
                    auto arrowSize = juce::jmax(stroke, stroke * 1.0f); // Ensure minimum arrow size

                    arrowHead.startNewSubPath(arrowEndX, arrowEndY);
                    arrowHead.lineTo(arrowEndX - arrowSize, arrowEndY - arrowSize * 1.5f);
                    arrowHead.lineTo(arrowEndX + arrowSize, arrowEndY - arrowSize * 0.5f);
                    arrowHead.closeSubPath();

                    g.fillPath(arrowHead);
                }
            }
        }
    }

    // LFO modulation indicator at bottom
    juce::Path lfoWave;
    auto lfoY = iconBounds.getBottom() - iconBounds.getHeight() * 0.2f;
    auto lfoAmplitude = iconBounds.getHeight() * 0.08f;

    lfoWave.startNewSubPath(iconBounds.getX(), lfoY);

    for (int i = 1; i <= 16; ++i)
    {
        auto x = iconBounds.getX() + (i / 16.0f) * iconBounds.getWidth();
        auto phase = (i / 16.0f) * juce::MathConstants<float>::twoPi * 0.75f;
        auto y = lfoY + std::sin(phase) * lfoAmplitude;
        lfoWave.lineTo(x, y);
    }

    g.setColour(color.withAlpha(0.6f));
    g.strokePath(lfoWave, createStroke(stroke * 0.8f));

    // "PHASE" label
    g.setColour(color.withAlpha(0.8f));
    g.setFont(juce::Font(iconBounds.getHeight() * 0.09f, juce::Font::bold));
    g.drawText("PHASE", juce::Rectangle<float>(iconBounds.getX(), iconBounds.getY(),
                                             iconBounds.getWidth(), iconBounds.getHeight() * 0.12f),
               juce::Justification::centred);
}

void FancyIconPack::drawGranular(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color)
{
    auto iconBounds = bounds;
    auto stroke = getOptimalStrokeWidth(iconBounds);

    // Granular synthesis visualization - scattered particles/grains
    auto centerX = iconBounds.getCentreX();
    auto centerY = iconBounds.getCentreY();
    auto maxRadius = juce::jmin(iconBounds.getWidth(), iconBounds.getHeight()) * 0.4f;

    // Source waveform (top)
    auto sourceArea = juce::Rectangle<float>(iconBounds.getX(), iconBounds.getY(),
                                           iconBounds.getWidth(), iconBounds.getHeight() * 0.25f);

    juce::Path sourceWave;
    auto sourceY = sourceArea.getCentreY();
    auto sourceAmplitude = sourceArea.getHeight() * 0.3f;
    auto points = 8;

    sourceWave.startNewSubPath(sourceArea.getX(), sourceY);
    for (int i = 1; i <= points; ++i)
    {
        auto x = sourceArea.getX() + (i / static_cast<float>(points)) * sourceArea.getWidth();
        auto phase = (i / static_cast<float>(points)) * juce::MathConstants<float>::twoPi * 1.5f;
        auto amp = std::sin(phase) * sourceAmplitude;
        sourceWave.lineTo(x, sourceY + amp);
    }

    g.setColour(color.withAlpha(0.6f));
    g.strokePath(sourceWave, createStroke(stroke));

    // Granular particles/grains
    juce::Random random(456); // Fixed seed for consistent appearance

    for (int i = 0; i < 16; ++i)
    {
        // Random position within circular area
        auto angle = random.nextFloat() * juce::MathConstants<float>::twoPi;
        auto radius = random.nextFloat() * maxRadius;
        auto x = centerX + std::cos(angle) * radius;
        auto y = centerY + std::sin(angle) * radius * 0.6f; // Flatten vertically

        // Grain size varies
        auto grainSize = (0.5f + random.nextFloat() * 0.8f) * stroke * 2;
        auto alpha = 0.4f + random.nextFloat() * 0.6f;

        g.setColour(color.withAlpha(alpha));

        // Some grains are circles, some are small waveforms
        if (i % 3 == 0)
        {
            // Mini waveform grain
            juce::Path grainWave;
            auto grainWidth = grainSize * 3;
            auto grainHeight = grainSize;

            grainWave.startNewSubPath(x - grainWidth * 0.5f, y);
            for (int j = 1; j <= 4; ++j)
            {
                auto grainX = x - grainWidth * 0.5f + (j / 4.0f) * grainWidth;
                auto grainPhase = (j / 4.0f) * juce::MathConstants<float>::twoPi * 2;
                auto grainAmp = std::sin(grainPhase) * grainHeight * 0.4f;
                grainWave.lineTo(grainX, y + grainAmp);
            }

            g.strokePath(grainWave, createStroke(stroke * 0.6f));
        }
        else
        {
            // Circular grain
            g.fillEllipse(x - grainSize * 0.5f, y - grainSize * 0.5f, grainSize, grainSize);
        }
    }

    // Processing arrows showing grain extraction
    g.setColour(color.withAlpha(0.7f));
    auto arrowCount = 3;
    for (int i = 0; i < arrowCount; ++i)
    {
        auto arrowX = sourceArea.getX() + (i + 1) * sourceArea.getWidth() / (arrowCount + 1);
        auto arrowStartY = sourceArea.getBottom();
        auto arrowEndY = centerY - maxRadius * 0.3f;

        // Arrow line
        g.drawLine(arrowX, arrowStartY, arrowX, arrowEndY, stroke * 0.8f);

        // Arrow head
        auto arrowSize = stroke * 1.2f;
        juce::Path arrowHead;
        arrowHead.startNewSubPath(arrowX - arrowSize, arrowEndY + arrowSize);
        arrowHead.lineTo(arrowX, arrowEndY);
        arrowHead.lineTo(arrowX + arrowSize, arrowEndY + arrowSize);

        g.strokePath(arrowHead, createStroke(stroke * 0.8f, juce::PathStrokeType::mitered, juce::PathStrokeType::butt));
    }

    // "GRAIN" label
    g.setColour(color);
    g.setFont(juce::Font(iconBounds.getHeight() * 0.12f, juce::Font::bold));
    auto labelArea = juce::Rectangle<float>(iconBounds.getX(), iconBounds.getBottom() - iconBounds.getHeight() * 0.15f,
                                          iconBounds.getWidth(), iconBounds.getHeight() * 0.12f);
    g.drawText("GRAIN", labelArea, juce::Justification::centred);
}

void FancyIconPack::drawFreeze(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color)
{
    auto iconBounds = bounds;
    auto stroke = getOptimalStrokeWidth(iconBounds);

    // Frozen/held audio state - crystalline/frozen waveform
    auto centerX = iconBounds.getCentreX();
    auto centerY = iconBounds.getCentreY();

    // Main frozen waveform
    auto waveArea = iconBounds.reduced(iconBounds.getWidth() * 0.1f, iconBounds.getHeight() * 0.2f);

    juce::Path frozenWave;
    auto waveY = waveArea.getCentreY();
    auto amplitude = waveArea.getHeight() * 0.3f;
    auto points = 10;

    frozenWave.startNewSubPath(waveArea.getX(), waveY);
    for (int i = 1; i <= points; ++i)
    {
        auto x = waveArea.getX() + (i / static_cast<float>(points)) * waveArea.getWidth();
        auto phase = (i / static_cast<float>(points)) * juce::MathConstants<float>::twoPi * 1.5f;
        auto amp = std::sin(phase) * amplitude;
        frozenWave.lineTo(x, waveY + amp);
    }

    g.setColour(color);
    g.strokePath(frozenWave, createStroke(stroke * 1.2f));

    // Ice crystal effect - geometric shapes overlaying the waveform
    g.setColour(color.withAlpha(0.5f));

    // Crystal formations at wave peaks
    for (int i = 0; i < 4; ++i)
    {
        auto crystalX = waveArea.getX() + (i + 1) * waveArea.getWidth() / 5.0f;
        auto phase = ((i + 1) / 5.0f) * juce::MathConstants<float>::twoPi * 1.5f;
        auto crystalY = waveY + std::sin(phase) * amplitude;
        auto crystalSize = stroke * 3;

        // Diamond/crystal shape
        juce::Path crystal;
        crystal.startNewSubPath(crystalX, crystalY - crystalSize);
        crystal.lineTo(crystalX + crystalSize * 0.7f, crystalY);
        crystal.lineTo(crystalX, crystalY + crystalSize);
        crystal.lineTo(crystalX - crystalSize * 0.7f, crystalY);
        crystal.closeSubPath();

        g.strokePath(crystal, createStroke(stroke * 0.8f));

        // Inner crystal lines
        g.drawLine(crystalX - crystalSize * 0.7f, crystalY, crystalX + crystalSize * 0.7f, crystalY, stroke * 0.6f);
    }

    // Freeze indicator symbols (snowflakes)
    auto snowflakeCount = 3;
    for (int i = 0; i < snowflakeCount; ++i)
    {
        auto snowX = iconBounds.getX() + (i + 1) * iconBounds.getWidth() / (snowflakeCount + 1);
        auto snowY = iconBounds.getY() + iconBounds.getHeight() * 0.15f;
        auto snowSize = stroke * 2;

        // Simple snowflake (6-pointed star)
        g.setColour(color.withAlpha(0.6f));

        // Main axes
        g.drawLine(snowX - snowSize, snowY, snowX + snowSize, snowY, stroke * 0.6f);
        g.drawLine(snowX, snowY - snowSize, snowX, snowY + snowSize, stroke * 0.6f);

        // Diagonal axes
        auto diagSize = snowSize * 0.7f;
        g.drawLine(snowX - diagSize, snowY - diagSize, snowX + diagSize, snowY + diagSize, stroke * 0.6f);
        g.drawLine(snowX - diagSize, snowY + diagSize, snowX + diagSize, snowY - diagSize, stroke * 0.6f);

        // Small branches
        auto branchSize = snowSize * 0.3f;
        for (int angle = 0; angle < 6; ++angle)
        {
            auto angleRad = angle * juce::MathConstants<float>::pi / 3.0f;
            auto endX = snowX + std::cos(angleRad) * snowSize;
            auto endY = snowY + std::sin(angleRad) * snowSize;

            // Small branches at 45 degrees
            auto branchX1 = endX + std::cos(angleRad + juce::MathConstants<float>::pi * 0.25f) * branchSize;
            auto branchY1 = endY + std::sin(angleRad + juce::MathConstants<float>::pi * 0.25f) * branchSize;
            auto branchX2 = endX + std::cos(angleRad - juce::MathConstants<float>::pi * 0.25f) * branchSize;
            auto branchY2 = endY + std::sin(angleRad - juce::MathConstants<float>::pi * 0.25f) * branchSize;

            g.drawLine(endX, endY, branchX1, branchY1, stroke * 0.4f);
            g.drawLine(endX, endY, branchX2, branchY2, stroke * 0.4f);
        }
    }

    // "FREEZE" label
    g.setColour(color);
    g.setFont(juce::Font(iconBounds.getHeight() * 0.12f, juce::Font::bold));
    auto labelArea = juce::Rectangle<float>(iconBounds.getX(), iconBounds.getBottom() - iconBounds.getHeight() * 0.15f,
                                          iconBounds.getWidth(), iconBounds.getHeight() * 0.12f);
    g.drawText("FREEZE", labelArea, juce::Justification::centred);

    // Frozen state indicator (ice block effect around waveform)
    g.setColour(color.withAlpha(0.15f));
    auto iceBlock = waveArea.expanded(stroke * 2);
    g.fillRoundedRectangle(iceBlock, 3.0f);
    g.setColour(color.withAlpha(0.3f));
    g.drawRoundedRectangle(iceBlock, 3.0f, stroke * 0.6f);
}

// Stereo and Spatial
// ============================================================================

void FancyIconPack::drawStereo(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color)
{
    auto iconBounds = bounds;
    auto stroke = getOptimalStrokeWidth(iconBounds);

    // L/R stereo indicator with waveforms
    auto leftArea = iconBounds.removeFromLeft(iconBounds.getWidth() * 0.45f);
    auto rightArea = iconBounds.removeFromRight(iconBounds.getWidth() / 0.55f * 0.45f);

    // Left channel waveform
    juce::Path leftWave;
    auto leftY = leftArea.getCentreY();
    auto leftAmplitude = leftArea.getHeight() * 0.3f;
    auto points = 8;

    leftWave.startNewSubPath(leftArea.getX(), leftY);
    for (int i = 1; i <= points; ++i)
    {
        auto x = leftArea.getX() + (i / static_cast<float>(points)) * leftArea.getWidth();
        auto phase = (i / static_cast<float>(points)) * juce::MathConstants<float>::twoPi * 1.5f;
        auto amp = std::sin(phase) * leftAmplitude;
        leftWave.lineTo(x, leftY + amp);
    }

    // Right channel waveform (slightly out of phase)
    juce::Path rightWave;
    auto rightY = rightArea.getCentreY();
    auto rightAmplitude = rightArea.getHeight() * 0.3f;

    rightWave.startNewSubPath(rightArea.getX(), rightY);
    for (int i = 1; i <= points; ++i)
    {
        auto x = rightArea.getX() + (i / static_cast<float>(points)) * rightArea.getWidth();
        auto phase = (i / static_cast<float>(points)) * juce::MathConstants<float>::twoPi * 1.5f + 0.5f; // Phase offset
        auto amp = std::sin(phase) * rightAmplitude;
        rightWave.lineTo(x, rightY + amp);
    }

    g.setColour(color);
    g.strokePath(leftWave, createStroke(stroke));
    g.strokePath(rightWave, createStroke(stroke));

    // L/R labels
    g.setFont(juce::Font(iconBounds.getHeight() * 0.25f, juce::Font::bold));

    auto labelY = iconBounds.getBottom() - iconBounds.getHeight() * 0.3f;
    g.drawText("L", juce::Rectangle<float>(leftArea.getX(), labelY, leftArea.getWidth(), iconBounds.getHeight() * 0.25f),
               juce::Justification::centred);
    g.drawText("R", juce::Rectangle<float>(rightArea.getX(), labelY, rightArea.getWidth(), iconBounds.getHeight() * 0.25f),
               juce::Justification::centred);

    // Center divider
    g.setColour(color.withAlpha(0.3f));
    auto centerX = iconBounds.getCentreX();
    g.drawLine(centerX, iconBounds.getY(), centerX, iconBounds.getBottom() - iconBounds.getHeight() * 0.3f, stroke * 0.5f);
}

void FancyIconPack::drawMono(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color)
{
    auto iconBounds = bounds;
    auto stroke = getOptimalStrokeWidth(iconBounds);

    // Single centered waveform
    auto waveArea = iconBounds.removeFromTop(iconBounds.getHeight() * 0.6f);

    juce::Path monoWave;
    auto waveY = waveArea.getCentreY();
    auto amplitude = waveArea.getHeight() * 0.4f;
    auto points = 10;

    monoWave.startNewSubPath(waveArea.getX(), waveY);
    for (int i = 1; i <= points; ++i)
    {
        auto x = waveArea.getX() + (i / static_cast<float>(points)) * waveArea.getWidth();
        auto phase = (i / static_cast<float>(points)) * juce::MathConstants<float>::twoPi * 1.5f;
        auto amp = std::sin(phase) * amplitude;
        monoWave.lineTo(x, waveY + amp);
    }

    g.setColour(color);
    g.strokePath(monoWave, createStroke(stroke * 1.2f)); // Thicker for mono

    // Center indicator circle
    auto centerRadius = iconBounds.getWidth() * 0.08f;
    auto centerPoint = waveArea.getCentre();
    g.setColour(color.withAlpha(0.7f));
    g.fillEllipse(centerPoint.x - centerRadius, centerPoint.y - centerRadius, centerRadius * 2, centerRadius * 2);

    // "MONO" label
    g.setColour(color);
    g.setFont(juce::Font(iconBounds.getHeight() * 0.2f, juce::Font::bold));
    auto labelArea = iconBounds.removeFromBottom(iconBounds.getHeight());
    g.drawText("MONO", labelArea, juce::Justification::centred);
}

void FancyIconPack::drawWidth(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color)
{
    auto iconBounds = bounds;
    auto stroke = getOptimalStrokeWidth(iconBounds);

    // Stereo width visualization - expanding/contracting arrows
    auto centerX = iconBounds.getCentreX();
    auto centerY = iconBounds.getCentreY();
    auto arrowLength = iconBounds.getWidth() * 0.3f;
    auto arrowSize = stroke * 2.5f;

    g.setColour(color);

    // Left arrow (pointing out)
    juce::Path leftArrow;
    leftArrow.startNewSubPath(centerX - arrowLength, centerY);
    leftArrow.lineTo(centerX - arrowLength - arrowSize, centerY - arrowSize);
    leftArrow.lineTo(centerX - arrowLength - arrowSize * 0.5f, centerY);
    leftArrow.lineTo(centerX - arrowLength - arrowSize, centerY + arrowSize);
    leftArrow.closeSubPath();

    // Right arrow (pointing out)
    juce::Path rightArrow;
    rightArrow.startNewSubPath(centerX + arrowLength, centerY);
    rightArrow.lineTo(centerX + arrowLength + arrowSize, centerY - arrowSize);
    rightArrow.lineTo(centerX + arrowLength + arrowSize * 0.5f, centerY);
    rightArrow.lineTo(centerX + arrowLength + arrowSize, centerY + arrowSize);
    rightArrow.closeSubPath();

    g.fillPath(leftArrow);
    g.fillPath(rightArrow);

    // Center lines connecting to arrows
    g.drawLine(centerX - arrowLength * 0.3f, centerY, centerX - arrowLength, centerY, stroke);
    g.drawLine(centerX + arrowLength * 0.3f, centerY, centerX + arrowLength, centerY, stroke);

    // Center stereo field visualization
    auto fieldHeight = iconBounds.getHeight() * 0.4f;
    auto fieldWidth = iconBounds.getWidth() * 0.2f;

    // Stereo field ellipse
    g.setColour(color.withAlpha(0.3f));
    g.fillEllipse(centerX - fieldWidth * 0.5f, centerY - fieldHeight * 0.5f, fieldWidth, fieldHeight);

    g.setColour(color);
    g.drawEllipse(centerX - fieldWidth * 0.5f, centerY - fieldHeight * 0.5f, fieldWidth, fieldHeight, stroke);

    // "WIDTH" label
    g.setFont(juce::Font(iconBounds.getHeight() * 0.15f, juce::Font::bold));
    auto labelArea = juce::Rectangle<float>(iconBounds.getX(), iconBounds.getBottom() - iconBounds.getHeight() * 0.2f,
                                          iconBounds.getWidth(), iconBounds.getHeight() * 0.15f);
    g.drawText("WIDTH", labelArea, juce::Justification::centred);
}

void FancyIconPack::drawBalance(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color)
{
    auto iconBounds = bounds;
    auto stroke = getOptimalStrokeWidth(iconBounds);

    // Balance control - scale/balance beam
    auto centerX = iconBounds.getCentreX();
    auto centerY = iconBounds.getCentreY();
    auto beamLength = iconBounds.getWidth() * 0.7f;
    auto beamY = centerY - iconBounds.getHeight() * 0.1f;

    g.setColour(color);

    // Balance beam
    g.drawLine(centerX - beamLength * 0.5f, beamY, centerX + beamLength * 0.5f, beamY, stroke * 1.5f);

    // Fulcrum (triangle)
    auto fulcrumSize = iconBounds.getHeight() * 0.15f;
    juce::Path fulcrum;
    fulcrum.startNewSubPath(centerX - fulcrumSize * 0.5f, beamY + stroke);
    fulcrum.lineTo(centerX, beamY + stroke + fulcrumSize);
    fulcrum.lineTo(centerX + fulcrumSize * 0.5f, beamY + stroke);
    fulcrum.closeSubPath();

    g.fillPath(fulcrum);

    // Left and Right weights (slightly unbalanced)
    auto weightSize = iconBounds.getHeight() * 0.2f;
    auto leftWeightX = centerX - beamLength * 0.35f;
    auto rightWeightX = centerX + beamLength * 0.35f;
    auto leftWeightY = beamY - weightSize - stroke;
    auto rightWeightY = beamY - weightSize * 0.8f - stroke; // Slightly different height

    // Left weight (L)
    g.fillRoundedRectangle(leftWeightX - weightSize * 0.4f, leftWeightY, weightSize * 0.8f, weightSize, 2.0f);
    g.drawLine(leftWeightX, leftWeightY + weightSize, leftWeightX, beamY, stroke);

    // Right weight (R)
    g.fillRoundedRectangle(rightWeightX - weightSize * 0.4f, rightWeightY, weightSize * 0.8f, weightSize * 0.8f, 2.0f);
    g.drawLine(rightWeightX, rightWeightY + weightSize * 0.8f, rightWeightX, beamY, stroke);

    // L/R labels on weights
    g.setFont(juce::Font(weightSize * 0.5f, juce::Font::bold));
    g.drawText("L", juce::Rectangle<float>(leftWeightX - weightSize * 0.4f, leftWeightY, weightSize * 0.8f, weightSize),
               juce::Justification::centred);
    g.drawText("R", juce::Rectangle<float>(rightWeightX - weightSize * 0.4f, rightWeightY, weightSize * 0.8f, weightSize * 0.8f),
               juce::Justification::centred);

    // Balance indicator needle
    g.setColour(color.brighter(0.3f));
    auto needleLength = fulcrumSize * 0.7f;
    auto needleAngle = 0.1f; // Slightly off center
    auto needleEndX = centerX + std::sin(needleAngle) * needleLength;
    auto needleEndY = beamY + stroke - std::cos(needleAngle) * needleLength;

    g.drawLine(centerX, beamY + stroke, needleEndX, needleEndY, stroke);
}
