#include "FancyIconPack.h"

// ============================================================================
// MIDI AND MODULATION ICONS IMPLEMENTATION - PART 1
// ============================================================================

// MIDI Core
// ============================================================================

void FancyIconPack::drawMidi(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color)
{
    auto iconBounds = bounds;
    auto stroke = getOptimalStrokeWidth(iconBounds);

    // MIDI connector representation (5-pin DIN style)
    auto connectorBounds = iconBounds.reduced(iconBounds.getWidth() * 0.2f, iconBounds.getHeight() * 0.25f);

    // Outer connector shell
    g.setColour(color);
    g.drawEllipse(connectorBounds, stroke);

    // Inner pins (5 pins in traditional MIDI pattern)
    auto centre = connectorBounds.getCentre();
    auto pinRadius = stroke * 0.8f;
    auto pinDistance = connectorBounds.getWidth() * 0.15f;

    // Center pin
    g.fillEllipse(centre.x - pinRadius, centre.y - pinRadius, pinRadius * 2, pinRadius * 2);

    // Four outer pins
    for (int i = 0; i < 4; ++i)
    {
        auto angle = i * juce::MathConstants<float>::halfPi + juce::MathConstants<float>::pi * 0.25f;
        auto pinX = centre.x + std::cos(angle) * pinDistance;
        auto pinY = centre.y + std::sin(angle) * pinDistance;

        g.fillEllipse(pinX - pinRadius, pinY - pinRadius, pinRadius * 2, pinRadius * 2);
    }

    // MIDI text indicator
    auto textBounds = juce::Rectangle<float>(iconBounds.getX(), iconBounds.getBottom() - iconBounds.getHeight() * 0.2f,
                                           iconBounds.getWidth(), iconBounds.getHeight() * 0.15f);

    g.setColour(color.withAlpha(0.8f));
    auto fontSize = textBounds.getHeight() * 0.8f;
    g.setFont(juce::Font(fontSize, juce::Font::bold));
    g.drawText("MIDI", textBounds, juce::Justification::centred);
}

void FancyIconPack::drawMidiIn(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color)
{
    auto iconBounds = bounds;
    auto stroke = getOptimalStrokeWidth(iconBounds);

    // MIDI connector with input arrow
    auto connectorBounds = iconBounds.reduced(iconBounds.getWidth() * 0.2f, iconBounds.getHeight() * 0.3f);

    // Outer connector shell
    g.setColour(color);
    g.drawEllipse(connectorBounds, stroke);

    // Input arrow pointing into connector
    auto arrowCentre = connectorBounds.getCentre() - juce::Point<float>(connectorBounds.getWidth() * 0.4f, 0);
    auto arrowSize = iconBounds.getWidth() * 0.08f;

    juce::Path arrow;
    arrow.startNewSubPath(arrowCentre.x, arrowCentre.y);
    arrow.lineTo(arrowCentre.x + arrowSize, arrowCentre.y - arrowSize * 0.6f);
    arrow.lineTo(arrowCentre.x + arrowSize, arrowCentre.y + arrowSize * 0.6f);
    arrow.closeSubPath();

    g.fillPath(arrow);

    // Arrow line
    g.drawLine(iconBounds.getX(), arrowCentre.y, arrowCentre.x, arrowCentre.y, stroke);

    // "IN" label
    auto labelBounds = juce::Rectangle<float>(iconBounds.getX(), iconBounds.getBottom() - iconBounds.getHeight() * 0.2f,
                                            iconBounds.getWidth(), iconBounds.getHeight() * 0.15f);
    g.setFont(juce::Font(labelBounds.getHeight() * 0.8f, juce::Font::bold));
    g.drawText("IN", labelBounds, juce::Justification::centred);
}

void FancyIconPack::drawMidiOut(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color)
{
    auto iconBounds = bounds;
    auto stroke = getOptimalStrokeWidth(iconBounds);

    // MIDI connector with output arrow
    auto connectorBounds = iconBounds.reduced(iconBounds.getWidth() * 0.2f, iconBounds.getHeight() * 0.3f);

    // Outer connector shell
    g.setColour(color);
    g.drawEllipse(connectorBounds, stroke);

    // Output arrow pointing out from connector
    auto arrowCentre = connectorBounds.getCentre() + juce::Point<float>(connectorBounds.getWidth() * 0.4f, 0);
    auto arrowSize = iconBounds.getWidth() * 0.08f;

    juce::Path arrow;
    arrow.startNewSubPath(arrowCentre.x, arrowCentre.y);
    arrow.lineTo(arrowCentre.x - arrowSize, arrowCentre.y - arrowSize * 0.6f);
    arrow.lineTo(arrowCentre.x - arrowSize, arrowCentre.y + arrowSize * 0.6f);
    arrow.closeSubPath();

    g.fillPath(arrow);

    // Arrow line
    g.drawLine(arrowCentre.x, arrowCentre.y, iconBounds.getRight(), arrowCentre.y, stroke);

    // "OUT" label
    auto labelBounds = juce::Rectangle<float>(iconBounds.getX(), iconBounds.getBottom() - iconBounds.getHeight() * 0.2f,
                                            iconBounds.getWidth(), iconBounds.getHeight() * 0.15f);
    g.setFont(juce::Font(labelBounds.getHeight() * 0.7f, juce::Font::bold));
    g.drawText("OUT", labelBounds, juce::Justification::centred);
}

void FancyIconPack::drawMidiChannel(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color)
{
    auto iconBounds = bounds;
    auto stroke = getOptimalStrokeWidth(iconBounds);

    // Channel number display with MIDI connector
    auto channelRect = iconBounds.reduced(iconBounds.getWidth() * 0.2f, iconBounds.getHeight() * 0.15f);

    // Draw channel number background (rounded rectangle)
    g.setColour(color.withAlpha(0.3f));
    g.fillRoundedRectangle(channelRect, stroke * 2.0f);

    // Draw channel number border
    g.setColour(color);
    g.drawRoundedRectangle(channelRect, stroke * 2.0f, stroke);

    // Draw "CH" text
    g.setFont(juce::Font(iconBounds.getHeight() * 0.2f, juce::Font::bold));
    g.drawText("CH", channelRect.removeFromTop(channelRect.getHeight() * 0.4f),
               juce::Justification::centred);

    // Draw channel number placeholder
    g.setFont(juce::Font(iconBounds.getHeight() * 0.25f, juce::Font::bold));
    g.drawText("#", channelRect, juce::Justification::centred);

    // Draw small MIDI connector indicators
    auto connectorSize = stroke * 3.0f;
    g.fillEllipse(iconBounds.getX(), iconBounds.getCentreY() - connectorSize * 0.5f,
                  connectorSize, connectorSize);
    g.fillEllipse(iconBounds.getRight() - connectorSize, iconBounds.getCentreY() - connectorSize * 0.5f,
                  connectorSize, connectorSize);
}

void FancyIconPack::drawMidiCC(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color)
{
    auto iconBounds = bounds;
    auto stroke = getOptimalStrokeWidth(iconBounds);

    // CC control as a continuous curve with discrete steps
    juce::Path ccCurve;
    auto baseY = iconBounds.getBottom() - iconBounds.getHeight() * 0.2f;
    auto curveHeight = iconBounds.getHeight() * 0.6f;
    auto steps = 8;

    ccCurve.startNewSubPath(iconBounds.getX(), baseY);

    // Stepped continuous curve
    for (int i = 1; i <= steps; ++i)
    {
        auto x = iconBounds.getX() + (i / static_cast<float>(steps)) * iconBounds.getWidth();
        auto value = std::sin(i * 0.8f) * 0.5f + 0.5f; // 0-1 range
        auto y = baseY - value * curveHeight;

        // Draw step
        if (i > 1)
        {
            auto prevX = iconBounds.getX() + ((i-1) / static_cast<float>(steps)) * iconBounds.getWidth();
            ccCurve.lineTo(prevX, y);
        }
        ccCurve.lineTo(x, y);
    }

    g.setColour(color);
    g.strokePath(ccCurve, createStroke(stroke));

    // CC value indicators (dots at control points)
    for (int i = 1; i <= steps; ++i)
    {
        auto x = iconBounds.getX() + (i / static_cast<float>(steps)) * iconBounds.getWidth();
        auto value = std::sin(i * 0.8f) * 0.5f + 0.5f;
        auto y = baseY - value * curveHeight;

        g.setColour(color.withAlpha(0.8f));
        auto dotRadius = stroke * 0.8f;
        g.fillEllipse(x - dotRadius, y - dotRadius, dotRadius * 2, dotRadius * 2);
    }

    // "CC" label
    auto labelBounds = juce::Rectangle<float>(iconBounds.getX(), iconBounds.getY(),
                                            iconBounds.getWidth(), iconBounds.getHeight() * 0.2f);
    g.setColour(color);
    g.setFont(juce::Font(labelBounds.getHeight() * 0.8f, juce::Font::bold));
    g.drawText("CC", labelBounds, juce::Justification::centred);
}

void FancyIconPack::drawMidiLearn(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color)
{
    auto iconBounds = bounds;
    auto stroke = getOptimalStrokeWidth(iconBounds);

    // Learning symbol - brain/head with MIDI signal
    auto centerX = iconBounds.getCentreX();
    auto centerY = iconBounds.getCentreY();
    auto radius = juce::jmin(iconBounds.getWidth(), iconBounds.getHeight()) * 0.3f;

    // Draw head/brain shape
    juce::Path headShape;
    headShape.addEllipse(centerX - radius, centerY - radius * 0.8f, radius * 2.0f, radius * 1.6f);

    g.setColour(color.withAlpha(0.3f));
    g.fillPath(headShape);
    g.setColour(color);
    g.strokePath(headShape, createStroke(stroke));

    // Draw brain pattern inside
    auto brainStroke = stroke * 0.7f;
    g.setColour(color.withAlpha(0.7f));

    // Brain wave lines
    for (int i = 0; i < 3; ++i)
    {
        auto y = centerY - radius * 0.4f + i * radius * 0.4f;
        juce::Path brainWave;
        brainWave.startNewSubPath(centerX - radius * 0.6f, y);
        brainWave.cubicTo(centerX - radius * 0.2f, y - radius * 0.15f,
                         centerX + radius * 0.2f, y + radius * 0.15f,
                         centerX + radius * 0.6f, y);
        g.strokePath(brainWave, createStroke(brainStroke));
    }

    // MIDI signal waves coming in
    g.setColour(color);
    auto signalY = centerY + radius * 0.8f;

    for (int i = 0; i < 3; ++i)
    {
        auto x = centerX - radius * 0.8f + i * radius * 0.8f;
        juce::Path signal;
        signal.startNewSubPath(x, signalY);
        signal.lineTo(x, signalY - radius * 0.3f);
        signal.lineTo(x + radius * 0.1f, signalY - radius * 0.4f);
        signal.lineTo(x + radius * 0.2f, signalY - radius * 0.3f);
        signal.lineTo(x + radius * 0.2f, signalY);

        g.strokePath(signal, createStroke(stroke * 0.8f));
    }
}

// Musical Elements
// ============================================================================

void FancyIconPack::drawNote(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color)
{
    auto iconBounds = bounds;
    auto stroke = getOptimalStrokeWidth(iconBounds);

    // Musical note (eighth note)
    auto noteHeadRadius = iconBounds.getWidth() * 0.15f;
    auto noteHeadCentre = juce::Point<float>(iconBounds.getX() + iconBounds.getWidth() * 0.3f,
                                           iconBounds.getBottom() - iconBounds.getHeight() * 0.25f);

    // Note head (filled oval)
    g.setColour(color);
    g.fillEllipse(noteHeadCentre.x - noteHeadRadius, noteHeadCentre.y - noteHeadRadius * 0.7f,
                 noteHeadRadius * 2, noteHeadRadius * 1.4f);

    // Note stem
    auto stemTop = juce::Point<float>(noteHeadCentre.x + noteHeadRadius * 0.8f,
                                    iconBounds.getY() + iconBounds.getHeight() * 0.15f);
    g.drawLine(juce::Line<float>(noteHeadCentre + juce::Point<float>(noteHeadRadius * 0.8f, 0), stemTop),
              stroke * 1.5f);

    // Note flag (eighth note flag)
    juce::Path flag;
    flag.startNewSubPath(stemTop);
    flag.quadraticTo(stemTop + juce::Point<float>(iconBounds.getWidth() * 0.25f, iconBounds.getHeight() * 0.1f),
                    stemTop + juce::Point<float>(iconBounds.getWidth() * 0.15f, iconBounds.getHeight() * 0.25f));
    flag.quadraticTo(stemTop + juce::Point<float>(iconBounds.getWidth() * 0.05f, iconBounds.getHeight() * 0.2f),
                    stemTop + juce::Point<float>(0, iconBounds.getHeight() * 0.15f));

    g.fillPath(flag);
}

void FancyIconPack::drawVelocity(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color)
{
    auto iconBounds = bounds;
    auto stroke = getOptimalStrokeWidth(iconBounds);

    // Velocity bars representing dynamic range
    auto barCount = 5;
    auto barSpacing = iconBounds.getWidth() / barCount;
    auto barWidth = barSpacing * 0.6f;

    for (int i = 0; i < barCount; ++i)
    {
        auto x = iconBounds.getX() + i * barSpacing + (barSpacing - barWidth) * 0.5f;
        auto heightRatio = (i + 1) / static_cast<float>(barCount);
        auto barHeight = iconBounds.getHeight() * heightRatio * 0.8f;
        auto y = iconBounds.getBottom() - barHeight;

        // Color intensity based on velocity level
        auto alpha = 0.4f + heightRatio * 0.6f;
        g.setColour(color.withAlpha(alpha));
        g.fillRoundedRectangle(x, y, barWidth, barHeight, 1.0f);
    }

    // Velocity indicator arrow
    auto arrowCentre = iconBounds.getCentre() + juce::Point<float>(iconBounds.getWidth() * 0.2f, -iconBounds.getHeight() * 0.1f);
    auto arrowSize = iconBounds.getWidth() * 0.12f;

    juce::Path arrow;
    arrow.startNewSubPath(arrowCentre.x, arrowCentre.y - arrowSize);
    arrow.lineTo(arrowCentre.x - arrowSize * 0.6f, arrowCentre.y + arrowSize * 0.3f);
    arrow.lineTo(arrowCentre.x + arrowSize * 0.6f, arrowCentre.y + arrowSize * 0.3f);
    arrow.closeSubPath();

    g.setColour(color);
    g.fillPath(arrow);
}

void FancyIconPack::drawAftertouch(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color)
{
    auto iconBounds = bounds;
    auto stroke = getOptimalStrokeWidth(iconBounds);

    // Piano key with pressure indication
    auto keyRect = iconBounds.reduced(iconBounds.getWidth() * 0.2f, iconBounds.getHeight() * 0.1f);

    // Draw key background
    g.setColour(color.withAlpha(0.2f));
    g.fillRoundedRectangle(keyRect, stroke);

    // Draw key border
    g.setColour(color);
    g.drawRoundedRectangle(keyRect, stroke, stroke);

    // Pressure waves emanating from center
    auto centerX = keyRect.getCentreX();
    auto centerY = keyRect.getCentreY();

    for (int i = 1; i <= 3; ++i)
    {
        auto radius = keyRect.getWidth() * 0.1f * i;
        auto alpha = 1.0f - (i - 1) * 0.3f;

        g.setColour(color.withAlpha(alpha * 0.6f));
        g.drawEllipse(centerX - radius, centerY - radius, radius * 2.0f, radius * 2.0f, stroke * 0.7f);
    }

    // Finger pressure indicator
    auto fingerSize = keyRect.getWidth() * 0.15f;
    g.setColour(color.withAlpha(0.8f));
    g.fillEllipse(centerX - fingerSize * 0.5f, centerY - fingerSize * 0.5f, fingerSize, fingerSize);
}

void FancyIconPack::drawPolyAftertouch(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color)
{
    auto iconBounds = bounds;
    auto stroke = getOptimalStrokeWidth(iconBounds);

    // Multiple piano keys with individual pressure indications
    auto numKeys = 4;
    auto keyWidth = iconBounds.getWidth() / numKeys;
    auto keyHeight = iconBounds.getHeight() * 0.7f;
    auto keyY = iconBounds.getY() + (iconBounds.getHeight() - keyHeight) * 0.5f;

    for (int i = 0; i < numKeys; ++i)
    {
        auto keyX = iconBounds.getX() + i * keyWidth;
        auto keyRect = juce::Rectangle<float>(keyX, keyY, keyWidth * 0.9f, keyHeight);

        // Draw key background
        auto intensity = (i + 1) * 0.2f; // Different pressure per key
        g.setColour(color.withAlpha(0.1f + intensity * 0.3f));
        g.fillRoundedRectangle(keyRect, stroke * 0.5f);

        // Draw key border
        g.setColour(color);
        g.drawRoundedRectangle(keyRect, stroke * 0.5f, stroke * 0.7f);

        // Individual pressure indicators
        if (intensity > 0.2f)
        {
            auto centerX = keyRect.getCentreX();
            auto centerY = keyRect.getCentreY();
            auto radius = keyRect.getWidth() * 0.15f * intensity;

            g.setColour(color.withAlpha(intensity * 0.8f));
            g.fillEllipse(centerX - radius * 0.5f, centerY - radius * 0.5f, radius, radius);
        }
    }

    // "POLY" indicator
    g.setColour(color.withAlpha(0.7f));
    g.setFont(juce::Font(iconBounds.getHeight() * 0.15f, juce::Font::bold));
    g.drawText("POLY", iconBounds.removeFromBottom(iconBounds.getHeight() * 0.2f),
               juce::Justification::centred);
}

void FancyIconPack::drawModWheel(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color)
{
    auto iconBounds = bounds;
    auto stroke = getOptimalStrokeWidth(iconBounds);

    // Vertical slider representing mod wheel
    auto sliderRect = iconBounds.reduced(iconBounds.getWidth() * 0.3f, iconBounds.getHeight() * 0.15f);

    // Draw slider track
    g.setColour(color.withAlpha(0.3f));
    g.fillRoundedRectangle(sliderRect, stroke);
    g.setColour(color);
    g.drawRoundedRectangle(sliderRect, stroke, stroke * 0.7f);

    // Draw slider thumb (positioned at about 1/3 up to show modulation)
    auto thumbHeight = sliderRect.getHeight() * 0.15f;
    auto thumbY = sliderRect.getBottom() - sliderRect.getHeight() * 0.4f - thumbHeight * 0.5f;
    auto thumbRect = juce::Rectangle<float>(sliderRect.getX() - stroke, thumbY,
                                          sliderRect.getWidth() + stroke * 2.0f, thumbHeight);

    g.setColour(color);
    g.fillRoundedRectangle(thumbRect, stroke * 0.5f);

    // Modulation wave coming from the side
    auto waveX = iconBounds.getRight() - iconBounds.getWidth() * 0.3f;
    auto waveY = thumbY + thumbHeight * 0.5f;

    juce::Path modWave;
    modWave.startNewSubPath(sliderRect.getRight() + stroke * 2.0f, waveY);

    auto waveWidth = iconBounds.getRight() - (sliderRect.getRight() + stroke * 2.0f);
    auto numCycles = 2;

    for (int i = 0; i <= 20; ++i)
    {
        auto x = sliderRect.getRight() + stroke * 2.0f + (i / 20.0f) * waveWidth;
        auto y = waveY + std::sin(i / 20.0f * numCycles * 2.0f * juce::MathConstants<float>::pi) * thumbHeight * 0.5f;
        modWave.lineTo(x, y);
    }

    g.strokePath(modWave, createStroke(stroke * 0.8f));

    // "MOD" label
    g.setColour(color.withAlpha(0.7f));
    g.setFont(juce::Font(iconBounds.getHeight() * 0.12f, juce::Font::bold));
    g.drawText("MOD", iconBounds.removeFromTop(iconBounds.getHeight() * 0.15f),
               juce::Justification::centred);
}

void FancyIconPack::drawPitchBend(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color)
{
    auto iconBounds = bounds;
    auto stroke = getOptimalStrokeWidth(iconBounds);

    // Pitch bend visualization as bent note
    auto centre = iconBounds.getCentre();

    // Straight reference line
    g.setColour(color.withAlpha(0.4f));
    g.drawLine(iconBounds.getX(), centre.y, iconBounds.getRight(), centre.y, stroke * 0.6f);

    // Bent pitch line
    juce::Path bendCurve;
    auto points = 15;
    bendCurve.startNewSubPath(iconBounds.getX(), centre.y);

    for (int i = 1; i <= points; ++i)
    {
        auto x = iconBounds.getX() + (i / static_cast<float>(points)) * iconBounds.getWidth();
        auto ratio = i / static_cast<float>(points);

        // S-curve for pitch bend (down then up)
        auto bendAmount = std::sin(ratio * juce::MathConstants<float>::pi * 2.0f) * iconBounds.getHeight() * 0.2f;
        auto y = centre.y + bendAmount;

        bendCurve.lineTo(x, y);
    }

    g.setColour(color);
    g.strokePath(bendCurve, createStroke(stroke));

    // Pitch bend wheel symbol
    auto wheelCentre = iconBounds.getTopRight() + juce::Point<float>(-iconBounds.getWidth() * 0.2f, iconBounds.getHeight() * 0.2f);
    auto wheelRadius = iconBounds.getWidth() * 0.08f;

    g.drawEllipse(wheelCentre.x - wheelRadius, wheelCentre.y - wheelRadius,
                 wheelRadius * 2, wheelRadius * 2, stroke);

    // Wheel indicator line
    g.drawLine(wheelCentre.x, wheelCentre.y - wheelRadius,
              wheelCentre.x, wheelCentre.y + wheelRadius, stroke * 1.2f);
}

// Modulation Sources
// ============================================================================

void FancyIconPack::drawKeytrack(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color)
{
    auto iconBounds = bounds;
    auto stroke = getOptimalStrokeWidth(iconBounds);

    // Piano keyboard at bottom
    auto keyboardHeight = iconBounds.getHeight() * 0.3f;
    auto keyboardRect = juce::Rectangle<float>(iconBounds.getX(),
                                             iconBounds.getBottom() - keyboardHeight,
                                             iconBounds.getWidth(), keyboardHeight);

    // Draw keyboard keys
    auto numKeys = 7;
    auto keyWidth = keyboardRect.getWidth() / numKeys;

    for (int i = 0; i < numKeys; ++i)
    {
        auto keyX = keyboardRect.getX() + i * keyWidth;
        auto keyRect = juce::Rectangle<float>(keyX, keyboardRect.getY(), keyWidth * 0.9f, keyboardRect.getHeight());

        g.setColour(color.withAlpha(0.2f));
        g.fillRoundedRectangle(keyRect, stroke * 0.5f);
        g.setColour(color);
        g.drawRoundedRectangle(keyRect, stroke * 0.5f, stroke * 0.7f);
    }

    // Tracking curve above keyboard
    juce::Path trackingCurve;
    auto curveArea = iconBounds.removeFromTop(iconBounds.getHeight() - keyboardHeight - stroke * 2.0f);

    trackingCurve.startNewSubPath(curveArea.getX(), curveArea.getBottom());

    // Create ascending curve (higher notes = higher values)
    for (int i = 0; i <= 20; ++i)
    {
        auto x = curveArea.getX() + (i / 20.0f) * curveArea.getWidth();
        auto y = curveArea.getBottom() - (i / 20.0f) * curveArea.getHeight() * 0.8f;
        trackingCurve.lineTo(x, y);
    }

    g.setColour(color);
    g.strokePath(trackingCurve, createStroke(stroke * 1.2f));

    // Key tracking indicator arrows
    for (int i = 1; i < numKeys; i += 2)
    {
        auto keyCenter = keyboardRect.getX() + (i + 0.5f) * keyWidth;
        auto arrowTop = curveArea.getY() + curveArea.getHeight() * 0.2f + (i / float(numKeys)) * curveArea.getHeight() * 0.6f;
        auto arrowBottom = keyboardRect.getY() - stroke;

        // Draw connecting line
        g.setColour(color.withAlpha(0.6f));
        g.drawLine(keyCenter, arrowTop, keyCenter, arrowBottom, stroke * 0.7f);

        // Draw arrow head
        juce::Path arrowHead;
        arrowHead.startNewSubPath(keyCenter, arrowTop);
        arrowHead.lineTo(keyCenter - stroke * 1.5f, arrowTop + stroke * 2.0f);
        arrowHead.lineTo(keyCenter + stroke * 1.5f, arrowTop + stroke * 2.0f);
        arrowHead.closeSubPath();

        g.fillPath(arrowHead);
    }
}

void FancyIconPack::drawEnvelopeFollow(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color)
{
    auto iconBounds = bounds;
    auto stroke = getOptimalStrokeWidth(iconBounds);

    // Input signal waveform (irregular)
    juce::Path inputSignal;
    auto inputArea = iconBounds.removeFromTop(iconBounds.getHeight() * 0.4f);

    inputSignal.startNewSubPath(inputArea.getX(), inputArea.getCentreY());

    // Create complex waveform
    for (int i = 0; i <= 40; ++i)
    {
        auto x = inputArea.getX() + (i / 40.0f) * inputArea.getWidth();
        auto y = inputArea.getCentreY() +
                std::sin(i * 0.5f) * inputArea.getHeight() * 0.3f *
                (1.0f + std::sin(i * 0.1f) * 0.5f); // Amplitude modulation
        inputSignal.lineTo(x, y);
    }

    g.setColour(color.withAlpha(0.7f));
    g.strokePath(inputSignal, createStroke(stroke * 0.8f));

    // Envelope follower output (smooth envelope)
    juce::Path envelopeOutput;
    auto outputArea = iconBounds.removeFromBottom(iconBounds.getHeight() * 0.6f);

    envelopeOutput.startNewSubPath(outputArea.getX(), outputArea.getBottom());

    // Create smooth envelope following the input amplitude
    for (int i = 0; i <= 40; ++i)
    {
        auto x = outputArea.getX() + (i / 40.0f) * outputArea.getWidth();
        auto amplitude = std::abs(std::sin(i * 0.5f)) * (1.0f + std::sin(i * 0.1f) * 0.5f);
        auto y = outputArea.getBottom() - amplitude * outputArea.getHeight() * 0.7f;
        envelopeOutput.lineTo(x, y);
    }

    g.setColour(color);
    g.strokePath(envelopeOutput, createStroke(stroke * 1.2f));

    // Arrow showing transformation
    auto arrowX = iconBounds.getCentreX();
    auto arrowY = iconBounds.getCentreY() - stroke;

    juce::Path arrow;
    arrow.startNewSubPath(arrowX, arrowY - stroke * 2.0f);
    arrow.lineTo(arrowX, arrowY + stroke * 2.0f);
    arrow.lineTo(arrowX - stroke * 1.5f, arrowY);
    arrow.lineTo(arrowX + stroke * 1.5f, arrowY);
    arrow.closeSubPath();

    g.setColour(color.withAlpha(0.8f));
    g.fillPath(arrow);
}

void FancyIconPack::drawMacro(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color)
{
    auto iconBounds = bounds;
    auto stroke = getOptimalStrokeWidth(iconBounds);

    // Large circular control knob
    auto centerX = iconBounds.getCentreX();
    auto centerY = iconBounds.getCentreY();
    auto radius = juce::jmin(iconBounds.getWidth(), iconBounds.getHeight()) * 0.35f;

    // Outer ring
    g.setColour(color.withAlpha(0.3f));
    g.fillEllipse(centerX - radius, centerY - radius, radius * 2.0f, radius * 2.0f);
    g.setColour(color);
    g.drawEllipse(centerX - radius, centerY - radius, radius * 2.0f, radius * 2.0f, stroke);

    // Inner knob
    auto innerRadius = radius * 0.7f;
    g.setColour(color.withAlpha(0.2f));
    g.fillEllipse(centerX - innerRadius, centerY - innerRadius, innerRadius * 2.0f, innerRadius * 2.0f);
    g.setColour(color);
    g.drawEllipse(centerX - innerRadius, centerY - innerRadius, innerRadius * 2.0f, innerRadius * 2.0f, stroke);

    // Knob pointer (at about 2 o'clock position)
    auto angle = juce::MathConstants<float>::pi * 0.25f; // 45 degrees
    auto pointerLength = innerRadius * 0.8f;
    auto pointerX = centerX + std::cos(angle) * pointerLength;
    auto pointerY = centerY + std::sin(angle) * pointerLength;

    g.setColour(color);
    g.drawLine(centerX, centerY, pointerX, pointerY, stroke * 1.5f);

    // Macro label
    g.setColour(color.withAlpha(0.8f));
    g.setFont(juce::Font(iconBounds.getHeight() * 0.15f, juce::Font::bold));
    g.drawText("M", juce::Rectangle<float>(centerX - radius * 0.3f, centerY - radius * 0.2f,
                                         radius * 0.6f, radius * 0.4f),
               juce::Justification::centred);

    // Assignment indicators (small dots around the perimeter)
    for (int i = 0; i < 8; ++i)
    {
        auto dotAngle = (i / 8.0f) * 2.0f * juce::MathConstants<float>::pi - juce::MathConstants<float>::pi * 0.5f;
        auto dotRadius = radius * 1.2f;
        auto dotX = centerX + std::cos(dotAngle) * dotRadius;
        auto dotY = centerY + std::sin(dotAngle) * dotRadius;
        auto dotSize = stroke * 1.5f;

        auto alpha = (i < 3) ? 0.8f : 0.3f; // Some assigned, some not
        g.setColour(color.withAlpha(alpha));
        g.fillEllipse(dotX - dotSize * 0.5f, dotY - dotSize * 0.5f, dotSize, dotSize);
    }
}

void FancyIconPack::drawMacroAssign(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color)
{
    auto iconBounds = bounds;
    auto stroke = getOptimalStrokeWidth(iconBounds);

    // Macro knob (smaller, on left)
    auto macroRadius = iconBounds.getHeight() * 0.15f;
    auto macroX = iconBounds.getX() + macroRadius + stroke;
    auto macroY = iconBounds.getCentreY();

    g.setColour(color.withAlpha(0.3f));
    g.fillEllipse(macroX - macroRadius, macroY - macroRadius, macroRadius * 2.0f, macroRadius * 2.0f);
    g.setColour(color);
    g.drawEllipse(macroX - macroRadius, macroY - macroRadius, macroRadius * 2.0f, macroRadius * 2.0f, stroke * 0.7f);

    // "M" label
    g.setFont(juce::Font(macroRadius * 0.8f, juce::Font::bold));
    g.drawText("M", juce::Rectangle<float>(macroX - macroRadius * 0.5f, macroY - macroRadius * 0.4f,
                                         macroRadius, macroRadius * 0.8f),
               juce::Justification::centred);

    // Target parameter (on right)
    auto targetRadius = iconBounds.getHeight() * 0.18f;
    auto targetX = iconBounds.getRight() - targetRadius - stroke;
    auto targetY = iconBounds.getCentreY();

    g.setColour(color.withAlpha(0.2f));
    g.fillEllipse(targetX - targetRadius, targetY - targetRadius, targetRadius * 2.0f, targetRadius * 2.0f);
    g.setColour(color);
    g.drawEllipse(targetX - targetRadius, targetY - targetRadius, targetRadius * 2.0f, targetRadius * 2.0f, stroke * 0.7f);

    // Parameter symbol (generic knob indicator)
    auto pointerAngle = juce::MathConstants<float>::pi * 0.3f;
    auto pointerLength = targetRadius * 0.6f;
    auto pointerEndX = targetX + std::cos(pointerAngle) * pointerLength;
    auto pointerEndY = targetY + std::sin(pointerAngle) * pointerLength;

    g.drawLine(targetX, targetY, pointerEndX, pointerEndY, stroke);

    // Assignment arrow/connection
    juce::Path assignmentPath;
    auto startX = macroX + macroRadius + stroke;
    auto endX = targetX - targetRadius - stroke;
    auto arrowY = iconBounds.getCentreY();

    assignmentPath.startNewSubPath(startX, arrowY);
    assignmentPath.lineTo(endX, arrowY);

    // Arrow head
    assignmentPath.lineTo(endX - stroke * 2.0f, arrowY - stroke * 1.5f);
    assignmentPath.startNewSubPath(endX, arrowY);
    assignmentPath.lineTo(endX - stroke * 2.0f, arrowY + stroke * 1.5f);

    g.setColour(color.withAlpha(0.8f));
    g.strokePath(assignmentPath, createStroke(stroke));

    // Assignment mode indicator (dashed line)
    for (int i = 0; i < 3; ++i)
    {
        auto dashX = startX + (i + 1) * (endX - startX) * 0.25f;
        auto dashY = arrowY - stroke * 2.0f;
        g.setColour(color.withAlpha(0.5f));
        g.drawLine(dashX - stroke, dashY, dashX + stroke, dashY, stroke * 0.7f);
    }
}
