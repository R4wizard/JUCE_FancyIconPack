#include "FancyIconPack.h"

// ============================================================================
// AUDIO-SPECIFIC ICONS IMPLEMENTATION - PART 1
// ============================================================================

// Volume and Gain
// ============================================================================

void FancyIconPack::drawVolume(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color)
{
    auto iconBounds = bounds;
    auto stroke = getOptimalStrokeWidth(iconBounds);

    // Speaker cone
    auto speakerWidth = iconBounds.getWidth() * 0.3f;
    auto speakerHeight = iconBounds.getHeight() * 0.5f;
    auto speakerBounds = juce::Rectangle<float>(iconBounds.getX(),
                                               iconBounds.getCentreY() - speakerHeight * 0.5f,
                                               speakerWidth, speakerHeight);

    g.setColour(color);
    g.fillRoundedRectangle(speakerBounds, 2.0f);

    // Speaker horn/cone extension
    juce::Path horn;
    horn.startNewSubPath(speakerBounds.getRight(), speakerBounds.getY());
    horn.lineTo(speakerBounds.getRight() + speakerWidth * 0.8f, speakerBounds.getY() - speakerHeight * 0.3f);
    horn.lineTo(speakerBounds.getRight() + speakerWidth * 0.8f, speakerBounds.getBottom() + speakerHeight * 0.3f);
    horn.lineTo(speakerBounds.getRight(), speakerBounds.getBottom());
    horn.closeSubPath();

    g.fillPath(horn);

    // Sound waves
    auto waveStart = speakerBounds.getRight() + speakerWidth * 0.9f;
    auto waveCentre = iconBounds.getCentreY();

    for (int i = 0; i < 3; ++i)
    {
        auto waveRadius = (i + 1) * iconBounds.getWidth() * 0.08f;
        auto alpha = 1.0f - (i * 0.25f);

        g.setColour(color.withAlpha(alpha));
        g.drawEllipse(waveStart - waveRadius, waveCentre - waveRadius,
                     waveRadius * 2, waveRadius * 2, stroke * 0.8f);
    }
}

void FancyIconPack::drawGain(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color)
{
    auto iconBounds = bounds;
    auto stroke = getOptimalStrokeWidth(iconBounds);
    auto centre = iconBounds.getCentre();

    // Triangle pointing up (gain/amplification symbol)
    auto triangleSize = juce::jmin(iconBounds.getWidth(), iconBounds.getHeight()) * 0.4f;

    juce::Path triangle;
    triangle.startNewSubPath(centre.x, centre.y - triangleSize); // Top
    triangle.lineTo(centre.x - triangleSize * 0.8f, centre.y + triangleSize * 0.5f); // Bottom left
    triangle.lineTo(centre.x + triangleSize * 0.8f, centre.y + triangleSize * 0.5f); // Bottom right
    triangle.closeSubPath();

    g.setColour(color);
    g.strokePath(triangle, createStroke(stroke));

    // Plus sign inside for amplification
    auto plusSize = triangleSize * 0.3f;
    g.fillRoundedRectangle(centre.x - plusSize * 0.5f, centre.y - stroke * 0.5f,
                          plusSize, stroke, stroke * 0.5f);
    g.fillRoundedRectangle(centre.x - stroke * 0.5f, centre.y - plusSize * 0.5f,
                          stroke, plusSize, stroke * 0.5f);
}

void FancyIconPack::drawPan(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color)
{
    auto iconBounds = bounds;
    auto stroke = getOptimalStrokeWidth(iconBounds);
    auto centre = iconBounds.getCentre();

    // Central circle (pan pot)
    auto potRadius = juce::jmin(iconBounds.getWidth(), iconBounds.getHeight()) * 0.15f;
    g.setColour(color);
    g.fillEllipse(centre.x - potRadius, centre.y - potRadius, potRadius * 2, potRadius * 2);

    // Left and right indicators
    auto indicatorSize = iconBounds.getWidth() * 0.2f;
    auto spacing = iconBounds.getWidth() * 0.35f;

    // Left indicator (L)
    auto leftCentre = centre - juce::Point<float>(spacing, 0);
    g.setColour(color.withAlpha(0.7f));
    g.drawLine(leftCentre.x - indicatorSize * 0.3f, leftCentre.y - indicatorSize * 0.3f,
              leftCentre.x - indicatorSize * 0.3f, leftCentre.y + indicatorSize * 0.3f, stroke);
    g.drawLine(leftCentre.x - indicatorSize * 0.3f, leftCentre.y + indicatorSize * 0.3f,
              leftCentre.x + indicatorSize * 0.1f, leftCentre.y + indicatorSize * 0.3f, stroke);

    // Right indicator (R)
    auto rightCentre = centre + juce::Point<float>(spacing, 0);
    g.drawLine(rightCentre.x - indicatorSize * 0.3f, rightCentre.y - indicatorSize * 0.3f,
              rightCentre.x - indicatorSize * 0.3f, rightCentre.y + indicatorSize * 0.3f, stroke);
    g.drawLine(rightCentre.x - indicatorSize * 0.3f, rightCentre.y - indicatorSize * 0.3f,
              rightCentre.x + indicatorSize * 0.1f, rightCentre.y - indicatorSize * 0.1f, stroke);
    g.drawLine(rightCentre.x - indicatorSize * 0.1f, rightCentre.y,
              rightCentre.x + indicatorSize * 0.1f, rightCentre.y + indicatorSize * 0.3f, stroke);

    // Connection lines
    g.setColour(color.withAlpha(0.5f));
    g.drawLine(leftCentre.x + indicatorSize * 0.2f, leftCentre.y,
              centre.x - potRadius, centre.y, stroke * 0.8f);
    g.drawLine(centre.x + potRadius, centre.y,
              rightCentre.x - indicatorSize * 0.4f, rightCentre.y, stroke * 0.8f);
}

void FancyIconPack::drawMute(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color)
{
    auto iconBounds = bounds;
    auto stroke = getOptimalStrokeWidth(iconBounds);

    // Speaker cone (similar to volume but muted)
    auto speakerWidth = iconBounds.getWidth() * 0.35f;
    auto speakerHeight = iconBounds.getHeight() * 0.5f;
    auto speakerBounds = juce::Rectangle<float>(iconBounds.getX(),
                                               iconBounds.getCentreY() - speakerHeight * 0.5f,
                                               speakerWidth, speakerHeight);

    g.setColour(color.withAlpha(0.6f));
    g.fillRoundedRectangle(speakerBounds, 2.0f);

    // Speaker horn/cone extension
    juce::Path horn;
    horn.startNewSubPath(speakerBounds.getRight(), speakerBounds.getY());
    horn.lineTo(speakerBounds.getRight() + speakerWidth * 0.6f, speakerBounds.getY() - speakerHeight * 0.2f);
    horn.lineTo(speakerBounds.getRight() + speakerWidth * 0.6f, speakerBounds.getBottom() + speakerHeight * 0.2f);
    horn.lineTo(speakerBounds.getRight(), speakerBounds.getBottom());
    horn.closeSubPath();

    g.fillPath(horn);

    // X mark indicating mute
    auto xCentre = iconBounds.getCentre() + juce::Point<float>(iconBounds.getWidth() * 0.2f, 0);
    auto xSize = iconBounds.getWidth() * 0.15f;

    g.setColour(color);
    g.drawLine(xCentre.x - xSize, xCentre.y - xSize, xCentre.x + xSize, xCentre.y + xSize, stroke * 1.5f);
    g.drawLine(xCentre.x - xSize, xCentre.y + xSize, xCentre.x + xSize, xCentre.y - xSize, stroke * 1.5f);
}

void FancyIconPack::drawSolo(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color)
{
    auto iconBounds = bounds;
    auto stroke = getOptimalStrokeWidth(iconBounds);
    auto centre = iconBounds.getCentre();

    // Headphones design
    // Headband
    auto headbandRadius = iconBounds.getWidth() * 0.35f;
    auto headbandThickness = stroke * 2;

    juce::Path headband;
    headband.addCentredArc(centre.x, centre.y, headbandRadius, headbandRadius, 0.0f,
                          juce::MathConstants<float>::pi * 0.2f,
                          juce::MathConstants<float>::pi * 0.8f, true);

    g.setColour(color);
    g.strokePath(headband, createStroke(headbandThickness));

    // Left ear cup
    auto cupSize = iconBounds.getWidth() * 0.15f;
    auto leftCupCentre = centre + juce::Point<float>(-headbandRadius * 0.8f, headbandRadius * 0.3f);
    g.fillRoundedRectangle(leftCupCentre.x - cupSize * 0.5f, leftCupCentre.y - cupSize * 0.5f,
                          cupSize, cupSize, cupSize * 0.3f);

    // Right ear cup
    auto rightCupCentre = centre + juce::Point<float>(headbandRadius * 0.8f, headbandRadius * 0.3f);
    g.fillRoundedRectangle(rightCupCentre.x - cupSize * 0.5f, rightCupCentre.y - cupSize * 0.5f,
                          cupSize, cupSize, cupSize * 0.3f);

    // Solo indicator (small S or dot in center)
    auto indicatorRadius = iconBounds.getWidth() * 0.05f;
    g.fillEllipse(centre.x - indicatorRadius, centre.y - indicatorRadius,
                 indicatorRadius * 2, indicatorRadius * 2);
}

// Metering and Analysis
// ============================================================================

void FancyIconPack::drawMeter(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color)
{
    auto iconBounds = bounds;
    auto stroke = getOptimalStrokeWidth(iconBounds);

    // VU meter background
    g.setColour(color.withAlpha(0.3f));
    g.fillRoundedRectangle(iconBounds, 2.0f);

    g.setColour(color);
    g.drawRoundedRectangle(iconBounds, 2.0f, stroke);

    // Meter bars (level indicators)
    auto barCount = 5;
    auto barSpacing = iconBounds.getWidth() / (barCount + 1);
    auto barWidth = barSpacing * 0.6f;

    for (int i = 0; i < barCount; ++i)
    {
        auto x = iconBounds.getX() + (i + 0.7f) * barSpacing;
        auto barHeight = iconBounds.getHeight() * (0.2f + (i + 1) * 0.12f); // Graduated heights
        auto y = iconBounds.getBottom() - barHeight - iconBounds.getHeight() * 0.1f;

        // Color coding: green -> yellow -> red
        auto alpha = (i < 3) ? 1.0f : 0.7f;
        auto barColor = (i < 2) ? color.withAlpha(alpha) :
                       (i < 4) ? color.withHue(0.15f).withAlpha(alpha) : color.withHue(0.0f).withAlpha(alpha);

        g.setColour(barColor);
        g.fillRoundedRectangle(x, y, barWidth, barHeight, 1.0f);
    }

    // Needle or indicator line
    auto needleX = iconBounds.getX() + iconBounds.getWidth() * 0.6f;
    g.setColour(color);
    g.drawLine(needleX, iconBounds.getY() + iconBounds.getHeight() * 0.2f,
              needleX, iconBounds.getBottom() - iconBounds.getHeight() * 0.2f, stroke * 1.5f);
}

void FancyIconPack::drawPeak(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color)
{
    auto iconBounds = bounds;
    auto stroke = getOptimalStrokeWidth(iconBounds);
    auto centre = iconBounds.getCentre();

    // Mountain peak shape representing peak level
    juce::Path peak;
    peak.startNewSubPath(iconBounds.getX(), iconBounds.getBottom());
    peak.lineTo(centre.x - iconBounds.getWidth() * 0.2f, centre.y);
    peak.lineTo(centre.x, iconBounds.getY() + iconBounds.getHeight() * 0.2f); // Main peak
    peak.lineTo(centre.x + iconBounds.getWidth() * 0.15f, centre.y + iconBounds.getHeight() * 0.1f);
    peak.lineTo(iconBounds.getRight(), iconBounds.getBottom());
    peak.closeSubPath();

    g.setColour(color.withAlpha(0.7f));
    g.fillPath(peak);

    g.setColour(color);
    g.strokePath(peak, createStroke(stroke));

    // Peak indicator dot at the highest point
    auto peakPoint = juce::Point<float>(centre.x, iconBounds.getY() + iconBounds.getHeight() * 0.2f);
    auto dotRadius = stroke * 1.5f;
    g.fillEllipse(peakPoint.x - dotRadius, peakPoint.y - dotRadius, dotRadius * 2, dotRadius * 2);

    // Peak hold line
    auto holdY = iconBounds.getY() + iconBounds.getHeight() * 0.3f;
    g.setColour(color.withAlpha(0.8f));
    g.drawLine(iconBounds.getX() + iconBounds.getWidth() * 0.2f, holdY,
              iconBounds.getRight() - iconBounds.getWidth() * 0.2f, holdY, stroke);
}

void FancyIconPack::drawClip(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color)
{
    auto iconBounds = bounds;
    auto stroke = getOptimalStrokeWidth(iconBounds);

    // Clipped waveform showing hard limiting
    juce::Path waveform;
    auto waveY = iconBounds.getCentreY();
    auto clipLevel = iconBounds.getHeight() * 0.25f;

    // Start from left
    waveform.startNewSubPath(iconBounds.getX(), waveY);

    // Normal wave that gradually clips
    auto points = 8;
    for (int i = 1; i <= points; ++i)
    {
        auto x = iconBounds.getX() + (i / static_cast<float>(points)) * iconBounds.getWidth();
        auto amplitude = (i < points * 0.6f) ?
            std::sin(i * 0.8f) * iconBounds.getHeight() * 0.3f :
            (i % 2 == 0 ? clipLevel : -clipLevel); // Hard clipping at the end

        waveform.lineTo(x, waveY + amplitude);
    }

    g.setColour(color);
    g.strokePath(waveform, createStroke(stroke));

    // Clip warning lines (showing the clipping boundaries)
    g.setColour(color.withHue(0.0f).withAlpha(0.8f)); // Red tint for warning
    g.drawLine(iconBounds.getX(), waveY - clipLevel, iconBounds.getRight(), waveY - clipLevel, stroke * 0.8f);
    g.drawLine(iconBounds.getX(), waveY + clipLevel, iconBounds.getRight(), waveY + clipLevel, stroke * 0.8f);

    // Warning indicator (!)
    auto warningX = iconBounds.getRight() - iconBounds.getWidth() * 0.15f;
    auto warningSize = iconBounds.getHeight() * 0.2f;

    g.setColour(color.withHue(0.0f));
    // Exclamation mark body
    g.fillRoundedRectangle(warningX - stroke * 0.5f, waveY - warningSize * 0.8f,
                          stroke, warningSize * 1.2f, stroke * 0.5f);
    // Exclamation mark dot
    g.fillEllipse(warningX - stroke * 0.8f, waveY + warningSize * 0.7f, stroke * 1.6f, stroke * 1.6f);
}

void FancyIconPack::drawWaveform(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color)
{
    auto iconBounds = bounds;
    auto stroke = getOptimalStrokeWidth(iconBounds);

    // Generic complex waveform
    juce::Path waveform;
    auto waveY = iconBounds.getCentreY();
    auto points = 12;

    waveform.startNewSubPath(iconBounds.getX(), waveY);

    for (int i = 1; i <= points; ++i)
    {
        auto x = iconBounds.getX() + (i / static_cast<float>(points)) * iconBounds.getWidth();
        // Complex waveform with harmonics
        auto amplitude = (std::sin(i * 0.6f) + std::sin(i * 1.2f) * 0.5f + std::sin(i * 2.4f) * 0.25f)
                        * iconBounds.getHeight() * 0.25f;
        waveform.lineTo(x, waveY + amplitude);
    }

    g.setColour(color);
    g.strokePath(waveform, createStroke(stroke));

    // Center line reference
    g.setColour(color.withAlpha(0.3f));
    g.drawLine(iconBounds.getX(), waveY, iconBounds.getRight(), waveY, stroke * 0.5f);
}

void FancyIconPack::drawSpectrum(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color)
{
    auto iconBounds = bounds;
    auto stroke = getOptimalStrokeWidth(iconBounds);

    // Spectrum analyzer bars
    auto barCount = 8;
    auto barSpacing = iconBounds.getWidth() / barCount;
    auto barWidth = barSpacing * 0.7f;

    for (int i = 0; i < barCount; ++i)
    {
        auto x = iconBounds.getX() + i * barSpacing + (barSpacing - barWidth) * 0.5f;
        // Simulate frequency spectrum heights (more energy in lower frequencies)
        auto heightRatio = (barCount - i) * 0.1f + 0.2f + std::sin(i * 0.5f) * 0.3f;
        heightRatio = juce::jlimit(0.2f, 0.9f, heightRatio);
        auto barHeight = iconBounds.getHeight() * heightRatio;
        auto y = iconBounds.getBottom() - barHeight;

        // Color gradient from green (low freq) to red (high freq)
        auto hue = (1.0f - i / static_cast<float>(barCount - 1)) * 0.3f; // Green to red
        auto barColor = color.withHue(hue);

        g.setColour(barColor);
        g.fillRoundedRectangle(x, y, barWidth, barHeight, 1.0f);
    }

    // Base line
    g.setColour(color.withAlpha(0.5f));
    g.drawLine(iconBounds.getX(), iconBounds.getBottom(), iconBounds.getRight(), iconBounds.getBottom(), stroke);
}

// Waveform Types
// ============================================================================

void FancyIconPack::drawSineWave(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color)
{
    auto iconBounds = bounds;
    auto stroke = getOptimalStrokeWidth(iconBounds);

    // Perfect sine wave
    juce::Path sineWave;
    auto waveY = iconBounds.getCentreY();
    auto points = 20;

    sineWave.startNewSubPath(iconBounds.getX(), waveY);

    for (int i = 1; i <= points; ++i)
    {
        auto x = iconBounds.getX() + (i / static_cast<float>(points)) * iconBounds.getWidth();
        auto phase = (i / static_cast<float>(points)) * juce::MathConstants<float>::twoPi * 2.0f;
        auto amplitude = std::sin(phase) * iconBounds.getHeight() * 0.35f;
        sineWave.lineTo(x, waveY + amplitude);
    }

    g.setColour(color);
    g.strokePath(sineWave, createStroke(stroke));

    // Center line reference
    g.setColour(color.withAlpha(0.3f));
    g.drawLine(iconBounds.getX(), waveY, iconBounds.getRight(), waveY, stroke * 0.5f);
}

void FancyIconPack::drawSquareWave(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color)
{
    auto iconBounds = bounds;
    auto stroke = getOptimalStrokeWidth(iconBounds);

    // Square wave with sharp transitions
    juce::Path squareWave;
    auto waveY = iconBounds.getCentreY();
    auto amplitude = iconBounds.getHeight() * 0.35f;
    auto cycleWidth = iconBounds.getWidth() / 3.0f; // 3 cycles

    squareWave.startNewSubPath(iconBounds.getX(), waveY + amplitude);

    for (int i = 0; i < 3; ++i)
    {
        auto cycleStart = iconBounds.getX() + i * cycleWidth;
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

    // Center line reference
    g.setColour(color.withAlpha(0.3f));
    g.drawLine(iconBounds.getX(), waveY, iconBounds.getRight(), waveY, stroke * 0.5f);
}

void FancyIconPack::drawTriangleWave(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color)
{
    auto iconBounds = bounds;
    auto stroke = getOptimalStrokeWidth(iconBounds);

    // Triangle wave with linear transitions
    juce::Path triangleWave;
    auto waveY = iconBounds.getCentreY();
    auto amplitude = iconBounds.getHeight() * 0.35f;
    auto cycleWidth = iconBounds.getWidth() / 2.5f; // 2.5 cycles

    triangleWave.startNewSubPath(iconBounds.getX(), waveY);

    for (int i = 0; i < 3; ++i)
    {
        auto cycleStart = iconBounds.getX() + i * cycleWidth;
        auto quarterCycle = cycleWidth * 0.25f;

        // Up slope
        triangleWave.lineTo(cycleStart + quarterCycle, waveY - amplitude);
        // Down slope
        triangleWave.lineTo(cycleStart + quarterCycle * 3, waveY + amplitude);
        // Back to center
        triangleWave.lineTo(cycleStart + cycleWidth, waveY);
    }

    g.setColour(color);
    g.strokePath(triangleWave, createStroke(stroke, juce::PathStrokeType::mitered));

    // Center line reference
    g.setColour(color.withAlpha(0.3f));
    g.drawLine(iconBounds.getX(), waveY, iconBounds.getRight(), waveY, stroke * 0.5f);
}

void FancyIconPack::drawSawWave(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color)
{
    auto iconBounds = bounds;
    auto stroke = getOptimalStrokeWidth(iconBounds);

    // Sawtooth wave with sharp drops
    juce::Path sawWave;
    auto waveY = iconBounds.getCentreY();
    auto amplitude = iconBounds.getHeight() * 0.35f;
    auto cycleWidth = iconBounds.getWidth() / 3.0f; // 3 cycles

    sawWave.startNewSubPath(iconBounds.getX(), waveY + amplitude);

    for (int i = 0; i < 3; ++i)
    {
        auto cycleStart = iconBounds.getX() + i * cycleWidth;

        // Linear ramp up
        sawWave.lineTo(cycleStart + cycleWidth, waveY - amplitude);
        // Sharp drop down
        sawWave.lineTo(cycleStart + cycleWidth, waveY + amplitude);
    }

    g.setColour(color);
    g.strokePath(sawWave, createStroke(stroke, juce::PathStrokeType::mitered, juce::PathStrokeType::butt));

    // Center line reference
    g.setColour(color.withAlpha(0.3f));
    g.drawLine(iconBounds.getX(), waveY, iconBounds.getRight(), waveY, stroke * 0.5f);
}

void FancyIconPack::drawNoise(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color)
{
    auto iconBounds = bounds;
    auto stroke = getOptimalStrokeWidth(iconBounds);

    // Random noise pattern
    juce::Path noisePath;
    auto waveY = iconBounds.getCentreY();
    auto points = 25;

    juce::Random random(42); // Fixed seed for consistent appearance
    noisePath.startNewSubPath(iconBounds.getX(), waveY);

    for (int i = 1; i <= points; ++i)
    {
        auto x = iconBounds.getX() + (i / static_cast<float>(points)) * iconBounds.getWidth();
        auto amplitude = (random.nextFloat() - 0.5f) * iconBounds.getHeight() * 0.6f;
        noisePath.lineTo(x, waveY + amplitude);
    }

    g.setColour(color);
    g.strokePath(noisePath, createStroke(stroke * 0.8f));

    // Center line reference
    g.setColour(color.withAlpha(0.3f));
    g.drawLine(iconBounds.getX(), waveY, iconBounds.getRight(), waveY, stroke * 0.5f);
}

// Phase and Signal Processing
// ============================================================================

void FancyIconPack::drawPhase(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color)
{
    auto iconBounds = bounds;
    auto stroke = getOptimalStrokeWidth(iconBounds);
    auto centre = iconBounds.getCentre();

    // Two sine waves with phase relationship
    juce::Path wave1, wave2;
    auto waveY = iconBounds.getCentreY();
    auto amplitude = iconBounds.getHeight() * 0.25f;
    auto points = 16;

    // First wave (reference)
    wave1.startNewSubPath(iconBounds.getX(), waveY);
    // Second wave (phase shifted)
    wave2.startNewSubPath(iconBounds.getX(), waveY + amplitude * 0.5f);

    for (int i = 1; i <= points; ++i)
    {
        auto x = iconBounds.getX() + (i / static_cast<float>(points)) * iconBounds.getWidth();
        auto phase = (i / static_cast<float>(points)) * juce::MathConstants<float>::twoPi * 2.0f;

        // Reference wave
        auto amp1 = std::sin(phase) * amplitude;
        wave1.lineTo(x, waveY + amp1);

        // Phase shifted wave (90 degrees)
        auto amp2 = std::sin(phase + juce::MathConstants<float>::halfPi) * amplitude * 0.7f;
        wave2.lineTo(x, waveY + amp2);
    }

    // Draw both waves with different alphas
    g.setColour(color);
    g.strokePath(wave1, createStroke(stroke));

    g.setColour(color.withAlpha(0.6f));
    g.strokePath(wave2, createStroke(stroke));

    // Phase indicator arrow
    auto arrowX = iconBounds.getX() + iconBounds.getWidth() * 0.7f;
    g.setColour(color.withAlpha(0.8f));
    g.drawLine(arrowX, waveY - amplitude * 0.8f, arrowX + amplitude * 0.3f, waveY - amplitude * 0.5f, stroke);
    g.drawLine(arrowX + amplitude * 0.3f, waveY - amplitude * 0.5f, arrowX, waveY - amplitude * 0.2f, stroke);
}

void FancyIconPack::drawInvertPhase(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color)
{
    auto iconBounds = bounds;
    auto stroke = getOptimalStrokeWidth(iconBounds);

    // Original and inverted waveforms
    juce::Path originalWave, invertedWave;
    auto waveY = iconBounds.getCentreY();
    auto amplitude = iconBounds.getHeight() * 0.25f;
    auto points = 12;

    originalWave.startNewSubPath(iconBounds.getX(), waveY);
    invertedWave.startNewSubPath(iconBounds.getX(), waveY);

    for (int i = 1; i <= points; ++i)
    {
        auto x = iconBounds.getX() + (i / static_cast<float>(points)) * iconBounds.getWidth();
        auto phase = (i / static_cast<float>(points)) * juce::MathConstants<float>::twoPi * 1.5f;
        auto amp = std::sin(phase) * amplitude;

        originalWave.lineTo(x, waveY + amp);
        invertedWave.lineTo(x, waveY - amp); // Inverted
    }

    // Draw original wave
    g.setColour(color.withAlpha(0.6f));
    g.strokePath(originalWave, createStroke(stroke * 0.8f));

    // Draw inverted wave
    g.setColour(color);
    g.strokePath(invertedWave, createStroke(stroke));

    // Center line
    g.setColour(color.withAlpha(0.3f));
    g.drawLine(iconBounds.getX(), waveY, iconBounds.getRight(), waveY, stroke * 0.5f);

    // Inversion symbol (phi or ~ with minus)
    auto symbolCentre = iconBounds.getTopRight() + juce::Point<float>(-iconBounds.getWidth() * 0.15f, iconBounds.getHeight() * 0.15f);
    auto symbolSize = iconBounds.getWidth() * 0.08f;

    g.setColour(color);
    // Minus sign
    g.fillRoundedRectangle(symbolCentre.x - symbolSize, symbolCentre.y - stroke * 0.5f,
                          symbolSize * 2, stroke, stroke * 0.5f);
}

void FancyIconPack::drawFrequency(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color)
{
    auto iconBounds = bounds;
    auto stroke = getOptimalStrokeWidth(iconBounds);

    // Frequency response curve with characteristic peaks and valleys
    juce::Path frequencyResponse;
    auto startX = iconBounds.getX();
    auto endX = iconBounds.getRight();
    auto centerY = iconBounds.getCentreY();
    auto amplitude = iconBounds.getHeight() * 0.3f;

    g.setColour(color);

    // Create a typical frequency response curve
    auto sampleCount = 64;
    auto sampleWidth = iconBounds.getWidth() / static_cast<float>(sampleCount);

    for (int i = 0; i <= sampleCount; ++i)
    {
        auto x = startX + i * sampleWidth;
        auto normalizedX = i / static_cast<float>(sampleCount);

        // Simulate typical audio frequency response with some resonant peaks
        auto response = 0.0f;

        // Low frequency rolloff
        if (normalizedX < 0.1f)
            response = normalizedX * 10.0f;
        else if (normalizedX < 0.8f)
        {
            // Mid-range with some peaks
            response = 1.0f + 0.3f * std::sin(normalizedX * juce::MathConstants<float>::pi * 6) *
                              std::exp(-normalizedX * 2);
        }
        else
        {
            // High frequency rolloff
            response = std::exp(-(normalizedX - 0.8f) * 15);
        }

        auto y = centerY - response * amplitude;

        if (i == 0)
            frequencyResponse.startNewSubPath(x, y);
        else
            frequencyResponse.lineTo(x, y);
    }

    g.strokePath(frequencyResponse, createStroke(stroke * 1.2f));

    // Frequency axis labels (low, mid, high indicators)
    g.setColour(color.withAlpha(0.6f));
    auto labelY = iconBounds.getBottom() - stroke;

    // Low frequency marker
    g.drawLine(startX + iconBounds.getWidth() * 0.1f, labelY - stroke,
              startX + iconBounds.getWidth() * 0.1f, labelY + stroke, stroke * 0.6f);

    // Mid frequency marker
    g.drawLine(startX + iconBounds.getWidth() * 0.5f, labelY - stroke,
              startX + iconBounds.getWidth() * 0.5f, labelY + stroke, stroke * 0.6f);

    // High frequency marker
    g.drawLine(startX + iconBounds.getWidth() * 0.9f, labelY - stroke,
              startX + iconBounds.getWidth() * 0.9f, labelY + stroke, stroke * 0.6f);

    // Amplitude axis
    g.drawLine(startX, iconBounds.getY(), startX, iconBounds.getBottom(), stroke * 0.5f);
    g.drawLine(startX, iconBounds.getBottom(), endX, iconBounds.getBottom(), stroke * 0.5f);

    // dB markers on amplitude axis
    auto markerCount = 3;
    for (int i = 1; i <= markerCount; ++i)
    {
        auto y = iconBounds.getY() + (iconBounds.getHeight() / (markerCount + 1)) * i;
        g.drawLine(startX - stroke, y, startX + stroke, y, stroke * 0.4f);
    }
}

void FancyIconPack::drawResonance(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color)
{
    auto iconBounds = bounds;
    auto stroke = getOptimalStrokeWidth(iconBounds);

    // Resonant peak in frequency response
    auto centerX = iconBounds.getCentreX();
    auto centerY = iconBounds.getCentreY();
    auto peakHeight = iconBounds.getHeight() * 0.4f;
    auto peakWidth = iconBounds.getWidth() * 0.3f;

    g.setColour(color);

    // Main frequency response curve with prominent resonant peak
    juce::Path resonanceCurve;
    auto startX = iconBounds.getX();
    auto endX = iconBounds.getRight();
    auto baselineY = iconBounds.getBottom() - iconBounds.getHeight() * 0.2f;

    auto sampleCount = 48;
    auto sampleWidth = iconBounds.getWidth() / static_cast<float>(sampleCount);

    for (int i = 0; i <= sampleCount; ++i)
    {
        auto x = startX + i * sampleWidth;
        auto normalizedX = i / static_cast<float>(sampleCount);

        // Create sharp resonant peak at center
        auto distanceFromCenter = std::abs(normalizedX - 0.5f) * 2.0f; // 0 at center, 1 at edges
        auto resonanceResponse = std::exp(-distanceFromCenter * distanceFromCenter * 25.0f); // Sharp Gaussian peak

        // Base response level
        auto baseResponse = 0.1f + 0.1f * std::sin(normalizedX * juce::MathConstants<float>::pi * 2);

        auto totalResponse = baseResponse + resonanceResponse;
        auto y = baselineY - totalResponse * peakHeight;

        if (i == 0)
            resonanceCurve.startNewSubPath(x, y);
        else
            resonanceCurve.lineTo(x, y);
    }

    g.strokePath(resonanceCurve, createStroke(stroke * 1.3f));

    // Highlight the resonant peak area
    g.setColour(color.brighter(0.3f).withAlpha(0.4f));
    juce::Path peakArea;
    peakArea.startNewSubPath(centerX - peakWidth * 0.5f, baselineY);

    // Create filled area under the peak
    auto peakSamples = 16;
    for (int i = 0; i <= peakSamples; ++i)
    {
        auto t = i / static_cast<float>(peakSamples);
        auto x = centerX - peakWidth * 0.5f + t * peakWidth;
        auto distanceFromCenter = std::abs(t - 0.5f) * 2.0f;
        auto response = std::exp(-distanceFromCenter * distanceFromCenter * 25.0f);
        auto y = baselineY - response * peakHeight;

        peakArea.lineTo(x, y);
    }

    peakArea.lineTo(centerX + peakWidth * 0.5f, baselineY);
    peakArea.closeSubPath();
    g.fillPath(peakArea);

    // Peak frequency indicator line
    g.setColour(color.brighter(0.4f));
    g.drawLine(centerX, baselineY, centerX, baselineY - peakHeight * 1.1f, stroke);

    // Resonance Q factor indicators (bandwidth markers)
    g.setColour(color.withAlpha(0.7f));
    auto qWidth = peakWidth * 0.7f; // Q factor width
    auto qHeight = peakHeight * 0.707f; // -3dB point
    auto qY = baselineY - qHeight;

    // Left Q marker
    g.drawLine(centerX - qWidth * 0.5f, qY - stroke, centerX - qWidth * 0.5f, qY + stroke, stroke * 0.8f);
    // Right Q marker
    g.drawLine(centerX + qWidth * 0.5f, qY - stroke, centerX + qWidth * 0.5f, qY + stroke, stroke * 0.8f);

    // Q factor line (showing bandwidth)
    g.drawLine(centerX - qWidth * 0.5f, qY, centerX + qWidth * 0.5f, qY, stroke * 0.6f);

    // Axes
    g.setColour(color.withAlpha(0.5f));
    g.drawLine(startX, baselineY, endX, baselineY, stroke * 0.5f); // Frequency axis
    g.drawLine(startX, iconBounds.getY(), startX, iconBounds.getBottom(), stroke * 0.5f); // Amplitude axis

    // Peak amplitude label/indicator
    g.setColour(color.brighter(0.5f));
    auto labelRadius = stroke * 0.6f;
    auto labelX = centerX + peakWidth * 0.3f;
    auto labelY = baselineY - peakHeight * 0.8f;
    g.fillEllipse(labelX - labelRadius, labelY - labelRadius, labelRadius * 2, labelRadius * 2);
}

void FancyIconPack::drawBandwidth(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color)
{
    auto iconBounds = bounds;
    auto stroke = getOptimalStrokeWidth(iconBounds);

    // Frequency band visualization with bandwidth indicators
    auto centerX = iconBounds.getCentreX();
    auto centerY = iconBounds.getCentreY();
    auto bandHeight = iconBounds.getHeight() * 0.6f;
    auto bandTop = iconBounds.getY() + iconBounds.getHeight() * 0.2f;
    auto baselineY = bandTop + bandHeight;

    g.setColour(color);

    // Main frequency response showing bandwidth
    juce::Path bandResponse;
    auto startX = iconBounds.getX();
    auto endX = iconBounds.getRight();

    // Create a band-pass response curve
    auto sampleCount = 48;
    auto sampleWidth = iconBounds.getWidth() / static_cast<float>(sampleCount);

    // Bandwidth parameters
    auto centerFreq = 0.5f; // Normalized center frequency
    auto bandwidth = 0.3f; // Normalized bandwidth
    auto lowCutoff = centerFreq - bandwidth * 0.5f;
    auto highCutoff = centerFreq + bandwidth * 0.5f;

    for (int i = 0; i <= sampleCount; ++i)
    {
        auto x = startX + i * sampleWidth;
        auto normalizedX = i / static_cast<float>(sampleCount);

        auto response = 0.0f;

        if (normalizedX >= lowCutoff && normalizedX <= highCutoff)
        {
            // Within the passband
            response = 1.0f;
        }
        else if (normalizedX < lowCutoff)
        {
            // Low frequency rolloff
            auto distance = (lowCutoff - normalizedX) / lowCutoff;
            response = std::exp(-distance * distance * 8.0f);
        }
        else
        {
            // High frequency rolloff
            auto distance = (normalizedX - highCutoff) / (1.0f - highCutoff);
            response = std::exp(-distance * distance * 8.0f);
        }

        auto y = baselineY - response * bandHeight;

        if (i == 0)
            bandResponse.startNewSubPath(x, y);
        else
            bandResponse.lineTo(x, y);
    }

    g.strokePath(bandResponse, createStroke(stroke * 1.2f));

    // Highlight the passband area
    g.setColour(color.withAlpha(0.3f));
    auto passbandLeft = startX + lowCutoff * iconBounds.getWidth();
    auto passbandRight = startX + highCutoff * iconBounds.getWidth();
    auto passbandWidth = passbandRight - passbandLeft;

    g.fillRoundedRectangle(passbandLeft, bandTop, passbandWidth, bandHeight, stroke);

    // Bandwidth indicators
    g.setColour(color.brighter(0.4f));

    // Left cutoff frequency marker
    g.drawLine(passbandLeft, bandTop - stroke * 2, passbandLeft, baselineY + stroke * 2, stroke);

    // Right cutoff frequency marker
    g.drawLine(passbandRight, bandTop - stroke * 2, passbandRight, baselineY + stroke * 2, stroke);

    // Center frequency marker
    g.setColour(color.brighter(0.2f));
    g.drawLine(centerX, bandTop - stroke, centerX, baselineY + stroke, stroke * 0.8f);

    // Bandwidth measurement line
    g.setColour(color.brighter(0.5f));
    auto measureY = bandTop - stroke * 3;
    g.drawLine(passbandLeft, measureY, passbandRight, measureY, stroke * 0.8f);

    // Bandwidth arrows
    auto arrowSize = stroke * 1.5f;

    // Left arrow
    juce::Path leftArrow;
    leftArrow.startNewSubPath(passbandLeft, measureY);
    leftArrow.lineTo(passbandLeft + arrowSize, measureY - arrowSize * 0.5f);
    leftArrow.lineTo(passbandLeft + arrowSize, measureY + arrowSize * 0.5f);
    leftArrow.closeSubPath();
    g.fillPath(leftArrow);

    // Right arrow
    juce::Path rightArrow;
    rightArrow.startNewSubPath(passbandRight, measureY);
    rightArrow.lineTo(passbandRight - arrowSize, measureY - arrowSize * 0.5f);
    rightArrow.lineTo(passbandRight - arrowSize, measureY + arrowSize * 0.5f);
    rightArrow.closeSubPath();
    g.fillPath(rightArrow);

    // -3dB indicators at cutoff points
    g.setColour(color.withAlpha(0.7f));
    auto cutoffLevel = baselineY - bandHeight * 0.707f; // -3dB point

    // Left -3dB point
    auto leftDotRadius = stroke * 0.6f;
    g.fillEllipse(passbandLeft - leftDotRadius, cutoffLevel - leftDotRadius,
                  leftDotRadius * 2, leftDotRadius * 2);

    // Right -3dB point
    auto rightDotRadius = stroke * 0.6f;
    g.fillEllipse(passbandRight - rightDotRadius, cutoffLevel - rightDotRadius,
                  rightDotRadius * 2, rightDotRadius * 2);

    // Axes
    g.setColour(color.withAlpha(0.4f));
    g.drawLine(startX, baselineY, endX, baselineY, stroke * 0.5f); // Frequency axis
    g.drawLine(startX, bandTop, startX, baselineY, stroke * 0.5f); // Amplitude axis
}

// Filters and EQ (Part 1)
// ============================================================================

void FancyIconPack::drawEQ(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color)
{
    auto iconBounds = bounds;
    auto stroke = getOptimalStrokeWidth(iconBounds);

    // Multi-band EQ with sliders/curve representation
    g.setColour(color);

    // EQ bands (typically 3-5 bands for visualization)
    auto bandCount = 4;
    auto bandWidth = iconBounds.getWidth() / static_cast<float>(bandCount);
    auto maxSliderHeight = iconBounds.getHeight() * 0.6f;
    auto sliderWidth = bandWidth * 0.3f;
    auto centerY = iconBounds.getCentreY();

    // Band gains (simulating different EQ settings)
    juce::Array<float> bandGains = {0.2f, -0.3f, 0.6f, -0.1f}; // Normalized gains (-1 to 1)

    // Draw EQ sliders
    for (int i = 0; i < bandCount; ++i)
    {
        auto bandX = iconBounds.getX() + (i + 0.5f) * bandWidth;
        auto sliderCenterX = bandX;

        // Slider track
        g.setColour(color.withAlpha(0.4f));
        g.fillRoundedRectangle(sliderCenterX - sliderWidth * 0.5f,
                              centerY - maxSliderHeight * 0.5f,
                              sliderWidth, maxSliderHeight, stroke * 0.5f);

        // Center line (0 dB)
        g.setColour(color.withAlpha(0.6f));
        g.drawLine(sliderCenterX - sliderWidth * 0.6f, centerY,
                  sliderCenterX + sliderWidth * 0.6f, centerY, stroke * 0.5f);

        // Slider handle
        auto handleY = centerY - bandGains[i] * maxSliderHeight * 0.4f;
        auto handleHeight = stroke * 2;
        auto handleWidth = sliderWidth * 0.8f;

        g.setColour(color);
        g.fillRoundedRectangle(sliderCenterX - handleWidth * 0.5f,
                              handleY - handleHeight * 0.5f,
                              handleWidth, handleHeight, stroke * 0.5f);

        // Handle highlight
        g.setColour(color.brighter(0.3f));
        g.drawRoundedRectangle(sliderCenterX - handleWidth * 0.5f,
                              handleY - handleHeight * 0.5f,
                              handleWidth, handleHeight, stroke * 0.5f, stroke * 0.5f);
    }

    // EQ frequency response curve
    g.setColour(color.brighter(0.2f));
    juce::Path eqCurve;
    auto curveTop = iconBounds.getY() + iconBounds.getHeight() * 0.1f;
    auto curveHeight = iconBounds.getHeight() * 0.25f;

    auto sampleCount = 64;
    auto sampleWidth = iconBounds.getWidth() / static_cast<float>(sampleCount);

    for (int i = 0; i <= sampleCount; ++i)
    {
        auto x = iconBounds.getX() + i * sampleWidth;
        auto normalizedX = i / static_cast<float>(sampleCount);

        // Calculate EQ response based on band settings
        auto response = 0.0f;

        for (int band = 0; band < bandCount; ++band)
        {
            auto bandCenter = (band + 0.5f) / bandCount;
            auto bandWidth_norm = 0.2f; // Bandwidth for each band
            auto distance = std::abs(normalizedX - bandCenter) / bandWidth_norm;
            auto bandResponse = std::exp(-distance * distance * 2.0f) * bandGains[band];
            response += bandResponse;
        }

        auto y = curveTop + curveHeight * 0.5f - response * curveHeight * 0.4f;

        if (i == 0)
            eqCurve.startNewSubPath(x, y);
        else
            eqCurve.lineTo(x, y);
    }

    g.strokePath(eqCurve, createStroke(stroke * 1.5f));

    // Frequency labels/markers
    g.setColour(color.withAlpha(0.5f));
    auto labelY = iconBounds.getBottom() - stroke;

    for (int i = 0; i < bandCount; ++i)
    {
        auto bandX = iconBounds.getX() + (i + 0.5f) * bandWidth;
        g.drawLine(bandX, labelY - stroke * 0.5f, bandX, labelY + stroke * 0.5f, stroke * 0.4f);
    }

    // Frequency axis
    g.drawLine(iconBounds.getX(), labelY, iconBounds.getRight(), labelY, stroke * 0.4f);

    // EQ type indicators (Low, Mid, High)
    g.setColour(color.withAlpha(0.7f));
    auto indicatorSize = stroke * 0.8f;

    // Low frequency indicator (bass)
    auto lowX = iconBounds.getX() + bandWidth * 0.5f;
    auto lowY = iconBounds.getY() + stroke * 2;
    g.fillEllipse(lowX - indicatorSize, lowY - indicatorSize, indicatorSize * 2, indicatorSize * 2);

    // High frequency indicator (treble)
    auto highX = iconBounds.getX() + bandWidth * (bandCount - 0.5f);
    auto highY = iconBounds.getY() + stroke * 2;
    auto triangleSize = indicatorSize * 1.2f;
    juce::Path triangle;
    triangle.startNewSubPath(highX, highY - triangleSize);
    triangle.lineTo(highX - triangleSize, highY + triangleSize);
    triangle.lineTo(highX + triangleSize, highY + triangleSize);
    triangle.closeSubPath();
    g.fillPath(triangle);
}

void FancyIconPack::drawFilter(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color)
{
    auto iconBounds = bounds;
    auto stroke = getOptimalStrokeWidth(iconBounds);

    // Generic filter frequency response curve
    juce::Path filterCurve;
    auto baseY = iconBounds.getBottom() - iconBounds.getHeight() * 0.2f;
    auto points = 15;

    filterCurve.startNewSubPath(iconBounds.getX(), baseY);

    for (int i = 1; i <= points; ++i)
    {
        auto x = iconBounds.getX() + (i / static_cast<float>(points)) * iconBounds.getWidth();
        auto ratio = i / static_cast<float>(points);

        // Generic filter response (with some resonance peak)
        auto response = 1.0f;
        if (ratio < 0.4f) response = 1.0f; // Passband
        else if (ratio < 0.6f) response = 1.0f + (ratio - 0.4f) * 2.0f; // Resonance peak
        else response = std::exp(-(ratio - 0.6f) * 8.0f); // Rolloff

        auto y = baseY - response * iconBounds.getHeight() * 0.6f;
        filterCurve.lineTo(x, y);
    }

    g.setColour(color);
    g.strokePath(filterCurve, createStroke(stroke));

    // Frequency axis
    g.setColour(color.withAlpha(0.4f));
    g.drawLine(iconBounds.getX(), baseY, iconBounds.getRight(), baseY, stroke * 0.6f);

    // Filter symbol (triangle)
    auto symbolCentre = iconBounds.getBottomLeft() + juce::Point<float>(iconBounds.getWidth() * 0.8f, -iconBounds.getHeight() * 0.15f);
    auto triangleSize = iconBounds.getWidth() * 0.08f;

    juce::Path triangle;
    triangle.startNewSubPath(symbolCentre.x, symbolCentre.y - triangleSize);
    triangle.lineTo(symbolCentre.x - triangleSize * 0.8f, symbolCentre.y + triangleSize * 0.5f);
    triangle.lineTo(symbolCentre.x + triangleSize * 0.8f, symbolCentre.y + triangleSize * 0.5f);
    triangle.closeSubPath();

    g.setColour(color);
    g.fillPath(triangle);
}

void FancyIconPack::drawLowpass(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color)
{
    auto iconBounds = bounds;
    auto stroke = getOptimalStrokeWidth(iconBounds);

    // Low-pass filter frequency response
    juce::Path lpfCurve;
    auto baseY = iconBounds.getBottom() - iconBounds.getHeight() * 0.2f;
    auto points = 15;

    lpfCurve.startNewSubPath(iconBounds.getX(), baseY - iconBounds.getHeight() * 0.5f);

    for (int i = 1; i <= points; ++i)
    {
        auto x = iconBounds.getX() + (i / static_cast<float>(points)) * iconBounds.getWidth();
        auto ratio = i / static_cast<float>(points);

        // Low-pass response: flat then rolls off
        auto response = (ratio < 0.5f) ? 1.0f : std::exp(-(ratio - 0.5f) * 6.0f);
        auto y = baseY - response * iconBounds.getHeight() * 0.5f;
        lpfCurve.lineTo(x, y);
    }

    g.setColour(color);
    g.strokePath(lpfCurve, createStroke(stroke));

    // Frequency axis
    g.setColour(color.withAlpha(0.4f));
    g.drawLine(iconBounds.getX(), baseY, iconBounds.getRight(), baseY, stroke * 0.6f);

    // Low frequency indicator (L)
    auto labelX = iconBounds.getX() + iconBounds.getWidth() * 0.2f;
    auto labelY = iconBounds.getY() + iconBounds.getHeight() * 0.3f;
    auto labelSize = iconBounds.getWidth() * 0.15f;

    g.setColour(color.withAlpha(0.8f));
    g.drawLine(labelX, labelY, labelX, labelY + labelSize, stroke);
    g.drawLine(labelX, labelY + labelSize, labelX + labelSize * 0.6f, labelY + labelSize, stroke);
}

void FancyIconPack::drawHighpass(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color)
{
    auto iconBounds = bounds;
    auto stroke = getOptimalStrokeWidth(iconBounds);

    // High-pass filter frequency response
    juce::Path hpfCurve;
    auto baseY = iconBounds.getBottom() - iconBounds.getHeight() * 0.2f;
    auto points = 15;

    hpfCurve.startNewSubPath(iconBounds.getX(), baseY);

    for (int i = 1; i <= points; ++i)
    {
        auto x = iconBounds.getX() + (i / static_cast<float>(points)) * iconBounds.getWidth();
        auto ratio = i / static_cast<float>(points);

        // High-pass response: rolls off then flat
        auto response = (ratio > 0.5f) ? 1.0f : std::exp(-(0.5f - ratio) * 6.0f);
        auto y = baseY - response * iconBounds.getHeight() * 0.5f;
        hpfCurve.lineTo(x, y);
    }

    g.setColour(color);
    g.strokePath(hpfCurve, createStroke(stroke));

    // Frequency axis
    g.setColour(color.withAlpha(0.4f));
    g.drawLine(iconBounds.getX(), baseY, iconBounds.getRight(), baseY, stroke * 0.6f);

    // High frequency indicator (H)
    auto labelX = iconBounds.getX() + iconBounds.getWidth() * 0.7f;
    auto labelY = iconBounds.getY() + iconBounds.getHeight() * 0.3f;
    auto labelSize = iconBounds.getWidth() * 0.15f;

    g.setColour(color.withAlpha(0.8f));
    // H shape
    g.drawLine(labelX, labelY, labelX, labelY + labelSize, stroke);
    g.drawLine(labelX + labelSize * 0.6f, labelY, labelX + labelSize * 0.6f, labelY + labelSize, stroke);
    g.drawLine(labelX, labelY + labelSize * 0.5f, labelX + labelSize * 0.6f, labelY + labelSize * 0.5f, stroke);
}

void FancyIconPack::drawBandpass(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color)
{
    auto iconBounds = bounds;
    auto stroke = getOptimalStrokeWidth(iconBounds);

    // Band-pass filter frequency response
    juce::Path bpfCurve;
    auto baseY = iconBounds.getBottom() - iconBounds.getHeight() * 0.2f;
    auto points = 15;

    bpfCurve.startNewSubPath(iconBounds.getX(), baseY);

    for (int i = 1; i <= points; ++i)
    {
        auto x = iconBounds.getX() + (i / static_cast<float>(points)) * iconBounds.getWidth();
        auto ratio = i / static_cast<float>(points);

        // Band-pass response: bell curve centered at 0.5
        auto centerDistance = std::abs(ratio - 0.5f);
        auto response = std::exp(-centerDistance * centerDistance * 25.0f);
        auto y = baseY - response * iconBounds.getHeight() * 0.6f;
        bpfCurve.lineTo(x, y);
    }

    g.setColour(color);
    g.strokePath(bpfCurve, createStroke(stroke));

    // Frequency axis
    g.setColour(color.withAlpha(0.4f));
    g.drawLine(iconBounds.getX(), baseY, iconBounds.getRight(), baseY, stroke * 0.6f);

    // Band indicators (vertical lines showing pass band)
    auto bandStart = iconBounds.getX() + iconBounds.getWidth() * 0.35f;
    auto bandEnd = iconBounds.getX() + iconBounds.getWidth() * 0.65f;

    g.setColour(color.withAlpha(0.6f));
    g.drawLine(bandStart, baseY - iconBounds.getHeight() * 0.1f, bandStart, baseY - iconBounds.getHeight() * 0.4f, stroke * 0.8f);
    g.drawLine(bandEnd, baseY - iconBounds.getHeight() * 0.1f, bandEnd, baseY - iconBounds.getHeight() * 0.4f, stroke * 0.8f);
}
