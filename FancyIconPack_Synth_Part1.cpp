#include "FancyIconPack.h"

// ============================================================================
// SYNTH AND FX COMPONENTS IMPLEMENTATION - PART 1
// ============================================================================

// Oscillators
// ============================================================================

void FancyIconPack::drawOsc(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color)
{
    auto iconBounds = bounds;
    auto stroke = getOptimalStrokeWidth(iconBounds);

    // Generic oscillator symbol - sine wave with electrical circuit symbol
    juce::Path sineWave;
    auto waveY = iconBounds.getCentreY();
    auto amplitude = iconBounds.getHeight() * 0.2f;
    auto points = 16;

    sineWave.startNewSubPath(iconBounds.getX(), waveY);

    for (int i = 1; i <= points; ++i)
    {
        auto x = iconBounds.getX() + (i / static_cast<float>(points)) * iconBounds.getWidth();
        auto phase = (i / static_cast<float>(points)) * juce::MathConstants<float>::twoPi * 1.5f;
        auto amp = std::sin(phase) * amplitude;
        sineWave.lineTo(x, waveY + amp);
    }

    g.setColour(color);
    g.strokePath(sineWave, createStroke(stroke));

    // Oscillator circuit symbol (triangle with circle)
    auto symbolCentre = iconBounds.getCentre() + juce::Point<float>(0, iconBounds.getHeight() * 0.25f);
    auto symbolSize = iconBounds.getWidth() * 0.15f;

    // Triangle (op-amp symbol)
    juce::Path triangle;
    triangle.startNewSubPath(symbolCentre.x - symbolSize, symbolCentre.y - symbolSize * 0.6f);
    triangle.lineTo(symbolCentre.x + symbolSize * 0.8f, symbolCentre.y);
    triangle.lineTo(symbolCentre.x - symbolSize, symbolCentre.y + symbolSize * 0.6f);
    triangle.closeSubPath();

    g.strokePath(triangle, createStroke(stroke));

    // Output circle
    g.drawEllipse(symbolCentre.x + symbolSize * 0.8f - stroke, symbolCentre.y - stroke,
                 stroke * 2, stroke * 2, stroke * 0.8f);
}

void FancyIconPack::drawOsc1(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color)
{
    auto iconBounds = bounds;
    auto stroke = getOptimalStrokeWidth(iconBounds);

    // Waveform area
    auto waveArea = iconBounds.removeFromTop(iconBounds.getHeight() * 0.6f);

    // Sine wave
    juce::Path sineWave;
    auto waveY = waveArea.getCentreY();
    auto amplitude = waveArea.getHeight() * 0.35f;
    auto points = 12;

    sineWave.startNewSubPath(waveArea.getX(), waveY);

    for (int i = 1; i <= points; ++i)
    {
        auto x = waveArea.getX() + (i / static_cast<float>(points)) * waveArea.getWidth();
        auto phase = (i / static_cast<float>(points)) * juce::MathConstants<float>::twoPi * 1.5f;
        auto amp = std::sin(phase) * amplitude;
        sineWave.lineTo(x, waveY + amp);
    }

    g.setColour(color);
    g.strokePath(sineWave, createStroke(stroke));

    // "1" label
    auto labelArea = iconBounds.removeFromBottom(iconBounds.getHeight());
    g.setFont(juce::Font(labelArea.getHeight() * 0.8f, juce::Font::bold));
    g.drawText("1", labelArea, juce::Justification::centred);
}

void FancyIconPack::drawOsc2(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color)
{
    auto iconBounds = bounds;
    auto stroke = getOptimalStrokeWidth(iconBounds);

    // Waveform area
    auto waveArea = iconBounds.removeFromTop(iconBounds.getHeight() * 0.6f);

    // Sawtooth wave (different from OSC1)
    juce::Path sawWave;
    auto waveY = waveArea.getCentreY();
    auto amplitude = waveArea.getHeight() * 0.35f;
    auto cycleWidth = waveArea.getWidth() / 2.5f;

    sawWave.startNewSubPath(waveArea.getX(), waveY + amplitude);

    for (int i = 0; i < 3; ++i)
    {
        auto cycleStart = waveArea.getX() + i * cycleWidth;
        sawWave.lineTo(cycleStart + cycleWidth, waveY - amplitude);
        sawWave.lineTo(cycleStart + cycleWidth, waveY + amplitude);
    }

    g.setColour(color);
    g.strokePath(sawWave, createStroke(stroke, juce::PathStrokeType::mitered, juce::PathStrokeType::butt));

    // "2" label
    auto labelArea = iconBounds.removeFromBottom(iconBounds.getHeight());
    g.setFont(juce::Font(labelArea.getHeight() * 0.8f, juce::Font::bold));
    g.drawText("2", labelArea, juce::Justification::centred);
}

void FancyIconPack::drawOsc3(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color)
{
    auto iconBounds = bounds;
    auto stroke = getOptimalStrokeWidth(iconBounds);

    // Waveform area
    auto waveArea = iconBounds.removeFromTop(iconBounds.getHeight() * 0.6f);

    // Square wave (different from OSC1 and OSC2)
    juce::Path squareWave;
    auto waveY = waveArea.getCentreY();
    auto amplitude = waveArea.getHeight() * 0.35f;
    auto cycleWidth = waveArea.getWidth() / 2.0f;

    squareWave.startNewSubPath(waveArea.getX(), waveY + amplitude);

    for (int i = 0; i < 2; ++i)
    {
        auto cycleStart = waveArea.getX() + i * cycleWidth;
        auto halfCycle = cycleWidth * 0.5f;

        // High part
        squareWave.lineTo(cycleStart, waveY + amplitude);
        squareWave.lineTo(cycleStart, waveY - amplitude);
        squareWave.lineTo(cycleStart + halfCycle, waveY - amplitude);

        // Low part
        squareWave.lineTo(cycleStart + halfCycle, waveY + amplitude);
        squareWave.lineTo(cycleStart + cycleWidth, waveY + amplitude);
    }

    g.setColour(color);
    g.strokePath(squareWave, createStroke(stroke, juce::PathStrokeType::mitered, juce::PathStrokeType::butt));

    // "3" label
    auto labelArea = iconBounds.removeFromBottom(iconBounds.getHeight());
    g.setFont(juce::Font(labelArea.getHeight() * 0.8f, juce::Font::bold));
    g.drawText("3", labelArea, juce::Justification::centred);
}

void FancyIconPack::drawSubOsc(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color)
{
    auto iconBounds = bounds;
    auto stroke = getOptimalStrokeWidth(iconBounds);

    // Sub-oscillator with lower frequency sine wave
    auto waveArea = iconBounds.removeFromTop(iconBounds.getHeight() * 0.6f);

    juce::Path subWave;
    auto waveY = waveArea.getCentreY();
    auto amplitude = waveArea.getHeight() * 0.4f;
    auto points = 16;

    subWave.startNewSubPath(waveArea.getX(), waveY);

    // Lower frequency (0.5 cycles instead of 1.5)
    for (int i = 1; i <= points; ++i)
    {
        auto x = waveArea.getX() + (i / static_cast<float>(points)) * waveArea.getWidth();
        auto phase = (i / static_cast<float>(points)) * juce::MathConstants<float>::twoPi * 0.5f;
        auto amp = std::sin(phase) * amplitude;
        subWave.lineTo(x, waveY + amp);
    }

    g.setColour(color);
    g.strokePath(subWave, createStroke(stroke * 1.2f)); // Thicker stroke for sub

    // "SUB" label
    auto labelArea = iconBounds.removeFromBottom(iconBounds.getHeight());
    g.setFont(juce::Font(labelArea.getHeight() * 0.6f, juce::Font::bold));
    g.drawText("SUB", labelArea, juce::Justification::centred);

    // Octave down indicator
    auto octaveIndicator = labelArea.removeFromRight(labelArea.getWidth() * 0.3f);
    g.setFont(juce::Font(octaveIndicator.getHeight() * 0.5f));
    g.drawText("-1", octaveIndicator, juce::Justification::centred);
}

void FancyIconPack::drawNoiseOsc(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color)
{
    auto iconBounds = bounds;
    auto stroke = getOptimalStrokeWidth(iconBounds);

    // Noise waveform
    auto waveArea = iconBounds.removeFromTop(iconBounds.getHeight() * 0.6f);

    juce::Path noisePath;
    auto waveY = waveArea.getCentreY();
    auto points = 20;

    juce::Random random(123); // Fixed seed for consistent appearance
    noisePath.startNewSubPath(waveArea.getX(), waveY);

    for (int i = 1; i <= points; ++i)
    {
        auto x = waveArea.getX() + (i / static_cast<float>(points)) * waveArea.getWidth();
        auto amplitude = (random.nextFloat() - 0.5f) * waveArea.getHeight() * 0.7f;
        noisePath.lineTo(x, waveY + amplitude);
    }

    g.setColour(color);
    g.strokePath(noisePath, createStroke(stroke * 0.8f));

    // "NOISE" label
    auto labelArea = iconBounds.removeFromBottom(iconBounds.getHeight());
    g.setFont(juce::Font(labelArea.getHeight() * 0.5f, juce::Font::bold));
    g.drawText("NOISE", labelArea, juce::Justification::centred);
}

void FancyIconPack::drawUnison(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color)
{
    auto iconBounds = bounds;
    auto stroke = getOptimalStrokeWidth(iconBounds);

    // Multiple stacked waveforms to show voice stacking
    auto waveArea = iconBounds.removeFromTop(iconBounds.getHeight() * 0.7f);
    auto amplitude = waveArea.getHeight() * 0.15f;
    auto points = 12;

    // Draw 3 slightly offset sine waves
    for (int voice = 0; voice < 3; ++voice)
    {
        juce::Path wave;
        auto waveY = waveArea.getCentreY() + (voice - 1) * amplitude * 0.3f;
        auto phaseOffset = voice * 0.1f; // Slight phase offset for chorus effect
        auto alpha = 1.0f - voice * 0.2f; // Decreasing alpha for depth

        wave.startNewSubPath(waveArea.getX(), waveY);

        for (int i = 1; i <= points; ++i)
        {
            auto x = waveArea.getX() + (i / static_cast<float>(points)) * waveArea.getWidth();
            auto phase = (i / static_cast<float>(points)) * juce::MathConstants<float>::twoPi + phaseOffset;
            auto amp = std::sin(phase) * amplitude;
            wave.lineTo(x, waveY + amp);
        }

        g.setColour(color.withAlpha(alpha));
        g.strokePath(wave, createStroke(stroke * (1.0f - voice * 0.2f)));
    }

    // "UNI" label
    auto labelArea = iconBounds.removeFromBottom(iconBounds.getHeight());
    g.setColour(color);
    g.setFont(juce::Font(labelArea.getHeight() * 0.7f, juce::Font::bold));
    g.drawText("UNI", labelArea, juce::Justification::centred);
}

void FancyIconPack::drawVoices(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color)
{
    auto iconBounds = bounds;
    auto stroke = getOptimalStrokeWidth(iconBounds);

    // Voice indicators as stacked rectangles
    auto voiceCount = 4;
    auto voiceHeight = iconBounds.getHeight() * 0.15f;
    auto voiceWidth = iconBounds.getWidth() * 0.6f;
    auto spacing = iconBounds.getHeight() * 0.05f;
    auto startY = iconBounds.getCentreY() - (voiceCount * (voiceHeight + spacing) - spacing) * 0.5f;

    g.setColour(color);

    for (int i = 0; i < voiceCount; ++i)
    {
        auto y = startY + i * (voiceHeight + spacing);
        auto x = iconBounds.getX() + (iconBounds.getWidth() - voiceWidth) * 0.5f;
        auto alpha = 1.0f - i * 0.15f; // Fade out for inactive voices

        g.setColour(color.withAlpha(alpha));
        g.fillRoundedRectangle(x, y, voiceWidth, voiceHeight, 2.0f);

        // Active indicator dot
        if (i < 3) // Show 3 active voices
        {
            g.setColour(color.brighter(0.3f));
            auto dotRadius = voiceHeight * 0.2f;
            g.fillEllipse(x + voiceWidth - dotRadius * 2, y + voiceHeight * 0.3f, dotRadius, dotRadius);
        }
    }

    // Voice count label
    g.setColour(color);
    g.setFont(juce::Font(iconBounds.getHeight() * 0.15f, juce::Font::bold));
    g.drawText("4", iconBounds.removeFromRight(iconBounds.getWidth() * 0.2f), juce::Justification::centred);
}

void FancyIconPack::drawPolyphony(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color)
{
    auto iconBounds = bounds;
    auto stroke = getOptimalStrokeWidth(iconBounds);

    // Multiple overlapping note heads to represent polyphony
    auto noteRadius = iconBounds.getWidth() * 0.12f;
    auto centre = iconBounds.getCentre();

    // Draw 3 overlapping note heads at different positions
    juce::Point<float> notePositions[] = {
        centre + juce::Point<float>(-noteRadius * 0.8f, -noteRadius * 0.3f),
        centre + juce::Point<float>(0, noteRadius * 0.3f),
        centre + juce::Point<float>(noteRadius * 0.8f, -noteRadius * 0.1f)
    };

    g.setColour(color);

    for (int i = 0; i < 3; ++i)
    {
        auto alpha = 1.0f - i * 0.2f;
        g.setColour(color.withAlpha(alpha));

        // Note head (elliptical)
        g.fillEllipse(notePositions[i].x - noteRadius, notePositions[i].y - noteRadius * 0.7f,
                     noteRadius * 2, noteRadius * 1.4f);

        // Note stem
        auto stemTop = notePositions[i] + juce::Point<float>(noteRadius * 0.8f, -iconBounds.getHeight() * 0.25f);
        g.drawLine(juce::Line<float>(notePositions[i] + juce::Point<float>(noteRadius * 0.8f, 0), stemTop),
                  stroke * 1.2f);
    }

    // "POLY" label at bottom
    auto labelArea = juce::Rectangle<float>(iconBounds.getX(), iconBounds.getBottom() - iconBounds.getHeight() * 0.2f,
                                          iconBounds.getWidth(), iconBounds.getHeight() * 0.15f);
    g.setColour(color);
    g.setFont(juce::Font(labelArea.getHeight() * 0.8f, juce::Font::bold));
    g.drawText("POLY", labelArea, juce::Justification::centred);
}

// Filter Components
// ============================================================================

void FancyIconPack::drawFilter1(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color)
{
    auto iconBounds = bounds;
    auto stroke = getOptimalStrokeWidth(iconBounds);

    // Filter frequency response curve
    auto responseArea = iconBounds.removeFromTop(iconBounds.getHeight() * 0.6f);

    juce::Path filterCurve;
    auto baseY = responseArea.getBottom() - responseArea.getHeight() * 0.1f;
    auto points = 12;

    filterCurve.startNewSubPath(responseArea.getX(), baseY);

    for (int i = 1; i <= points; ++i)
    {
        auto x = responseArea.getX() + (i / static_cast<float>(points)) * responseArea.getWidth();
        auto ratio = i / static_cast<float>(points);

        // Low-pass response with resonance
        auto response = 1.0f;
        if (ratio < 0.5f) response = 1.0f;
        else if (ratio < 0.6f) response = 1.0f + (ratio - 0.5f) * 3.0f; // Resonance peak
        else response = std::exp(-(ratio - 0.6f) * 5.0f);

        auto y = baseY - response * responseArea.getHeight() * 0.7f;
        filterCurve.lineTo(x, y);
    }

    g.setColour(color);
    g.strokePath(filterCurve, createStroke(stroke));

    // "F1" label
    auto labelArea = iconBounds.removeFromBottom(iconBounds.getHeight());
    g.setFont(juce::Font(labelArea.getHeight() * 0.8f, juce::Font::bold));
    g.drawText("F1", labelArea, juce::Justification::centred);
}

void FancyIconPack::drawFilter2(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color)
{
    auto iconBounds = bounds;
    auto stroke = getOptimalStrokeWidth(iconBounds);

    // Filter frequency response curve (different from Filter1)
    auto responseArea = iconBounds.removeFromTop(iconBounds.getHeight() * 0.6f);

    juce::Path filterCurve;
    auto baseY = responseArea.getBottom() - responseArea.getHeight() * 0.1f;
    auto points = 12;

    filterCurve.startNewSubPath(responseArea.getX(), baseY);

    for (int i = 1; i <= points; ++i)
    {
        auto x = responseArea.getX() + (i / static_cast<float>(points)) * responseArea.getWidth();
        auto ratio = i / static_cast<float>(points);

        // Band-pass response
        auto centerDistance = std::abs(ratio - 0.5f);
        auto response = std::exp(-centerDistance * centerDistance * 20.0f);
        auto y = baseY - response * responseArea.getHeight() * 0.7f;
        filterCurve.lineTo(x, y);
    }

    g.setColour(color);
    g.strokePath(filterCurve, createStroke(stroke));

    // "F2" label
    auto labelArea = iconBounds.removeFromBottom(iconBounds.getHeight());
    g.setFont(juce::Font(labelArea.getHeight() * 0.8f, juce::Font::bold));
    g.drawText("F2", labelArea, juce::Justification::centred);
}

// Amplifier and VCA
// ============================================================================

void FancyIconPack::drawAmp(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color)
{
    auto iconBounds = bounds;
    auto stroke = getOptimalStrokeWidth(iconBounds);

    // Amplifier triangle symbol
    auto symbolArea = iconBounds.removeFromTop(iconBounds.getHeight() * 0.6f);
    auto centre = symbolArea.getCentre();
    auto triangleSize = juce::jmin(symbolArea.getWidth(), symbolArea.getHeight()) * 0.4f;

    juce::Path triangle;
    triangle.startNewSubPath(centre.x - triangleSize, centre.y - triangleSize * 0.7f);
    triangle.lineTo(centre.x + triangleSize, centre.y);
    triangle.lineTo(centre.x - triangleSize, centre.y + triangleSize * 0.7f);
    triangle.closeSubPath();

    g.setColour(color);
    g.strokePath(triangle, createStroke(stroke));

    // Input and output lines
    g.drawLine(centre.x - triangleSize * 1.3f, centre.y - triangleSize * 0.3f,
              centre.x - triangleSize, centre.y - triangleSize * 0.3f, stroke);
    g.drawLine(centre.x - triangleSize * 1.3f, centre.y + triangleSize * 0.3f,
              centre.x - triangleSize, centre.y + triangleSize * 0.3f, stroke);
    g.drawLine(centre.x + triangleSize, centre.y,
              centre.x + triangleSize * 1.3f, centre.y, stroke);

    // "AMP" label
    auto labelArea = iconBounds.removeFromBottom(iconBounds.getHeight());
    g.setFont(juce::Font(labelArea.getHeight() * 0.7f, juce::Font::bold));
    g.drawText("AMP", labelArea, juce::Justification::centred);
}

void FancyIconPack::drawVCA(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color)
{
    auto iconBounds = bounds;
    auto stroke = getOptimalStrokeWidth(iconBounds);

    // VCA symbol (triangle with control input)
    auto symbolArea = iconBounds.removeFromTop(iconBounds.getHeight() * 0.6f);
    auto centre = symbolArea.getCentre();
    auto triangleSize = juce::jmin(symbolArea.getWidth(), symbolArea.getHeight()) * 0.35f;

    juce::Path triangle;
    triangle.startNewSubPath(centre.x - triangleSize, centre.y - triangleSize * 0.7f);
    triangle.lineTo(centre.x + triangleSize, centre.y);
    triangle.lineTo(centre.x - triangleSize, centre.y + triangleSize * 0.7f);
    triangle.closeSubPath();

    g.setColour(color);
    g.strokePath(triangle, createStroke(stroke));

    // Control voltage input (top)
    g.drawLine(centre.x, centre.y - triangleSize * 0.7f,
              centre.x, centre.y - triangleSize * 1.2f, stroke);

    // Small circle at control input
    auto controlRadius = stroke * 1.5f;
    g.fillEllipse(centre.x - controlRadius, centre.y - triangleSize * 1.2f - controlRadius,
                 controlRadius * 2, controlRadius * 2);

    // Audio input and output
    g.drawLine(centre.x - triangleSize * 1.3f, centre.y,
              centre.x - triangleSize, centre.y, stroke);
    g.drawLine(centre.x + triangleSize, centre.y,
              centre.x + triangleSize * 1.3f, centre.y, stroke);

    // "VCA" label
    auto labelArea = iconBounds.removeFromBottom(iconBounds.getHeight());
    g.setFont(juce::Font(labelArea.getHeight() * 0.7f, juce::Font::bold));
    g.drawText("VCA", labelArea, juce::Justification::centred);
}
